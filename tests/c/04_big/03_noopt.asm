include a1.inc

	string_const$1	db 	020h, "$"

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+54]
	@@l$a	equ dword ptr ss:[ebp+12]
	@@l$i	equ dword ptr ss:[ebp+8]
	@@l$j	equ dword ptr ss:[ebp+4]
	sub	esp,48
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
	push	dword ptr 9
	pop	eax
	pop	ebx
	sub	eax,ebx
	push	eax
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
	push	dword ptr 10
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
	add	eax,dword ptr 8
	push	eax
	push	dword ptr 0
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$3:
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$i
	pop	eax
	pop	ebx
	add	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$5:
	push	@@l$j
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	push	@@l$i
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setg	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$7
	push	@@l$i
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	@@l$j
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	call	f$swap
lbl$7:
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	inc	dword ptr ss:[eax]
	push	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	dword ptr 10
	push	@@l$j
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$6
	jmp	lbl$5
lbl$6:
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	pop	eax
	inc	dword ptr ss:[eax]
	push	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	dword ptr 10
	push	@@l$i
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$4
	jmp	lbl$3
lbl$4:
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	push	dword ptr 0
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$8:
	push	@@l$i
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	pop	eax
	inc	dword ptr ss:[eax]
	push	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	dword ptr 10
	push	@@l$i
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$9
	jmp	lbl$8
lbl$9:

@@lbl_exit:
	pop	ebp
	add	esp,48
	ret	0
f$main endp

f$swap proc
	@@result	equ dword ptr ss:[ebp+18]
	@@p$a	equ dword ptr ss:[ebp+14]
	@@p$b	equ dword ptr ss:[ebp+10]
	@@l$tmp	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	@@p$a
	pop	eax
	push	dword ptr ss:[eax]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@p$a
	push	@@p$b
	pop	eax
	push	dword ptr ss:[eax]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@p$b
	push	@@l$tmp
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	8
f$swap endp

include b.inc