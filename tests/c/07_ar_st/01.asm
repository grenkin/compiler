include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+26]
	@@l$p	equ dword ptr ss:[ebp+8]
	@@l$x	equ dword ptr ss:[ebp+4]
	sub	esp,20
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 0
	imul	ebx,dword ptr 8
	add	eax,ebx
	add	eax,dword ptr 0
	mov	ebx,dword ptr 1
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 1
	imul	ebx,dword ptr 8
	add	eax,ebx
	add	eax,dword ptr 4
	mov	ebx,dword ptr 2
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 0
	imul	ebx,dword ptr 8
	add	eax,ebx
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 1
	imul	ebx,dword ptr 8
	add	eax,ebx
	add	eax,dword ptr 4
	push	dword ptr ss:[eax]
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 0
	imul	ebx,dword ptr 8
	add	eax,ebx
	add	eax,dword ptr 4
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 0
	imul	ebx,dword ptr 8
	add	eax,ebx
	add	eax,dword ptr 0
	mov	ebx,dword ptr ss:[eax]
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 1
	imul	ebx,dword ptr 8
	add	eax,ebx
	add	eax,dword ptr 0
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 1
	imul	ebx,dword ptr 8
	add	eax,ebx
	add	eax,dword ptr 4
	mov	ebx,dword ptr ss:[eax]
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 0
	imul	ebx,dword ptr 8
	add	eax,ebx
	add	eax,dword ptr 4
	push	dword ptr ss:[eax]
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 1
	imul	ebx,dword ptr 8
	add	eax,ebx
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,20
	ret	0
f$main endp

include b.inc