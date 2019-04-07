#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	char *str1, *str2;
	int r;

	srand(time(NULL));
	str1 = new char[37];
	str2 = new char[37];
	for(int j = 0; j < 10; j++) {
		for(int i = 0; i < 37; i++) {
			if(i % 4 == 0) {
				str1[i] = '+';
				str2[i] = '|';
			} else {
				str1[i] = '-';
				str2[i] = ' ';
			}
			/*
			if(((i+2) % 4 == 0)&&(i > 6)&&(i < 25)){
				str2[i] = '*';
			}
			if(((i+2) % 4 == 0)&&((i <= 6)||(i >= 25))) {
				str2[i] = '.';
			}*/
			r =0 + (int)(9.0*rand()/(RAND_MAX+1.0));
			if((i-2) % 4 == 0) {
				str2[2+r*4] = '*';
			}
		}

		printf("%s\n", str1);
		printf("%s\n", str2);
	}
	printf("%s\n", str1);
	return 0;
}
