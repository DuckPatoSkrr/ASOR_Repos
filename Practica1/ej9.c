#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>



int main(){

	printf("REAL UID: %d\nEFECTIVE UID: %d\n", getuid(), geteuid());

	return 0;
}

