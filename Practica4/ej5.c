#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int max(int a, int b){
	if(a > b)
		return a;
	return b;
}

int main(int argc, int *argv[]){
	fd_set set;
	
	FD_ZERO(set);
	
	int fd1 = open("tuberia1", O_RDONLY | O_NONBLOCK );
	
	FD_SET(fd1,set);
	int fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK );
	
	FD_SET(fd2,set);
	max(f1,fd2);
	select(max(f1,fd2) + 1 ,set, NULL, NULL, NULL);
	
	char buffer[255];
	int count;
	if (cambios == -1)
        perror("select()");
    else if (cambios == 1) {
        if(FD_ISSET(fd1, &set)){
			printf("Es la tuberia1\n");
			count = read(fd1, buffer, 255);
			buffer[count] = '\0';
			prinf("%s", buffer);
		}
		
		else{
			printf("Es la tuberia2\n");
			count = read(fd2, buffer, 255);
			buffer[count] = '\0';
			prinf("%s", buffer);
		}
    } 
	
	return 0;
}