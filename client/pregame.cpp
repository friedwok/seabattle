#include<stdio.h>
#include<cstdlib>
#include<sys/types.h>
#include<unistd.h>
#include "pregame.h"

void check_buf(int *buf, int *fl, int *player_num, int& pl_num_flag)
{
	fflush(stdout);
	if(buf[0] > buf[1]) {
		printf("The game has been started\n");
		*fl = 2;
	} else {
		if(!pl_num_flag) {
			*player_num = buf[0];
			pl_num_flag = 1;
		}
		printf("Connected players: %d/%d\n", buf[0], buf[1]);
		if(buf[0] == buf[1])
			*fl = 1;
	}
}

void pre_game(int ls, int *pl_num, int *fl)
{
	int rs;
	fd_set readfds;
	int buf[2], pl_num_flag = 0;

	while(!(*fl)) {
		FD_ZERO(&readfds);
		FD_SET(0, &readfds);
		FD_SET(ls, &readfds);
		select(ls+1, &readfds, NULL, NULL, NULL);
		if(FD_ISSET(ls, &readfds)) {
			rs = read(ls, buf, sizeof(buf));
			if(rs == -1) {
				perror("read");
				exit(1);
			}
			check_buf(buf, fl, pl_num, pl_num_flag);
		}
	}
}
