	.file "utilityfn_s.S"

#include <msp430.h>

	.globl Utility_hexchars

	.section .text,"ax",@progbits

Utility_hexchars:
	.ascii	"0123456789ABCDEF"

	.end

