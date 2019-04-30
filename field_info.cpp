#include<stdio.h>
#include<cstdlib>
#include<time.h>
#include "field_info.h"

Ship::Ship(const char *msg)
{
	x1 = msg[0] - 'A';
	y1 = msg[1] - '0';
	x2 = msg[2] - 'A';
	y2 = msg[3] - '0';
	if(x1 == x2) {
		size = abs(y2 - y1) + 1;
	} else {
		size = abs(x2 - x1) + 1;
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

void Field::hit(const char *msg, char *buf_to_send)
{
	int x, y;
	x = msg[0] - 'A';
	y = msg[1] - '0';
	if(f_info[x][y] == 1) {
		f_info[x][y] = 2;
		int res = this->check_ship_killed(x, y);
		if(!res) {
			printf("Error in code\n");
			exit(1);
		}
		buf_to_send[0] = res;
		if(first == NULL)
			buf_to_send[0] = 3;
	} else {
		buf_to_send[0] = 0;
	}
	buf_to_send[1] = msg[0];
	buf_to_send[2] = msg[1];
}

int Field::check_ship_killed(int x, int y)
{
	Ships *s_tmp = first;
	int fl = 0;
	while(s_tmp != NULL) {
		if(s_tmp->ship->x1 == s_tmp->ship->x2) {
			int y_tmp;
			s_tmp->ship->y1 > s_tmp->ship->y2 ? y_tmp = s_tmp->ship->y2 : y_tmp = s_tmp->ship->y1;
			for(int i = 0; i < s_tmp->ship->size; i++) {
				if((s_tmp->ship->x1 == x)&&(y_tmp + i == y)) {
					fl = 1;
					break;
				}
					
			}
			if(fl) {
				for(int i = 0; i < s_tmp->ship->size; i++) {
					if(f_info[s_tmp->ship->x1][y_tmp+i] == 1)
						return 1;
				}
				this->remove_ship(s_tmp);
				return 2;
			}
		} else {
			int x_tmp;
			s_tmp->ship->x1 > s_tmp->ship->x2 ? x_tmp = s_tmp->ship->x2 : x_tmp = s_tmp->ship->x1;
			for(int i = 0; i < s_tmp->ship->size; i++) {
				if((x_tmp + i == x)&&(s_tmp->ship->y1 == y)) {
					fl = 1;
					break;
				}
			}
			if(fl) {
				for(int i = 0; i < s_tmp->ship->size; i++) {
					if(f_info[x_tmp+i][s_tmp->ship->y1] == 1)
						return 1;
				}
				this->remove_ship(s_tmp);
				return 2;
			}
		}
		s_tmp = s_tmp->next;
	}
	return 0;
}

void Field::remove_ship(Ships *ship_to_delete)
{
	Ships *s_tmp = first, *s_del;
	if(first == ship_to_delete) {
		first = first->next;
		delete s_tmp->ship;
		delete s_tmp;
		return;
	}
	while(s_tmp->next != NULL) {
		if(s_tmp->next == ship_to_delete) {
			s_del = s_tmp->next;
			s_tmp->next = s_tmp->next->next;
			delete s_del->ship;
			delete s_del;
			return;
		}
		s_tmp = s_tmp->next;
	}
	printf("Error in remove\n");
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
							if(f_info[(i-offset)/4][j-1] == 2) {
								str2[i] = 'x';
							} else if(f_info[(i-offset)/4][j-1] == 1) {
								str2[i] = '.';
							} else {
								str2[i] = ' ';
							}
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
						str2[i] = '0' + j - 1;
					} else {
						str1[i] = '-';
						str2[i] = ' ';
					}
				} else {
					str1[i] = ' ';
					str2[i] = ' ';
				}
			}
		}
		printf("%s\n", str1);
		printf("%s\n", str2);
	}
	printf("%s\n", str1);
}
