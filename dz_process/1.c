#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
  pid_t pid;
  pid = fork();
  if (pid < 0) {
    perror("fork failed");
    exit(1);
  } else if (pid == 0) { 
    printf("Child proc: PID=%d, PPID=%d\n", getpid(), getppid());
    exit(2);
  } else {
    printf("Parent proc: PID=%d, PPID=%d\n", getpid(), getppid());
    int status;
    wait(&status);

    if (WIFEXITED(status)) {
      printf("Child proc ended with code: %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("Child proc ended by signal: %d\n", WTERMSIG(status));
    }
  }

  return 0;
}
