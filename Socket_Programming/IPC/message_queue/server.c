#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>

#define MAX_BUFF_SIZE 5

int main () {
    int res = 0;
    mqd_t fd;
    char buffer[MAX_BUFF_SIZE + 1];
    struct mq_attr mqa;
    //mqa.mq_maxmsg = 256;
    //mqa.mq_msgsize = 10;

    fd= mq_open("/test1", O_RDONLY | O_CREAT, 0666, NULL);
    if (fd < 0) {
        perror("mq_open failed");
        exit(1);
    }
    fd_set rset;

    while (1) {
        //FD_ZERO(&rset);
        //FD_SET(fd, &rset);
        //select(fd+1, &rset, 0, 0, 0);
        //if (FD_ISSET(fd, &rset)) {
        memset(buffer, 0, MAX_BUFF_SIZE);
        res = mq_receive(fd, buffer, MAX_BUFF_SIZE, NULL);
        if (res < 0) {
            perror("mq_receive failed");
            exit (1);
        }
        printf("message received from client is %s\n", buffer);
       // }    
    }
    mq_close(fd);
}
