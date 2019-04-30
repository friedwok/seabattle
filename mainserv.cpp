#include<cstdio>
#include<cstring>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstdlib>
#include<sys/types.h>
#include<unistd.h>
#include "game_info.h"
#include "handler.h"


struct field_info field;

int main(int argc, char **argv)
{
	int ls, port, dscr_came, opt = 1, rs;
	char tmp_buffer[256];

	field.players_connected = 0;
	field.players_count = 2;
	struct sockaddr_in addr;
	struct sockaddr addr_for_accept;
	socklen_t addrlen = sizeof(struct sockaddr);
	clients *head = NULL, *tmp, *last;

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

	ls = socket(AF_INET, SOCK_STREAM, 0);
	if(ls == -1) {
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	setsockopt(ls, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if(0 != bind(ls, (struct sockaddr*)&addr, sizeof(addr))) {
		perror("bind");
		exit(1);
	}

	if(-1 == listen(ls, 5)) {
		perror("listen");
		exit(1);
	}

	head = new clients;
	head->next = NULL;
	last = head;
	tmp = head;
	field.head = head;

	for(;;) {
		fd_set readfds;
		//at first, maximum length - length of listen socket
		int max_d = ls;
		//clear the set
		FD_ZERO(&readfds);
		FD_SET(ls, &readfds);
		int fd;
		//do a cycle on client sockets
		tmp = head;
		for(fd = head->dscr; tmp->next != NULL; tmp = tmp->next) {
			//fd - import regular client descriptor
			fd = tmp->next->dscr;
			FD_SET(fd, &readfds);
			//checking maximum
			if(fd > max_d)
				max_d = fd;
		}
		int res = select(max_d+1, &readfds, NULL, NULL, NULL);
		if(res < 1) {
			perror("select");
		}

		if(FD_ISSET(ls, &readfds)) {
			dscr_came = accept(ls, &addr_for_accept, &addrlen);
			if(dscr_came < 0) {
				perror("accept");
				exit(1);
			}
			field.players_connected++;
 			handle_accepted_player(head, &last, &field, dscr_came);
		}

		//now iterate through all client descriptors
		tmp = head;
		for(fd = head->dscr; tmp->next != NULL; tmp = tmp->next) {
			fd = tmp->next->dscr;
			if(FD_ISSET(fd, &readfds)) {
				//send data from client with socket fd
				//read and handle it
				rs = read(fd, tmp_buffer, sizeof(tmp_buffer)-1);
				if(rs == -1) {
					perror("read");
					exit(1);
				}
				tmp_buffer[rs] = '\0';
				handle(tmp_buffer, rs, fd, &field, &last);
				if(tmp->next == NULL)
					break;
				//here should be func for if player alone - win
			}
		}
		//end of main cycle, next iteration
	}
	return 0;
}
