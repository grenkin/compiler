include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+14]
	@@l$x	equ dword ptr ss:[ebp+8]
	@@l$y	equ dword ptr ss:[ebp+4]
	sub	esp,8
	push	ebp
	mov	ebp,esp

	push	dword ptr 2
	add	esp,dword ptr 4
	push	dword ptr 3
	add	esp,dword ptr 4
	push	dword ptr 3
	call	f$print_int
	push	dword ptr 2
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	push	dword ptr 5
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
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
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$x
	pop	eax
	pop	ebx
	add	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,8
	ret	0
f$main endp

include b.inc