#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>

#define SHARED_MEMORY_NAME "/my_shared_memory"
#define SHARED_MEMORY_SIZE 256

#define SEMAPHORE_NAME "/my_semaphore"

int main() {

    sem_t * sem_id = sem_open(SEMAPHORE_NAME, O_CREAT, 0666, 1);
    if (sem_id == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }
    if (sem_post(sem_id) == -1) {
            perror("sem_post");
            exit(1);
        }
    
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(shm_fd, SHARED_MEMORY_SIZE) == -1) {
        perror("ftruncate");
        close(shm_fd);
        shm_unlink(SHARED_MEMORY_NAME);
        exit(1);
    }

    char *shared_memory = mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        shm_unlink(SHARED_MEMORY_NAME);
        exit(1);
    }

    strcpy(shared_memory, "Hi!");

    while (strcmp(shared_memory, "Hello!") != 0) {
        sleep(1);
    }

    printf("Received response from client: %s\n", shared_memory);

    munmap(shared_memory, SHARED_MEMORY_SIZE);
    close(shm_fd);
    if (sem_wait(sem_id) == -1) {
            perror("sem_wait");
            exit(1);
    }
    sem_close(sem_id); 
    sem_unlink(SEMAPHORE_NAME); 
    shm_unlink(SHARED_MEMORY_NAME);

    return 0;
}
