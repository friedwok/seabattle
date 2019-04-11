#ifndef FIELD_INFO_H_SENTRY
#define FIELD_INFO_H_SENTRY

#include<stdio.h>
#include<cstdlib>
#define F_LENGTH 10
#define F_WIDTH 10

class Field;

class Ship {
	int size;
	int x1, y1;
	int x2, y2;
public:
	Ship(const char *msg)
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
	friend class Field;
};

class Field {
	int f_info[F_LENGTH][F_WIDTH];
	struct Ships {
		Ship *ship;
		Ships *next;
	};
	struct Ships_count {
		int ships4;
		int ships3;
		int ships2;
		int ships1;
	};
public:
	Ships *first, *last;
	struct Ships_count s_count;

	Field()
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

	void put_ship_to_field(const char *msg);

	~Field()
	{
		Ships *tmp;
		while(first != NULL) {
			tmp = first;
			first = first->next;
			delete tmp;
		}
	}
};

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

#endif
