include a1.inc

	g$x	dd	1 dup (0)

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+10]
	@@l$a	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	push	0
	push	offset g$x
	push	dword ptr 2
	pop	ebx
	pop	eax
	mov	dword ptr [eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	eax
	push	dword ptr 3
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	g$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	eax
	push	g$x
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	add	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	call	f$print_int
	push	0
	push	offset g$x
	push	dword ptr 1
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	add	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr [eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	g$x
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc