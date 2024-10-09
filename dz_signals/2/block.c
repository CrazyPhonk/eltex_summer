#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t set;

    // Инициализируем набор сигналов
    sigemptyset(&set);

    // Добавляем SIGINT в набор
    sigaddset(&set, SIGINT);

    // Блокируем сигналы из набора
    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) {
        perror("Ошибка при вызове sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("Сигнал SIGINT заблокирован. Входим в бесконечный цикл...\n");

    // Бесконечный цикл
    while (1) {
        // Можем добавить сюда какую-то полезную работу,
        // которая не должна прерываться SIGINT
    }

    return 0;
}
