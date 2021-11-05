#include <time.h>
#include <stdio.h>


int main(){
	time_t t = time(NULL);
	printf("%s", asctime(localtime(&t)));
	return 0;
}

