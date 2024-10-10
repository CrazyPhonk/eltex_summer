#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t set;

    sigemptyset(&set);

    sigaddset(&set, SIGINT);
    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) {
        perror("Ошибка при вызове sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("Сигнал SIGINT заблокирован. Входим в бесконечный цикл...\n");
    while (1) {
        sleep(10);
    }

    return 0;
}
