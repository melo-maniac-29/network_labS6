#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
    char ack[BUFFER_SIZE];

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert address from text to binary format
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter message to send (type 'exit' to stop): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Send message
        send(sock, buffer, strlen(buffer), 0);
        printf("Message sent. Waiting for ACK...\n");

        // Wait for ACK
        memset(ack, 0, BUFFER_SIZE);
        recv(sock, ack, BUFFER_SIZE, 0);
        printf("Received: %s\n", ack);
    }

    close(sock);
    return 0;
}

//client.