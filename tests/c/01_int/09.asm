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
	mov	ebx,dword ptr 2
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	mov	eax,dword ptr 5
	neg	eax
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
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
	mov	eax,@@l$x
	imul	eax,@@l$y
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$z
	call	f$print_int
	push	0
	push	offset string_const$3
	call	f$print_string
	mov	eax,@@l$z
	neg	eax
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$4
	call	f$print_string
	mov	eax,@@l$z
	neg	eax
	mov	ebx,dword ptr 3
	cdq
	idiv	ebx
	push	edx
	call	f$print_int
	push	0
	push	offset string_const$5
	call	f$print_string
	mov	eax,@@l$y
	neg	eax
	push	eax
	mov	eax,@@l$x
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
	mov	eax,@@l$x
	pop	ebx
	imul	eax,ebx
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	push	@@l$y
	mov	eax,@@l$y
	pop	ebx
	imul	eax,ebx
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
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
	mov	eax,@@l$x
	mov	ebx,dword ptr 2
	cdq
	idiv	ebx
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	mov	eax,@@l$y
	mov	ebx,dword ptr 5
	cdq
	idiv	ebx
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
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
	mov	eax,dword ptr 5
	neg	eax
	push	eax
	mov	eax,dword ptr 3
	neg	eax
	pop	ebx
	imul	eax,ebx
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$11
	call	f$print_string
	mov	eax,dword ptr 5
	neg	eax
	push	eax
	mov	eax,dword ptr 3
	pop	ebx
	imul	eax,ebx
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$12
	call	f$print_string
	mov	eax,dword ptr 3
	neg	eax
	imul	eax,dword ptr 5
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