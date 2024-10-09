#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <ifaddrs.h>
#include <net/if.h>

#define SERVER_PORT 12345
#define CLIENT_PORT 9999
#define BUFFER_SIZE 1500
#define SERVER_IP "10.0.2.4"
#define CLIENT_IP "10.0.2.15"
#define SERVER_MAC {0x08, 0x00, 0x27, 0xa4, 0x32, 0x28}
#define CLIENT_MAC {0x08, 0x00, 0x27, 0x9f, 0x2f, 0xaf}
#define CLIENT_IF "enp0s3"
#define OFFSET 42

void fill_ethernet_header(struct ethhdr* eth_header, unsigned char* src_mac, unsigned char* dest_mac) {
    memcpy(eth_header->h_dest, dest_mac, 6); 
    memcpy(eth_header->h_source, src_mac, 6);  
    eth_header->h_proto = htons(ETH_P_IP); 
}

void fill_udp_header(struct udphdr* udp_header, int msg_size) {
    udp_header->uh_sport = htons(CLIENT_PORT);
    udp_header->uh_dport = htons(SERVER_PORT);
    udp_header->len = htons(sizeof(struct udphdr) + msg_size);
    udp_header->check = 0;
}



uint16_t checksum(const void *buf, int len) {
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

void fill_ip_header(struct iphdr* ip_header, int msg_size) {
    ip_header->ihl = 5; 
    ip_header->version = 4; 
    ip_header->tos = 0; 
    ip_header->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + msg_size);
    ip_header->id = 2; 
    ip_header->frag_off = 0;
    ip_header->ttl = 255; 
    ip_header->protocol = IPPROTO_UDP;
    ip_header->saddr = inet_addr(CLIENT_IP);
    ip_header->daddr = inet_addr(SERVER_IP);
    ip_header->check = 0;
    ip_header->check = checksum((uint16_t *) ip_header, ip_header->ihl * 4);
}



void print_buffer(char* buffer, int len, int offset) {
    for (int i = offset; i < len; i++) {
        printf("%c", buffer[i]);
    }
    printf("\n");
}

int main() {
    int fd;
    char buf[BUFFER_SIZE];
    char message[] = "Hi?";
    struct sockaddr_ll addr = {0};
    struct ethhdr eth_header;
    struct iphdr ip_header;
    struct udphdr udp_header;
    unsigned char src_mac[6] = CLIENT_MAC, dest_mac[6] = SERVER_MAC;

    fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    printf("Client started on interface %s\n", CLIENT_IF);

    fill_ethernet_header(&eth_header, src_mac, dest_mac);
    fill_udp_header(&udp_header, sizeof(message));
    fill_ip_header(&ip_header, sizeof(message));

    memcpy(buf, &eth_header, sizeof(eth_header));
    memcpy(buf + sizeof(eth_header), &ip_header, sizeof(ip_header));
    memcpy(buf + sizeof(eth_header) + sizeof(ip_header), &udp_header, sizeof(udp_header));
    memcpy(buf + sizeof(eth_header) + sizeof(ip_header) + sizeof(udp_header), message, sizeof(message));

    addr.sll_ifindex = if_nametoindex(CLIENT_IF); 
    addr.sll_halen = ETH_ALEN;  
    memcpy(addr.sll_addr, dest_mac, 6);

    sendto(fd, buf, sizeof(eth_header) + sizeof(ip_header) + sizeof(udp_header) + sizeof(message), 0, (struct sockaddr*)&addr, sizeof(addr));

    printf("Sent \"%s\" to server on port %d\n", message, SERVER_PORT);

    while (1) {
        ssize_t bytes_received = recvfrom(fd, buf, BUFFER_SIZE, 0, NULL, NULL);
        if (bytes_received == -1) {
            perror("recvfrom");
            close(fd);
            exit(EXIT_FAILURE);
        }

        if (buf[OFFSET + 2] == '!') {
            printf("Received from server: ");
            print_buffer(buf, (int)bytes_received, OFFSET);
            break;
        }
    }

    close(fd);
}
