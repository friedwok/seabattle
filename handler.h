#ifndef HANDLER_H_SENTRY
#define HANDLER_H_SENTRY

extern int game_started;

void notify_players_about_disconnect(struct field_info *field, clients *disc_pl);

void alarm_players(struct field_info *field);

void handle_accepted_player(clients *head, clients **last, struct field_info *field, int dscr);

void handle(char *tmp_buffer, int rs, int fd, struct field_info *field, clients **last);

void add_ship(char *tmp_buffer, int rs, int fd, struct field_info *field);

#endif
