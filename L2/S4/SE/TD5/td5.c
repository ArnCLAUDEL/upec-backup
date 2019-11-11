#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main() {

	int fd[2];
	//char buf[100];
	pipe(fd);
	

if(fork()){
dup2(fd[1], STDOUT_FILENO);
close(fd[0]);
close(fd[1]);

}
else{
dup2(fd[0], STDIN_FILENO);
close(fd[0]);
close(fd[1]);
execlp("ls","ls",NULL);
}
	return EXIT_SUCCESS;
}