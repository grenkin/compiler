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
	push	eax
	push	dword ptr 1
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$1:
	push	@@l$i
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	inc	dword ptr ss:[eax]
	push	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	dword ptr 5
	push	@@l$i
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setle	cl
	push	ecx
	pop	eax
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