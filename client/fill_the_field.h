#ifndef FILL_THE_FIELD_H_SENTRY
#define FILL_THE_FIELD_H_SENTRY

enum State { four = 4, three = 3, two = 2, one = 1, end = 0 };

void make_fleet(int ls);

void print_invite();

void printmsg(const char *msg1, const char *msg2);

void remake_command(char *buffer, int size, int ls);

void make_command_to_send(char *buf, int size, int ls);

void handle_buf_servin(struct ships_num *ships, char *buf_for_servin);

int check_message(char *buf, int size_buf, char *msg_send, int ls, int words_count, int sym_count);

int check_length(char *msg_send);

#endif
