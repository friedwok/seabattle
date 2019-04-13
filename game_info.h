#ifndef GAMEINFO_H_SENTRY
#define GAMEINFO_H_SENTRY
#include "field_info.h"

extern int game_started;

typedef struct clientlist {
	int dscr;
	int player_num;
	Field *my_field;
	Field *enemy_field;
	struct clientlist *next;
} clients;

struct field_info {
	struct clientlist *head;
	int players_connected;
	int players_count;
};

#endif
