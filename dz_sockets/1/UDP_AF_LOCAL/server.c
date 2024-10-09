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


int main()
{
    int sock;
    struct sockaddr_un addr;
    char buf[BUFFER_SIZE/2];
    int bytes_read;
    char msg[BUFFER_SIZE];
    sock = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, SOCK_PATH);
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }
    char addToSTR[3] = "123";
        bytes_read = recvfrom(sock, buf, BUFFER_SIZE/2, 0, NULL, NULL);
        //printf("%s\n", buf);
        sprintf(msg, "%s%s", buf, addToSTR);
        printf("%s\n", msg);

        if (sendto(sock, msg, sizeof(msg), 0, (struct sockaddr *)&addr, sizeof(addr)) < 0){
            perror("sendto");
            exit(1);
        }
    
    return 0;
}