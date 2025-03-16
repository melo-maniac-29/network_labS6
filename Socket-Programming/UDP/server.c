#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main(int argc, char *argv[])
{

	if(argc != 2)
	{
		printf("\n___Usage___\n\n<executable> PORT\n");
		return -1;
	}
	
	printf("\nPORT : %s\n", argv[1]);
	
	char buff[BUFF_SIZE];
	socklen_t len;
	int k, sock_desc, temp_sock_desc;
	struct sockaddr_in server, client;
	const char *recv_success = "MSG RECEIVED";
	
	//socket creation.
	sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_desc == -1)
	{
		printf("Error in socket creation");
		return -1;
	}
	printf("\nCreated socket");
	
	server.sin_family = AF_INET;
	server.sin_family = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));
	
	//bind socket with ip and port.
	k = bind(sock_desc, (struct sockaddr *) &server, sizeof(server));
	if(k == -1)
	{
	 	printf("\nError in binding\n");
	 	return -1;
	}
	printf("\nBind success\n");
	
	len = sizeof(client);

	  while(1)
	  {
	  	//receive data from client.
	  	k = recvfrom(sock_desc, buff, BUFF_SIZE, 0, (struct sockaddr *) &client, &len);
	  	if(k == -1)
	  	{
			printf("\nError in receiving data\n");
			return -1;
	  	}
	  	printf("\nStarted receving for data\n");
	
	  	printf("Message from client : %s", buff);
	  	
	  	k = sendto(sock_desc, recv_success, strlen(recv_success), 0, (struct sockaddr*) &client, sizeof(client));
	  	
	  	if( k < 0)
	  	{
	  		printf("\nRECV CONF NOT SENT\n");
	  		return -1;
	  	}
	  	
	  	printf("\nRECV CONF SENT\n");
	  	
  	}
                          
 close(temp_sock_desc);
	return 0;
}

//output
// baymax@walle:~/code/network_labS6/Socket-Programming/UDP$ ./server 3000

// PORT : 3000

// Created socket
// Bind success

// Started receving for data
// Message from client : hi there

// RECV CONF SENT

// Started receving for data
// Message from client : haha worked

// RECV CONF SENT


