#include<stdio.h>
#include<cstdlib>
#include<sys/types.h>
#include<unistd.h>
#include<cctype>
#include "field_info.h"
#include "fill_the_field.h"

struct ships_num {
	int ships4;
	int ships3;
	int ships2;
	int ships1;
};

Field field;

const char msg4[64] = "Enter the coordinates of the ships of 4 cells\n";
const char msg3[64] = "Enter the coordinates of the ships of 3 cells\n";
const char msg2[64] = "Enter the coordinates of the ships the size of two cells\n";
const char msg1[64] = "Enter the coordinates of the ships the size of one cell\n";
const char msg[64] = "For example: B4 E4\n";
State st = four;

void make_fleet(int ls)
{
	fd_set readfds;
	int r = 0;
	struct ships_num ships = { .ships4 = 0, .ships3 = 0, .ships2 = 0, .ships1 = 0 };
	char buf_for_stdin[256];
	char buf_for_servin[256];

	while(st != end) {
		print_invite();
		FD_ZERO(&readfds);
		FD_SET(0, &readfds);
		FD_SET(ls, &readfds);
		select(ls+1, &readfds, NULL, NULL, NULL);
		if(FD_ISSET(0, &readfds)) {
			r = read(0, buf_for_stdin, sizeof(buf_for_stdin)-1);
			if(r == -1) {
				perror("read");
				exit(1);
			}
			printf("r = %d\n", r);
			buf_for_stdin[r] = 0;
			if(st != waiting) {
				make_command_to_send(buf_for_stdin, sizeof(buf_for_stdin), ls);
			} else {
				printf("Not all players are ready\n");
			}
		}

		if(FD_ISSET(ls, &readfds)) {
			r = read(ls, buf_for_servin, sizeof(buf_for_servin)-1);
			if(r == -1) {
				perror("read");
				exit(1);
			}
			buf_for_servin[r] = 0;
			if(!r) {
				printf("Server crashed\n");
				exit(0);
			}
			printf("%s", buf_for_servin + 1);
			handle_buf_servin(&ships, buf_for_servin);
		}
	}
}

void print_invite()
{
	switch(st)
	{
		case four :
			printmsg(msg4, msg);
			printf(">");
			fflush(stdout);
			break;
		case three : printmsg(msg3, ">"); break;
		case two : printmsg(msg2, ">"); break;
		case one : printmsg(msg1, ">"); break;
		default : break;
	}
	fflush(stdout);
}

void printmsg(const char *msg1, const char *msg2)
{
	printf("%s%s", msg1, msg2);
	fflush(stdout);
}

void remake_command(char *buffer, int size, int ls)
{
	int r;
	r = read(0, buffer, size - 1);
	if(r == -1) {
		perror("read");
		exit(1);
	}
	buffer[r] = 0;
	make_command_to_send(buffer, size, ls);
}

void make_command_to_send(char *buf, int size, int ls)
{
	int words_count = 0, fl = 0, sym_count = 0;
	char msg_send[5];

	msg_send[4] = 0;
	for(int i = 0; i < size; i++) {
		if((!std::isspace(buf[i]))&&(!fl)&&(buf[i] != 0)) {
			words_count++;
			fl = 1;
		} else if(std::isspace(buf[i])) {
			fl = 0;
		}

		if(!std::isspace(buf[i])) {
			msg_send[sym_count] = buf[i];
			printf("%c\n", buf[i]);
			if(msg_send[sym_count] == 0)
				break;
			sym_count++;
			if(sym_count > 4) {
				printf("Invalid command\n");
				remake_command(buf, size, ls);
				return;
			}
		}
	}

	printf("msgsend = %s\n", msg_send);
	/*if((words_count != 2)||(sym_count != 4)) {
		printf("Invalid command\n");
		remake_command(buf, size, ls);
		return;
	} else if((msg_send[0] != msg_send[2])&&(msg_send[1] != msg_send[3])) {
		printf("The ship can only stand parallel to the axes\n");
		remake_command(buf, size, ls);
	//} else if(check_other)) { length, crossing, back to back
	} else {
		field.put_ship_to_field(msg_send); 
		write(ls, msg_send, sizeof(msg_send));
	}*/
	if(check_message(buf, size, msg_send, ls, words_count, sym_count)) {
		return;
	} else {
		field.put_ship_to_field(msg_send);
		write(ls, msg_send, sizeof(msg_send));
	}
}

int check_message(char *buf, int size_buf, char *msg_send, int ls, int words_count, int sym_count)
{
	int k = 0;
	if((words_count != 2)||(sym_count != 4)) {
		printf("Invalid command\n");
		//remake_command(buf, size_buf, ls);
		//return 1;
	} else if((msg_send[0] != msg_send[2])&&(msg_send[1] != msg_send[3])) {
		printf("The ship can only stand parallel to the axes\n");
	//} else if(check_symbols(msg_send)) {
	} else if(Check::check_symbols(msg_send, 4)) {
		printf("Invalid characters or sequences\n");
	} else if(Check::check_length_f(msg_send)) {
		printf("Wrong length\n");
		//remake_command(buf, size_buf, ls);
		//return 1;
	} else if(Check::check_crossing_and_back_f(msg_send)) {
		printf("The ship must not cross another or stay back to back\n");
	} else {
		k = 1;
	}

	if(!k) {
		print_invite();
		remake_command(buf, size_buf, ls);
		return 1;
	}
	return 0;
}
/*
int check_symbols(const char *msg_send)
{
	for(int i = 0; i < 4; i++) {
		if(i % 2 == 0) {
			if((msg_send[i] < 'A')||(msg_send[i] > 'Z'))
				return 1;
		} else {
			if((msg_send[i] < '0')||(msg_send[i] > '9'))
				return 1;
		}
	}

	return 0;
}

int check_length(const char *msg_send)
{
	int length;
	int state_int = static_cast<int>(st);
	if(msg_send[0] == msg_send[2]) {
		length = abs(msg_send[3] - msg_send[1]) + 1;
	} else {
		length = abs(msg_send[2] - msg_send[0]) + 1;
	}

	if(length != state_int)
		return 1;

	return 0;
}

int check_crossing_and_back(const char *msg_send)
{
	int x, y;
	Ship tmp_ship(msg_send);

	tmp_ship.y1 < tmp_ship.y2 ? y = tmp_ship.y1 : y = tmp_ship.y2;
	tmp_ship.x1 < tmp_ship.x2 ? x = tmp_ship.x1 : x = tmp_ship.x2;
	if(tmp_ship.x1 == tmp_ship.x2) {
		for(int i = 0; i < tmp_ship.size; i++) {
			if(check_cell(tmp_ship.x1, y+i))
				return 1;
		}
	} else {
		for(int i = 0; i < tmp_ship.size; i++) {
			if(check_cell(x+i, tmp_ship.y1))
				return 1;
		}
	}
	return 0;
}

int check_cell(int x, int y)
{
	for(int i = -1; i <= 1; i++) {
		for(int j = -1; j <= 1; j++) {
			if((x+i >= 0)&&(y+j >= 0)&&(x+i <= 9)&&(y+j <= 9)) {
				if(field.f_info[x+i][y+j])
					return 1;
			}
		}
	}
	return 0;
}
*/
/*
int check_length(const char *msg_send)
{
	int length;
	int state_int = static_cast<int>(st);

	if(msg_send[0] == msg_send[2]) {
		length = abs(msg_send[3] - msg_send[1]) + 1;
	} else {
		length = abs(msg_send[2] - msg_send[0]) + 1;
	}

	if(length != state_int)
		return 1;
	return 0;
}
*/
void handle_buf_servin(struct ships_num *ships, char *buf_for_servin)
{
	printf("servin\n");
	if(buf_for_servin[0] == '1') {
		switch(st) {
			case four:
				ships->ships4++;
				st = three;
				printf("four = %d\n", ships->ships4);
				break;
			case three:
				ships->ships3++;
				printf("three = %d\n", ships->ships3);
				if(ships->ships3 == 2)
					st = two;
				break;
			case two:
				ships->ships2++;
				if(ships->ships2 == 3)
					st = one;
				break;
			case one:
				ships->ships1++;
				if(ships->ships1 == 4)
					st = waiting;
			default:
				break;
		}
	} else if(buf_for_servin[0] == '3') {
		st = end;
	}
	field.field_print();
}
