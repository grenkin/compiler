include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,dword ptr 1
	mov	ebx,dword ptr 1
	xor	ecx,ecx
	push	dword ptr 0
	push	dword ptr 10
	cmp	eax,ebx
	sete	cl
	mov	eax,ecx
	pop	ebx
	pop	ecx
	test	eax,eax
	jz	lbl$1
	push	ebx
	jmp	lbl$2
lbl$1:
	push	ecx
lbl$2:
	call	f$print_int
	mov	eax,dword ptr 1
	mov	ebx,dword ptr 1
	xor	ecx,ecx
	push	dword ptr 10
	push	dword ptr 0
	cmp	eax,ebx
	setne	cl
	mov	eax,ecx
	pop	ebx
	pop	ecx
	test	eax,eax
	jz	lbl$3
	push	ebx
	jmp	lbl$4
lbl$3:
	push	ecx
lbl$4:
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc