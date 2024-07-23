#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024

int main() {
  char cmd[MAX_CMD_LEN];

  while (1) {
    printf("$ ");
    fgets(cmd, MAX_CMD_LEN, stdin);

    cmd[strcspn(cmd, "\n")] = 0;
    if (strcmp(cmd, "exit") == 0) {
      break;
    }
    pid_t pid = fork();

    if (pid < 0) {
      perror("fork failed");
      exit(1);
    } else if (pid == 0) {
      char *args[MAX_CMD_LEN];
      int i = 0;
      char *token = strtok(cmd, " ");
      while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
      }
      args[i] = NULL; 
      execvp(args[0], args);
      perror("execvp failed");
      exit(1);
    } else {
      wait(NULL);
    }
  }

  return 0;
}
