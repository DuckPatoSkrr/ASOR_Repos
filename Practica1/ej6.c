#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>



int main(){
	long ret;
	if(ret = sysconf(_SC_ARG_MAX) != -1){
		printf("Max args: %d\n",ret);
	}
	if(ret = sysconf(_SC_CHILD_MAX) != -1){
		printf("Max child: %d\n",ret);
	}
	if(ret = sysconf(_SC_OPEN_MAX) != -1){
		printf("Max files: %d\n",ret);
	}
	return 0;
}

