// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void log_message(const char *client_addr, const char *message) {
    printf("%s: %s\n", client_addr, message);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        char client_addr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &address.sin_addr, client_addr, sizeof(client_addr));
        log_message(client_addr, "Client connected");

        while (recv(new_socket, buffer, BUFFER_SIZE, 0)) {
            log_message(client_addr, buffer);
            send(new_socket, buffer, strlen(buffer), 0);
        }

        log_message(client_addr, "Client disconnected");
        close(new_socket);
    }

    return 0;
}
