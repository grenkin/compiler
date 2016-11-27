include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+30]
	@@l$a	equ dword ptr ss:[ebp+4]
	sub	esp,24
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 3
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 1
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 5
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 3
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	eax,dword ptr ss:[eax]
	inc	eax
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 3
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 5
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