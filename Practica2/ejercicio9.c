//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char * argv[]){

	if(argc != 2){
		printf("Usage: ./ejercicio9 <filename>\n");
		return 1;
	}

	struct stat ret;
	if(stat(argv[1],&ret) == -1){
		perror("stat call error");
		return -1;
	}

	char* filename = argv[1];
	int major = major(ret.st_dev);
	int minor = minor(ret.st_dev);
	int inode = ret.st_ino;

	
	char* type;
	if(S_ISREG(ret.st_mode)){
		type = "regular";
	}
	else if (S_ISDIR(ret.st_mode))	{
		type = "directory";
	}
	else if(S_ISLNK(ret.st_mode)){
		type = "symlink";
	}
	char* last_acc = ctime(&ret.st_atim.tv_sec);

	printf("  File:\t%s\nMajor:\t%d\tMinor:\t%d\nInode:\t%d\nType:\t%s\nLast access:\t%s"
			,filename, major, minor, inode, type, last_acc);

	return 0;
}
