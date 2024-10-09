#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Функция-обработчик сигнала SIGUSR1
void sigusr1_handler(int signum) {
    printf("Received SIGUSR1!\n");
}

int main() {
    struct sigaction sa;

    // Struct sigaction
    sa.sa_handler = sigusr1_handler; // signal handler
    sigemptyset(&sa.sa_mask);       // do not block any signals
    sa.sa_flags = 0;                // flags

    //redefine SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction error");
        exit(EXIT_FAILURE);
    }

    printf("Recv prog is working! Waiting for SIGUSR1...\n");

    while (1) {
        pause(); // pause to wait signal
    }

    return 0;
}
