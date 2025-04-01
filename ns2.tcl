#create simulator object
set ns [new Simulator]
#open xgraph in write mode
set nr [open thro.tr w]
$ns trace-all $nr
#open the nam file in write mode
set nf [open thro.nam w]


$ns namtrace-all $nf
#define a finish procedure
proc finish { } {
global ns nr nf
$ns flush-trace
#close the nam trace file
close $nf
close $nr
exec nam thro.nam &
exit 0
}
#Creation of Nodes:
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]


#Creation of Links:
$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail


set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set ftp [new Application/FTP]
$ftp set packetSize_ 500
$ftp set interval_ 0.005
$ftp attach-agent $tcp0
set sink [new Agent/TCPSink]
$ns attach-agent $n3 $sink
$ns connect $tcp0 $sink


set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1
set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 500
$cbr set interval_ 0.005
$cbr attach-agent $udp1

set null [new Agent/Null]
$ns attach-agent $n3 $null
$ns connect $udp1 $null
$tcp0 set fid_  2
$ns color 2 Green
$udp1 set fid_ 3
$ns color 2 Red


#Schedule events for the CBR and FTP agents
$ns at 0.5 "$ftp start"
$ns at 0.3 "$cbr start"
$ns at 5.0 "finish"
$ns run