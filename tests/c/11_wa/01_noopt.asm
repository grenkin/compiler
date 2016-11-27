include a1.inc

	string_const$1	db 	0ah, "$"

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+22]
	@@l$x	equ dword ptr ss:[ebp+12]
	@@l$y	equ dword ptr ss:[ebp+4]
	sub	esp,16
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	add	eax,dword ptr 0
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
	pop	eax
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 7
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	push	@@l$y
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	pop	eax
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	pop	eax
	add	eax,dword ptr 4
	push	dword ptr ss:[eax]
	call	f$print_float

@@lbl_exit:
	pop	ebp
	add	esp,16
	ret	0
f$main endp

include b.inc