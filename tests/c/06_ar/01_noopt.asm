include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+30]
	@@l$a	equ dword ptr ss:[ebp+4]
	sub	esp,24
	push	ebp
	mov	ebp,esp

	push	dword ptr 3
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 1
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 5
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 1
	push	dword ptr 3
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	add	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 3
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int
	push	dword ptr 5
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,24
	ret	0
f$main endp

include b.inc