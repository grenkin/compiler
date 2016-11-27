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
	mov	ebx,dword ptr 35170000
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	push	0
	push	offset g$y
	mov	ebx,dword ptr 5
	pop	eax
	mov	dword ptr [eax],ebx
	push	g$y
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,g$y
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 3
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	push	0
	push	offset g$y
	mov	ebx,@@l$x
	pop	eax
	mov	dword ptr [eax],ebx
	push	g$y
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc