#ifndef GAMEINFO_H_SENTRY
#define GAMEINFO_H_SENTRY

extern int game_started;

typedef struct clientlist {
	int dscr;
	struct clientlist *next;
} clients;

struct field_info {
	struct clientlist *head;
	int players_connected;
	int players_count;
};

#endif
