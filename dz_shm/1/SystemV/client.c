#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <fcntl.h>

#define SHMSIZE 256


int main(){
    key_t key = ftok("server.c", 'A');
    key_t keySem = ftok("server.c", 'B');
    struct sembuf lock =  {{0,0,0},{0,1,0}};
    struct sembuf unlock = {0,-1,0};
    int sem_id;
    sem_id = semget(keySem, 1, 0666);
    if(sem_id == -1){
        perror("semget");
        exit(-1);
    }
    char * msg;
    char * msgToSend = "Hello!"; 
    int shmid = shmget(key, SHMSIZE, 0666);
    void * shmptr;
    if (semop(sem_id, &lock, 2) < 0){
        perror("semop lock");
        exit(-1);
    }
    shmptr = shmat(shmid, NULL, O_RDWR);
    if (shmptr == NULL){
        perror("shmat");
        exit(-1);
    }
    msg = (char * )shmptr;
    printf("%s\n", msg);
    memcpy(shmptr, msgToSend, 7);
    if (shmdt(shmptr) < 0){
        perror("shmdt");
        exit(-1);
    }
    if (semop(sem_id, &unlock, 1) < 0){
        perror("semop lock");
        exit(-1);
    }
}