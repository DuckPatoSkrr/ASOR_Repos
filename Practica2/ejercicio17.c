//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

	if(argc != 2){
		printf("Usage: ./ejercicio15 <DIR>\n");
		return 1;
	}
	
	DIR *d;
	d = opendir(argv[1]);	
	if(!d){
		perror("opendir call failed");
		return -1;
	}

	struct dirent *entrada;
	struct stat stats;
	long int tamFiles = 0;
	
	entrada = readdir(d);

	char path[256];
	char aux[256];
	while(entrada){
	
		strcpy(path, argv[1]);
		strcat(path, "/");
		strcat(path, entrada->d_name);
		strcat(path, "\0");
	
		if(stat(path, &stats) == -1){
			perror("stat call failed");
			return -1;
		}
		
		
		if(stats.st_mode & S_IFREG){

		}
		else if(stats.st_mode & S_IFLNK){
			strcat(path,"->");
			readlink(argv[1],aux,256);
			strcat(path,aux);
		}
		else if(stats.st_mode & S_IXUSR){
			strcat(path,"*");
		}
		else if(stats.st_mode & S_IFDIR){
			strcat(path,"/");
		}
			
		printf("%s\n",path);
		tamFiles += stats.st_size;
		entrada = readdir(d);
	}
	
	printf("Size: %ld kbytes.\n", tamFiles/1024);
	closedir(d);
	
	return 0;
}

