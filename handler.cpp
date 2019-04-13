/* format while filling the field
	example of a ship 3 cells long - C3C5
*/

#include<stdio.h>
#include<cstdlib>
#include<cstring>
#include "game_info.h"
#include "handler.h"
#include<sys/socket.h>
#include<unistd.h>
#include "field_info.h"

void notify_players_about_disconnect(struct field_info *field, clients *disc_pl)
{
	clients *tmp = field->head;
	int buf[2];

	printf("con = %d\n", field->players_connected);
	if(field->players_connected == 0) {
		printf("All disconnected\n");
		return;
	}
	if(!game_started) {
		buf[0] = field->players_connected;
		buf[1] = field->players_count;
		while(tmp->next != NULL) {
			tmp = tmp->next;
			write(tmp->dscr, buf, sizeof(buf));
		}
	}
}

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
		printf("alarm\n");
	}
	//printf("alarm\n");
}


void handle_accepted_player(clients *head, clients **last, struct field_info *field, int dscr)
{
	printf("zxcsa\n");
	int buf[2];
	clients *tmp;
	//const char *message1 = "The game has not started yet\n";

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
		tmp->my_field = new Field;
		tmp->enemy_field = new Field;
		tmp->next = NULL;
		printf("plnum = %d\n", tmp->player_num);
		(*last)->next = tmp;
		(*last) = (*last)->next;
		alarm_players(field);
	}

	tmp = head;
	while(tmp->next != NULL) {
		printf("ds_connected = %d\n", tmp->next->dscr);
		tmp = tmp->next;
	}
	//if(!game_started) {
	//	write(dscr, message1, strlen(message1)+1);
	//	return;
	//}
}

void handle(char *tmp_buffer, int rs, int fd, struct field_info *field, clients **last)
{
	clients *tmp = field->head, *tmp1;

	if(!rs) {
		while(tmp->next->dscr != fd) {
			tmp = tmp->next;
		}
		tmp1 = tmp->next;
		tmp->next = tmp->next->next;
		field->players_connected--;
		notify_players_about_disconnect(field, tmp1);
		if(tmp->next == NULL) {
			*last = tmp;
		}
		free(tmp1);
		shutdown(fd, 2);
		close(fd);
		return;
	}

	switch(game_started) {
		case 1 : add_ship(tmp_buffer, rs, fd, field); break;
		//case 2 : hit_the_ship(tmp_buffer, rs, fd, field); break;
		default: break;
	}
}

void add_ship(char *tmp_buffer, int rs, int fd, struct field_info *field)
{
	clients *tmp = field->head;
	const char msg[128] = "1Ship is installed\n";

	while(tmp->next->dscr != fd) {
		if(tmp->next == NULL) {
			printf("no descriptor in list\n");
			exit(0);
		}
		tmp = tmp->next;
	}
	tmp->next->my_field->put_ship_to_field(tmp_buffer);
	tmp->next->my_field->field_print();
	write(fd, msg, sizeof(msg));
}
