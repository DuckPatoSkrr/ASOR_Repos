//VENTURA MATEOS PEREZ
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: <name of pipe>");
        return 1;
    }

	int fd = open(argv[1], O_WRONLY);
	
	if(fd == -1){
		perror("open call failed");
		return -1;
	}
	
	write(fd, argv[0], strlen(argv[0]));
	close(fd);

}
