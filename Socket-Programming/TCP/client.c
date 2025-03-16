#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
	char buff[100];
	int k, sock_desc;
	struct sockaddr_in client;
	
	//client side socket creation.
	sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_desc == -1)
	{
		printf("Error in socket creation\n");
		return -1;
	}
	printf("\nClient socket created\n");
	
	//define ip family, ip addr, port for the socket.
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = 4000;
	
	//connect server.
	k = connect(sock_desc, (struct sockaddr*) &client, sizeof(client));
	if( k == -1)
	{
		printf("\nServer connection failed\n");
		return -1;
	}
	printf("\nServer connection success\n");
	
	//send data to server.
	printf("Enter the data to send : ");
	fgets(buff, 100, stdin);
	k = send(sock_desc, buff, 100, 0);
	if(k == -1)
	{
		printf("\nError in sending data\n");
		return -1;
	}
	printf("\nSending data...\n");
	
	close(sock_desc);
	
	return 0;
}

//output
//------
s6@administrator-desktop:~/alwin$ ./client

Client socket created

Server connection success
Enter the data to send : hello people

Sending data...
s6@administrator-desktop:~/alwin$
