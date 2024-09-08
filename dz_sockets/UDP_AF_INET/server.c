// server.c
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

  // Создание сокета
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    perror("socket");
    exit(1);
  }

  // Заполнение адреса сервера
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  // Привязка сокета к адресу
  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    perror("bind");
    exit(1);
  }

  // Отправка строки клиенту
  strcpy(buffer, "Привет от сервера!");
  client_addr_len = sizeof(client_addr);
  if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, client_addr_len) == -1) {
    perror("sendto");
    exit(1);
  }

  // Получение строки от клиента
  if (recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len) == -1) {
    perror("recvfrom");
    exit(1);
  }

  printf("Получено от клиента: %s\n", buffer);

  // Закрытие сокета
  close(sockfd);

  return 0;
}
