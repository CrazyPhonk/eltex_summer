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
    mqd_t qd_server; 
    struct mq_attr attr;
    char buffer[MSG_SIZE];
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; 
    attr.mq_msgsize = MSG_SIZE;
    attr.mq_curmsgs = 0;

    qd_server = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    if (qd_server == (mqd_t) -1) {
        perror("mq_open (server)");
        exit(1);
    }
    printf("qd_serv: %d\n", qd_server);
    strcpy(buffer, "Hi!");
    if (mq_send(qd_server, buffer, strlen(buffer) + 1, 0) == -1) {
        perror("mq_send");
        mq_close(qd_server);
        exit(1);
    }
    printf("Server: sended msg 'Hi!'\n");
    sleep(5);
    printf("qd_serv: %d\n", qd_server);
    if (mq_receive(qd_server, buffer, MSG_SIZE, NULL) == -1) {
        printf("qd_serv: %d\n", qd_server);
        perror("mq_receive");
        mq_close(qd_server);
        exit(1);
    }
    printf("Server: msg accepted '%s'\n", buffer);

    if (mq_close(qd_server) == -1) {
        perror("mq_close (server)");
        exit(1);
    }
    if (mq_unlink(QUEUE_NAME) == -1) {
        perror("mq_unlink");
        exit(1);
    }

    printf("Server: mq deleted.\n");
    return 0;
}
