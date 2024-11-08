// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);
    
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while (1) {
        printf("Enter a number (or 'exit' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        if (strcmp(buffer, "exit\n") == 0) break;

        send(sock, buffer, strlen(buffer), 0);
        recv(sock, buffer, BUFFER_SIZE, 0);
        printf("Server response: %s", buffer);
    }

    close(sock);
    return 0;
}
