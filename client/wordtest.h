#ifndef WORDTEST_H_SENTRY
#define WORDTEST_H_SENTRY

class Check {

public:
	//general funtions
	static int words_count(const char *buf, const int size);
	static int check_symbols(const char *msg_send, const int msg_size);
	//functions for checking at the stage of filling the field
	static int check_length_f(const char *msg_send);
	static int check_crossing_and_back_f(const char *msg_send);
	static int check_cell(int x, int y);
};

#endif


