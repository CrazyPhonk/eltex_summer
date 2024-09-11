
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
  char buffer[BUFFER_SIZE];
  socklen_t server_addr_len;

  // Создание сокета
  sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    perror("socket");
    exit(1);
  }

  // Заполнение адреса сервера
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_LOCAL;
  strcpy(server_addr.sun_path, SOCK_PATH);
  server_addr_len = sizeof(server_addr);

  // Получение строки от сервера
  if (recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &server_addr_len) == -1) {
    perror("recvfrom");
    exit(1);
  }

  printf("Получено от сервера: %s\n", buffer);

  // Отправка строки на сервер
  strcpy(buffer, "Привет от клиента!");
  if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, server_addr_len) == -1) {
    perror("sendto");
    exit(1);
  }

  // Закрытие сокета
  close(sockfd);

  return 0;
}
