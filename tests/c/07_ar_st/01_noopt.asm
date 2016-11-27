include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+26]
	@@l$p	equ dword ptr ss:[ebp+8]
	@@l$x	equ dword ptr ss:[ebp+4]
	sub	esp,20
	push	ebp
	mov	ebp,esp

	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
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
	push	dword ptr 1
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
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
	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
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
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 4
	push	dword ptr ss:[eax]
	call	f$print_int
	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 1
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	eax
	push	dword ptr 1
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 4
	push	dword ptr ss:[eax]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
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
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 8
	add	eax,ebx
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,20
	ret	0
f$main endp

include b.inc