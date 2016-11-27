include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+10]
	@@l$i	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
lbl$1:
	mov	eax,ebp
	add	eax,dword ptr 4
	inc	dword ptr ss:[eax]
	mov	eax,@@l$i
	mov	ebx,dword ptr 2
	cdq
	idiv	ebx
	mov	eax,edx
	mov	ebx,dword ptr 0
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$3
	jmp	lbl$1
lbl$3:
	push	@@l$i
	call	f$print_int
	mov	eax,@@l$i
	mov	ebx,dword ptr 7
	xor	ecx,ecx
	cmp	eax,ebx
	setg	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$4
	jmp	lbl$2
lbl$4:
	mov	eax,dword ptr 1
	test	eax,eax
	jz	lbl$2
	jmp	lbl$1
lbl$2:

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc