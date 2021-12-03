//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>


void proceso(int fd, char * arg1, char * arg2,int stdio){
    dup2(fd,stdio);
    close(fd);
    char * command = malloc(sizeof(char)*(strlen(arg1)+strlen(arg2)+2));
    strcpy(command,arg1);
    strcat(command," ");
    strcat(command,arg2);
    strcat(command,"\0");
    system(command);
}

int main(int argc, char * argv[]){

    if(argc != 5){
	
		printf("Usage: %s <command 1> <arg 1> <command 2> <arg 2>\n", argv[0]);
		return -1;
	}

    int pipefd[2]; //0 read 1 write
    pipe(pipefd);

    switch (fork())
    {
    case -1:
        perror("fork call failed");
        break;
    
    case 0:
        close(pipefd[1]);
        proceso(pipefd[0],argv[1],argv[2],STDIN_FILENO);
        break;

    default:
        close(pipefd[0]);
        proceso(pipefd[1],argv[3],argv[4],STDOUT_FILENO);
        break;
    }


    return 0;
}