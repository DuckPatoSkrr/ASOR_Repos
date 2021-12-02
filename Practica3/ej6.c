//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

void daemonProcess(){
    printf("Daemon: PID:\t%d\nPPID:\t%d\nGID:\t%d\nSID:\t%d\n",
                getpid(),getppid(),getgid(),getsid(getpid()));

    struct rlimit limit;
    getrlimit(RLIMIT_NOFILE, &limit);
    printf("Daemon: Max number of allowed open files: %d\n",limit.rlim_cur);

    char aux[256];
    getcwd(&aux, 256);
    printf("Daemon: CWD: %s\n", aux);
}



int main(int argc, char * argv[]){

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
            daemonProcess();
			break;

        default:
            printf("Parent ending...\n");
            break;
			
			
	}
	
	return 0;

}
