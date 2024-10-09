#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAIN_SERVER_PORT 7777
#define BUFFER_SIZE 1024

void connect_to_server(int port) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        close(sock);
        exit(EXIT_FAILURE);
    }

    char *message = "Hi!";
    ssize_t bytes_sent = send(sock, message, strlen(message), 0);
    if (bytes_sent < 0) {
        perror("send");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Sent to server on port %d: %s\n", port, message);

    ssize_t bytes_read = read(sock, buffer, BUFFER_SIZE);
    if (bytes_read < 0) {
        perror("read");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Received from server on port %d: %s\n", port, buffer);

    close(sock);
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(MAIN_SERVER_PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        close(sock);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_read = read(sock, buffer, BUFFER_SIZE);
    if (bytes_read < 0) {
        perror("read");
        close(sock);
        exit(EXIT_FAILURE);
    }

    int new_port = atoi(buffer);
    printf("Received new server port: %d\n", new_port);
    close(sock);

    connect_to_server(new_port);
}