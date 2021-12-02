//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>



int main(int argc, char * argv[]){

    printf("PID:\t%d\nPPID:\t%d\nGID:\t%d\nSID:\t%d\n",
                getpid(),getppid(),getgid(),getsid(getpid()));

    struct rlimit limit;
    getrlimit(RLIMIT_NOFILE, &limit);
    printf("Max number of allowed open files: %d\n",limit.rlim_cur);

    char aux[256];
    getcwd(&aux, 256);
    printf("CWD: %s\n", aux);

    return 0;
}