#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int sockfd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_len;
  char buffer[BUFFER_SIZE];

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    perror("socket");
    exit(1);
  }

  int broadcast_enable = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
  server_addr.sin_port = htons(PORT);

  strcpy(buffer, "Hello!");
  client_addr_len = sizeof(client_addr);
  if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, client_addr_len) == -1) {
    perror("sendto");
    exit(1);
  }

  printf("Сообщение отправлено в broadcast\n");

  close(sockfd);

  return 0;
}