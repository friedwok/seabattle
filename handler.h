#ifndef HANDLER_H_SENTRY
#define HANDLER_H_SENTRY

extern int game_started;

void alarm_players(struct field_info *field);

void handle_accepted_player(clients *head, clients **last, struct field_info *field, int dscr);

#endif
