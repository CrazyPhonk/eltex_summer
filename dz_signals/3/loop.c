#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handle_sigusr1(int sig) {
  printf("Получен сигнал SIGUSR1!\n");
}

int main() {
  sigset_t mask;
  int sig;
  signal(SIGUSR1, handle_sigusr1);
  sigemptyset(&mask);
  sigaddset(&mask, SIGUSR1);
  sigprocmask(SIG_BLOCK, &mask, NULL);

  while (1) {
    printf("Ожидание сигнала SIGUSR1...\n");
    sigwait(&mask, &sig); 
  }

  return 0;
}
