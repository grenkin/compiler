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
	mov	ebx,dword ptr 2
	pop	eax
	mov	dword ptr [eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 0
	mov	ebx,dword ptr 3
	mov	dword ptr ss:[eax],ebx
	push	g$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 0
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 0
	mov	eax,dword ptr ss:[eax]
	add	eax,g$x
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	call	f$print_int
	push	0
	push	offset g$x
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 0
	mov	eax,dword ptr ss:[eax]
	inc	eax
	mov	ebx,eax
	pop	eax
	mov	dword ptr [eax],ebx
	push	g$x
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc