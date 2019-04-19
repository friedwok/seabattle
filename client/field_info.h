#ifndef FIELD_INFO_H_SENTRY
#define FIELD_INFO_H_SENTRY

#include "fill_the_field.h"
#include "wordtest.h"
#define F_LENGTH 10
#define F_WIDTH 10

class Field;

class Ship {
	int size;
	int x1, y1;
	int x2, y2;
public:
	Ship(const char *msg);
	friend class Field;
	friend int check_crossing_and_back(const char*);
	friend class Check;
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

	Field();
	void put_ship_to_field(const char *msg);
	void field_print();
	void hit(const char *msg, char *buf_to_send);
	int check_ship_killed(int x, int y);
	friend int check_cell(int, int);
	friend void handle_hit(const char *buf);
	friend class Check;
	~Field();
};

#endif
