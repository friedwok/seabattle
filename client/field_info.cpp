#ifndef FIELD_INFO_H_SENTRY
#define FIELD_INFO_H_SENTRY

#include<stdio.h>
#define F_LENGTH 10
#define F_WIDTH 10

class Field;
class Ship;

class Field {
	int f_info[F_LENGTH][F_WIDTH];
	//static int num_of_ships;
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
	Ships *first;
	struct Ships_count s_count;

	Field()
	{
		for(int i = 0; i < F_LENGTH; i++) {
			for(int j = 0; j < F_WIDTH; j++) {
				f_info[i][j] = 0;
			}
		}

		//num_of_ships = 0;
		first = NULL;
		s_count.ships4 = 0;
		s_count.ships3 = 0;
		s_count.ships2 = 0;
		s_count.ships1 = 0;
	}

	void put_ship_to_field(char *msg);

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

//void Field::put_ship_to_field

class Ship {
	int size;
	int x1, y1;
	int x2, y2;
public:
	Ship(char *msg)
	{
		x1 = msg[0] - 'A';
		y1 = msg[1] - '1';
		x2 = msg[2] - 'A';
		y2 = msg[3] - '1';
		if(x1 == x2) {
			size = y2 - y1;
		} else {
			size = x2 - x1;
		}
	}
};

/*
class Ship {
	int size;
	int num_of_ships;
	int ships_count;
public:
	Ship(int size_s, int num_of_ships_s)
	{
		size = size_s;
		num_of_ships = num_of_ships_s;
		ships_count = 0;
	}
	virtual ~Ship() {}
	virtual void f() = 0;
};

class Ship4 : Ship {
	int x1, y1;
	int x2, y2;
public:
	Ship4(int x1_l, int y1_l, int x2_w, int y2_w)
		: Ship(4, 1)
	{
		x1 = x1_l;
		y1 = y1_l;
		x2 = x2_w;
		y2 = y2_w;
	}

	virtual ~Ship4() {}
	virtual void f() {}
};

int Ship::ships_count = 0;

class Ship3 : Ship {
	int x1, y1;
	int x2, y2;
public:
	Ship3(int x1_l, int y1_l, int x2_w, int y2_w)
		: Ship(3, 2)
	{
		x1 = x1_l;
		y1 = y1_l;
		x2 = x2_w;
		y2 = y2_w;
	}

	virtual ~Ship3() {}
	virtual void f() {}
};

class Ship2 : Ship {
	int x1, y1;
	int x2, y2;
public:
	Ship2(int x1_l, int y1_l, int x2_w, int y2_w)
		: Ship(2, 3)
	{
		x1 = x1_l;
		y1 = y1_l;
		x2 = x2_w;
		y2 = y2_w;
	}

	virtual ~Ship2() {}
	virtual void f() {}
};

class Ship1 : Ship {
	int x1, y1;
	int x2, y2;
public:
	Ship1(int x1_l, int y1_l, int x2_w, int y2_w)
		: Ship(1, 4)
	{
		x1 = x1_l;
		y1 = y1_l;
		x2 = x2_w;
		y2 = y2_w;
	}
};
*/

#endif
