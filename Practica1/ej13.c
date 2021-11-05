#include <stdio.h>
#include <sys/time.h>



int main(){

	int init, end;
	struct timeval time;	

	init = gettimeofday(&time, NULL);
	for(int i = 0; i < 1000000; ++i);
	end = gettimeofday(&time, NULL);

	printf("Difference: %d\n",end-init);
	return 0;
}

