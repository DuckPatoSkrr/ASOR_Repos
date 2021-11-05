#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>



int main(){

	int ret = 0;

	if(setuid(0) == -1){
		perror("setuid call failed");
		ret = 1;
	}
	return ret;
}

