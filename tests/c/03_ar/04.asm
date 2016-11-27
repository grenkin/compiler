include a1.inc

	real_const$1	dd	1.500000e+000
	string_const$1	db 	020h, "$"
	string_const$2	db 	020h, "$"

include a2.inc

f$f proc
	@@result	equ dword ptr ss:[ebp+14]
	@@p$p	equ dword ptr ss:[ebp+10]
	@@l$i	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
lbl$1:
	mov	eax,@@p$p
	add	eax,dword ptr 0
	mov	ebx,@@l$i
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_float
	push	0
	push	offset string_const$1
	call	f$print_string
	mov	eax,ebp
	add	eax,dword ptr 4
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
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
lbl$3:
	mov	eax,@@p$p
	add	eax,dword ptr 12
	mov	ebx,@@l$i
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int
	push	0
	push	offset string_const$2
	call	f$print_string
	mov	eax,ebp
	add	eax,dword ptr 4
	inc	dword ptr ss:[eax]
	mov	eax,@@l$i
	mov	ebx,dword ptr 3
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$4
	jmp	lbl$3
lbl$4:

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	4
f$f endp

f$main proc
	@@result	equ dword ptr ss:[ebp+30]
	@@l$p	equ dword ptr ss:[ebp+4]
	sub	esp,24
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 0
	mov	ebx,dword ptr 0
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 5
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 0
	mov	ebx,dword ptr 1
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 6
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 0
	mov	ebx,dword ptr 2
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 7
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 12
	mov	ebx,dword ptr 0
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 1
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 12
	mov	ebx,dword ptr 1
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 2
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 12
	mov	ebx,dword ptr 2
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 3
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	call	f$f
	push	real_const$1
	call	f$print_float

@@lbl_exit:
	pop	ebp
	add	esp,24
	ret	0
f$main endp

include b.inc