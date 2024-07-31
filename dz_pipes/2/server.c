#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    char *fifo = "/tmp/myfifo";
    mkfifo(fifo, 0666);
    int fd = open(fifo, O_WRONLY); 
    write(fd, "Hi!", sizeof("Hi!"));
    close(fd);
    return 0;
}
