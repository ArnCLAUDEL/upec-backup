#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <poll.h>


#define BUFF_SIZE 1024*sizeof(char)

int exercice2() {
	int fd = creat("tmp",S_IRWXU|S_IRWXO|S_IRWXG);
	char* buffer = malloc(BUFF_SIZE);

	int rd,save1 = dup(1);
	while(1) {
		rd = read(1,buffer,BUFF_SIZE);
		if(rd == 0) exit(0);

		dup2(fd,1);
		write(1,buffer,strlen(buffer));
		dup2(save1,1);
	}
	return 0;
}


int exercice3(const char* file) {


   	struct stat s;
	struct passwd *pw;

	stat(file,&s);
	pw = getpwuid(s.st_uid);
	printf("%s\n",pw->pw_name);
	
	return 0;
}

int exercice4(int nb_arg,const char ** arg) {

	int fdpipe[2],i;
	int save1 = dup(1);

	for(i = 1; i < nb_arg; i++) {
		if(i == nb_arg -1) dup2(save1,1);
		else dup2(fdpipe[1],1);

		if(fork()) execlp(arg[i],arg[i],NULL);

		dup2(fdpipe[0],0);
	}

	return 0;
}
/*
int exercice7(const char* file) {

	int fd = open(file,O_RDONLY);
	char* buffer = malloc(BUFF_SIZE);
	char* revbuffer = malloc(BUFF_SIZE);
	int alire, rd, i;

	alire = lseek(fd,0,SEEK_END);
	lseek(fd,alire - (alire % BUFF_SIZE),SEEK_SET);

	while(alire > 0) {
		rd = read(fd,buffer,BUFF_SIZE > alire ? alire : BUFF_SIZE);
		for(i = 0; i < rd ; i++) {
			revbuffer[i] = buffer[rd-i-1];
		}
		write(1,revbuffer,rd);
		alire -= rd;
        lseek(fd, alire - BUFF_SIZE, SEEK_SET);
			
	}

    close(fd);
	return 0;
}
*/
int pollo () {

	struct pollfd p[1];
	p[0].fd = 0;
	p[0].events = POLLIN;

		poll(p,1,5000);
            if(p[0].revents & POLLIN) write(1,"oui\n",4);
               
	return 0;
}

int main(int argc, char const *argv[])
{
	//Exercice 1
	printf("nb arg : %d\n",argc-1 );

	//exercice2();
	
	//exercice3(argv[1]);

	//exercice4(argc,argv);

	//exercice7(argv[1]);

	pollo();

	return 0;
}