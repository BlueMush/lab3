#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(){
	int fd;
	struct flock testlock;
	int pid;
	testlock.l_type = F_WRLCK;
	testlock.l_whence = SEEK_SET;
	testlock.l_start = 0;
	testlock.l_len = 10;

	fd = open("testlock", O_RDWR | O_CREAT, 0666);
	if(fcntl(fd, F_SETLKW, &testlock)== -1){
		perror("parent:locking");
		exit(1);
	}
	pid = fork();
	if(pid==0){
		testlock.l_len = 5;
		if(fcntl(fd, F_SETLKW, &testlock)== -1){
			perror("child/; locking");
			exit(1);
		}
		sleep(5);
		printf("parent:exiting\n");
	}
	else{
		perror("fork failed");
	}
}
