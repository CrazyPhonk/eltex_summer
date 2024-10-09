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
#define BUFFER_SIZE 1500       

uint16_t ip_checksum(const void *buf, int len) {
    const uint16_t *sbuf = (const uint16_t *)buf;
    uint32_t sum = 0;
    while (len > 1) {
        sum += *sbuf++;
        len -= 2;
    }

    if (len) {
        sum += *(uint8_t *)sbuf;
    }

    while (sum >> 16) {
        sum = (sum & 0xffff) + (sum >> 16);
    }

    return ~(uint16_t)sum;
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char data[BUFFER_SIZE - sizeof(struct iphdr) - sizeof(struct udphdr)];
    struct iphdr *iph;
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

    strcpy(data, "Привет от клиента!");

    iph = (struct iphdr *)buffer;
    iph -> ihl = 5;
    iph -> version = 4;
    iph -> ttl = 8;
    iph -> protocol = IPPROTO_UDP;
    iph -> saddr = inet_addr("127.0.0.1");
    iph -> daddr = inet_addr(SERVER_IP);
    iph -> tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + strlen(data));
    iph -> id = htons(rand() % 65535);
    iph -> check = 0;

    udph = (struct udphdr *)(buffer + sizeof(struct iphdr));
    udph -> source = htons(rand() % 65535); 
    udph->dest = htons(SERVER_PORT);
    udph->len = htons(sizeof(struct udphdr) + strlen(data));
    udph->check = 0;

    memcpy(buffer + sizeof(struct iphdr) + sizeof(struct udphdr), data, strlen(data));

    iph->check = ip_checksum(buffer, iph->ihl << 2);

    if (sendto(sockfd, buffer, iph->tot_len, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("sendto");
        exit(1);
    }

    printf("Данные отправлены на сервер\n");
    close(sockfd);

    return 0;
}
