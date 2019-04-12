#include<stdio.h>
#include<cstdlib>
#include<time.h>
#include "field_info.h"

//class Field;

Ship::Ship(const char *msg)
{
	x1 = msg[0] - 'A';
	y1 = msg[1] - '1';
	x2 = msg[2] - 'A';
	y2 = msg[3] - '1';
	if(x1 == x2) {
		size = abs(y2 - y1);
	} else {
		size = abs(x2 - x1);
	}
}

Field::Field()
{
	for(int i = 0; i < F_LENGTH; i++) {
		for(int j = 0; j < F_WIDTH; j++) {
			f_info[i][j] = 0;
		}
	}

	first = NULL;
	last = NULL;
	s_count.ships4 = 0;
	s_count.ships3 = 0;
	s_count.ships2 = 0;
	s_count.ships1 = 0;
}

Field::~Field()
{
	Ships *tmp;
	while(first != NULL) {
		tmp = first;
		first = first->next;
		delete tmp->ship;
		delete tmp;
	}
}

void Field::put_ship_to_field(const char *msg)
{
	Ships *ships_tmp = new Ships;
	if(first == NULL) {
		first = ships_tmp;
		last = first;
	} else {
		last->next = ships_tmp;
		last = last->next;
	}
	last->ship = new Ship(msg);
	last->next = NULL;

	if(last->ship->x1 == last->ship->x2) {
		int y;
		last->ship->y1 > last->ship->y2 ? y = last->ship->y2 : y = last->ship->y1;
		for(int i = 0; i < last->ship->size; i++) {
			f_info[last->ship->x1][y+i] = 1;
		}
	} else {
		int x;
		last->ship->x1 > last->ship->x2 ? x = last->ship->x2 : x = last->ship->x1;
		for(int i = 0; i < last->ship->size; i++) {
			f_info[x+i][last->ship->y1] = 1;
		}
	}
}

void Field::field_print()
{
	char *str1, *str2;
	const int offset = 4;

	srand(time(NULL));
	str1 = new char[offset + 41];
	str2 = new char[offset + 41];
	str1[offset + 40] = 0;
	str2[offset + 40] = 0;
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
						if((i - offset) % 4 == 2) {
							f_info[(i-offset)/4][j-1] == 1 ? str2[i] = '.' : str2[i] = ' ';
						}
					}
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
						str2[i] = '0' + i;
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
}
