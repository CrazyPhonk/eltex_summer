#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <unistd.h>

#define MAX_NAME_LEN 32
#define MAX_MSG_LEN 512
#define MAX_CLIENTS 100
#define MAX_MESSAGES 1000
#define MAX_DATE_LEN 64
#define SHM_KEY 0x1234
#define SEM_KEY 0x5678

typedef struct {
    char username[MAX_NAME_LEN];
    char message[MAX_MSG_LEN];
    char datetime[MAX_DATE_LEN];
} Message;

typedef struct {
    int num_clients;
    char clients[MAX_CLIENTS][MAX_NAME_LEN];
    Message messages[MAX_MESSAGES];
    int message_count;
} ChatRoom;

int shm_id;
int sem_id;
ChatRoom *chatroom;

void cleanup(int signum) {
    shmdt(chatroom);
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID, 0);
    exit(0);
}

void p(int sem_id) {
    struct sembuf p = {0, -1, SEM_UNDO};
    semop(sem_id, &p, 1);
}

void v(int sem_id) {
    struct sembuf v = {0, 1, SEM_UNDO};
    semop(sem_id, &v, 1);
}

int main() {
    signal(SIGINT, cleanup);

    shm_id = shmget(SHM_KEY, sizeof(ChatRoom), IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }

    chatroom = (ChatRoom *)shmat(shm_id, NULL, 0);
    if (chatroom == (ChatRoom *)-1) {
        perror("shmat");
        exit(1);
    }

    sem_id = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (sem_id < 0) {
        perror("semget");
        exit(1);
    }

    semctl(sem_id, 0, SETVAL, 1);

    chatroom->num_clients = 0;
    chatroom->message_count = 0;

    while (1) {
        sleep(1);
    }
    
}

