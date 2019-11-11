#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>

#define BUFSIZE 1024
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

#define ___ "/tmp/f1"
#define ____ "/tmp/f2"
#define az );
#define toto sizeof(n)
#define foo read(0, g
#define m_ write(_
#define j write(__
#define t =open(
#define h (
#define l ;
#define ______ )
#define k9 mkfifo h
#define ev chmod h
#define _m unlink(
#define panzer typedef

panzer int tralalapouetpouet; panzer char chapeau;
int main h void ______ { tralalapouetpouet _ t ___, 01101 ______, __ t ____, 01101 ______, b=ev ___, 0777 ______, bb = ev  ____, 0777 az chapeau g[1] , n[100] l b=bb l bb=b l printf h "Programme de test du programme 2fr. Le programme écrit à tour de rôle sur f1 et sur f2 des nombres de plus en plus grands, la sortie de votre programme doit donc être une suite ordonnée d'entiers :\n\t1 2 3 4 5 6 7 8 9 10 11 12 ..\n\nLes fichiers ont normalement été créées, appuyez sur n'importe quelle touche pour commencer à écrire.\n")l fflush h stdout az foo,1)l tralalapouetpouet i=0 l while(++i){ tralalapouetpouet nn = snprintf(n,100,"%d ",i) l usleep(300000) l 1&rand()? m_,n,nn ______ : j,n,nn az }_m ___)l _m ____ az return 0; }

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


