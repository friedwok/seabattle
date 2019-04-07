#ifndef FILL_THE_FIELD_H_SENTRY
#define FILL_THE_FIELD_H_SENTRY

enum State { four, three, two, one, end };

void make_fleet(int ls);

void print_invite(State st);

void printmsg(const char *msg1, const char *msg2);

void remake_command(char *buffer, int size, int ls);

void make_command_to_send(char *buf, int size, int ls);

void handle_buf_servin(State *st, struct ships_num *ships, char *buf_for_servin);

#endif
