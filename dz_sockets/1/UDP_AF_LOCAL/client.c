#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/local_socket"
#define BUFFER_SIZE 1024


char msg1[] = "Hello there!";

int main()
{
    int sock;
    struct sockaddr_un addr;
    char bufToRead[BUFFER_SIZE];
    sock = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, SOCK_PATH);
    if (sendto(sock, msg1, sizeof(msg1), 0, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("sendto");
        exit(1);
    }
    //int bytes_read = recvfrom(sock, bufToRead, BUFFER_SIZE, 0, NULL, NULL);
    //printf("%s", bufToRead);

    // // if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){ //we can use just send() but first we need to connect socket
    // //     perror("connect");
    // //     exit(1);
    // // }

    if (recvfrom(sock, bufToRead, BUFFER_SIZE, 0, NULL, NULL) < 0){
        perror("recvfrom");
        exit(1);
    }
    printf("%s", bufToRead);
    close(sock);

    return 0;
}