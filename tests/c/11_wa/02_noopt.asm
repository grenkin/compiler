include a1.inc

	g$A	dd	30 dup (0)

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 0
	push	dword ptr 0
	push	0
	push	offset g$A
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 40
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	eax
	push	dword ptr 1
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 0
	push	dword ptr 0
	push	0
	push	offset g$A
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 40
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 2
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 1
	push	dword ptr 0
	push	0
	push	offset g$A
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 40
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	eax
	push	dword ptr 3
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 1
	push	dword ptr 0
	push	0
	push	offset g$A
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 40
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 4
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 0
	push	dword ptr 0
	push	0
	push	offset g$A
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 40
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	call	f$print_int
	push	dword ptr 0
	push	dword ptr 0
	push	0
	push	offset g$A
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 40
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 4
	push	dword ptr ss:[eax]
	call	f$print_int
	push	dword ptr 1
	push	dword ptr 0
	push	0
	push	offset g$A
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 40
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	call	f$print_int
	push	dword ptr 1
	push	dword ptr 0
	push	0
	push	offset g$A
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 40
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 4
	push	dword ptr ss:[eax]
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc