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
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
lbl$1:
	mov	eax,ebp
	add	eax,dword ptr 12
	mov	ebx,@@l$i
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	mov	eax,dword ptr 9
	sub	eax,@@l$i
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	inc	dword ptr ss:[eax]
	mov	eax,@@l$i
	mov	ebx,dword ptr 10
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$2
	jmp	lbl$1
lbl$2:
	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
lbl$3:
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@l$i
	inc	eax
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
lbl$5:
	mov	eax,ebp
	add	eax,dword ptr 12
	mov	ebx,@@l$j
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	mov	eax,ebp
	add	eax,dword ptr 12
	mov	ebx,@@l$i
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	eax,dword ptr ss:[eax]
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setg	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$7
	mov	eax,ebp
	add	eax,dword ptr 12
	mov	ebx,@@l$i
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 12
	mov	ebx,@@l$j
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	call	f$swap
lbl$7:
	mov	eax,ebp
	add	eax,dword ptr 4
	inc	dword ptr ss:[eax]
	mov	eax,@@l$j
	mov	ebx,dword ptr 10
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$6
	jmp	lbl$5
lbl$6:
	mov	eax,ebp
	add	eax,dword ptr 8
	inc	dword ptr ss:[eax]
	mov	eax,@@l$i
	mov	ebx,dword ptr 10
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$4
	jmp	lbl$3
lbl$4:
	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
lbl$8:
	mov	eax,ebp
	add	eax,dword ptr 12
	mov	ebx,@@l$i
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string
	mov	eax,ebp
	add	eax,dword ptr 8
	inc	dword ptr ss:[eax]
	mov	eax,@@l$i
	mov	ebx,dword ptr 10
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	mov	eax,ecx
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
	mov	eax,@@p$a
	mov	ebx,dword ptr ss:[eax]
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,@@p$b
	mov	ebx,dword ptr ss:[eax]
	mov	eax,@@p$a
	mov	dword ptr ss:[eax],ebx
	mov	ebx,@@l$tmp
	mov	eax,@@p$b
	mov	dword ptr ss:[eax],ebx

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	8
f$swap endp

include b.inc