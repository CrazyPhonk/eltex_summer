#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


/*Write to pipe function*/


void write_to(int *fd, char * str){
    close(fd[0]);
    write(fd[1], str, sizeof(str));
    close(fd[1]);
}

int main(){
    char * str = "Hi!";
    char buf[3];
    int pipefd[2];
    if (pipe(pipefd)==-1){
        perror("Pipes creation error");
        exit(-2);
    }
    pid_t pid;
    pid = fork();
    if (pid < 0){
        perror("fork error");
        exit(-1);
    }
    else if (pid == 0){
    
    /*Reading from pipe*/
    
        close(pipefd[1]);
        read(pipefd[0], buf, sizeof(buf));
        close(pipefd[0]);
        printf("String from pipe: %s\n", buf);
        wait(NULL);
    }
    else{
            write_to(pipefd, str);
    }
}