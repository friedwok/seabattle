#include<stdio.h>
#include<cstdlib>
#include<cctype>
#include "wordtest.h"
#include "fill_the_field.h"
//#include "testfill.h"
#include "field_info.h"

extern State st;
extern Field field;

//general functions
int Check::words_count(const char *buf, const int size)
{
	int words_count = 0, fl = 0;

	for(int i = 0; i < size; i++) {
		if((!std::isspace(buf[i]))&&(!fl)&&(buf[i] != 0)) {
			words_count++;
			fl = 1;
		} else if(std::isspace(buf[i])) {
			fl = 0;
		}
		if(buf[i] == 0) {
			break;
		}
	}

	return words_count;
}

int Check::check_symbols(const char *msg_send, const int msg_size)
{
	for(int i = 0; i < msg_size; i++) {
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

//functions for checking at the stage of filling the field
int Check::check_length_f(const char *msg_send)
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

int Check::check_crossing_and_back_f(const char *msg_send)
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

int Check::check_cell(int x, int y)
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

	
