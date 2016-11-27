include a1.inc

	real_const$1	dd	5.000000e+000
	string_const$1	db 	0ah, "$"

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+30]
	@@l$p	equ dword ptr ss:[ebp+4]
	sub	esp,24
	push	ebp
	mov	ebp,esp

	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	real_const$1
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 1
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_float
	push	0
	push	offset string_const$1
	call	f$print_string
	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 12
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,24
	ret	0
f$main endp

include b.inc