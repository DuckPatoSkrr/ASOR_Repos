
int main(int argc, int *argv[]){
	if(argc != 5){
		 printf("Usage: %s <comando1> <argumento1> <comando2> <argumento2>\n", argv[0]);
		return -1;
	}
	
	int fd[2];
	
	
	if(!pipe(fd)){
		perror("pipe");
		return -1;
	}
	
	pid_t pid;
	pid = fork();
	switch (pid) {
		case -1:
			perror(“fork”);
			exit(1);
		case 0: //HIJO
			close(fd[1]);
			dub2(fd[0],0);
			char* comm = malloc(sizeof(char)*255);
            strcpy(comm, argv[3]);
            strcat(comm, " ");
            strcat(comm, argv[4]);
			system(comm);
			close(fd[0]);
			break;
		default:
			close(fd[0]);
			char* comm = malloc(sizeof(char)*255);
            strcpy(comm, argv[1]);
            strcat(comm, " ");
            strcat(comm, argv[2]);
			
			dup2(fd[1], 1);
			system(comm);
			
			close(fd[1]);
			break;
	}

	
	
	
	return 0;
}