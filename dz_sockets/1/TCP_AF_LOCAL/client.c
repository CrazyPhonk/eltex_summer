// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/local_socket"
#define BUFFER_SIZE 1024

int main() {
  int sockfd;
  struct sockaddr_un server_addr;
  char buffer[BUFFER_SIZE/2];
  char buffer2[BUFFER_SIZE];
  sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("socket");
    exit(1);
  }
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_LOCAL;
  strcpy(server_addr.sun_path, SOCK_PATH);
  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    perror("connect");
    exit(1);
  }
  if (recv(sockfd, buffer, BUFFER_SIZE, 0) == -1) {
    perror("recv");
    exit(1);
  }
  const char * addStr = "123";
  printf("Recv from server: %s\n", buffer);
  sprintf(buffer2, "%s%s", buffer, addStr);
  if (send(sockfd, buffer2, strlen(buffer2), 0) == -1) {
    perror("send");
    exit(1);
  }

  close(sockfd);

  return 0;
}