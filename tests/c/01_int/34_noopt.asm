include a1.inc


include a2.inc

f$compare proc
	@@result	equ dword ptr ss:[ebp+14]
	@@p$x	equ dword ptr ss:[ebp+10]
	@@p$y	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	@@p$y
	push	@@p$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	call	f$print_int
	push	@@p$y
	push	@@p$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setle	cl
	push	ecx
	call	f$print_int
	push	@@p$y
	push	@@p$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setg	cl
	push	ecx
	call	f$print_int
	push	@@p$y
	push	@@p$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setge	cl
	push	ecx
	call	f$print_int
	push	@@p$y
	push	@@p$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	call	f$print_int
	push	@@p$y
	push	@@p$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setne	cl
	push	ecx
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	8
f$compare endp

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 1
	push	dword ptr 1
	call	f$compare
	push	dword ptr 5
	push	dword ptr 6
	call	f$compare
	push	dword ptr 10
	push	dword ptr 20
	pop	eax
	neg	eax
	push	eax
	call	f$compare

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc