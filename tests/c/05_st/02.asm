include a1.inc

	g$a	dd	1 dup (0)

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+18]
	@@l$b	equ dword ptr ss:[ebp+12]
	@@l$c	equ dword ptr ss:[ebp+4]
	sub	esp,12
	push	ebp
	mov	ebp,esp

	push	0
	push	offset g$a
	pop	eax
	add	eax,dword ptr 0
	push	eax
	mov	eax,dword ptr 1
	neg	eax
	mov	ebx,eax
	pop	eax
	mov	dword ptr [eax],ebx
	push	ebx
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 12
	add	eax,dword ptr 0
	push	eax
	mov	eax,dword ptr 5
	neg	eax
	add	eax,dword ptr 10
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 4
	add	eax,dword ptr 0
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 12
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	push	0
	push	offset g$a
	pop	eax
	add	eax,dword ptr 0
	mov	eax,dword ptr [eax]
	pop	ebx
	imul	eax,ebx
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,12
	ret	0
f$main endp

include b.inc