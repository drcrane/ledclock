#include "uart.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <termios.h>
// #include <asm/termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>

uart_context_t * uart_initialise(char * filename, int speed) {
	uart_context_t * ctx;

	ctx = malloc(sizeof(uart_context_t));
	if (ctx == NULL) {
		goto error;
	}
	ctx->fd = open(filename, O_RDWR | O_NOCTTY);

	uart_setspeed(ctx, speed);
	return ctx;
error:
	return ctx;
}

int uart_setspeed(uart_context_t * ctx, int speed) {
	struct termios tios;
	int baudr, err;

	switch (speed) {
	case 1200:
		baudr = B1200;
		break;
	case 2400:
		baudr = B2400;
		break;
	case 4800:
		baudr = B4800;
		break;
	case 9600:
		baudr = B9600;
		break;
	default:
		return -1;
	}

	memset(&tios, 0, sizeof(tios));
	tios.c_cflag = baudr | CS8 | CLOCAL | CREAD;
	tios.c_iflag = IGNPAR;
	tios.c_oflag = 0;
	tios.c_lflag = 0;
	tios.c_cc[VMIN] = 1;
	tios.c_cc[VTIME] = 0;
	err = tcsetattr(ctx->fd, TCSANOW, &tios);
	if (err != 0) {
		return err;
	}

	return err;
}

/*
int uart_setspeed(uart_context_t * ctx, int speed) {
	struct termios2 tios;
	int res;

	res = ioctl(ctx->fd, TCGETS2, &tios);
	tios.c_cflag &= ~CBAUD;
	tios.c_cflag |= (BOTHER | CS8 | CLOCAL | CREAD);
	tios.c_iflag = IGNPAR;
	tios.c_oflag = 0;
	tios.c_lflag = 0;
	tios.c_ispeed = speed;
	tios.c_ospeed = speed;
	res = ioctl(ctx->fd, TCSETS2, &tios);

	return res;
}
*/

void uart_finalise(uart_context_t * ctx) {
	close(ctx->fd);
}

