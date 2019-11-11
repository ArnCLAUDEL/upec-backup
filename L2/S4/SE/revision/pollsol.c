#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]){
    struct pollfd fds[2];
    int n,i;
    fds[0].fd = open("/tmp/f1", O_RDONLY);
    fds[1].fd = open("/tmp/f2", O_RDONLY);
    fds[0].events = POLLIN;
    fds[1].events = POLLIN;
    char buf[BUFSIZ];

    
    while(1){
        poll(fds,2,-1);
        for(i=0; i<2; i++)
            if(fds[i].revents & POLLIN){
                while((n=read(fds[i].fd, buf, BUFSIZE))>0)
                    write(STDOUT_FILENO, buf, n);
            }
    }

    
}
