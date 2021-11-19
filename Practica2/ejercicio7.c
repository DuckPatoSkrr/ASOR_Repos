//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[]){
	
	int fd;
	fd = open("FILE_EJ7" , O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IXOTH);
	
	if(fd == -1){
		perror("Error om open() call");
		return -1;
	}

	printf("File created\n");
	
	return 0;
}

