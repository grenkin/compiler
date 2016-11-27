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
	push	eax
	push	dword ptr 1
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	0
	push	offset g$X
	push	dword ptr 20
	pop	ebx
	pop	eax
	mov	dword ptr [eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	push	dword ptr ss:[eax]
	inc	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	0
	push	offset g$X
	pop	eax
	push	dword ptr [eax]
	inc	dword ptr [eax]
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