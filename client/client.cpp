#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<cstdlib>
#include<ctype.h>
#include "pregame.h"
#include<unistd.h>

int main(int argc, char **argv)
{
	int ls, port, c, i = 0, player_number, fl = 0;
	struct sockaddr_in addr;
	char *serv_ip, *tmp;

	if(argc < 2) {
		fprintf(stderr, "Program has one argument - number of port\n");
		return 1;
	}

	try {
		int s = sscanf(argv[1], "%d", &port);
		if(!s)
			throw "Wrong parameter";
	} catch(const char *exception) {
		fprintf(stderr, "%s\n", exception);
		return 1;
	}

	printf("Please, input IP address of the server\n");
	c = getchar();
	while(!isspace(c)) {
		if(i == 0) {
			tmp = (char*)malloc(1);
		} else {
			tmp = (char*)realloc(tmp, i+1);
		}
		tmp[i] = c;
		i++;
		c = getchar();
		if(i > 16) {
			printf("false IP\n");
			exit(1);
		}
	}
	tmp = (char*)realloc(tmp,i+1);
	tmp[i] = 0;

	serv_ip = tmp;

	ls = socket(AF_INET, SOCK_STREAM, 0);

	port = 8080;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if(!inet_aton(serv_ip, &(addr.sin_addr))) {
		printf("IP adress is not valid\n");
	}

	if(0 != connect(ls, (struct sockaddr*)&addr, sizeof(addr))) {
		perror("connect");
		exit(1);
	}

	printf("Connection established\n");
	pre_game(ls, &player_number, &fl);
	printf("Your number is %d\n", player_number);
	start_the_game(ls, fl);
	return 0;
}
