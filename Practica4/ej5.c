//VENTURA MATEOS PEREZ
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char*argv[]){

    if(argc!=3){
        printf("Usage: <fifo1> <fifo2>\n");
    }

	int fd1 = open(argv[1], O_RDONLY | O_NONBLOCK);
	int fd2 = open(argv[2], O_RDONLY | O_NONBLOCK);
	
	if(fd1 == -1 || fd2 == -1){
		perror("open call failed");
		close(fd1);
		close(fd2);
		return -1;
	}

	fd_set set;
	
	FD_ZERO(&set);
	FD_SET(fd1, &set);
	FD_SET(fd2, &set);
	
	char buf[256];
	int tamBuf = 0;
	
	int max = fd1;
	
	if(fd2 > fd1)
		max = fd2;
	
	max++;
	
	int selector = select(max, &set, NULL, NULL, NULL);

	if (selector == -1){
    	perror("select call failed");
    	close(fd1);
		close(fd1);
    	return -1;
    }
    
    if (selector > 0) {
   		
    	if(FD_ISSET(fd1, &set)){
    	
    		tamBuf = read(fd1, buf, 256);
    		buf[tamBuf] = '\0';
    		
    		printf("%s: %s\n", argv[1], buf);
    		
    	}else{
    	
    	    tamBuf = read(fd2, buf, 256);
    		buf[tamBuf] = '\0';
    		
    		printf("%s: %s\n", argv[2], buf);
    	}
    } 

	close(fd1);
	close(fd2);

	return 0;
}