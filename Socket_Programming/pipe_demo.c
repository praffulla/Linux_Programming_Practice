/*
    Historically, they have been half duplex (data flows in only one direction). Some systems now provide full-duplex pipes, but for maximum portability, we should never assume that this is the case.
    Pipes can be used only between processes that have a common ancestor. Normally, a pipe is created by a process, that process calls fork, and the pipe is used between the parent and the child.

*/


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFF 100
int main()
{
    int fd[2];
    char line[BUFF] = {0};
    pipe(fd);
    
    pid_t f = fork();
    if(f < 0) {
        printf("\n fork failed\n");
    }else if (f > 0) {
        close(fd[0]);
        write(fd[1], "Hello", strlen("Hello"));
    }else{
        close(fd[1]);
        read(fd[0], line, BUFF);
        printf("\nchild read %s", line);
    }

    return 0;
}
