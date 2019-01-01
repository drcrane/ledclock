#ifndef UART_H
#define UART_H

typedef struct uart_context_s {
	int fd;
} uart_context_t;

uart_context_t * uart_initialise(char * filename, int speed);
int uart_setspeed(uart_context_t * ctx, int speed);
void uart_finalise(uart_context_t * ctx);

#endif // UART_H

