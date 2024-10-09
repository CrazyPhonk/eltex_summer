// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int sockfd;
  struct sockaddr_in server_addr;
  char buffer[BUFFER_SIZE/2];
  char buffer2[BUFFER_SIZE];
  const char *addSTR = "123";
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("socket");
    exit(1);
  }
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  server_addr.sin_port = htons(PORT);
  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    perror("connect");
    exit(1);
  }
  if (recv(sockfd, buffer, BUFFER_SIZE, 0) == -1) {
    perror("recv");
    exit(1);
  }

  printf("Recv from server: %s\n", buffer);
  sprintf(buffer2, "%s%s", buffer, addSTR);
  if (send(sockfd, buffer2, strlen(buffer2), 0) == -1) {
    perror("send");
    exit(1);
  }

  close(sockfd);

  return 0;
}
