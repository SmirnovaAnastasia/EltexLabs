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

    mqd = mq_open("/mqp", O_RDWR);

    if(mqd == -1){
    	perror("Can't open file");
    }

    sleep (2);
    //===Read===
    char buff[1000];
    buff[0] = '\0';

    mq_getattr(mqd, &attr);
    // Read from the POSIX message queue
    if(mq_receive(mqd, buff, attr.mq_msgsize, NULL) < 0){
        perror("Recieve fall");
    }
    printf("Child reads message: %s\n", buff);

    // Read the number of messages in the queue
    mq_getattr(mqd, &attr);
    printf("Number of message in queue: %ld\n\n", attr.mq_curmsgs);

    //sleep (2);
    //===Write===
    char str[80] = "Hello";
    str[5] = '\0';
    mq_send(mqd, str, strlen(str), 0);
    printf("Child writes message: %s\n", str);

    // Read the number of messages in the queue
    mq_getattr(mqd, &attr);
    printf("Number of message in queue: %ld\n\n", attr.mq_curmsgs);

    //getchar();
    mq_close(mqd);
    
       
    mq_unlink("/mqp");
    return 0;
}