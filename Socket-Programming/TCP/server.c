#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
	
	char buff[100];
	socklen_t len;
	int k, sock_desc, temp_sock_desc;
	struct sockaddr_in server, client;
	
	//socket creation.
	sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_desc == -1)
	{
		printf("Error in socket creation");
		return -1;
	}
	printf("\nCreated socket");
	
	server.sin_family = AF_INET;
	server.sin_family = INADDR_ANY;
	server.sin_port = 4000;
	client.sin_family = INADDR_ANY;
	client.sin_port = 4000;
	
	//bind socket with ip and port.
	k = bind(sock_desc, (struct sockaddr *) &server, sizeof(server));
	if(k == -1)
	{
	 	printf("\nError in binding\n");
	 	return -1;
	}
	printf("\nBind success\n");
	
	//listen to connections.
	k = listen(sock_desc, 5);
	if( k == -1)
	{
		printf("\nError in listening\n");
		return -1;
	}
	printf("\nL	istening...\n");
	
	//accepting client connection.
	len = sizeof(client);
	temp_sock_desc = accept(sock_desc, (struct sockaddr*) &client, &len);
	if(temp_sock_desc == -1)
	{
		printf("\nError in accepting connection\n");
		return -1;
	}
	printf("\nStarted accepting connections\n");
	
	//receive data from client.
	k = recv(temp_sock_desc, buff, 100, 0);
	if(k == -1)
	{
		printf("\nError in receiving data\n");
		return -1;
	}
	printf("\nStarted receving for data\n");
	
	printf("Message from client : %s", buff);
	close(temp_sock_desc);

	return 0;
}

//output
//------
s6@administrator-desktop:~/alwin$ ./server

Created socket
Bind success

Listening...

Started accepting connections

Started receving for data
Message from client : hello people
s6@administrator-desktop:~/alwin$
