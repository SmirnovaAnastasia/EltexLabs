#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    mqd_t mqd;

    struct mq_attr attr;

    mqd = mq_open("/mqp", O_RDWR | O_CREAT, 0660, NULL);

    if(mqd == -1){
    	perror("Can't open file");
    }

    //===Write===
    char str[80] = "Hi";
    str[2] = '\0';
    mq_send(mqd, str, 2, 0);
    printf("Parent writes message: %s\n", str);

    // Read the number of messages in the queue
    mq_getattr(mqd, &attr);
    printf("Number of message in queue: %ld\n\n", attr.mq_curmsgs);

    //printf("am!\n");
    sleep (4);
    //===Read===
    char buff[1000];
    buff[0] = '\0';

    mq_getattr(mqd, &attr);
    // Read from the POSIX message queue
    if(mq_receive(mqd, buff, attr.mq_msgsize, NULL) < 0){
        perror("Recieve fall");
    }
    printf("Parent reads message: %s\n", buff);

    // Read the number of messages in the queue
    mq_getattr(mqd, &attr);
    printf("Number of message in queue: %ld\n\n", attr.mq_curmsgs);
    mq_close(mqd);

    //getchar();
    mq_unlink("/mqp");
    return 0;
}