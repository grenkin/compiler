include a1.inc

	string_const$1	db 	0ah, "$"
	string_const$2	db 	0ah, "$"
	string_const$3	db 	0ah, "$"
	string_const$4	db 	0ah, "$"
	string_const$5	db 	0ah, "$"
	string_const$6	db 	0ah, "$"
	string_const$7	db 	0ah, "$"
	string_const$8	db 	0ah, "$"
	string_const$9	db 	0ah, "$"
	string_const$10	db 	0ah, "$"
	string_const$11	db 	0ah, "$"
	string_const$12	db 	0ah, "$"
	string_const$13	db 	0ah, "$"

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
	push	dword ptr 2
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	push	dword ptr 5
	pop	eax
	neg	eax
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
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	@@l$y
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
	push	0
	push	offset string_const$4
	call	f$print_string
	push	dword ptr 3
	push	@@l$z
	pop	eax
	neg	eax
	push	eax
	pop	eax
	pop	ebx
	cdq
	idiv	ebx
	push	edx
	call	f$print_int
	push	0
	push	offset string_const$5
	call	f$print_string
	push	@@l$y
	pop	eax
	neg	eax
	push	eax
	push	@@l$x
	pop	eax
	pop	ebx
	cdq
	idiv	ebx
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$6
	call	f$print_string
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	push	@@l$x
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
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	push	@@l$y
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
	push	@@l$x
	call	f$print_int
	push	0
	push	offset string_const$7
	call	f$print_string
	push	@@l$y
	call	f$print_int
	push	0
	push	offset string_const$8
	call	f$print_string
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	push	dword ptr 2
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
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	push	dword ptr 5
	push	@@l$y
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
	push	offset string_const$9
	call	f$print_string
	push	@@l$y
	call	f$print_int
	push	0
	push	offset string_const$10
	call	f$print_string
	push	dword ptr 5
	pop	eax
	neg	eax
	push	eax
	push	dword ptr 3
	pop	eax
	neg	eax
	push	eax
	pop	eax
	pop	ebx
	imul	eax,ebx
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$11
	call	f$print_string
	push	dword ptr 5
	pop	eax
	neg	eax
	push	eax
	push	dword ptr 3
	pop	eax
	pop	ebx
	imul	eax,ebx
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$12
	call	f$print_string
	push	dword ptr 5
	push	dword ptr 3
	pop	eax
	neg	eax
	push	eax
	pop	eax
	pop	ebx
	imul	eax,ebx
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$13
	call	f$print_string

@@lbl_exit:
	pop	ebp
	add	esp,12
	ret	0
f$main endp

include b.inc