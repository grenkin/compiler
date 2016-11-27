include a1.inc

	string_const$1	db 	0ah, "$"
	string_const$2	db 	0ah, "$"

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+14]
	@@l$x	equ dword ptr ss:[ebp+8]
	@@l$y	equ dword ptr ss:[ebp+4]
	sub	esp,8
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	push	dword ptr 3
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 5
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 3
	push	@@l$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jnz	lbl$1
	push	dword ptr 5
	push	@@l$y
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jnz	lbl$1
	push	dword ptr 0
	jmp	lbl$2
lbl$1:
	push	dword ptr 1
lbl$2:
	call	f$print_int
	push	dword ptr 3
	push	@@l$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$3
	push	dword ptr 5
	push	@@l$y
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$3
	push	dword ptr 1
	jmp	lbl$4
lbl$3:
	push	dword ptr 0
lbl$4:
	call	f$print_int
	push	dword ptr 3
	push	@@l$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jnz	lbl$5
	push	dword ptr 4
	push	@@l$y
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jnz	lbl$5
	push	dword ptr 0
	jmp	lbl$6
lbl$5:
	push	dword ptr 1
lbl$6:
	call	f$print_int
	push	dword ptr 3
	push	@@l$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$7
	push	dword ptr 4
	push	@@l$y
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$7
	push	dword ptr 1
	jmp	lbl$8
lbl$7:
	push	dword ptr 0
lbl$8:
	call	f$print_int
	push	dword ptr 4
	push	@@l$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jnz	lbl$9
	push	dword ptr 5
	push	@@l$y
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jnz	lbl$9
	push	dword ptr 0
	jmp	lbl$10
lbl$9:
	push	dword ptr 1
lbl$10:
	call	f$print_int
	push	dword ptr 4
	push	@@l$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$11
	push	dword ptr 5
	push	@@l$y
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$11
	push	dword ptr 1
	jmp	lbl$12
lbl$11:
	push	dword ptr 0
lbl$12:
	call	f$print_int
	push	dword ptr 4
	push	@@l$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jnz	lbl$13
	push	dword ptr 4
	push	@@l$y
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jnz	lbl$13
	push	dword ptr 0
	jmp	lbl$14
lbl$13:
	push	dword ptr 1
lbl$14:
	call	f$print_int
	push	dword ptr 4
	push	@@l$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$15
	push	dword ptr 4
	push	@@l$y
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$15
	push	dword ptr 1
	jmp	lbl$16
lbl$15:
	push	dword ptr 0
lbl$16:
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string
	push	dword ptr 3
	pop	eax
	test	eax,eax
	jz	lbl$17
	push	dword ptr 5
	pop	eax
	test	eax,eax
	jz	lbl$17
	push	dword ptr 1
	jmp	lbl$18
lbl$17:
	push	dword ptr 0
lbl$18:
	call	f$print_int
	push	dword ptr 0
	pop	eax
	test	eax,eax
	jz	lbl$19
	push	dword ptr 3
	pop	eax
	test	eax,eax
	jz	lbl$19
	push	dword ptr 1
	jmp	lbl$20
lbl$19:
	push	dword ptr 0
lbl$20:
	call	f$print_int
	push	dword ptr 3
	pop	eax
	test	eax,eax
	jz	lbl$21
	push	dword ptr 0
	pop	eax
	test	eax,eax
	jz	lbl$21
	push	dword ptr 1
	jmp	lbl$22
lbl$21:
	push	dword ptr 0
lbl$22:
	call	f$print_int
	push	dword ptr 0
	pop	eax
	test	eax,eax
	jz	lbl$23
	push	dword ptr 0
	pop	eax
	test	eax,eax
	jz	lbl$23
	push	dword ptr 1
	jmp	lbl$24
lbl$23:
	push	dword ptr 0
lbl$24:
	call	f$print_int
	push	0
	push	offset string_const$2
	call	f$print_string
	push	dword ptr 3
	pop	eax
	test	eax,eax
	jnz	lbl$25
	push	dword ptr 5
	pop	eax
	test	eax,eax
	jnz	lbl$25
	push	dword ptr 0
	jmp	lbl$26
lbl$25:
	push	dword ptr 1
lbl$26:
	call	f$print_int
	push	dword ptr 0
	pop	eax
	test	eax,eax
	jnz	lbl$27
	push	dword ptr 3
	pop	eax
	test	eax,eax
	jnz	lbl$27
	push	dword ptr 0
	jmp	lbl$28
lbl$27:
	push	dword ptr 1
lbl$28:
	call	f$print_int
	push	dword ptr 3
	pop	eax
	test	eax,eax
	jnz	lbl$29
	push	dword ptr 0
	pop	eax
	test	eax,eax
	jnz	lbl$29
	push	dword ptr 0
	jmp	lbl$30
lbl$29:
	push	dword ptr 1
lbl$30:
	call	f$print_int
	push	dword ptr 0
	pop	eax
	test	eax,eax
	jnz	lbl$31
	push	dword ptr 0
	pop	eax
	test	eax,eax
	jnz	lbl$31
	push	dword ptr 0
	jmp	lbl$32
lbl$31:
	push	dword ptr 1
lbl$32:
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,8
	ret	0
f$main endp

include b.inc