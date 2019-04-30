#ifndef STAGE2_H_SENTRY
#define STAGE2_H_SENTRY

void hit_again(char *buffer, int size, int ls);

void hit_the_ship(char *buf, int size, int ls);

int check_msg(char *buf, int size_buf, char *msg_send, int ls, int words_count, int sym_count);

void handle_my_hit(const char *buf);

void handle_enemy_hit(const char *buf);

#endif
