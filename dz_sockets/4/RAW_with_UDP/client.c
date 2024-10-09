#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" 
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char data[BUFFER_SIZE - sizeof(struct udphdr)];
    struct udphdr *udph;

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    strcpy(data, "Hello!");

    udph = (struct udphdr *)buffer;
    udph->source = htons(rand() % 65535);
    udph->dest = htons(SERVER_PORT);
    udph->len = htons(sizeof(struct udphdr) + strlen(data));
    udph->check = 0; 

    memcpy(buffer + sizeof(struct udphdr), data, strlen(data));

    if (sendto(sockfd, buffer, sizeof(struct udphdr) + strlen(data), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("sendto");
        exit(1);
    }

    printf("msg sended\n");

    close(sockfd);

    return 0;
}
