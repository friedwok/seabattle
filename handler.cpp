#include<stdio.h>
#include<cstdlib>
#include "game_info.h"
#include "handler.h"
#include<sys/socket.h>
#include<unistd.h>

void alarm_players(struct field_info *field)
{
	clients *tmp;
	tmp = field->head;
	int buf[2];

	buf[0] = field->players_connected;
	buf[1] = field->players_count;
	while(tmp->next != NULL) {
		write(tmp->next->dscr, buf, sizeof(buf));
		tmp = tmp->next;
	}
}


void handle_accepted_player(clients *head, clients **last, struct field_info *field, int dscr)
{
	printf("zxcsa\n");
	int buf[2];
	clients *tmp;

	if(field->players_connected == field->players_count) {
			game_started = 1;
	}
	printf("jopf\n");
	if(field->players_connected > field->players_count) {
		buf[0] = field->players_connected;
		buf[1] = field->players_count;
		write(dscr, buf, sizeof(buf));
		(field->players_connected)--;
		shutdown(dscr, 2);
		close(dscr);
	} else {
		tmp = new clients;;
		tmp->player_num = field->players_connected;
		tmp->dscr = dscr;
		tmp->next = NULL;
		printf("plnum = %d\n", tmp->player_num);
		(*last)->next = tmp;
		(*last) = (*last)->next;
		alarm_players(field);
	}
}
