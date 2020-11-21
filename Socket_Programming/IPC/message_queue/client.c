#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>

#define MAX_BUFF_SIZE 5

int main () {
    int res = 0;
    mqd_t cfd;
    char buffer[MAX_BUFF_SIZE];
    
    cfd= mq_open("/test", O_WRONLY | O_CREAT, 0, 0);
    if (cfd < 0) {
        perror("mq_open failed");
        exit(1);
    }

    memset(buffer, 0, MAX_BUFF_SIZE);
    puts("Write to server!");
    scanf("%s", buffer);
    res = mq_send(cfd, buffer, strlen(buffer) + 1, 0);
    if (res < 0) {
        perror("mq_send failed");
        exit(1);
    }

    mq_close(cfd);
    return 0;
}
