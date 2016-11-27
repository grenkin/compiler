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
	push	eax
	push	dword ptr 0
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$1:
	push	@@l$i
	push	@@p$p
	pop	eax
	add	eax,dword ptr 0
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_float
	push	0
	push	offset string_const$1
	call	f$print_string
	mov	eax,ebp
	add	eax,dword ptr 4
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
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$3:
	push	@@l$i
	push	@@p$p
	pop	eax
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int
	push	0
	push	offset string_const$2
	call	f$print_string
	mov	eax,ebp
	add	eax,dword ptr 4
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

	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 5
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 1
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 6
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 2
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 7
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 12
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
	push	dword ptr 1
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 2
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 2
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 3
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
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