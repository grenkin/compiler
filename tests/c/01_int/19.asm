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
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
	mov	eax,@@l$x
	mov	ebx,dword ptr 0
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	mov	eax,ecx
	test	eax,eax
	jnz	lbl$1
	mov	eax,dword ptr 1
	mov	ebx,@@l$x
	cdq
	idiv	ebx
	test	eax,eax
	jnz	lbl$1
	push	dword ptr 0
	jmp	lbl$2
lbl$1:
	push	dword ptr 1
lbl$2:
	call	f$print_int
	mov	eax,@@l$x
	mov	ebx,dword ptr 0
	xor	ecx,ecx
	cmp	eax,ebx
	setne	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$3
	mov	eax,dword ptr 1
	mov	ebx,@@l$x
	cdq
	idiv	ebx
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