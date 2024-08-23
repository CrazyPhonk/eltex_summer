#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_SIZE 256

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    key_t key = ftok("msgqueue", 65); 
    int msg_id = msgget(key, 0666 | IPC_CREAT); 
    struct msg_buffer message;
    message.msg_type = 1; 
    strcpy(message.msg_text, "Hi!");
    if (msgsnd(msg_id, &message, sizeof(message.msg_text), 0) == -1){
        perror("msgsnd");
        exit(-1);
    } 
    printf("Сервер: Отправлено сообщение: %s\n", message.msg_text);
    if (msgrcv(msg_id, &message, sizeof(message.msg_text), 2, 0) == -1){
        perror("msgrcv");
        exit(-1);
    }
    printf("Сервер: Получено сообщение: %s\n", message.msg_text);
    if (msgctl(msg_id, IPC_RMID, NULL) == -1){
        perror("msgctl");
        exit(-1);
    }
    return 0;
}
