	.file "startup.S"

#include <msp430.h>

	.section .text,"ax",@progbits

_start:
	mov.w	#(__stack-16), SP
	mov.w	#main, r15
	mov.w	r15, PC

	.section "__reset_vector","ax",@progbits
	.word _start            ;0xfffe (RESET_VECTOR)

	.end

