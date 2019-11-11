#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 1024

int main(int argc, char **argv){
    int fd = open(argv[1], O_RDONLY);
    char buffer[BUFSIZE], revbuffer[BUFSIZE];
    int alire, n, i;

    alire = lseek(fd, 0, SEEK_END); // taille du fichier
    lseek(fd, alire - (alire % BUFSIZE), SEEK_SET);
    while(alire>0){
        n=read(fd, buffer, BUFSIZE > alire ? alire : BUFSIZE);
        for(i=0; i<n; i++)
            revbuffer[i]=buffer[n-1-i];
        write(STDOUT_FILENO, revbuffer, n);
        alire-=n;
        
        lseek(fd, alire - BUFSIZE, SEEK_SET);
    }
    close(fd);
    return 0;
}
