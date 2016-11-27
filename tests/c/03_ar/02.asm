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
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
lbl$1:
	mov	eax,ebp
	add	eax,dword ptr 12
	mov	ebx,@@l$i
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,@@l$i
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	inc	dword ptr ss:[eax]
	mov	eax,@@l$i
	mov	ebx,dword ptr 3
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$2
	jmp	lbl$1
lbl$2:
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 12
	mov	ebx,dword ptr 0
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,@@l$p
	push	dword ptr ss:[eax]
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 12
	mov	ebx,dword ptr 1
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,@@l$p
	push	dword ptr ss:[eax]
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 12
	mov	ebx,dword ptr 2
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,@@l$p
	push	dword ptr ss:[eax]
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,20
	ret	0
f$main endp

include b.inc