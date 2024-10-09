#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handle_sigusr1(int sig) {
  printf("Получен сигнал SIGUSR1!\n");
}

int main() {
  sigset_t mask;
  int sig;

  // Настройка обработчика для SIGUSR1
  signal(SIGUSR1, handle_sigusr1);

  // Блокировка сигнала SIGUSR1, чтобы он не завершил программу
  // до того, как мы вызовем sigwait()
  sigemptyset(&mask);
  sigaddset(&mask, SIGUSR1);
  sigprocmask(SIG_BLOCK, &mask, NULL);

  while (1) {
    printf("Ожидание сигнала SIGUSR1...\n");
    sigwait(&mask, &sig); 
    // Программа блокируется здесь до тех пор,
    // пока не будет получен сигнал SIGUSR1
  }

  return 0;
}
