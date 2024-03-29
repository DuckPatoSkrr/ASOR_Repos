//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]){

	if(argc != 2){
		printf("Usage: ./ejercicio12 <filename>\n");
		return 1;
	}

	int fd = open(argv[1], O_CREAT | O_RDWR, 0777);

	if(fd == -1){
		perror("open call failed");
		return -1;
	}
	
	dup2(fd, 1);
	
	printf("Test line 1\n");
	printf("STDOUT is now redirected to %s\n",argv[1]);
	
	return 0;
}
