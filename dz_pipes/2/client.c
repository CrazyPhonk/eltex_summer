#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    char *fifo = "/tmp/myfifo";
    char buffer[20]; 
    int fd = open(fifo, O_RDONLY); 
    read(fd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);
    close(fd);
    unlink(fifo);
    return 0;
}
