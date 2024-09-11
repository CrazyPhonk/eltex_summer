#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/unix_sock.sock"
#define MESSAGE "Hello from client!"

int main() {
    int sockfd;
    struct sockaddr_un addr;

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (sendto(sockfd, MESSAGE, strlen(MESSAGE), 0, (struct sockaddr *)&addr, sizeof(addr)) <0){
      perror("sendto");
      exit(1);
    }
    char msg[1024];
    if (recvfrom(sockfd, msg, sizeof(msg), 0, NULL, NULL) < 0){
      perror("recvfrom");
      exit(1);
    }
    printf("MSG from server: %s\n", msg);

    close(sockfd);
    return 0;
}