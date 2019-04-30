#ifndef TESTFILL_H_SENTRY
#define TESTFILL_H_SENTRY

enum State { waiting = 5, four = 4, three = 3, two = 2, one = 1, end = 0 };

void make_fleet_test(int ls);

void print_invite();

void printmsg(const char *msg1, const char *msg2);

void remake_command(char *buffer, int size, int ls);

void make_command_to_send(char *buf, int size, int ls);

int check_message(char *buf, int size_buf, char *msg_send, int ls, int words_count);

int check_symbols(const char *msg_send);

int check_length(const char *msg_send);

int check_crossing_and_back(const char *msg_send);

int check_cell(int x, int y);

void handle_buf_servin_test(struct ships_num1 *ships, char *buf_for_servin);

#endif
