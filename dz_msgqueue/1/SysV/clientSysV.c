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
    int msg_id = msgget(key, 0666);
    if (msg_id == -1){
        perror("msgget");
        exit(-1);
    }
    struct msg_buffer message;
    if(msgrcv(msg_id, &message, sizeof(message.msg_text), 1, 0) == -1){
        perror("msgrcv");
        exit(-1);
    }
    printf("Client: MSG received: %s\n", message.msg_text);
    message.msg_type = 2;
    strcpy(message.msg_text, "Hello!");
    if (msgsnd(msg_id, &message, sizeof(message.msg_text), 0) == -1){
        perror("msgsnd");
        exit(-1);
    } 
    return 0;
}
