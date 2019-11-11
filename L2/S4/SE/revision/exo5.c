#include <unistd.h>

int main(int argc, char **argv){
    int pipefds[2], i;
    int oldstdout = dup(STDOUT_FILENO);
    
    for(i=1; i<argc; i++){
        pipe(pipefds);
        if(i==argc-1) 
            dup2(oldstdout, STDOUT_FILENO);
        else 
            dup2(pipefds[1], STDOUT_FILENO);
        if(fork()){
            execlp(argv[i], argv[i], NULL);
        }
        dup2(pipefds[0], STDIN_FILENO);
    }
    return 0;
}
