#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

int listening_socket;
int client_socket;
int term_socket;

fd_set socks_read;
fd_set socks_write;

static int term_init(uint16_t port) {
	int s;
	int res;
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		return -1;
	}

	res = bind(s, (struct sockaddr *)&addr, sizeof(addr));
	if (res < 0) {
		close(s);
		return -1;
	}

	res = listen(s, 1);
	if (res < 0) {
		close(s);
		return -1;
	}

	FD_ZERO(&socks_read);
	FD_ZERO(&socks_write);

	listening_socket = s;
	client_socket = -1;
	return 0;
}

char cli_buf[128];
char term_buf[128];

static int term_process() {
	int res;
	int ret = 0;
	int maxfd = listening_socket;
	struct timeval tv;
	struct sockaddr_in cli_sa;
	socklen_t cli_sa_len;
	if (client_socket != -1) {
		FD_SET(client_socket, &socks_read);
		maxfd = MAX(maxfd, client_socket);
	}
	if (term_socket != -1) {
		FD_SET(term_socket, &socks_read);
		maxfd = MAX(maxfd, term_socket);
	}
	FD_SET(listening_socket, &socks_read);
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	res = select(maxfd + 1, &socks_read, &socks_write, NULL, &tv);
	printf("select done %d\n", res);
	if (FD_ISSET(listening_socket, &socks_read)) {
		cli_sa_len = sizeof(cli_sa);
		client_socket = accept(listening_socket, (struct sockaddr *)&cli_sa, &cli_sa_len);
		FD_CLR(listening_socket, &socks_read);
		printf("accepted\n");
	}
	if (FD_ISSET(client_socket, &socks_read)) {
		res = recv(client_socket, cli_buf, 128, 0);
		if (res > 0) {
			printf("read %d\n", res);
		} else
		if (res == 0) {
			close(client_socket);
			client_socket = -1;
			printf("client disconnected\n");
		} else {
			ret = -1;
		}
		FD_CLR(client_socket, &socks_read);
	}
	if (FD_ISSET(term_socket, &socks_read)) {
		//res = recv(term_socket, term_buf, 128, 0);
		res = read(term_socket, term_buf, 128);
		if (res > 0) {
			printf("read %d\n", res);
		} else
		if (res == 0) {
			close(term_socket);
			term_socket = -1;
		} else {
			printf("err %d\n", errno);
			ret = -1;
		}
		FD_CLR(term_socket, &socks_read);
	}
	return ret;
}

int main(int argc, char *argv[]) {
	term_socket = 0;
	term_init(5000);
	while (term_process() == 0) {
	}
	return 0;
}

