#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>



int main(){

	struct utsname * ptr;
	ptr = malloc(sizeof(struct utsname));
	
	if (uname(ptr) == -1){
		
		perror("uname call failed");
	}
	else{
	
		printf("Sysname: %s.\nNodename: %s.\nRelease: %s.\nVersion: %s.\nMachine: %s.\n", 
			ptr->sysname, ptr->nodename, ptr->release, ptr->version, ptr->machine);
		
	}

	return 0;	
}

