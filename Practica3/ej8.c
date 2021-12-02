//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>



void daemonProcess(char* target, char** arg_vec){
    int fdout = open("/tmp/daemon.out", O_CREAT | O_WRONLY);
    dup2(STDOUT_FILENO, fdout);
    int fderr = open("/tmp/daemon.err", O_CREAT | O_WRONLY);
    dup2(STDERR_FILENO, fderr);
    int fdin = open("/tmp/null", O_CREAT | O_WRONLY);
    dup2(STDERR_FILENO, fdin);
    
    execvp(target,arg_vec);
    printf("Command finished executing\n");

    close(fdout);
    close(fdin);
    close(fderr);
}



int main(int argc, char * argv[]){

    if(argc < 2){
        printf("Usage: command [args]\n");
        return -1;
    }

	pid_t pid, sid;
	
	pid = fork();	
		
	switch(pid){
	
		case -1:
			perror("fork call failed");
			return -1;
		
		case 0:
			
			if(chdir("/tmp") == -1){
				perror("Daemon: chdir call failed");
				return -1;
			}	
			
			if((sid = setsid()) == -1){
				perror("Daemon: setsid call failed");
				return -1;
			}

            char ** arg_vec = (char**)malloc(sizeof(char*) * argc - 1);
    
            int len;
            for(int i = 1; i < argc; ++i){
                arg_vec[i-1] = (char*) malloc(len= strlen(argv[i])+ 1);
                strncpy(arg_vec[i-1],argv[i],len);
            }
            
            daemonProcess(arg_vec[0],&arg_vec[1]);

            for(int i = 0; i < argc - 1; ++i){
                free(arg_vec[i]);
            }
            free(arg_vec);

			break;

        default:
            printf("Parent ending...\n");
            break;
			
			
	}
	
	return 0;

}
