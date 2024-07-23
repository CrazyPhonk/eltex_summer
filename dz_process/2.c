#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
  pid_t pid1, pid2, pid3, pid4, pid5;

  pid1 = fork();
  if (pid1 < 0) {
    perror("fork failed (process 1)");
    exit(1);
  } else if (pid1 == 0) { 
    printf("Proc 1: PID=%d, PPID=%d\n", getpid(), getppid());
    pid3 = fork();
    if (pid3 < 0) {
      perror("fork failed (process 3)");
      exit(1);
    } else if (pid3 == 0) {
      printf("Proc 3: PID=%d, PPID=%d\n", getpid(), getppid());
      exit(0);
    } else { 
      pid4 = fork();
      if (pid4 < 0) {
        perror("fork failed (process 4)");
        exit(1);
      } else if (pid4 == 0) {
        printf("Proc 4: PID=%d, PPID=%d\n", getpid(), getppid());
        exit(0);
      } else {
        wait(NULL);
        wait(NULL);
      }
    }
    exit(0);
  } else { 
    pid2 = fork();
    if (pid2 < 0) {
      perror("fork failed (process 2)");
      exit(1);
    } else if (pid2 == 0) {
      printf("Proc 2: PID=%d, PPID=%d\n", getpid(), getppid());
      pid5 = fork();
      if (pid5 < 0) {
        perror("fork failed (process 5)");
        exit(1);
      } else if (pid5 == 0) { 
        //sleep(2);
        printf("Proc 5: PID=%d, PPID=%d\n", getpid(), getppid());
        exit(0);
      } else {
        wait(NULL); 
      }
      exit(0);
    } else { 
      printf("Main proc 0: PID=%d, PPID=%d\n", getpid(), getppid());
      wait(NULL); 
      wait(NULL);
    }
  }
  return 0;
}
