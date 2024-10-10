#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void sigusr1_handler(int signum) {
    printf("Received SIGUSR1!\n");
}

int main() {
    struct sigaction sa;

    sa.sa_handler = sigusr1_handler; 
    sigemptyset(&sa.sa_mask);       
    sa.sa_flags = 0;                

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction error");
        exit(EXIT_FAILURE);
    }

    printf("Recv prog is working! Waiting for SIGUSR1...\n");

    while (1) {
        pause();
    }

    return 0;
}
