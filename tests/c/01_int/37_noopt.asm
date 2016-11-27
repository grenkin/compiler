include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 6
	push	dword ptr 2
	pop	eax
	pop	ebx
	imul	eax,ebx
	push	eax
	call	f$print_int
	push	dword ptr 6
	push	dword ptr 2
	pop	eax
	pop	ebx
	cdq
	idiv	ebx
	push	eax
	call	f$print_int
	push	dword ptr 6
	push	dword ptr 2
	pop	eax
	pop	ebx
	cdq
	idiv	ebx
	push	edx
	call	f$print_int
	push	dword ptr 2
	push	dword ptr 6
	pop	eax
	pop	ebx
	cdq
	idiv	ebx
	push	eax
	call	f$print_int
	push	dword ptr 2
	push	dword ptr 6
	pop	eax
	pop	ebx
	cdq
	idiv	ebx
	push	edx
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc