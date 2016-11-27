include a1.inc

	real_const$1	dd	4.000000e+000
	real_const$2	dd	4.000000e+000

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+10]
	@@l$x	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 3
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	real_const$1
	push	@@l$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	call	f$print_int
	push	dword ptr 4
	push	@@l$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	call	f$print_int
	push	@@l$x
	push	dword ptr 4
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	call	f$print_int
	push	@@l$x
	push	real_const$2
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc