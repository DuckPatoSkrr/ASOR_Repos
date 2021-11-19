//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]){

	if(argc != 2){
		printf("Usage: ./ejercicio15 <filename>\n");
		return 1;
	}

	int fd = open(argv[1], O_WRONLY);

	if(fd == -1){
		perror("open call failed");
		return -1;
	}

	int lock_state = lockf(fd, F_TLOCK, 3);
	
	if(lock_state != -1){
		time_t aux;
		  
		struct tm *timeinfo;

		time(&aux);
		timeinfo = localtime(&aux);
		printf ("Time: %0d:%0d:%0d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
		
		sleep(30);
		
		lockf(fd, F_UNLCK, 0);
	
	}
	else
		printf("Locked\n");
	
	return 0;
}
