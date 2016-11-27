include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,dword ptr 3
	mov	ebx,dword ptr 2
	xor	ecx,ecx
	cmp	eax,ebx
	setg	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$1
	push	dword ptr 1
	call	f$print_int
	jmp	lbl$2
lbl$1:
	push	dword ptr 0
	call	f$print_int
lbl$2:
	mov	eax,dword ptr 2
	mov	ebx,dword ptr 3
	xor	ecx,ecx
	cmp	eax,ebx
	setg	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$3
	push	dword ptr 0
	call	f$print_int
	jmp	lbl$4
lbl$3:
	push	dword ptr 1
	call	f$print_int
lbl$4:

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc