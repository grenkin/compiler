include a1.inc

	g$X	dd	1 dup (0)

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+10]
	@@l$x	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
	push	0
	push	offset g$X
	mov	ebx,dword ptr 20
	pop	eax
	mov	dword ptr [eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	push	dword ptr ss:[eax]
	dec	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	0
	push	offset g$X
	pop	eax
	push	dword ptr [eax]
	dec	dword ptr [eax]
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	push	g$X
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc