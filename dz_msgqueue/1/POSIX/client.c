#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME  "/my_queue"
#define MSG_SIZE 256

int main() {
    mqd_t qd_client; 
    char buffer[MSG_SIZE];
    qd_client = mq_open(QUEUE_NAME, O_RDWR);
    if (qd_client == (mqd_t) -1) {
        perror("mq_open (client)");
        exit(1);
    }
    if (mq_receive(qd_client, buffer, MSG_SIZE, NULL) == -1) {
        perror("mq_receive");
        mq_close(qd_client);
        exit(1);
    }
    printf("Client: msg accepted '%s'\n", buffer);
    strcpy(buffer, "Hello!");
    if (mq_send(qd_client, buffer, strlen(buffer) + 1, 0) == -1) {
        perror("mq_send");
        mq_close(qd_client);
        exit(1);
    }
    printf("Client: msg sended 'Hello!'\n");
    if (mq_close(qd_client) == -1) {
        perror("mq_close (client)");
        exit(1);
    }

    return 0;
}
