#include<stdio.h>
#include<ctime>
#include<cstdlib>
#include<unistd.h>

int main()
{
	int r = 0;
	srand(time(NULL));
	while(r != 5) {
	r = 1 + (int)(12.0*rand()/(RAND_MAX+1.0));
	printf("r = %d\n", r);
	sleep(1);
	}
	return 0;
}
