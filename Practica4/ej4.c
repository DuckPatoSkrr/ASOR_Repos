#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, int *argv[]){
	int fd = open("tubieria", O_WRONLY);
	
	write(fd, argv[0], 255);
	close(fd);
	return 0;
}