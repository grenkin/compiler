include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+14]
	@@l$x	equ dword ptr ss:[ebp+8]
	@@l$y	equ dword ptr ss:[ebp+4]
	sub	esp,8
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	push	dword ptr 0
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
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
	pop	eax
	xor	ecx,ecx
	test	eax,eax
	setz	cl
	push	ecx
	call	f$print_int
	push	@@l$y
	pop	eax
	xor	ecx,ecx
	test	eax,eax
	setz	cl
	push	ecx
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,8
	ret	0
f$main endp

include b.inc