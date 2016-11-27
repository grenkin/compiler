include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+26]
	@@l$a	equ dword ptr ss:[ebp+12]
	@@l$i	equ dword ptr ss:[ebp+8]
	@@l$p	equ dword ptr ss:[ebp+4]
	sub	esp,20
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	push	dword ptr 0
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$1:
	push	@@l$i
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	@@l$i
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	pop	eax
	inc	dword ptr ss:[eax]
	push	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	dword ptr 3
	push	@@l$i
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$2
	jmp	lbl$1
lbl$2:
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$p
	pop	eax
	push	dword ptr ss:[eax]
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$p
	pop	eax
	push	dword ptr ss:[eax]
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 2
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$p
	pop	eax
	push	dword ptr ss:[eax]
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,20
	ret	0
f$main endp

include b.inc