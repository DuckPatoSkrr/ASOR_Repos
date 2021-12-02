//VENTURA MATEOS PEREZ
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>


volatile int cont_sigint = 0;
volatile int cont_sigtstp = 0;


void handler(int signal){

	if (signal == SIGINT) 
		cont_sigint++;
		
  	if (signal == SIGTSTP) 
  		cont_sigtstp++;
}


int main(){

	struct sigaction action, action2;
	
	sigaction(SIGINT, NULL, &action);
	action.sa_handler = handler;
	sigaction(SIGINT, &action, NULL);

	sigaction(SIGTSTP, NULL, &action2);
	action2.sa_handler = handler;
	sigaction(SIGTSTP, &action2, NULL);
	
	while(cont_sigint + cont_sigtstp < 10){}
	
	printf("SIGINT %d\n", cont_sigint);
	printf("SIGTSTP %d\n", cont_sigtstp);
	
	return 0;
}