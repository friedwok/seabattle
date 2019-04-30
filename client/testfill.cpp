#include<stdio.h>
#include<cstdlib>
#include<sys/types.h>
#include<unistd.h>
#include<cctype>
#include "field_info.h"
#include "testfill.h"
#include<fcntl.h>

struct ships_num1 {
	int ships4;
	int ships3;
	int ships2;
	int ships1;
};

Field field;

const char msg4[64] = "Enter the coordinates of the ships of 4 cells\n";
const char msg3[64] = "Enter 3\n";
const char msg2[64] = "Enter 2\n";
const char msg1[64] = "Enter 1\n";
const char msg[64] = "For ex: B4 E4\n";

State st1 = four;

void make_fleet_test(int ls)
{

	fd_set readfds;
	char arr[40];
	int r = 0, fd;
	struct ships_num1 ships = { .ships4 = 0, .ships3 = 0, .ships2 = 0, .ships1 = 0 };
	char buf_for_stdin[64];
	char buf_for_servin[256];

	fd = open("flist.txt", O_RDWR, 0666);
	if(fd == -1) {
		perror("flist");
		exit(1);
	}
	printf("write go\n");
	scanf("%s", arr);
	printf("%s\n", arr);
	while(st1 != end) {
		print_invite();
		FD_ZERO(&readfds);
		//FD_SET(0, &readfds);
		FD_SET(ls, &readfds);
		r = read(fd, buf_for_stdin, 5);
		if(r == -1) {
			perror("read");
			exit(1);
		}
		printf("r = %d\n", r);
		buf_for_stdin[r] = 0;
		write(1, buf_for_stdin, 5);
		printf("\n");
		if(st1 != waiting) {
			make_command_to_send(buf_for_stdin, sizeof(buf_for_stdin), ls);
		} else {
			printf("Not all\n");
		}

		printf("presele\n");
		select(ls+1, &readfds, NULL, NULL, NULL);
		printf("aftersele\n");
		sleep(1);
		if(FD_ISSET(ls, &readfds)) {
			r = read(ls, buf_for_servin, sizeof(buf_for_servin)-1);
			if(r == -1) {
				perror("read");
				exit(1);
			}
			buf_for_servin[r] = 0;
			if(!r) {
				if(!r) {
					printf("Server crashed\n");
					exit(0);
				}
			}
			printf("%s\n", buf_for_servin + 1);
			handle_buf_servin_test(&ships, buf_for_servin);
		}
	}
}

void print_invite()
{
	switch(st1)
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
	} else if((msg_send[0] != msg_send[2])&&(msg_send[1] != msg_send[3])) {
		printf("The ship can only stand parallel to the axes\n");
	} else if(Check::check_symbols(msg_send, 4)) {
		printf("Invalid characters or sequences\n");
	} else if(Check::check_length_f(msg_send)) {
		printf("Wrond length\n");
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

void handle_buf_servin_test(struct ships_num1 *ships, char *buf_for_servin)
{
	printf("servin\n");
	if(buf_for_servin[0] == '1') {
		switch(st1) {
			case four:
				ships->ships4++;
				st1 = three;
				printf("four = %d\n", ships->ships4);
				break;
			case three:
				ships->ships3++;
				printf("three = %d\n", ships->ships3);
				if(ships->ships3 == 2)
					st1 = two;
				break;
			case two:
				ships->ships2++;
				if(ships->ships2 == 3)
					st1 = one;
				break;
			case one:
				ships->ships1++;
				if(ships->ships1 == 4)
					st1 = waiting;
			default:
				break;
		}
	} else if(buf_for_servin[0] == '3') {
		st1 = end;
	}
	field.field_print();
}
