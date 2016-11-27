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
	mov	ebx,dword ptr 1
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@l$x
	imul	eax,dword ptr 2
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@l$x
	mov	ebx,dword ptr 2
	cdq
	idiv	ebx
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@l$x
	add	eax,dword ptr 10
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@l$x
	mov	ebx,dword ptr 7
	cdq
	idiv	ebx
	mov	ebx,edx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@l$x
	sub	eax,dword ptr 2
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@l$x
	mov	ebx,dword ptr 1
	mov	cl,bl
	shl	eax,cl
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@l$x
	mov	ebx,dword ptr 1
	mov	cl,bl
	shr	eax,cl
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@l$x
	and	eax,dword ptr 3
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@l$x
	or	eax,dword ptr 1
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@l$x
	xor	eax,dword ptr 1
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc