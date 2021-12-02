//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){
    if(argc != 2){
        printf("Usage: \"command [args]\"");
        return -1;
    }
    system(argv[1]);
    printf("Command finished executing\n");

    return 0;
}