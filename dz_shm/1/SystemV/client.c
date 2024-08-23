#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_KEY 1234567
#define SHM_SIZE 256

int main() {
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    char *shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(1);
    }
    printf("MSG from server: %s\n", shared_memory);
    strcpy(shared_memory, "Hello!");
    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        exit(1);
    }
}
