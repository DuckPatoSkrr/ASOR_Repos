//VENTURA MATEOS PEREZ
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char *argv[]){

	if(argc != 2){
		printf("Usage: ./ejercicio9 <filename>\n");
		return 1;
	}
	
	struct stat ret;
	if(stat(argv[1],&ret) == -1){
		perror("stat call error");
		return -1;
	}

	if(S_ISREG(ret.st_mode)){
		char filename_sym[256];
		char filename_hard[256];
		strcpy(filename_sym,argv[1]);
		strcpy(filename_hard,argv[1]);
		strcat(filename_sym,".sym");
		strcat(filename_hard,".hard");

		if(link(argv[1], filename_hard) == -1){
			perror("Hard link creation failed");
		}

		if(symlink(argv[1],filename_sym) == -1){
			perror("Soft link creation failed");
		}
	}
	
	return 0;
}
