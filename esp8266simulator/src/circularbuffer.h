#ifndef __CB_H__
#define __CB_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read from the tail and write to the head
 *
 * This implementation of the circular buffer means that one byte is wasted.
 * The maximum capacity of this buffer is size - 1.
 *
 * Benjamin Green 2015-03-04
 *
 * Should be improved, see:
 *    https://www.snellman.net/blog/archive/2016-12-13-ring-buffers/
 *    http://lkml.iu.edu/hypermail/linux/kernel/0409.1/2709.html
 *
 */

#define CB_FLAGS_OVERFLOW 1

#ifdef CB_EMBEDDED_FIXED
typedef struct {
	size_t size;
	volatile size_t head;
	volatile size_t tail;
	volatile int flags;
	unsigned char buffer[CB_EMBEDDED_FIXED];
} circularbuffer_t;
#else
typedef struct {
	size_t size;
	volatile size_t head;
	volatile size_t tail;
	volatile int flags;
	unsigned char buffer[1];
} circularbuffer_t;
#endif

#ifdef CB_EMBEDDED_FIXED
int cb_initialise(circularbuffer_t * cb);
int cb_finalise(circularbuffer_t * cb);
#else
int cb_initialise(circularbuffer_t ** cb_in, size_t buffersz);
int cb_finalise(circularbuffer_t ** cb_in);
#endif

size_t cb_write(circularbuffer_t * cb, void * buf, size_t len);
size_t cb_read(circularbuffer_t * cb, void * buf, size_t len);

// Total space available in the buffer, contiguous or not.
size_t cb_free(circularbuffer_t * cb);
// amount of space used
size_t cb_used(circularbuffer_t * cb);
// total capacity of buffer
size_t cb_capacity(circularbuffer_t * cb);
// contiguous space available after the head
size_t cb_freeafterhead(circularbuffer_t * cb);
// contiguous data available after the tail
size_t cb_sizeaftertail(circularbuffer_t * cb);
// location of the head
void * cb_gethead(circularbuffer_t * cb);
// location of the tail
void * cb_gettail(circularbuffer_t * cb);
// bytes are added to the head
void cb_addbytes(circularbuffer_t * cb, size_t bytes);
// bytes are subtracted from the tail
void cb_subtractbytes(circularbuffer_t * cb, size_t bytes);
// see if bytes match (or wildcard '?') and if all len bytes match consume len bytes 
int cb_match(circularbuffer_t * cb, unsigned char * match, size_t len);
// get the byte at offset from the tail
int cb_peek(circularbuffer_t * cb, size_t offs);
// get a single byte from the buffer (return -1 if buffer is empty)
int cb_getchar(circularbuffer_t * cb);
// put a byte back in the buffer
void cb_ungetchar(circularbuffer_t * cb, int c);
// put a single byte into the buffer
int cb_putchar(circularbuffer_t * cb, int c);
// get the byte at offset from the tail
int cb_peek(circularbuffer_t * cb, size_t offs);
// get the bytes at offset from the tail
size_t cb_peek_ex(circularbuffer_t * cb, void * dst, size_t offs, size_t len);
// set the tail to be at the head (empty the buffer)
void cb_flush(circularbuffer_t * cb);
// find a sequence of bytes and return the number of bytes before them
int cb_findbyteseq(circularbuffer_t * cb, unsigned char * seq, size_t seqlen, size_t * len);
// read until the end of the buffer or you meet the byte specified
// 0 = all bytes read including the one you specified
// -1 = reached the end of the destination buffer
// -2 = reached the end of the source buffer
int cb_readuntilbyte(circularbuffer_t * cb, char * dst, size_t dstsz, int byte, size_t * pos_ctx);
// get a number from the buffer, it will read a single value from the buffer
// if it does not match a number
int cb_atoi(circularbuffer_t * cb);
double cb_atof(circularbuffer_t * cb);

int cb_full(circularbuffer_t * cb);
int cb_empty(circularbuffer_t * cb);
size_t cb_memcmp(circularbuffer_t * cb, unsigned char * cmp, size_t len);

#ifdef __cplusplus
};
#endif

#endif // __CB_H__
