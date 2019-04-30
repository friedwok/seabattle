#include<stdio.h>
#include<cstdlib>
#include<sys/types.h>
#include<unistd.h>
#include "startgame.h"
#include "fill_the_field.h"
#include "stage2.h"
//#include "testfill.h"

void start_the_game(int ls, int& fl, int player_num)
{
	fd_set readfds;
	int r = 0, turn;
	char buffer_for_stdin[64];
	char buffer_for_servin[256];
	const char msg[64] = "Enter the coordinates to hit the ship\n";

	player_num == 1 ? turn = 1 : turn = 0;
	if(fl == 2)
		exit(0);
	make_fleet(ls);
	printf("%s", msg);
	for(;;) {
		FD_ZERO(&readfds);
		FD_SET(0, &readfds);
		FD_SET(ls, &readfds);
		printf(">");
		fflush(stdout);
		select(ls+1, &readfds, NULL, NULL, NULL);
		if(FD_ISSET(0, &readfds)) {
			r = read(0, buffer_for_stdin, sizeof(buffer_for_stdin)-1);
			if(r == -1) {
				perror("read");
				exit(1);
			}
			buffer_for_stdin[r] = 0;
			if(turn) {
				hit_the_ship(buffer_for_stdin, sizeof(buffer_for_stdin), ls);
			} else {
				printf("Now it's the enemy's turn\n");
			}
		}
		if(FD_ISSET(ls, &readfds)) {
			r = read(ls, buffer_for_servin, sizeof(buffer_for_servin)-1);
			if(r == -1) {
				perror("read");
				exit(1);
			}
			//printf("buf for servin = %s\n", buffer_for_servin + 1);
			buffer_for_servin[r] = 0;
			if(turn) {
				handle_my_hit(buffer_for_servin);
				turn = 0;
			} else {
				handle_enemy_hit(buffer_for_servin);
				turn = 1;
			}
		}
	}
}
