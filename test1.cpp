#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	char *str1, *str2;
	const int offset = 4;
	int r;

	srand(time(NULL));
	str1 = new char[offset + 41];
	str2 = new char[offset + 41];
	str1[offset + 41] = 0;
	str2[offset + 41] = 0;
	for(int j = 0; j < 11; j++) {
		for(int i = 0; i < offset + 41; i++) {
			if(i >= offset) {
				if(j > 0) {
					if(i % 4 == 0) {
						str1[i] = '+';
						str2[i] = '|';
					} else {
						str1[i] = '-';
						str2[i] = ' ';
					}
					//r = 0 + (int)(10.0*rand()/(RAND_MAX+1.0));
					//if((i-2) % 4 == 0) {
					//	str2[offset + 2 + r*4] = '*';
					//}
				} else {
					if((i-2) % 4 == 0) {
						str2[i] = 'A' + (i-2)/4 - 1;
					} else if(i % 4 == 0) {
						str2[i] = '|';
					} else {
						str2[i] = ' ';
					}
					str1[i] = ' ';
				}
			} else {
				if(j > 0) {
					if((i+2) % 4 == 0) {
						str1[i] = '-';
						str2[i] = '0' + j;
					} else {
						str1[i] = '-';
						str2[i] = ' ';
					}
				} else {
					str1[i] = ' ';
					str2[i] = ' ';
				}
				if(j == 10) {
					str2[1] = '1';
					str2[2] = '0';
				}
			}
		}
		printf("%s\n", str1);
		printf("%s\n", str2);
	}
	printf("%s\n", str1);
	return 0;
}
