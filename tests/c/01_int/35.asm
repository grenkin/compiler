include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,dword ptr 1
	test	eax,eax
	jnz	lbl$1
	mov	eax,dword ptr 1
	test	eax,eax
	jnz	lbl$1
	push	dword ptr 0
	jmp	lbl$2
lbl$1:
	push	dword ptr 1
lbl$2:
	call	f$print_int
	mov	eax,dword ptr 0
	test	eax,eax
	jnz	lbl$3
	mov	eax,dword ptr 1
	test	eax,eax
	jnz	lbl$3
	push	dword ptr 0
	jmp	lbl$4
lbl$3:
	push	dword ptr 1
lbl$4:
	call	f$print_int
	mov	eax,dword ptr 0
	test	eax,eax
	jnz	lbl$5
	mov	eax,dword ptr 0
	test	eax,eax
	jnz	lbl$5
	push	dword ptr 0
	jmp	lbl$6
lbl$5:
	push	dword ptr 1
lbl$6:
	call	f$print_int
	mov	eax,dword ptr 3
	test	eax,eax
	jz	lbl$7
	mov	eax,dword ptr 5
	test	eax,eax
	jz	lbl$7
	push	dword ptr 1
	jmp	lbl$8
lbl$7:
	push	dword ptr 0
lbl$8:
	call	f$print_int
	mov	eax,dword ptr 3
	test	eax,eax
	jz	lbl$9
	mov	eax,dword ptr 0
	test	eax,eax
	jz	lbl$9
	push	dword ptr 1
	jmp	lbl$10
lbl$9:
	push	dword ptr 0
lbl$10:
	call	f$print_int
	mov	eax,dword ptr 0
	test	eax,eax
	jz	lbl$11
	mov	eax,dword ptr 3
	test	eax,eax
	jz	lbl$11
	push	dword ptr 1
	jmp	lbl$12
lbl$11:
	push	dword ptr 0
lbl$12:
	call	f$print_int
	mov	eax,dword ptr 0
	test	eax,eax
	jz	lbl$13
	mov	eax,dword ptr 0
	test	eax,eax
	jz	lbl$13
	push	dword ptr 1
	jmp	lbl$14
lbl$13:
	push	dword ptr 0
lbl$14:
	call	f$print_int
	mov	eax,dword ptr 1
	or	eax,dword ptr 0
	push	eax
	call	f$print_int
	mov	eax,dword ptr 0
	or	eax,dword ptr 0
	push	eax
	call	f$print_int
	mov	eax,dword ptr 1
	or	eax,dword ptr 1
	push	eax
	call	f$print_int
	mov	eax,dword ptr 0
	xor	eax,dword ptr 0
	push	eax
	call	f$print_int
	mov	eax,dword ptr 1
	xor	eax,dword ptr 1
	push	eax
	call	f$print_int
	mov	eax,dword ptr 1
	xor	eax,dword ptr 0
	push	eax
	call	f$print_int
	mov	eax,dword ptr 0
	and	eax,dword ptr 0
	push	eax
	call	f$print_int
	mov	eax,dword ptr 1
	and	eax,dword ptr 0
	push	eax
	call	f$print_int
	mov	eax,dword ptr 1
	and	eax,dword ptr 1
	push	eax
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc