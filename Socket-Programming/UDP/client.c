#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main(int argc, char* argv[])
{

	if(argc != 2)
	{
		printf("\n___Usage___\n\n<executable> SERVER_PORT\n");
		return -1;
	}
	
	char buff[BUFF_SIZE];
	int k, sock_desc, port;
	struct sockaddr_in client,server;
	
	//client side socket creation.
	sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_desc == -1)
	{
		printf("Error in socket creation\n");
		return -1;
	}
	printf("\nClient socket created\n");
	
	//define ip family, ip addr, port for the socket.
	client.sin_port = htons(atoi(argv[1]));
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	
	socklen_t len;
	len = sizeof(server);
	
	//send data to server.
	while(1)
  	{
		printf("Enter the data to send : ");
		fgets(buff, BUFF_SIZE, stdin);
		k = sendto(sock_desc, buff, BUFF_SIZE, 0, (struct sockaddr*) &server, sizeof(server));
		if(k == -1)
		{
			printf("\nError in sending data\n");
			return -1;
		}
		
		printf("\nSending data...\n");
		
		k = recvfrom(sock_desc, buff, BUFF_SIZE, 0, (struct sockaddr*) &server, &len);
		if(k < 0)
		{
			printf("\nNO MESSSAGE FROM SERVER\n");
			return -1;
		}
		printf("\nMSG FROM SERVER : %s\n", buff);

  	}

	close(sock_desc);
	
	return 0;
}

//output
//------
// baymax@walle:~/code/network_labS6/Socket-Programming/UDP$ ./client 3000

// Client socket created
// Enter the data to send : hi there

// Sending data...

// MSG FROM SERVER : MSG RECEIVED�
// Enter the data to send : haha worked

// Sending data...

// MSG FROM SERVER : MSG RECEIVED
// Enter the data to send : 
                               
