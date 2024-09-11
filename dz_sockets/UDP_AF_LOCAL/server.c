#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/unix_sock.sock"
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_un addr;
    char buffer[BUFFER_SIZE/2];
    char msg[BUFFER_SIZE];
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    unlink(SOCKET_PATH);
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

        if (recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL) < 0){
          perror("recvfrom");
          exit(1);
        }
        printf("Received: %s\n", buffer);
        char *addSTR;
        sprintf(msg, "%s%s", buffer, addSTR);
        if (sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&addr, sizeof(addr)) < 0){
          perror("sendto");
          exit(1);
        }
      printf("MSG sended...\n");

    close(sockfd);
    return 0;
}