include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+10]
	@@l$x	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 0
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 0
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
	push	@@l$x
	push	dword ptr 1
	pop	eax
	pop	ebx
	cdq
	idiv	ebx
	push	eax
	pop	eax
	test	eax,eax
	jnz	lbl$1
	push	dword ptr 0
	jmp	lbl$2
lbl$1:
	push	dword ptr 1
lbl$2:
	call	f$print_int
	push	dword ptr 0
	push	@@l$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setne	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$3
	push	@@l$x
	push	dword ptr 1
	pop	eax
	pop	ebx
	cdq
	idiv	ebx
	push	eax
	pop	eax
	test	eax,eax
	jz	lbl$3
	push	dword ptr 1
	jmp	lbl$4
lbl$3:
	push	dword ptr 0
lbl$4:
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc