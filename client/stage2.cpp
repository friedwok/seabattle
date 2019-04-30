#include<stdio.h>
#include<cstdlib>
#include<cctype>
#include<unistd.h>
#include "stage2.h"
#include "field_info.h"
#include "fill_the_field.h"

Field f_enemy;
extern Field field;

void hit_again(char *buffer, int size, int ls)
{
	int r;
	printf(">");
	fflush(stdout);
	r = read(0, buffer, size - 1);
	if(r == -1) {
		perror("read");
		exit(1);
	}
	buffer[r] = 0;
	hit_the_ship(buffer, size, ls);
}

void hit_the_ship(char *buf, int size, int ls)
{
	int words_count = 0, sym_count = 0;
	char msg_send[3];

	msg_send[2] = 0;
	words_count = Check::words_count(buf, size);
	for(int i = 0; i < size; i++) {
		if(!std::isspace(buf[i])) {
			msg_send[sym_count] = buf[i];
			if(msg_send[sym_count] == 0) {
				break;
			}
			sym_count++;
			if(sym_count > 2) {
				printf("Invalid command\n");
				hit_again(buf, size, ls);
				return;
			}
		}
	}

	//printf("msgsend = %s\n", msg_send);

	if(check_msg(buf, size, msg_send, ls, words_count, sym_count)) {
		return;
	} else {
		write(ls, msg_send, sizeof(msg_send));
	}
}

int check_msg(char *buf, int size_buf, char *msg_send, int ls, int words_count, int sym_count)
{
	int k = 0;
	if((words_count != 1)||(sym_count != 2)) {
		printf("Invalid command\n");
	} else if(Check::check_symbols(msg_send, 2)) {
		printf("Invalid characters or sequences\n");
	} else if(f_enemy.f_info[msg_send[0] - 'A'][msg_send[1] - '0']) {
		printf("This point has already been hit\n");
	} else {
		k = 1;
	}

	if(!k) {
		print_invite();
		hit_again(buf, size_buf, ls);
		return 1;
	}

	return 0;
}

void handle_my_hit(const char *buf)
{
	if(buf[0] == 2) {
		printf("Enemy ship killed\n");
		f_enemy.f_info[buf[1] - 'A'][buf[2] - '0'] = 1;
	} else if(buf[0] == 1) {
		printf("Enemy ship hited\n");
		f_enemy.f_info[buf[1] - 'A'][buf[2] - '0'] = 1;
	} else if(buf[0] == 3) {
		printf("You win\n");
		f_enemy.f_info[buf[1] - 'A'][buf[2] - '0'] = 1;
	} else {
		printf("Miss\n");
		f_enemy.f_info[buf[1] - 'A'][buf[2] - '0'] = 2;
	}
	printf("Enemy field:\n");
	f_enemy.field_enemy_print();
	printf("My field:\n");
	field.field_print();
}

void handle_enemy_hit(const char *buf)
{
	if(buf[0] == 2) {
		printf("My ship killed\n");
		field.f_info[buf[1] - 'A'][buf[2] - '0'] = 3;
	} else if(buf[0] == 1) {
		printf("My ship hited\n");
		field.f_info[buf[1] - 'A'][buf[2] - '0'] = 3;
	} else if(buf[0] == 3) {
		printf("You lost\n");
		field.f_info[buf[1] - 'A'][buf[2] - '0'] = 3;
	} else {
		printf("Miss\n");
		field.f_info[buf[1] - 'A'][buf[2] - '0'] = 2;
	}
	printf("Enemy field:\n");
	f_enemy.field_enemy_print();
	printf("My field\n");
	field.field_print();
}
