#include <time.h>
#include <stdio.h>


int main(){
	time_t t = time(NULL);
	printf("Year: %d\n", localtime(&t)->tm_year + 1900);
	return 0;
}

