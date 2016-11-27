include a1.inc

	g$x	dd	3 dup (0)

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 0
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 1
	mov	dword ptr ss:[eax],ebx
	push	dword ptr 1
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 2
	mov	dword ptr ss:[eax],ebx
	push	dword ptr 2
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 3
	mov	dword ptr ss:[eax],ebx
	push	dword ptr 0
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int
	push	dword ptr 1
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int
	push	dword ptr 2
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc