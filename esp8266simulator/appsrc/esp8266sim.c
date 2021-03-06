#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "uart.h"
#include "circularbuffer.h"
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#include "dbg.h"

uart_context_t * uart_ctx;

circularbuffer_t * rd_cb;
circularbuffer_t * wr_cb;

fd_set fd_read;
fd_set fd_write;

ssize_t perform_read(int fd, circularbuffer_t * cb) {
	size_t to_read;
	ssize_t readed;
	to_read = cb_freeafterhead(cb);
	if (to_read == 0) {
		return -1;
	}
	readed = read(fd, cb_gethead(cb), to_read);
	if (readed > 0) {
		char * head;
		int c, pc;
		size_t i;
		head = cb_gethead(cb);
		fprintf(stdout, "%d: ", (int)readed);
		for (i = 0; i < readed; i++) {
			c = head[i] & 0xff;
			pc = '.';
			if (c >= 0x20 && c <= 0x7e) {
				pc = c;
			}
			fprintf(stdout, "%02x(%c) ", c, pc);
		}
		fprintf(stdout, "\n");
		cb_addbytes(cb, readed);
	}
	return readed;
}

ssize_t perform_write(int fd, circularbuffer_t * cb) {
	size_t to_write;
	ssize_t written;
	to_write = cb_sizeaftertail(cb);
	if (to_write == 0) {
		return 0;
	}
	written = write(fd, cb_gettail(cb), to_write);
	if (written > 0) {
		cb_subtractbytes(cb, written);
	}
	return written;
}

int main(int argc, char *argv[]) {
	struct timeval tv;
	int maxfd, res, ctr;
	char * buf;
	size_t rd_idx;

	uart_ctx = uart_initialise(argv[1], 9600);
	check_debug(uart_ctx != NULL, "Could not initialise serial port");
	cb_initialise(&rd_cb, 1024);
	cb_initialise(&wr_cb, 1024);
	buf = malloc(1024);

	ctr = 0;
	rd_idx = 0;
next_activity:
	FD_ZERO(&fd_read);
	FD_ZERO(&fd_write);
	FD_SET(uart_ctx->fd, &fd_read);
	if (cb_used(wr_cb)) {
		FD_SET(uart_ctx->fd, &fd_write);
	}
	maxfd = uart_ctx->fd;

	tv.tv_sec = 5;
	tv.tv_usec = 0;
	res = select(maxfd + 1, &fd_read, &fd_write, NULL, &tv);

	if (res == -1) {
		debug("select() error!");
	} else
	if (res) {
		debug("select() returned %d", res);
	} else {
		debug("select() timeout");
		goto next_activity;
	}

	if (FD_ISSET(uart_ctx->fd, &fd_read)) {
		perform_read(uart_ctx->fd, rd_cb);
check_next_line:
		res = cb_readuntilbyte(rd_cb, buf, 1024, '\r', &rd_idx);
		if (res == -2) {
			fprintf(stdout, "terminating char not found\r\n");
		} else
		if (res == 0) {
			buf[rd_idx] = '\0';
			fprintf(stdout, "[%s]\r\n", buf);
			rd_idx = 0;
			if (strncmp(buf, "time sync", 9) == 0) {
				char * str = "\% time sync beverly.bengreen.eu\r\n\% et 1546630368\r1546630368: 1521939600 1540688400\r\nN\r\n\r\n\r\nTIME12:59:00\r\n";
				int len = strlen(str);
				cb_write(wr_cb, str, len);
				//cb_write(wr_cb, "\% time sync beverly.bengreen.eu\r\% et 1546630368\r1546630368: 1521939600 1540688400\rN\r\r\rTIME12:45:00\r", 13);
				fprintf(stdout, "Sent Time\n");
			}
			goto check_next_line;
		}
	}
	if (FD_ISSET(uart_ctx->fd, &fd_write)) {
		perform_write(uart_ctx->fd, wr_cb);
	}

	ctr ++;
	goto next_activity;

	uart_finalise(uart_ctx);

error:
	return 0;
}

