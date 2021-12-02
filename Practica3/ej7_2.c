//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int main(int argc, char * argv[]){

    char ** arg_vec = (char**)malloc(sizeof(char*) * argc - 1);
    
    int len;
    for(int i = 1; i < argc; ++i){
        arg_vec[i-1] = (char*) malloc(len= strlen(argv[i])+ 1);
        strncpy(arg_vec[i-1],argv[i],len);
    }
    execvp(argv[1],arg_vec);
    printf("Command finished executing\n");

    for(int i = 0; i < argc - 1; ++i){
        free(arg_vec[i]);
    }
    free(arg_vec);

    return 0;
}