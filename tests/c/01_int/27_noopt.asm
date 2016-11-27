include a1.inc

	g$y	dd	1 dup (0)

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
	push	dword ptr 35170000
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	push	0
	push	offset g$y
	push	dword ptr 5
	pop	ebx
	pop	eax
	mov	dword ptr [eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	g$y
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	g$y
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
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	push	0
	push	offset g$y
	push	@@l$x
	pop	ebx
	pop	eax
	mov	dword ptr [eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	g$y
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc