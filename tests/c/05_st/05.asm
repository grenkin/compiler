include a1.inc

	g$t	dd	2 dup (0)

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	0
	push	offset g$t
	pop	eax
	add	eax,dword ptr 0
	mov	ebx,dword ptr 1
	mov	dword ptr [eax],ebx
	push	0
	push	offset g$t
	pop	eax
	add	eax,dword ptr 4
	mov	ebx,dword ptr 2
	mov	dword ptr [eax],ebx
	push	0
	push	offset g$t
	pop	eax
	add	eax,dword ptr 0
	push	dword ptr [eax]
	call	f$print_int
	push	0
	push	offset g$t
	pop	eax
	add	eax,dword ptr 4
	push	dword ptr [eax]
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc