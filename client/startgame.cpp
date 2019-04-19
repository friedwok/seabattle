#include<stdio.h>
#include<cstdlib>
#include<sys/types.h>
#include<unistd.h>
#include "startgame.h"
#include "fill_the_field.h"
#include "stage2.h"


void start_the_game(int ls, int& fl)
{
	fd_set readfds;
	int r = 0;
	char buffer_for_stdin[128];
	char buffer_for_servin[256];
	const char msg[64] = "Enter the coordinates to hit the ship\n";

	if(fl == 2)
		exit(0);
	make_fleet(ls);
	printf("%s", msg);
	printf(">");
	fflush(stdout);
	for(;;) {
		FD_ZERO(&readfds);
		FD_SET(0, &readfds);
		FD_SET(ls, &readfds);
		select(ls+1, &readfds, NULL, NULL, NULL);
		if(FD_ISSET(0, &readfds)) {
			r = read(0, buffer_for_stdin, sizeof(buffer_for_stdin)-1);
			if(r == -1) {
				perror("read");
				exit(1);
			}
			printf("r = %d\n", r);
			buffer_for_stdin[r] = 0;
			hit_the_ship(buffer_for_stdin, r, ls);
		}
		if(FD_ISSET(ls, &readfds)) {
			r = read(0, buffer_for_servin, sizeof(buffer_for_servin)-1);
			if(r == -1) {
				perror("read");
				exit(1);
			}
			buffer_for_stdin[r] = 0;
			handle_hit(buffer_for_stdin);
		}
	}
}
