include a1.inc

	string_const$1	db 	020h, "$"
	string_const$2	db 	0ah, 07ah, 020h, 03dh, 020h, 02dh, 031h, 030h, 02fh, 033h, 020h, 03dh, 020h, "$"
	string_const$3	db 	0ah, 02dh, 07ah, 020h, 03dh, 020h, "$"

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+18]
	@@l$x	equ dword ptr ss:[ebp+12]
	@@l$y	equ dword ptr ss:[ebp+8]
	@@l$z	equ dword ptr ss:[ebp+4]
	sub	esp,12
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	push	dword ptr 10
	pop	eax
	neg	eax
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	push	dword ptr 3
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	@@l$y
	push	@@l$x
	pop	eax
	pop	ebx
	cdq
	idiv	ebx
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
	push	@@l$z
	call	f$print_int
	push	0
	push	offset string_const$3
	call	f$print_string
	push	@@l$z
	pop	eax
	neg	eax
	push	eax
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,12
	ret	0
f$main endp

include b.inc