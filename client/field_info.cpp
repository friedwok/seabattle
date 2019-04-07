#include<stdio.h>
#include "field_info.h"

class Field {
	int f_info[F_LENGTH][F_WIDTH];
public:
	Field()
	{
		for(int i = 0; i < F_LENGTH; i++) {
			for(int j = 0; j < F_WIDTH; j++) {
				f_info[i][j] = 0;
			}
		}
	}

	//void add_ship(Ship& ship);
};

class Ship {
	static int size;
	static int num_of_ships;
	static int ships_count;
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
