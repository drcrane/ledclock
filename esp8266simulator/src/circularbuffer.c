#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "circularbuffer.h"

//#include "dbg.h"
//#include "dumphex.h"

// #define cb_memcpy memcpy

#ifndef cb_memcpy
static void cb_memcpy(void * dst, void * src, size_t len) {
	while (len--) {
		*((char *)dst) = *((char *)src);
		dst = ((char *)dst) + 1;
		src = ((char *)src) + 1;
	}
}
#endif

#ifdef CB_EMBEDDED_FIXED
int cb_initialise(circularbuffer_t * cb) {
	cb->size = CB_EMBEDDED_FIXED;
	cb->head = 0;
	cb->tail = 0;
	return 0;
}

int cb_finalise(circularbuffer_t * cb) {
	// do nothing, it is static or allocated by the user
	return 0;
}

#else

int cb_initialise(circularbuffer_t ** cb_in, size_t buffersz) {
	circularbuffer_t * cb;
	size_t alloc_sz = offsetof(circularbuffer_t, buffer[buffersz]);
	*cb_in = NULL;
	cb = malloc(alloc_sz);
	memset(cb, 0, alloc_sz);
	if(cb == NULL) { goto error; }
	cb->size = (int)buffersz;
	cb->head = 0;
	cb->tail = 0;
	*((circularbuffer_t **)cb_in) = cb;
	return 0;
error:
	return -1;
}

int cb_finalise(circularbuffer_t ** cb_in) {
	free(*cb_in);
	*cb_in = NULL;
	return 0;
}
#endif

size_t cb_freeafterhead(circularbuffer_t * cb) {
	size_t cfree = 0;
	size_t tail = cb->tail;
	if (cb->head < tail) {
		cfree = (cb->size - cb->head + (tail - cb->size)) - 1;
	} else
	if (cb->head >= tail) {
		cfree = cb->size - cb->head - 1;
		// Special case, we are at the end of the buffer and that one pesky 
		// byte causes us this problem!
		if (cfree == 0 && ((cb->size - cb->head + tail) - 1)) {
			cfree = 1;
		}
	}
	return cfree;
}

size_t cb_free(circularbuffer_t * cb) {
	size_t free = 0;
	size_t tail = cb->tail;
	if (cb->head < tail) {
		free = (cb->size - cb->head + (tail - cb->size)) - 1;
	} else
	if (cb->head >= tail) {
		free = (cb->size - cb->head + tail) - 1;
	}
	return free;
}

void * cb_gethead(circularbuffer_t * cb) {
	return (void *)(cb->buffer + cb->head);
}

void * cb_gettail(circularbuffer_t * cb) {
	return (void *)(cb->buffer + cb->tail);
}

void cb_flush(circularbuffer_t * cb) {
	cb->tail = cb->head;
}

/**
 * CANNOT WRITE cb->tail!
 * Functions are inlined MANUALLY!.
 */
size_t cb_write(circularbuffer_t * cb, void * buf, size_t len) {
	size_t cfree = 0;
	size_t free = 0;
	size_t tocopy;
	size_t newhead;
	size_t tail = cb->tail;
	size_t head = cb->head;
	// MANUAL INLINE
	//free = cb_free(cb);
	if (head < tail) {
		free = (cb->size - head + (tail - cb->size)) - 1;
	} else
	if (head >= tail) {
		free = (cb->size - head + tail) - 1;
	}
	// ---------------------
	if (len <= free) {
		// MANUAL INLINE
		//cfree = cb_getfreeafterhead(cb);
		if (head < tail) {
			cfree = (cb->size - head + (tail - cb->size));
		} else
		if (head >= tail) {
			cfree = cb->size - head;
		}
		// ---------------------
		if (len <= cfree) {
			tocopy = len;
		} else {
			tocopy = cfree;
		}
		cb_memcpy(cb->buffer + head, buf, tocopy);
		newhead = head + tocopy;
		if (newhead == cb->size) {
			newhead = 0;
		}
		if (tocopy < len) {
			buf = ((unsigned char *)buf) + tocopy;
			tocopy = len - tocopy;
			cb_memcpy(cb->buffer + newhead, buf, tocopy);
			newhead = newhead + tocopy;
			if (newhead == cb->size) {
				newhead = 0;
			}
		}
		cb->head = newhead;
	} else {
		cb->flags |= CB_FLAGS_OVERFLOW;
		len = 0;
	}
	return len;
}

size_t cb_sizeaftertail(circularbuffer_t * cb) {
	size_t datasz = 0;
	size_t head = cb->head;
	size_t tail = cb->tail;
	if (head < tail) {
		datasz = cb->size - tail;
	} else
	if (head >= tail) {
		datasz = head - tail;
	}
	return datasz;
}

size_t cb_used(circularbuffer_t * cb) {
	size_t datasz = 0;
	size_t head = cb->head;
	size_t tail = cb->tail;
	if (head < tail) {
		datasz = cb->size - tail + head;
	} else
	if (head >= tail) {
		datasz = head - tail;
	}
	return datasz;
}

size_t cb_capacity(circularbuffer_t * cb) {
	return cb->size - 1;
}

/**
 * Cannot write to cb->head!
 * Functions are inlined MANUALLY!.
 */
size_t cb_read(circularbuffer_t * cb, void * buf, size_t len) {
	size_t head = cb->head;
	size_t tail = cb->tail;
	size_t datasz = 0;
	size_t cdata = 0;
	size_t tocopy;
	size_t newtail = 0;
	
	// cb_size()
	if (head < tail) {
		datasz = cb->size - tail + head;
	} else
	if (head >= tail) {
		datasz = head - tail;
	}
	
	if (len > datasz) {
		len = datasz;
	}
	if (datasz == 0) {
		return 0;
	}
	
	// cb_sizeaftertail()
	if (head < tail) {
		cdata = cb->size - tail;
	} else
	if (head >= tail) {
		cdata = head - tail;
	}
	
	if (len <= cdata) {
		tocopy = len;
	} else {
		tocopy = cdata;
	}
	cb_memcpy(buf, cb->buffer + tail, tocopy);
	newtail = tail + tocopy;
	if (newtail == cb->size) {
		newtail = 0;
	}
	if (cdata < len) {
		tocopy = len - cdata;
		cb_memcpy((char *)buf + cdata, cb->buffer + newtail, tocopy);
		newtail = newtail + tocopy;
		if (newtail == cb->size) {
			newtail = 0;
		}
	}
	cb->tail = newtail;
		
	return len;
}

int cb_findbyteseq(circularbuffer_t * cb, unsigned char * seq, size_t seqlen, size_t * len) {
	int i, j;
	size_t pos;
	size_t tail = cb->tail;
	size_t size = cb_used(cb);
	for (i = 0; i < size; i++) {
		pos = (tail + i) % cb->size;
		//debug("matching at %d : %d with %d", i, cb->buffer[pos], seq[0]);
		if (cb->buffer[pos] == seq[0]) {
			//debug("matched %d with %d at %d", cb->buffer[pos], seq[0], i);
			// Found the first char, now match the rest
			if (i + seqlen > size) {
				// cannot be a match because the remaining buffer is too small
				//debug("terminating because %d > %d", i + seqlen, size);
				return -1;
			}
			for (j = 1; j < seqlen; j++) {
				pos = (tail + i + j) % cb->size;
				//debug("inner matching at %d : %d with %d", j, cb->buffer[pos], seq[j]);
				if (cb->buffer[pos] != seq[j]) {
					break;
				}
			}
			if (j == seqlen) {
				if (len != NULL) {
					*len = i;
				}
				return 0;
			}
		}
	}
	return -1;
}

/*
 * Read out of the buffer until a specific byte is encountered
 * If the byte is encountered return 0
 * If the destination buffer is too small return -1
 *    - pos_ctx contains the index of the last byte read
 * If the byte is not encountered return -2
 *    - pos_ctx contains the index of the last byte read
 */
int cb_readuntilbyte(circularbuffer_t * cb, char * dst, size_t dstsz, int byte, size_t * pos_ctx) {
	size_t i;
	size_t pos;
	size_t tail = cb->tail;
	size_t size = cb_used(cb);
	//fprintf(stdout, "cb_readuntilbyte() looking at %d bytes\n", size);
	for (i = *pos_ctx; i < size; i++) {
		pos = (tail + i) % cb->size;
		if (i >= dstsz) {
			*pos_ctx = i;
			return -1;
		}
		dst[i] = cb->buffer[pos];
		// we got it!
		//fprintf(stdout, "%d: 0x%02x %c\n", i, dst[i], (dst[i] <= 0x73 && dst[i] >= 0x20) ? dst[i] : '.');
		if ((cb->buffer[pos] & 0xff) == byte) {
			*pos_ctx = i;
			cb_subtractbytes(cb, i + 1);
			return 0;
		}
	}
	*pos_ctx = i;
	return -2;
}

void cb_addbytes(circularbuffer_t * cb, size_t bytes) {
	size_t head = cb->head;
	head = (head + bytes) % cb->size;
	cb->head = head;
}

void cb_subtractbytes(circularbuffer_t * cb, size_t bytes) {
	size_t tail = cb->tail;
	tail = (tail + bytes) % cb->size;
	cb->tail = tail;
}

/*
// Careful, name is misleading...
void cb_tail_addbytes(circularbuffer_t * cb, int bytes) {
	int tail = cb->tail;
	tail = (tail - bytes) % cb->size;
	cb->tail = tail;
}
*/

int cb_match(circularbuffer_t * cb, unsigned char * match, size_t len) {
	size_t i;
	
	if (cb_used(cb) < len) {
		return 0;
	}
	i = len;
	do {
		i--;
		if (match[i] == (unsigned char)cb_peek(cb, i) || match[i] == '?') {
			continue;
		} else {
			break;
		}
	} while (i);
	if (i == 0) {
		cb_subtractbytes(cb, len);
		return 1;
	}
	return 0;
}

int cb_peek(circularbuffer_t * cb, size_t offs) {
	return *(unsigned char *)(cb->buffer + ((cb->tail + offs) % cb->size));
}

size_t cb_peek_ex(circularbuffer_t * cb, void * dst_ptr, size_t offs, size_t len) {
	char * dst = dst_ptr;
	int c;
	do {
		c = cb_peek(cb, offs);
		if (offs >= cb_used(cb)) {
			break;
		}
		*dst = c;
		dst++;
		offs++;
	} while (len --);
	return (size_t)(dst - (char*)dst_ptr);
}

int cb_getchar(circularbuffer_t * cb) {
	int c;
	if (cb_used(cb) == 0) {
		return -1;
	}
	size_t tail = cb->tail;
	
	c = *(unsigned char *)(cb->buffer + tail);
	tail = (tail + 1) % cb->size;
	cb->tail = tail;
	
	return c;
}

void cb_ungetchar(circularbuffer_t * cb, int c) {
	size_t tail = cb->tail;

	tail = (tail - 1) % cb->size;
	*(unsigned char *)(cb->buffer + tail) = c;

	cb->tail = tail;
}

int cb_putchar(circularbuffer_t * cb, int c) {
	//if (cb_used(cb) == 0) {
	//	return -1;
	//}
	size_t head = cb->head;
	
	*(unsigned char *)(cb->buffer + head) = c;
	
	head = (head + 1) % cb->size;
	cb->head = head;
	
	return c;
}

// Read from the buffer, byte by byte, and make an integer
// Please ensure that this is the same as the one in
// Utility FN.
// If a read value does not match a required value then it
// will be put back into the buffer.
int cb_atoi(circularbuffer_t * cb) {
	int chr;
	int valueisnegative = 0;
	int result_value = 0;
	do {
		chr = cb_getchar(cb);
	} while (chr == '\t' || chr == ' ');
	if (chr == '-') {
		valueisnegative = 1;
		chr = cb_getchar(cb);
	} else if (chr == '+') {
		chr = cb_getchar(cb);
	}
	while (chr >= '0' && chr <= '9') {
		result_value = result_value * 10;
		result_value += (chr - '0');
		chr = cb_getchar(cb);
	}
	if (valueisnegative) {
		result_value = -(result_value);
	}
	if (chr != -1) {
		cb_ungetchar(cb, chr);
	}
	return result_value;
}

static int isHexDigit(int c, int * val) {
	if (c >= '0' && c <= '9') {
		*val = c - '0';
		goto end_success;
	}
	if (c >= 'a' && c <= 'f') {
		*val = c - ('a' - 10);
		goto end_success;
	}
	if (c >= 'A' && c <= 'F') {
		*val = c - ('A' - 10);
		goto end_success;
	}
	return 0;
end_success:
	return 1;
}

// Read a string of hex digits.
// WARNING: this will not return until a non-hex digit is encountered.
int cb_hextob(circularbuffer_t * cb, char * dst) {
	int cur;
	int c;
	int val;
	do {
		c = cb_getchar(cb);
		if (isHexDigit(c, &val)) {
			cur = val;
		} else {
			if (c != -1) {
				cb_ungetchar(cb, c);
			}
			break;
		}
		c = cb_getchar(cb);
		if (isHexDigit(c, &val)) {
			cur = (cur << 4) | val;
			*dst = cur;
		} else {
			if (c != -1) {
				cb_ungetchar(cb, c);
			}
			*dst = cur;
			break;
		}
		dst++;
	} while (1);
	return 0;
}

double cb_atof(circularbuffer_t * cb) {
	double val, power, rtn;
	int i = 0, sign = 1, chr;
	do {
		chr = cb_getchar(cb);
	} while (chr == ' ' || chr == '\t');
	if (chr == '-') {
		sign = -1;
		chr = cb_getchar(cb);
	} else if (chr == '+') {
		chr = cb_getchar(cb);
	}
	val = 0.0;
	while (chr >= '0' && chr <= '9') {
		val = 10.0 * val + (chr - '0');
		chr = cb_getchar(cb);
	}
	if (chr == '.') {
		chr = cb_getchar(cb);
	}
	power = 1.0;
	while (chr >= '0' && chr <= '9') {
		val = 10.0 * val + (chr - '0');
		power *= 10.0;
		chr = cb_getchar(cb);
	}
	rtn = sign * val / power;
	if (chr == 'e' || chr == 'E') {
		int esign;
		int expv = 0;
		// HMM??
		do {
			chr = cb_getchar(cb);
		} while (chr == ' ' || chr == '\t');
		esign = (chr == '-') ? -1 : 1;
		if (chr == '+' || chr == '-') {
			chr = cb_getchar(cb);
		}
		while (chr >= '0' && chr <= '9') {
			expv = 10 * expv + (chr - '0');
			chr = cb_getchar(cb);
			i++;
		}
		int l;
		for (l = 0; l < expv; l++) {
			if (esign >= 0) {
				rtn *= 10;
			} else {
				rtn /= 10;
			}
		}
	}
	if (chr != -1) {
		cb_ungetchar(cb, chr);
	}
	return rtn;
}

int cb_full(circularbuffer_t * cb) { return 0; }
int cb_empty(circularbuffer_t * cb) { return 0; }
size_t cb_memcmp(circularbuffer_t * cb, unsigned char * cmp, size_t len) { return 0; }

