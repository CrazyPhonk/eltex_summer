#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MULTICAST_GROUP "224.0.0.1" 
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int sockfd;
  struct sockaddr_in server_addr;
  char buffer[BUFFER_SIZE];
  struct ip_mreq mreq;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    perror("socket");
    exit(1);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
  server_addr.sin_port = htons(PORT);

  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    perror("bind");
    exit(1);
  }

  // Подписка на multicast-группу
  mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
  mreq.imr_interface.s_addr = htonl(INADDR_ANY); // Привязка к любому интерфейсу
  if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  strcpy(buffer, "Hello!");
  if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    perror("sendto");
    exit(1);
  }

  printf("msg sended to multicast\n");

  // Закрытие сокета
  close(sockfd);

  return 0;
}