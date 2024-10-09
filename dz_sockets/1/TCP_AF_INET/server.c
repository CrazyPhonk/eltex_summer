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
  int sockfd, clientfd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_len;
  char buffer[BUFFER_SIZE];
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("socket");
    exit(1);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);
  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    perror("bind");
    exit(1);
  }
  if (listen(sockfd, 5) == -1) {
    perror("listen");
    exit(1);
  }
  client_addr_len = sizeof(client_addr);
  clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
  if (clientfd == -1) {
    perror("accept");
    exit(1);
  }
  strcpy(buffer, "Hello from server!");
  if (send(clientfd, buffer, strlen(buffer) - 1, 0) == -1) {
    perror("send");
    exit(1);
  }

  if (recv(clientfd, buffer, BUFFER_SIZE, 0) == -1) {
    perror("recv");
    exit(1);
  }

  printf("Recv from client: %s\n", buffer);

  close(clientfd);
  close(sockfd);

  return 0;
}
