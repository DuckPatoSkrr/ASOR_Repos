//VENTURA MATEOS PEREZ
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	
	sigset_t blk_set;
	
	sigemptyset(&blk_set);
	sigaddset(&blk_set, SIGINT);
  	sigaddset(&blk_set, SIGTSTP);
	
	if(sigprocmask(SIG_BLOCK, &blk_set, NULL) == -1){
		perror("sigprocmask call failed");
		return -1;
	}
		
	sleep(30);
	
	sigset_t pending_set;
	
	if(sigpending(&pending_set) == -1){
		perror("sigpending call failed");
		return -1;
	}

	if(sigismember(&pending_set, SIGINT) == 1)
		printf("SIGINT\n");
		
		
	if(sigismember(&pending_set, SIGTSTP) == 1){
	
		printf("SIGTSTP\n");
	
		sigdelset(&blk_set, SIGINT);
		sigprocmask(SIG_UNBLOCK, &blk_set, NULL);
	}
	
    printf("Finished\n");
	return 0;
}