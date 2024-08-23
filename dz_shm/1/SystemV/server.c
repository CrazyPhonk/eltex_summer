#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SHMSIZE 256

int main(){
    char * msgToCheck = "Hello!";
    key_t key = ftok("server.c", 'A');
    key_t keySem = ftok("server.c", 'B');
    char * msg = "Hi!";
    struct sembuf lock =  {{0,0,0},{0,1,0}};
    struct sembuf unlock = {0,-1,0};
    int sem_id;
    char * msgToRecv = "asd";
    sem_id = semget(keySem, 1, 0666 | IPC_CREAT);
    if (sem_id == -1){
        perror("semget");
        exit(-1);
    }
    int shmid = shmget(key, SHMSIZE, 0666 | IPC_CREAT);
    if (shmid == -1){
        perror("shmget");
        exit(-1);
    }
    void * shmptr;
    if (semop(sem_id, &lock, 1) == -1){
        perror("semop");
        exit(-1);
    }
    shmptr = shmat(shmid, NULL, O_RDWR);
    if (shmptr == NULL){
        perror("shmat");
        exit(-1);
    }
    memcpy(shmptr, msg, 4);
    shmdt(shmptr);
    if (semop(sem_id, &unlock, 1) == -1){
        perror("semop2");
        exit(-1);
    }
    int a = 1;
    while(a != 0){
        int a = strcmp(msgToRecv, msgToCheck);
    printf("%d\n", a);
    if (a < 0){
        perror("strcmp");
        exit(-1);
    }
        if (semop(sem_id, &lock, 1) == -1){
        perror("semop3");
        exit(-1);
    }
        shmptr = shmat(shmid, NULL, O_RDWR);
        if (shmptr == NULL){
            perror("shmat2");
            exit(-1);
        }
        msgToRecv = (char *)shmptr;
        if (strcmp(msgToRecv, msgToCheck) != 0){
            msgToRecv = "asd";
        }
        if (shmdt(shmptr) == -1){
            perror("shmdt");
            exit(-1);
        }
        if (semop(sem_id, &unlock, 1) == -1){
        perror("semop4");
        exit(-1);
        }
    }
    printf("%s\n", msgToRecv);
    if(semctl(sem_id, 1, IPC_RMID) == -1){
        perror("semctl");
        exit(-1);
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(-1);
    }
}