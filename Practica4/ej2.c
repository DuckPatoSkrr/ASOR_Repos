//VENTURA MATEOS PEREZ
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void hijo(int rd, int wr){

    int cont = 0;
   	char* msg = malloc(sizeof(char)*255);

    while(cont < 10){
        
        read(rd, msg, 255);
        printf("Son: Father says: %s\n", msg);
        
        ++cont;
        
        if(cont < 10)
            write(wr, "l", 2);
    }
    
    write(wr, "q", 2);
    printf("Son: finished\n");
    
    free(msg);
    close(rd);
    close(wr);
}

void padre(int rd, int wr){
    char* msg = malloc(sizeof(char)*255);

    while(msg != "q"){
    
        printf("Father: Write msg: ");
        scanf("%s", msg);
        
        write(wr, msg, 255);
        read(rd, msg, 255);
    }
    
    free(msg);
    close(rd);
    close(wr);
}

int main(){

	char* msg = malloc(sizeof(char)*255);
	char* confirmation = malloc(sizeof(char)*255);
		
	int p_h[2];
	int h_p[2];
	
	if(pipe(p_h) == -1){
		perror("pipe call failed");
		return -1;
	}
	
	if(pipe(h_p) == -1){
		perror("pipe call failed");
		return -1;
	}

	
	switch (fork()) {
	
	case -1:
		perror("fork call failed");
		exit(1);
		
	case 0:
        close(p_h[1]);
        close(h_p[0]);
        hijo(p_h[0],h_p[1]);
	
		break;
		
	default:
		
		close(p_h[0]);
		close(h_p[1]);
		
		padre(h_p[0],p_h[1]);
		
		break;
	}
	return 0;
}