#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    char buff[1000], input[100];
    int k, sock_desc;
    struct sockaddr_in client;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc < 0) {
        printf("\nSocket Creation Failed\n");
        return -1;
    }
    printf("\nSocket Created\n");

    client.sin_family = AF_INET;
    client.sin_port = htons(4000);
    client.sin_addr.s_addr = INADDR_ANY;

    k = connect(sock_desc, (struct sockaddr*)&client, sizeof(client));
    if (k < 0) {
        printf("\nConnection Failed!\n");
        return -1;
    }
    printf("\nConnection Success\n");

    strcpy(buff, "HI");
    k = send(sock_desc, buff, strlen(buff), 0);
    if (k < 0) {
        printf("\nData Sent Failed!\n");
        return -1;
    }

    bzero(buff, sizeof(buff));
    read(sock_desc, buff, sizeof(buff));
    if (strncmp(buff, "220", 3) == 0) {
        printf("\nMsg from server: %s\n", buff);
    }

    strcpy(buff, "HELLO");
    send(sock_desc, buff, strlen(buff), 0);

    bzero(buff, sizeof(buff));
    read(sock_desc, buff, sizeof(buff));
    if (strncmp(buff, "250 OK", 6) == 0) {
        printf("\nMsg from server: %s\n", buff);
    }

    printf("Enter MAILFROM address: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    snprintf(buff, sizeof(buff), "MAILFROM %s", input);
    send(sock_desc, buff, strlen(buff), 0);

    bzero(buff, sizeof(buff));
    read(sock_desc, buff, sizeof(buff));
    if (strncmp(buff, "250 OK", 6) == 0) {
        printf("\nMsg from server: %s\n", buff);
    }

    printf("Enter MAILTO address: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    snprintf(buff, sizeof(buff), "MAILTO %s", input);
    send(sock_desc, buff, strlen(buff), 0);

    bzero(buff, sizeof(buff));
    read(sock_desc, buff, sizeof(buff));
    if (strncmp(buff, "250 OK", 6) == 0) {
        printf("\nMAILTO response from server: %s\n", buff);
    }

    strcpy(buff, "DATA");
    send(sock_desc, buff, strlen(buff), 0);

    bzero(buff, sizeof(buff));
    read(sock_desc, buff, sizeof(buff));
    if (strncmp(buff, "354", 3) == 0) {
        printf("\nDATA response from server: %s\n", buff);
    }

    printf("Enter email body (type 'END' to finish):\n");
    bzero(buff, sizeof(buff));
    while (1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, "END") == 0) break;
        strcat(buff, input);
        strcat(buff, "\n");
    }

    send(sock_desc, buff, strlen(buff), 0);

    strcpy(buff, "END");
    send(sock_desc, buff, strlen(buff), 0);

    bzero(buff, sizeof(buff));
    read(sock_desc, buff, sizeof(buff));
    if (strncmp(buff, "221", 3) == 0) {
        printf("\nMsg from server: %s\n", buff);
    }

    close(sock_desc);
    printf("\n__Qutting__\n");
    return 0;
}

OUTPUT
------
s6@ubuntu:/alwin:$ ./client 

Socket Created

Connection Success

Msg from server: 220

Msg from server: 250 OK
Enter MAILFROM address: abc@gmail.com

Msg from server: 250 OK
Enter MAILTO address: bcd@gmail.com

MAILTO response from server: 250 OK

DATA response from server: 354
Enter email body (type 'END' to finish):
Hi
Hello
END

Msg from server: 221

__Qutting__