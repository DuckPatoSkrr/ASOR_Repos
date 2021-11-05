#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM__MAX_ERRORS 255

int main(){

	for(int i = 0; i < NUM__MAX_ERRORS; ++i){
		printf("Error %d: %s\n",i,strerror(i));
	}

	return 0;
}

