#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, int *argv[]){
	
	int ph[2], hp[2];
	char * msg[];
	pipe(ph);
	pipe(hp);
	
	pid_t pid;
	pid = fork();
	switch (pid) {
		case -1:
			perror(“fork”);
			exit(1);
		case 0: //HIJO
			int c = 0;
			
			while(c < 10){
				read(ph[0], msg, 255);
			
				printf("%s", msg);
				++c;
			
				write(hp[1], "l", 2);
			}
			
			write(hp[1], "q", 2);
			
			close(hp[0]);
			close(hp[1]);
			close(ph[0]);
			close(ph[1]);
			
			break;
		default:
			
			while(msg != "q"){
				scanf("%s", msg);
			
				write(ph[1], msg, strlen(msg));
			
				read(hp[0],msg, 255);
			}
			
			close(hp[0]);
			close(hp[1]);
			close(ph[0]);
			close(ph[1]);
			
			break;
	}
	
	
	return 0;
}