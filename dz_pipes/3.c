#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 100

/* Split args and command to execute*/

void execute_command(char *cmd) {
    char *args[MAX_ARGS];
    char *token;
    int i = 0;

    token = strtok(cmd, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    pid_t pid = fork();
    if (pid == 0) {

        execvp(args[0], args);
        perror("execvp"); 
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
    } else {
        wait(NULL);
    }
}

/* Deviding incoming command into several processes to excute it individually*/

void execute_pipeline(char *command) {
    char *cmds[MAX_ARGS];
    char *token;
    int pipes[2];
    int fd_in = 0;

    token = strtok(command, "|");
    int i = 0;

    while (token != NULL && i < MAX_ARGS - 1) {
        cmds[i++] = token;
        token = strtok(NULL, "|");
    }
    cmds[i] = NULL;

    for (int j = 0; j < i; j++) {
        if (j < i - 1) {
            pipe(pipes); 
        }
        
        pid_t pid = fork(); 
        if (pid == 0) {
            if (fd_in != 0) {
                dup2(fd_in, 0);
                close(fd_in);
            }
            
            if (j < i - 1) {
                dup2(pipes[1], 1);
                close(pipes[1]);
            }
            close(pipes[0]); 
            
            execute_command(cmds[j]);
            exit(0);
        } else if (pid < 0) {
            perror("fork");
        }

        if (fd_in != 0) {
            close(fd_in);
        }
        
        if (j < i - 1) {
            close(pipes[1]);
        }
        
        fd_in = pipes[0];
    }
    for (int j = 0; j < i; j++) {
        wait(NULL);
    }
}

int main() {
    char command[MAX_CMD_LENGTH];
    while (1) {
        printf("$ ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; 
        }
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break;
        }
        execute_pipeline(command);
    }
    return 0;
}
