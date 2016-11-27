include a1.inc

	string_const$1	db 	020h, "$"
	string_const$2	db 	020h, "$"
	string_const$3	db 	020h, "$"

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
	push	dword ptr 2
	push	dword ptr 2
	pop	eax
	pop	ebx
	imul	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 2
	push	@@l$x
	pop	eax
	pop	ebx
	imul	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string
	push	@@l$y
	call	f$print_int
	push	0
	push	offset string_const$2
	call	f$print_string
	push	dword ptr 1
	push	@@l$y
	pop	eax
	pop	ebx
	add	eax,ebx
	push	eax
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 2
	push	@@l$y
	pop	eax
	pop	ebx
	imul	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	0
	push	offset string_const$3
	call	f$print_string
	push	@@l$y
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,8
	ret	0
f$main endp

include b.inc