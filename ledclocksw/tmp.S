
main.elf:     file format elf32-msp430


Disassembly of section __interrupt_vector_7:

0000ffec <__interrupt_vector_7>:
    ffec:	d6 c3       	interrupt service routine at 0xc3d6

Disassembly of section __interrupt_vector_8:

0000ffee <__interrupt_vector_8>:
    ffee:	b8 c3       	interrupt service routine at 0xc3b8

Disassembly of section __interrupt_vector_9:

0000fff0 <__interrupt_vector_9>:
    fff0:	62 c0       	interrupt service routine at 0xc062

Disassembly of section __interrupt_vector_10:

0000fff2 <__interrupt_vector_10>:
    fff2:	ee c3       	interrupt service routine at 0xc3ee

Disassembly of section __interrupt_vector_13:

0000fff8 <__interrupt_vector_13>:
    fff8:	40 c0       	interrupt service routine at 0xc040

Disassembly of section __interrupt_vector_14:

0000fffa <__interrupt_vector_14>:
    fffa:	3e c0       	interrupt service routine at 0xc03e

Disassembly of section .text:

0000c00c <_start>:
    c00c:	31 40 f0 03 	mov	#1008,	r1	;#0x03f0

0000c010 <L0L1>:
    c010:	3f 40 6c c0 	mov	#-16276,r15	;#0xc06c

0000c014 <L0L2>:
    c014:	00 4f       	br	r15		;

0000c016 <Utility_hexchars>:
    c016:	30 31       	jn	$+610    	;abs 0xc278
    c018:	32 33       	jn	$-410    	;abs 0xbe7e
    c01a:	34 35       	jge	$+618    	;abs 0xc284
    c01c:	36 37       	jge	$-402    	;abs 0xbe8a
    c01e:	38 39       	jl	$+626    	;abs 0xc290
    c020:	41 42       	mov.b	r2,	r1	;
    c022:	43 44       	.word	0x4443;	????
    c024:	45 46       	mov.b	r6,	r5	;

0000c026 <printtime>:
    c026:	31 82       	sub	#8,	r1	;r2 As==11

0000c028 <.LCFI0>:
    c028:	6e 43       	mov.b	#2,	r14	;r3 As==10
    c02a:	3d 40 3c 02 	mov	#572,	r13	;#0x023c
    c02e:	0c 41       	mov	r1,	r12	;
    c030:	b0 12 30 c2 	call	#-15824	;#0xc230

0000c034 <.LVL0>:
    c034:	0c 41       	mov	r1,	r12	;
    c036:	b0 12 9e c3 	call	#-15458	;#0xc39e

0000c03a <.LVL1>:
    c03a:	31 52       	add	#8,	r1	;r2 As==11
    c03c:	30 41       	ret			

0000c03e <Timer1_A0>:
    c03e:	00 13       	reti			

0000c040 <Timer1_A1>:
    c040:	0c 12       	push	r12		;

0000c042 <.LCFI1>:
    c042:	1c 42 1e 01 	mov	&0x011e,r12	;0x011e
    c046:	2c 93       	cmp	#2,	r12	;r3 As==10
    c048:	04 24       	jz	$+10     	;abs 0xc052
    c04a:	2c 92       	cmp	#4,	r12	;r2 As==10
    c04c:	06 24       	jz	$+14     	;abs 0xc05a

0000c04e <.L3>:
    c04e:	3c 41       	pop	r12		;
    c050:	00 13       	reti			

0000c052 <.L5>:
    c052:	92 53 06 02 	inc	&0x0206		;

0000c056 <.Loc.40.1>:
    c056:	30 40 4e c0 	br	#0xc04e		;

0000c05a <.L6>:
    c05a:	92 53 00 02 	inc	&0x0200		;

0000c05e <.Loc.49.1>:
    c05e:	30 40 4e c0 	br	#0xc04e		;

0000c062 <Timer0_A1>:
    c062:	0c 12       	push	r12		;

0000c064 <.LCFI2>:
    c064:	1c 42 2e 01 	mov	&0x012e,r12	;0x012e

0000c068 <.Loc.60.1>:
    c068:	3c 41       	pop	r12		;
    c06a:	00 13       	reti			

0000c06c <main>:
    c06c:	b2 40 80 5a 	mov	#23168,	&0x0120	;#0x5a80
    c070:	20 01 

0000c072 <.Loc.68.1>:
    c072:	d2 42 fd 10 	mov.b	&0x10fd,&0x0057	;0x10fd
    c076:	57 00 

0000c078 <.Loc.69.1>:
    c078:	d2 42 fc 10 	mov.b	&0x10fc,&0x0056	;0x10fc
    c07c:	56 00 

0000c07e <.Loc.72.1>:
    c07e:	f2 f0 1f 00 	and.b	#31,	&0x0019	;#0x001f
    c082:	19 00 

0000c084 <.Loc.73.1>:
    c084:	f2 d0 e0 ff 	bis.b	#-32,	&0x001a	;#0xffe0
    c088:	1a 00 

0000c08a <.Loc.76.1>:
    c08a:	f2 d0 06 00 	bis.b	#6,	&0x0026	;
    c08e:	26 00 

0000c090 <.Loc.77.1>:
    c090:	f2 d0 06 00 	bis.b	#6,	&0x0041	;
    c094:	41 00 

0000c096 <.Loc.78.1>:
    c096:	f2 d0 81 ff 	bis.b	#-127,	&0x0061	;#0xff81
    c09a:	61 00 

0000c09c <.Loc.79.1>:
    c09c:	f2 40 34 00 	mov.b	#52,	&0x0062	;#0x0034
    c0a0:	62 00 

0000c0a2 <.Loc.80.1>:
    c0a2:	c2 43 63 00 	mov.b	#0,	&0x0063	;r3 As==00

0000c0a6 <.Loc.81.1>:
    c0a6:	f2 40 31 00 	mov.b	#49,	&0x0064	;#0x0031
    c0aa:	64 00 

0000c0ac <.Loc.82.1>:
    c0ac:	d2 c3 61 00 	bic.b	#1,	&0x0061	;r3 As==01

0000c0b0 <.Loc.84.1>:
    c0b0:	d2 c3 03 00 	bic.b	#1,	&0x0003	;r3 As==01

0000c0b4 <.Loc.85.1>:
    c0b4:	d2 d3 01 00 	bis.b	#1,	&0x0001	;r3 As==01

0000c0b8 <.Loc.89.1>:
    c0b8:	f2 d0 0c 00 	bis.b	#12,	&0x0053	;#0x000c
    c0bc:	53 00 

0000c0be <.Loc.95.1>:
    c0be:	b2 40 24 01 	mov	#292,	&0x0160	;#0x0124
    c0c2:	60 01 

0000c0c4 <.Loc.97.1>:
    c0c4:	b2 40 ff 7f 	mov	#32767,	&0x0172	;#0x7fff
    c0c8:	72 01 

0000c0ca <.Loc.98.1>:
    c0ca:	b2 40 10 00 	mov	#16,	&0x0162	;#0x0010
    c0ce:	62 01 

0000c0d0 <.Loc.100.1>:
    c0d0:	f2 40 49 00 	mov.b	#73,	&0x0067	;#0x0049
    c0d4:	67 00 

0000c0d6 <.L9>:
    c0d6:	e2 b3 03 00 	bit.b	#2,	&0x0003	;r3 As==10
    c0da:	45 24       	jz	$+140    	;abs 0xc166

0000c0dc <.Loc.104.1>:
    c0dc:	d2 d3 22 00 	bis.b	#1,	&0x0022	;r3 As==01

0000c0e0 <.Loc.105.1>:
    c0e0:	d2 c3 21 00 	bic.b	#1,	&0x0021	;r3 As==01

0000c0e4 <.Loc.107.1>:
    c0e4:	c2 43 19 00 	mov.b	#0,	&0x0019	;r3 As==00

0000c0e8 <.Loc.108.1>:
    c0e8:	f2 43 1a 00 	mov.b	#-1,	&0x001a	;r3 As==11

0000c0ec <.Loc.110.1>:
    c0ec:	f2 40 0a 00 	mov.b	#10,	&0x0029	;#0x000a
    c0f0:	29 00 

0000c0f2 <.Loc.111.1>:
    c0f2:	f2 43 2a 00 	mov.b	#-1,	&0x002a	;r3 As==11

0000c0f6 <.Loc.115.1>:
    c0f6:	b2 40 d6 02 	mov	#726,	&0x0180	;#0x02d6
    c0fa:	80 01 

0000c0fc <.Loc.116.1>:
    c0fc:	b2 40 e7 03 	mov	#999,	&0x0192	;#0x03e7
    c100:	92 01 

0000c102 <.Loc.117.1>:
    c102:	b2 40 10 00 	mov	#16,	&0x0182	;#0x0010
    c106:	82 01 

0000c108 <.Loc.119.1>:
    c108:	82 43 02 02 	mov	#0,	&0x0202	;r3 As==00

0000c10c <.Loc.121.1>:
    c10c:	b0 12 d8 c3 	call	#-15400	;#0xc3d8

0000c110 <.LVL2>:
    c110:	3a 40 26 c0 	mov	#-16346,r10	;#0xc026
    c114:	8a 12       	call	r10		;

0000c116 <.LVL3>:
    c116:	3c 40 fa ff 	mov	#-6,	r12	;#0xfffa

0000c11a <.L11>:
    c11a:	3c 53       	add	#-1,	r12	;r3 As==11
    c11c:	3c 93       	cmp	#-1,	r12	;r3 As==11
    c11e:	26 20       	jnz	$+78     	;abs 0xc16c
    c120:	82 4c 04 02 	mov	r12,	&0x0204	;

0000c124 <.Loc.126.1>:
    c124:	32 d2       	eint			

0000c126 <.Loc.127.1>:
    c126:	03 43       	nop			

0000c128 <.Loc.139.1>:
    c128:	39 40 00 c0 	mov	#-16384,r9	;#0xc000
    c12c:	37 40 36 02 	mov	#566,	r7	;#0x0236
    c130:	38 40 a2 c4 	mov	#-15198,r8	;#0xc4a2

0000c134 <.L16>:
    c134:	92 b3 34 02 	bit	#1,	&0x0234	;r3 As==01
    c138:	0a 24       	jz	$+22     	;abs 0xc14e

0000c13a <.Loc.132.1>:
    c13a:	d2 e3 21 00 	xor.b	#1,	&0x0021	;r3 As==01

0000c13e <.Loc.133.1>:
    c13e:	92 c3 34 02 	bic	#1,	&0x0234	;r3 As==01

0000c142 <.Loc.134.1>:
    c142:	1c 42 32 02 	mov	&0x0232,r12	;0x0232
    c146:	3c 90 70 00 	cmp	#112,	r12	;#0x0070
    c14a:	01 20       	jnz	$+4      	;abs 0xc14e

0000c14c <.Loc.135.1>:
    c14c:	8a 12       	call	r10		;

0000c14e <.L14>:
    c14e:	7d 40 0a 00 	mov.b	#10,	r13	;#0x000a
    c152:	1c 47 06 00 	mov	6(r7),	r12	;
    c156:	88 12       	call	r8		;
    c158:	0c 59       	add	r9,	r12	;
    c15a:	e2 4c 19 00 	mov.b	@r12,	&0x0019	;

0000c15e <.Loc.141.1>:
    c15e:	b0 12 60 c3 	call	#-15520	;#0xc360

0000c162 <.LVL6>:
    c162:	30 40 34 c1 	br	#0xc134		;

0000c166 <.L10>:
    c166:	03 43       	nop			
    c168:	30 40 d6 c0 	br	#0xc0d6		;

0000c16c <.L12>:
    c16c:	03 43       	nop			
    c16e:	30 40 1a c1 	br	#0xc11a		;

0000c172 <memcpy>:
    c172:	0a 12       	push	r10		;

0000c174 <.LCFI0>:
    c174:	0f 4c       	mov	r12,	r15	;

0000c176 <.L2>:
    c176:	4a 43       	clr.b	r10		;
    c178:	0a 9e       	cmp	r14,	r10	;
    c17a:	02 38       	jl	$+6      	;abs 0xc180

0000c17c <.Loc.16.1>:
    c17c:	3a 41       	pop	r10		;
    c17e:	30 41       	ret			

0000c180 <.L3>:
    c180:	ef 4d 00 00 	mov.b	@r13,	0(r15)	;
    c184:	3e 53       	add	#-1,	r14	;r3 As==11

0000c186 <.LVL4>:
    c186:	1f 53       	inc	r15		;
    c188:	1d 53       	inc	r13		;

0000c18a <.LVL5>:
    c18a:	30 40 76 c1 	br	#0xc176		;

0000c18e <Utility_hexToInt>:
    c18e:	0a 12       	push	r10		;

0000c190 <.LCFI1>:
    c190:	09 12       	push	r9		;

0000c192 <.LCFI2>:
    c192:	08 12       	push	r8		;

0000c194 <.LCFI3>:
    c194:	0b 4c       	mov	r12,	r11	;
    c196:	0b 5d       	add	r13,	r11	;

0000c198 <.Loc.30.1>:
    c198:	4e 43       	clr.b	r14		;
    c19a:	0d 4e       	mov	r14,	r13	;

0000c19c <.LBB2>:
    c19c:	0a 4e       	mov	r14,	r10	;

0000c19e <.L5>:
    c19e:	6f 4c       	mov.b	@r12,	r15	;

0000c1a0 <.LVL10>:
    c1a0:	0f 93       	cmp	#0,	r15	;r3 As==00
    c1a2:	02 24       	jz	$+6      	;abs 0xc1a8

0000c1a4 <.LVL11>:
    c1a4:	0c 9b       	cmp	r11,	r12	;
    c1a6:	03 20       	jnz	$+8      	;abs 0xc1ae

0000c1a8 <.L4>:
    c1a8:	0c 4e       	mov	r14,	r12	;

0000c1aa <.LVL13>:
    c1aa:	30 40 ec c4 	br	#0xc4ec		;

0000c1ae <.L10>:
    c1ae:	49 4f       	mov.b	r15,	r9	;
    c1b0:	79 50 d0 ff 	add.b	#-48,	r9	;#0xffd0
    c1b4:	78 40 09 00 	mov.b	#9,	r8	;
    c1b8:	48 99       	cmp.b	r9,	r8	;
    c1ba:	14 28       	jnc	$+42     	;abs 0xc1e4

0000c1bc <.Loc.34.1>:
    c1bc:	3f 50 d0 ff 	add	#-48,	r15	;#0xffd0

0000c1c0 <.L7>:
    c1c0:	0e 5e       	rla	r14		;

0000c1c2 <.LVL16>:
    c1c2:	0d 6d       	rlc	r13		;
    c1c4:	0e 5e       	rla	r14		;
    c1c6:	0d 6d       	rlc	r13		;
    c1c8:	0e 5e       	rla	r14		;
    c1ca:	0d 6d       	rlc	r13		;
    c1cc:	0e 5e       	rla	r14		;
    c1ce:	0d 6d       	rlc	r13		;
    c1d0:	08 4f       	mov	r15,	r8	;
    c1d2:	38 b0 00 80 	bit	#-32768,r8	;#0x8000
    c1d6:	09 79       	subc	r9,	r9	;
    c1d8:	39 e3       	inv	r9		;
    c1da:	0e 58       	add	r8,	r14	;
    c1dc:	0d 69       	addc	r9,	r13	;

0000c1de <.LVL17>:
    c1de:	1c 53       	inc	r12		;

0000c1e0 <.LVL18>:
    c1e0:	30 40 9e c1 	br	#0xc19e		;

0000c1e4 <.L6>:
    c1e4:	49 4f       	mov.b	r15,	r9	;
    c1e6:	79 50 9f ff 	add.b	#-97,	r9	;#0xff9f
    c1ea:	78 40 05 00 	mov.b	#5,	r8	;
    c1ee:	48 99       	cmp.b	r9,	r8	;
    c1f0:	04 28       	jnc	$+10     	;abs 0xc1fa

0000c1f2 <.Loc.35.1>:
    c1f2:	3f 50 a9 ff 	add	#-87,	r15	;#0xffa9

0000c1f6 <.LVL20>:
    c1f6:	30 40 c0 c1 	br	#0xc1c0		;

0000c1fa <.L8>:
    c1fa:	49 4f       	mov.b	r15,	r9	;
    c1fc:	79 50 bf ff 	add.b	#-65,	r9	;#0xffbf
    c200:	78 40 05 00 	mov.b	#5,	r8	;
    c204:	48 99       	cmp.b	r9,	r8	;
    c206:	04 28       	jnc	$+10     	;abs 0xc210

0000c208 <.Loc.36.1>:
    c208:	3f 50 c9 ff 	add	#-55,	r15	;#0xffc9

0000c20c <.LVL22>:
    c20c:	30 40 c0 c1 	br	#0xc1c0		;

0000c210 <.L12>:
    c210:	0f 4a       	mov	r10,	r15	;
    c212:	30 40 c0 c1 	br	#0xc1c0		;

0000c216 <Utility_uint16_beToLe>:
    c216:	6d 4c       	mov.b	@r12,	r13	;
    c218:	0d 5d       	rla	r13		;
    c21a:	0d 5d       	rla	r13		;
    c21c:	0d 5d       	rla	r13		;
    c21e:	0d 5d       	rla	r13		;
    c220:	0d 5d       	rla	r13		;
    c222:	0d 5d       	rla	r13		;
    c224:	0d 5d       	rla	r13		;
    c226:	0d 5d       	rla	r13		;

0000c228 <.LVL25>:
    c228:	5c 4c 01 00 	mov.b	1(r12),	r12	;

0000c22c <.LVL26>:
    c22c:	0c dd       	bis	r13,	r12	;

0000c22e <.LVL27>:
    c22e:	30 41       	ret			

0000c230 <Utility_intToHex>:
    c230:	0a 12       	push	r10		;

0000c232 <.LCFI4>:
    c232:	09 12       	push	r9		;

0000c234 <.LCFI5>:
    c234:	08 12       	push	r8		;

0000c236 <.LCFI6>:
    c236:	07 12       	push	r7		;

0000c238 <.LCFI7>:
    c238:	06 12       	push	r6		;

0000c23a <.LCFI8>:
    c23a:	07 4d       	mov	r13,	r7	;
    c23c:	08 4e       	mov	r14,	r8	;

0000c23e <.LVL29>:
    c23e:	0a 4e       	mov	r14,	r10	;
    c240:	0a 5e       	add	r14,	r10	;

0000c242 <.Loc.58.1>:
    c242:	0a 5c       	add	r12,	r10	;
    c244:	ca 43 00 00 	mov.b	#0,	0(r10)	;r3 As==00

0000c248 <.LVL30>:
    c248:	09 4d       	mov	r13,	r9	;

0000c24a <.Loc.60.1>:
    c24a:	36 40 16 c0 	mov	#-16362,r6	;#0xc016

0000c24e <.L15>:
    c24e:	3a 50 fe ff 	add	#-2,	r10	;#0xfffe

0000c252 <.LVL32>:
    c252:	0c 49       	mov	r9,	r12	;
    c254:	0c 87       	sub	r7,	r12	;
    c256:	0c 98       	cmp	r8,	r12	;
    c258:	02 38       	jl	$+6      	;abs 0xc25e

0000c25a <.Loc.63.1>:
    c25a:	30 40 e8 c4 	br	#0xc4e8		;

0000c25e <.L16>:
    c25e:	6c 49       	mov.b	@r9,	r12	;
    c260:	7c f0 0f 00 	and.b	#15,	r12	;#0x000f
    c264:	0c 56       	add	r6,	r12	;
    c266:	ea 4c 01 00 	mov.b	@r12,	1(r10)	;

0000c26a <.LVL34>:
    c26a:	6c 49       	mov.b	@r9,	r12	;
    c26c:	b0 12 20 c5 	call	#-15072	;#0xc520
    c270:	3c f0 ff 00 	and	#255,	r12	;#0x00ff
    c274:	0c 56       	add	r6,	r12	;
    c276:	ea 4c 00 00 	mov.b	@r12,	0(r10)	;

0000c27a <.LVL36>:
    c27a:	19 53       	inc	r9		;

0000c27c <.LVL37>:
    c27c:	30 40 4e c2 	br	#0xc24e		;

0000c280 <timer_initialise>:
    c280:	3d 40 30 02 	mov	#560,	r13	;#0x0230

0000c284 <.Loc.11.1>:
    c284:	7c 40 0a 00 	mov.b	#10,	r12	;#0x000a

0000c288 <.L2>:
    c288:	3c 53       	add	#-1,	r12	;r3 As==11

0000c28a <.Loc.14.1>:
    c28a:	8d 43 00 00 	mov	#0,	0(r13)	;r3 As==00
    c28e:	3d 50 fe ff 	add	#-2,	r13	;#0xfffe

0000c292 <.Loc.15.1>:
    c292:	0c 93       	cmp	#0,	r12	;r3 As==00
    c294:	f9 23       	jnz	$-12     	;abs 0xc288

0000c296 <.Loc.16.1>:
    c296:	82 4c 08 02 	mov	r12,	&0x0208	;

0000c29a <.Loc.17.1>:
    c29a:	30 41       	ret			

0000c29c <timer_callback>:
    c29c:	3f 40 30 02 	mov	#560,	r15	;#0x0230

0000c2a0 <.Loc.22.1>:
    c2a0:	7e 40 0a 00 	mov.b	#10,	r14	;#0x000a

0000c2a4 <.L7>:
    c2a4:	3e 53       	add	#-1,	r14	;r3 As==11

0000c2a6 <.Loc.25.1>:
    c2a6:	8f 93 00 00 	cmp	#0,	0(r15)	;r3 As==00
    c2aa:	0d 20       	jnz	$+28     	;abs 0xc2c6

0000c2ac <.Loc.26.1>:
    c2ac:	0f 4e       	mov	r14,	r15	;
    c2ae:	1f 53       	inc	r15		;
    c2b0:	0f 5f       	rla	r15		;
    c2b2:	8f 4c 08 02 	mov	r12,	520(r15); 0x0208

0000c2b6 <.Loc.27.1>:
    c2b6:	3e 50 0b 00 	add	#11,	r14	;#0x000b

0000c2ba <.LVL7>:
    c2ba:	0e 5e       	rla	r14		;

0000c2bc <.LVL8>:
    c2bc:	8e 4d 08 02 	mov	r13,	520(r14); 0x0208

0000c2c0 <.Loc.28.1>:
    c2c0:	5e 43       	mov.b	#1,	r14	;r3 As==01

0000c2c2 <.L4>:
    c2c2:	0c 4e       	mov	r14,	r12	;

0000c2c4 <.LVL9>:
    c2c4:	30 41       	ret			

0000c2c6 <.L5>:
    c2c6:	3f 50 fe ff 	add	#-2,	r15	;#0xfffe

0000c2ca <.Loc.30.1>:
    c2ca:	0e 93       	cmp	#0,	r14	;r3 As==00
    c2cc:	eb 23       	jnz	$-40     	;abs 0xc2a4

0000c2ce <.Loc.31.1>:
    c2ce:	92 c3 08 02 	bic	#1,	&0x0208	;r3 As==01

0000c2d2 <.Loc.32.1>:
    c2d2:	30 40 c2 c2 	br	#0xc2c2		;

0000c2d6 <timer_set_dummy>:
    c2d6:	a2 d3 08 02 	bis	#2,	&0x0208	;r3 As==10

0000c2da <.Loc.37.1>:
    c2da:	30 41       	ret			

0000c2dc <timer_clear_dummy>:
    c2dc:	a2 c3 08 02 	bic	#2,	&0x0208	;r3 As==10

0000c2e0 <.Loc.41.1>:
    c2e0:	30 41       	ret			

0000c2e2 <timer_is_present>:
    c2e2:	3e 40 30 02 	mov	#560,	r14	;#0x0230

0000c2e6 <.Loc.45.1>:
    c2e6:	7d 40 0a 00 	mov.b	#10,	r13	;#0x000a

0000c2ea <.L13>:
    c2ea:	3d 53       	add	#-1,	r13	;r3 As==11

0000c2ec <.Loc.48.1>:
    c2ec:	8e 9c 00 00 	cmp	r12,	0(r14)	;
    c2f0:	06 24       	jz	$+14     	;abs 0xc2fe
    c2f2:	3e 50 fe ff 	add	#-2,	r14	;#0xfffe

0000c2f6 <.Loc.51.1>:
    c2f6:	0d 93       	cmp	#0,	r13	;r3 As==00
    c2f8:	f8 23       	jnz	$-14     	;abs 0xc2ea

0000c2fa <.L11>:
    c2fa:	0c 4d       	mov	r13,	r12	;

0000c2fc <.LVL16>:
    c2fc:	30 41       	ret			

0000c2fe <.L14>:
    c2fe:	5d 43       	mov.b	#1,	r13	;r3 As==01

0000c300 <.LVL18>:
    c300:	30 40 fa c2 	br	#0xc2fa		;

0000c304 <timer_is_present_remove>:
    c304:	3e 40 30 02 	mov	#560,	r14	;#0x0230

0000c308 <.Loc.57.1>:
    c308:	7d 40 0a 00 	mov.b	#10,	r13	;#0x000a

0000c30c <.L19>:
    c30c:	3d 53       	add	#-1,	r13	;r3 As==11

0000c30e <.Loc.60.1>:
    c30e:	8e 9c 00 00 	cmp	r12,	0(r14)	;
    c312:	08 20       	jnz	$+18     	;abs 0xc324

0000c314 <.Loc.61.1>:
    c314:	3d 50 0b 00 	add	#11,	r13	;#0x000b

0000c318 <.LVL23>:
    c318:	0d 5d       	rla	r13		;

0000c31a <.LVL24>:
    c31a:	8d 43 08 02 	mov	#0,	520(r13);r3 As==00, 0x0208

0000c31e <.Loc.62.1>:
    c31e:	5d 43       	mov.b	#1,	r13	;r3 As==01

0000c320 <.L16>:
    c320:	0c 4d       	mov	r13,	r12	;

0000c322 <.LVL25>:
    c322:	30 41       	ret			

0000c324 <.L17>:
    c324:	3e 50 fe ff 	add	#-2,	r14	;#0xfffe

0000c328 <.Loc.64.1>:
    c328:	0d 93       	cmp	#0,	r13	;r3 As==00
    c32a:	f0 23       	jnz	$-30     	;abs 0xc30c
    c32c:	30 40 20 c3 	br	#0xc320		;

0000c330 <timer_wait_for>:
    c330:	0a 12       	push	r10		;

0000c332 <.LCFI0>:
    c332:	09 12       	push	r9		;

0000c334 <.LCFI1>:
    c334:	32 d0 18 00 	bis	#24,	r2	;#0x0018

0000c338 <.LVL28>:
    c338:	3a 40 30 02 	mov	#560,	r10	;#0x0230
    c33c:	79 40 0a 00 	mov.b	#10,	r9	;#0x000a

0000c340 <.L23>:
    c340:	2c 4a       	mov	@r10,	r12	;
    c342:	0c 93       	cmp	#0,	r12	;r3 As==00
    c344:	06 24       	jz	$+14     	;abs 0xc352

0000c346 <.Loc.77.1>:
    c346:	8a 93 ec ff 	cmp	#0,	-20(r10);r3 As==00, 0xffec
    c34a:	03 20       	jnz	$+8      	;abs 0xc352

0000c34c <.LVL30>:
    c34c:	8a 43 00 00 	mov	#0,	0(r10)	;r3 As==00

0000c350 <.Loc.80.1>:
    c350:	8c 12       	call	r12		;

0000c352 <.L22>:
    c352:	39 53       	add	#-1,	r9	;r3 As==11

0000c354 <.LVL32>:
    c354:	3a 50 fe ff 	add	#-2,	r10	;#0xfffe

0000c358 <.Loc.82.1>:
    c358:	09 93       	cmp	#0,	r9	;r3 As==00
    c35a:	f2 23       	jnz	$-26     	;abs 0xc340

0000c35c <.Loc.86.1>:
    c35c:	30 40 ee c4 	br	#0xc4ee		;

0000c360 <timer_docallbacks>:
    c360:	0a 12       	push	r10		;

0000c362 <.LCFI2>:
    c362:	09 12       	push	r9		;

0000c364 <.LCFI3>:
    c364:	3a 40 30 02 	mov	#560,	r10	;#0x0230

0000c368 <.Loc.88.1>:
    c368:	79 40 0a 00 	mov.b	#10,	r9	;#0x000a

0000c36c <.L30>:
    c36c:	2c 4a       	mov	@r10,	r12	;
    c36e:	0c 93       	cmp	#0,	r12	;r3 As==00
    c370:	06 24       	jz	$+14     	;abs 0xc37e

0000c372 <.Loc.95.1>:
    c372:	8a 93 ec ff 	cmp	#0,	-20(r10);r3 As==00, 0xffec
    c376:	03 20       	jnz	$+8      	;abs 0xc37e

0000c378 <.LVL35>:
    c378:	8a 43 00 00 	mov	#0,	0(r10)	;r3 As==00

0000c37c <.Loc.98.1>:
    c37c:	8c 12       	call	r12		;

0000c37e <.L29>:
    c37e:	39 53       	add	#-1,	r9	;r3 As==11

0000c380 <.LVL37>:
    c380:	3a 50 fe ff 	add	#-2,	r10	;#0xfffe

0000c384 <.Loc.101.1>:
    c384:	09 93       	cmp	#0,	r9	;r3 As==00
    c386:	f2 23       	jnz	$-26     	;abs 0xc36c

0000c388 <.Loc.102.1>:
    c388:	30 40 ee c4 	br	#0xc4ee		;

0000c38c <hwuart_sendb>:
    c38c:	c2 4c 67 00 	mov.b	r12,	&0x0067	;

0000c390 <.L2>:
    c390:	e2 b3 03 00 	bit.b	#2,	&0x0003	;r3 As==10
    c394:	01 24       	jz	$+4      	;abs 0xc398

0000c396 <.Loc.13.1>:
    c396:	30 41       	ret			

0000c398 <.L3>:
    c398:	03 43       	nop			
    c39a:	30 40 90 c3 	br	#0xc390		;

0000c39e <hwuart_sendstr>:
    c39e:	6d 4c       	mov.b	@r12,	r13	;
    c3a0:	0d 93       	cmp	#0,	r13	;r3 As==00
    c3a2:	01 20       	jnz	$+4      	;abs 0xc3a6

0000c3a4 <.Loc.20.1>:
    c3a4:	30 41       	ret			

0000c3a6 <.L8>:
    c3a6:	1c 53       	inc	r12		;

0000c3a8 <.LVL2>:
    c3a8:	c2 4d 67 00 	mov.b	r13,	&0x0067	;

0000c3ac <.L6>:
    c3ac:	e2 b3 03 00 	bit.b	#2,	&0x0003	;r3 As==10
    c3b0:	f6 23       	jnz	$-18     	;abs 0xc39e

0000c3b2 <.Loc.18.1>:
    c3b2:	03 43       	nop			
    c3b4:	30 40 ac c3 	br	#0xc3ac		;

0000c3b8 <USCI0RX_ISR>:
    c3b8:	0c 12       	push	r12		;

0000c3ba <.LCFI0>:
    c3ba:	d2 b3 03 00 	bit.b	#1,	&0x0003	;r3 As==01
    c3be:	09 24       	jz	$+20     	;abs 0xc3d2

0000c3c0 <.Loc.25.1>:
    c3c0:	5c 42 66 00 	mov.b	&0x0066,r12	;0x0066
    c3c4:	82 4c 32 02 	mov	r12,	&0x0232	;

0000c3c8 <.Loc.26.1>:
    c3c8:	92 d3 34 02 	bis	#1,	&0x0234	;r3 As==01

0000c3cc <.Loc.27.1>:
    c3cc:	b1 c0 10 00 	bic	#16,	2(r1)	;#0x0010
    c3d0:	02 00 

0000c3d2 <.L9>:
    c3d2:	3c 41       	pop	r12		;
    c3d4:	00 13       	reti			

0000c3d6 <USCI0TX_ISR>:
    c3d6:	00 13       	reti			

0000c3d8 <rtc_initialise>:
    c3d8:	3c 40 36 02 	mov	#566,	r12	;#0x0236
    c3dc:	8c 43 00 00 	mov	#0,	0(r12)	;r3 As==00

0000c3e0 <.Loc.11.1>:
    c3e0:	8c 43 02 00 	mov	#0,	2(r12)	;r3 As==00

0000c3e4 <.Loc.12.1>:
    c3e4:	8c 43 04 00 	mov	#0,	4(r12)	;r3 As==00

0000c3e8 <.Loc.13.1>:
    c3e8:	8c 43 06 00 	mov	#0,	6(r12)	;r3 As==00

0000c3ec <.Loc.14.1>:
    c3ec:	30 41       	ret			

0000c3ee <Timer0_A0>:
    c3ee:	0c 12       	push	r12		;

0000c3f0 <.LCFI0>:
    c3f0:	3c 40 36 02 	mov	#566,	r12	;#0x0236
    c3f4:	9c 53 06 00 	inc	6(r12)		;

0000c3f8 <.Loc.21.1>:
    c3f8:	3c 41       	pop	r12		;
    c3fa:	00 13       	reti			

0000c3fc <udivmodhi4>:
    c3fc:	0a 12       	push	r10		;

0000c3fe <.LCFI0>:
    c3fe:	09 12       	push	r9		;

0000c400 <.LCFI1>:
    c400:	08 12       	push	r8		;

0000c402 <.LCFI2>:
    c402:	07 12       	push	r7		;

0000c404 <.LCFI3>:
    c404:	06 12       	push	r6		;

0000c406 <.LCFI4>:
    c406:	07 4c       	mov	r12,	r7	;
    c408:	09 4d       	mov	r13,	r9	;
    c40a:	06 4e       	mov	r14,	r6	;

0000c40c <.LVL1>:
    c40c:	7a 40 11 00 	mov.b	#17,	r10	;#0x0011

0000c410 <.Loc.35.1>:
    c410:	58 43       	mov.b	#1,	r8	;r3 As==01

0000c412 <.L2>:
    c412:	09 97       	cmp	r7,	r9	;
    c414:	09 28       	jnc	$+20     	;abs 0xc428

0000c416 <.L15>:
    c416:	4a 43       	clr.b	r10		;

0000c418 <.L4>:
    c418:	08 93       	cmp	#0,	r8	;r3 As==00
    c41a:	0f 20       	jnz	$+32     	;abs 0xc43a

0000c41c <.L5>:
    c41c:	06 93       	cmp	#0,	r6	;r3 As==00
    c41e:	01 24       	jz	$+4      	;abs 0xc422
    c420:	0a 47       	mov	r7,	r10	;

0000c422 <.L1>:
    c422:	0c 4a       	mov	r10,	r12	;
    c424:	30 40 e8 c4 	br	#0xc4e8		;

0000c428 <.L3>:
    c428:	3a 53       	add	#-1,	r10	;r3 As==11

0000c42a <.Loc.38.1>:
    c42a:	0a 93       	cmp	#0,	r10	;r3 As==00
    c42c:	f7 27       	jz	$-16     	;abs 0xc41c

0000c42e <.Loc.38.1>:
    c42e:	09 93       	cmp	#0,	r9	;r3 As==00
    c430:	f2 3b       	jl	$-26     	;abs 0xc416

0000c432 <.Loc.40.1>:
    c432:	09 59       	rla	r9		;

0000c434 <.Loc.41.1>:
    c434:	08 58       	rla	r8		;
    c436:	30 40 12 c4 	br	#0xc412		;

0000c43a <.L9>:
    c43a:	07 99       	cmp	r9,	r7	;
    c43c:	02 28       	jnc	$+6      	;abs 0xc442

0000c43e <.Loc.47.1>:
    c43e:	07 89       	sub	r9,	r7	;

0000c440 <.Loc.48.1>:
    c440:	0a d8       	bis	r8,	r10	;

0000c442 <.L8>:
    c442:	0c 48       	mov	r8,	r12	;
    c444:	b0 12 2c c5 	call	#-15060	;#0xc52c
    c448:	08 4c       	mov	r12,	r8	;

0000c44a <.Loc.51.1>:
    c44a:	0c 49       	mov	r9,	r12	;
    c44c:	b0 12 2c c5 	call	#-15060	;#0xc52c
    c450:	09 4c       	mov	r12,	r9	;
    c452:	30 40 18 c4 	br	#0xc418		;

0000c456 <__mspabi_divi>:
    c456:	0a 12       	push	r10		;

0000c458 <.LCFI5>:
    c458:	0f 4c       	mov	r12,	r15	;
    c45a:	0e 4d       	mov	r13,	r14	;

0000c45c <.LVL16>:
    c45c:	3b 40 fc c3 	mov	#-15364,r11	;#0xc3fc

0000c460 <.Loc.64.1>:
    c460:	0c 93       	cmp	#0,	r12	;r3 As==00
    c462:	1a 34       	jge	$+54     	;abs 0xc498

0000c464 <.Loc.66.1>:
    c464:	4c 43       	clr.b	r12		;

0000c466 <.LVL17>:
    c466:	0c 8f       	sub	r15,	r12	;
    c468:	0f 4c       	mov	r12,	r15	;

0000c46a <.LVL18>:
    c46a:	0d 93       	cmp	#0,	r13	;r3 As==00
    c46c:	0d 34       	jge	$+28     	;abs 0xc488

0000c46e <.Loc.67.1>:
    c46e:	5a 43       	mov.b	#1,	r10	;r3 As==01

0000c470 <.L21>:
    c470:	0d 43       	clr	r13		;
    c472:	0d 8e       	sub	r14,	r13	;

0000c474 <.LVL20>:
    c474:	4e 43       	clr.b	r14		;

0000c476 <.LVL21>:
    c476:	0c 4f       	mov	r15,	r12	;

0000c478 <.LVL22>:
    c478:	8b 12       	call	r11		;

0000c47a <.LVL23>:
    c47a:	1a 93       	cmp	#1,	r10	;r3 As==01
    c47c:	03 24       	jz	$+8      	;abs 0xc484

0000c47e <.L20>:
    c47e:	4d 43       	clr.b	r13		;
    c480:	0d 8c       	sub	r12,	r13	;
    c482:	0c 4d       	mov	r13,	r12	;

0000c484 <.L16>:
    c484:	3a 41       	pop	r10		;
    c486:	30 41       	ret			

0000c488 <.L18>:
    c488:	4e 43       	clr.b	r14		;
    c48a:	8b 12       	call	r11		;

0000c48c <.LVL27>:
    c48c:	30 40 7e c4 	br	#0xc47e		;

0000c490 <.L27>:
    c490:	4e 43       	clr.b	r14		;
    c492:	8b 12       	call	r11		;

0000c494 <.LVL29>:
    c494:	30 40 84 c4 	br	#0xc484		;

0000c498 <.L17>:
    c498:	0d 93       	cmp	#0,	r13	;r3 As==00
    c49a:	fa 37       	jge	$-10     	;abs 0xc490

0000c49c <.Loc.61.1>:
    c49c:	4a 43       	clr.b	r10		;
    c49e:	30 40 70 c4 	br	#0xc470		;

0000c4a2 <__mspabi_remi>:
    c4a2:	0a 12       	push	r10		;

0000c4a4 <.LCFI6>:
    c4a4:	0c 93       	cmp	#0,	r12	;r3 As==00
    c4a6:	13 34       	jge	$+40     	;abs 0xc4ce

0000c4a8 <.Loc.92.1>:
    c4a8:	4e 43       	clr.b	r14		;
    c4aa:	0e 8c       	sub	r12,	r14	;
    c4ac:	0c 4e       	mov	r14,	r12	;

0000c4ae <.LVL33>:
    c4ae:	5a 43       	mov.b	#1,	r10	;r3 As==01

0000c4b0 <.L29>:
    c4b0:	0d 93       	cmp	#0,	r13	;r3 As==00
    c4b2:	03 34       	jge	$+8      	;abs 0xc4ba
    c4b4:	4e 43       	clr.b	r14		;
    c4b6:	0e 8d       	sub	r13,	r14	;
    c4b8:	0d 4e       	mov	r14,	r13	;

0000c4ba <.L30>:
    c4ba:	5e 43       	mov.b	#1,	r14	;r3 As==01
    c4bc:	b0 12 fc c3 	call	#-15364	;#0xc3fc

0000c4c0 <.LVL36>:
    c4c0:	0a 93       	cmp	#0,	r10	;r3 As==00
    c4c2:	03 24       	jz	$+8      	;abs 0xc4ca

0000c4c4 <.LVL37>:
    c4c4:	4d 43       	clr.b	r13		;
    c4c6:	0d 8c       	sub	r12,	r13	;
    c4c8:	0c 4d       	mov	r13,	r12	;

0000c4ca <.L28>:
    c4ca:	3a 41       	pop	r10		;
    c4cc:	30 41       	ret			

0000c4ce <.L32>:
    c4ce:	4a 43       	clr.b	r10		;
    c4d0:	30 40 b0 c4 	br	#0xc4b0		;

0000c4d4 <__mspabi_divu>:
    c4d4:	4e 43       	clr.b	r14		;
    c4d6:	b0 12 fc c3 	call	#-15364	;#0xc3fc

0000c4da <.LVL41>:
    c4da:	30 41       	ret			

0000c4dc <__mspabi_remu>:
    c4dc:	5e 43       	mov.b	#1,	r14	;r3 As==01
    c4de:	b0 12 fc c3 	call	#-15364	;#0xc3fc

0000c4e2 <.LVL43>:
    c4e2:	30 41       	ret			

0000c4e4 <__mspabi_func_epilog_7>:
    c4e4:	34 41       	pop	r4		;

0000c4e6 <__mspabi_func_epilog_6>:
    c4e6:	35 41       	pop	r5		;

0000c4e8 <__mspabi_func_epilog_5>:
    c4e8:	36 41       	pop	r6		;

0000c4ea <__mspabi_func_epilog_4>:
    c4ea:	37 41       	pop	r7		;

0000c4ec <__mspabi_func_epilog_3>:
    c4ec:	38 41       	pop	r8		;

0000c4ee <__mspabi_func_epilog_2>:
    c4ee:	39 41       	pop	r9		;

0000c4f0 <__mspabi_func_epilog_1>:
    c4f0:	3a 41       	pop	r10		;
    c4f2:	30 41       	ret			

0000c4f4 <__mspabi_srli_15>:
    c4f4:	12 c3       	clrc			
    c4f6:	0c 10       	rrc	r12		;

0000c4f8 <__mspabi_srli_14>:
    c4f8:	12 c3       	clrc			
    c4fa:	0c 10       	rrc	r12		;

0000c4fc <__mspabi_srli_13>:
    c4fc:	12 c3       	clrc			
    c4fe:	0c 10       	rrc	r12		;

0000c500 <__mspabi_srli_12>:
    c500:	12 c3       	clrc			
    c502:	0c 10       	rrc	r12		;

0000c504 <__mspabi_srli_11>:
    c504:	12 c3       	clrc			
    c506:	0c 10       	rrc	r12		;

0000c508 <__mspabi_srli_10>:
    c508:	12 c3       	clrc			
    c50a:	0c 10       	rrc	r12		;

0000c50c <__mspabi_srli_9>:
    c50c:	12 c3       	clrc			
    c50e:	0c 10       	rrc	r12		;

0000c510 <__mspabi_srli_8>:
    c510:	12 c3       	clrc			
    c512:	0c 10       	rrc	r12		;

0000c514 <__mspabi_srli_7>:
    c514:	12 c3       	clrc			
    c516:	0c 10       	rrc	r12		;

0000c518 <__mspabi_srli_6>:
    c518:	12 c3       	clrc			
    c51a:	0c 10       	rrc	r12		;

0000c51c <__mspabi_srli_5>:
    c51c:	12 c3       	clrc			
    c51e:	0c 10       	rrc	r12		;

0000c520 <__mspabi_srli_4>:
    c520:	12 c3       	clrc			
    c522:	0c 10       	rrc	r12		;

0000c524 <__mspabi_srli_3>:
    c524:	12 c3       	clrc			
    c526:	0c 10       	rrc	r12		;

0000c528 <__mspabi_srli_2>:
    c528:	12 c3       	clrc			
    c52a:	0c 10       	rrc	r12		;

0000c52c <__mspabi_srli_1>:
    c52c:	12 c3       	clrc			
    c52e:	0c 10       	rrc	r12		;
    c530:	30 41       	ret			

0000c532 <.L11>:
    c532:	3d 53       	add	#-1,	r13	;r3 As==11
    c534:	12 c3       	clrc			
    c536:	0c 10       	rrc	r12		;

0000c538 <__mspabi_srli>:
    c538:	0d 93       	cmp	#0,	r13	;r3 As==00
    c53a:	fb 23       	jnz	$-8      	;abs 0xc532
    c53c:	30 41       	ret			

0000c53e <__mspabi_srll_15>:
    c53e:	12 c3       	clrc			
    c540:	0d 10       	rrc	r13		;
    c542:	0c 10       	rrc	r12		;

0000c544 <__mspabi_srll_14>:
    c544:	12 c3       	clrc			
    c546:	0d 10       	rrc	r13		;
    c548:	0c 10       	rrc	r12		;

0000c54a <__mspabi_srll_13>:
    c54a:	12 c3       	clrc			
    c54c:	0d 10       	rrc	r13		;
    c54e:	0c 10       	rrc	r12		;

0000c550 <__mspabi_srll_12>:
    c550:	12 c3       	clrc			
    c552:	0d 10       	rrc	r13		;
    c554:	0c 10       	rrc	r12		;

0000c556 <__mspabi_srll_11>:
    c556:	12 c3       	clrc			
    c558:	0d 10       	rrc	r13		;
    c55a:	0c 10       	rrc	r12		;

0000c55c <__mspabi_srll_10>:
    c55c:	12 c3       	clrc			
    c55e:	0d 10       	rrc	r13		;
    c560:	0c 10       	rrc	r12		;

0000c562 <__mspabi_srll_9>:
    c562:	12 c3       	clrc			
    c564:	0d 10       	rrc	r13		;
    c566:	0c 10       	rrc	r12		;

0000c568 <__mspabi_srll_8>:
    c568:	12 c3       	clrc			
    c56a:	0d 10       	rrc	r13		;
    c56c:	0c 10       	rrc	r12		;

0000c56e <__mspabi_srll_7>:
    c56e:	12 c3       	clrc			
    c570:	0d 10       	rrc	r13		;
    c572:	0c 10       	rrc	r12		;

0000c574 <__mspabi_srll_6>:
    c574:	12 c3       	clrc			
    c576:	0d 10       	rrc	r13		;
    c578:	0c 10       	rrc	r12		;

0000c57a <__mspabi_srll_5>:
    c57a:	12 c3       	clrc			
    c57c:	0d 10       	rrc	r13		;
    c57e:	0c 10       	rrc	r12		;

0000c580 <__mspabi_srll_4>:
    c580:	12 c3       	clrc			
    c582:	0d 10       	rrc	r13		;
    c584:	0c 10       	rrc	r12		;

0000c586 <__mspabi_srll_3>:
    c586:	12 c3       	clrc			
    c588:	0d 10       	rrc	r13		;
    c58a:	0c 10       	rrc	r12		;

0000c58c <__mspabi_srll_2>:
    c58c:	12 c3       	clrc			
    c58e:	0d 10       	rrc	r13		;
    c590:	0c 10       	rrc	r12		;

0000c592 <__mspabi_srll_1>:
    c592:	12 c3       	clrc			
    c594:	0d 10       	rrc	r13		;
    c596:	0c 10       	rrc	r12		;
    c598:	30 41       	ret			

0000c59a <.L12>:
    c59a:	3e 53       	add	#-1,	r14	;r3 As==11
    c59c:	12 c3       	clrc			
    c59e:	0d 10       	rrc	r13		;
    c5a0:	0c 10       	rrc	r12		;

0000c5a2 <__mspabi_srll>:
    c5a2:	0e 93       	cmp	#0,	r14	;r3 As==00
    c5a4:	fa 23       	jnz	$-10     	;abs 0xc59a
    c5a6:	30 41       	ret			

Disassembly of section __reset_vector:

0000fffe <__reset_vector>:
    fffe:	0c c0       	interrupt service routine at 0xc00c
