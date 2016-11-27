include a1.inc


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
	push	dword ptr 1
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 2
	push	@@l$x
	pop	eax
	pop	ebx
	imul	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 2
	push	@@l$x
	pop	eax
	pop	ebx
	cdq
	idiv	ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 10
	push	@@l$x
	pop	eax
	pop	ebx
	add	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 7
	push	@@l$x
	pop	eax
	pop	ebx
	cdq
	idiv	ebx
	push	edx
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 2
	push	@@l$x
	pop	eax
	pop	ebx
	sub	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$x
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$x
	pop	eax
	pop	ebx
	mov	cl,bl
	shr	eax,cl
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 3
	push	@@l$x
	pop	eax
	pop	ebx
	and	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$x
	pop	eax
	pop	ebx
	or	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$x
	pop	eax
	pop	ebx
	xor	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc