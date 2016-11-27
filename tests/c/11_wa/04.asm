include a1.inc

	g$i	dd	1 dup (0)
	g$x	dd	6 dup (0)

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+30]
	@@l$y	equ dword ptr ss:[ebp+4]
	sub	esp,24
	push	ebp
	mov	ebp,esp

	push	dword ptr 0
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 1
	mov	dword ptr ss:[eax],ebx
	push	dword ptr 1
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 2
	mov	dword ptr ss:[eax],ebx
	push	dword ptr 2
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 3
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 3
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 4
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 4
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 5
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 5
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 6
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 0
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 0
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr ss:[eax]
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 1
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 1
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr ss:[eax]
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 2
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 2
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr ss:[eax]
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	dword ptr 3
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 3
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr ss:[eax]
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	dword ptr 4
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 4
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr ss:[eax]
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	dword ptr 5
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 5
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr ss:[eax]
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	0
	push	offset g$i
	mov	ebx,dword ptr 0
	pop	eax
	mov	dword ptr [eax],ebx
lbl$1:
	push	g$i
	push	0
	push	offset g$x
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,g$i
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int
	push	0
	push	offset g$i
	pop	eax
	inc	dword ptr [eax]
	mov	eax,g$i
	mov	ebx,dword ptr 6
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$2
	jmp	lbl$1
lbl$2:

@@lbl_exit:
	pop	ebp
	add	esp,24
	ret	0
f$main endp

include b.inc