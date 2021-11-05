#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>



int main(){
	long ret;
	if(ret = pathconf("/",_PC_LINK_MAX) != -1){
		printf("Max links: %d\n",ret);
	}
	if(ret = pathconf("/",_PC_PATH_MAX) != -1){
		printf("Max path: %d\n",ret);
	}
	if(ret = pathconf("/",_PC_NAME_MAX) != -1){
		printf("Max name size: %d\n",ret);
	}
	return 0;
}


