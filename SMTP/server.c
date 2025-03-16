#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    char buff[100];
    socklen_t len;
    int k, sock_desc, temp_sock_desc;
    struct sockaddr_in server, client;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc < 0) {
        printf("\nSocket Creation Failed!\n");
        return -1;
    }
    printf("\nSocket Created!\n");

    server.sin_family = AF_INET;
    server.sin_port = htons(4000);
    server.sin_addr.s_addr = INADDR_ANY;

    k = bind(sock_desc, (struct sockaddr*)&server, sizeof(server));
    if (k < 0) {
        printf("\nSocket Bind Failed!\n");
        return -1;
    }
    printf("\nSocket Bind Success\n");

    listen(sock_desc, 5);
    printf("\nListening for connections...\n");

    len = sizeof(client);
    temp_sock_desc = accept(sock_desc, (struct sockaddr*)&client, &len);
    if (temp_sock_desc < 0) {
        printf("\nAccept Connection Failed!\n");
        return -1;
    }
    printf("\nAccepted Connection\n");

    read(temp_sock_desc, buff, sizeof(buff));
    printf("\nMsg from client: %s\n", buff);
    strcpy(buff, "220");
    write(temp_sock_desc, buff, sizeof(buff));

    read(temp_sock_desc, buff, sizeof(buff));
    if (strncmp(buff, "HELLO", 5) == 0) {
        printf("\nMsg from client: %s\n", buff);
        strcpy(buff, "250 OK");
        write(temp_sock_desc, buff, sizeof(buff));
    }

    read(temp_sock_desc, buff, sizeof(buff));
    if (strncmp(buff, "MAILFROM", 8) == 0) {
        printf("\nMsg from client: %s\n", buff);
        strcpy(buff, "250 OK");
        write(temp_sock_desc, buff, sizeof(buff));
    }

    read(temp_sock_desc, buff, sizeof(buff));
    if (strncmp(buff, "MAILTO", 6) == 0) {
        printf("\nMsg from client: %s\n", buff);
        strcpy(buff, "250 OK");
        write(temp_sock_desc, buff, sizeof(buff));
    }

    read(temp_sock_desc, buff, sizeof(buff));
    if (strncmp(buff, "DATA", 4) == 0) {
        printf("\nMsg from client: %s\n", buff);
        strcpy(buff, "354");
        write(temp_sock_desc, buff, sizeof(buff));
    }

    printf("\nEmail Body:\n");
	bzero(buff, sizeof(buff));
    read(temp_sock_desc, buff, sizeof(buff));
	printf("\n---------------------------------\n");
    printf("%s\n", buff);
	printf("\n---------------------------------\n");

    strcpy(buff, "221");
    write(temp_sock_desc, buff, sizeof(buff));

	printf("__Quitting__");

    close(temp_sock_desc);
    close(sock_desc);
    return 0;
}

OUTPUT
------

s6@ubuntu:/alwin:$ ./server 

Socket Created!

Socket Bind Success

Listening for connections...

Accepted Connection

Msg from client: HI�

Msg from client: HELLO

Msg from client: MAILFROM abc@gmail.com

Msg from client: MAILTO bcd@gmail.comom

Msg from client: DATAOK

Email Body:

---------------------------------
Hi
Hello


---------------------------------
__Quitting__