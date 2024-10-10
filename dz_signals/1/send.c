#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <PID процесса-получателя>\n", argv[0]);
        return 1;
    }

    pid_t receiver_pid = atoi(argv[1]);
    if (kill(receiver_pid, SIGUSR1) == -1) {
        perror("Error to send sig");
        return 1;
    }

    printf("Signal SIGUSR1 sended to PID %d\n", receiver_pid);

    return 0;
}
