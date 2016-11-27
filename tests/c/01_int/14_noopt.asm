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
	string_const$14	db 	0ah, "$"

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 0
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string
	push	dword ptr 1
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$2
	call	f$print_string
	push	dword ptr 2
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$3
	call	f$print_string
	push	dword ptr 3
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$4
	call	f$print_string
	push	dword ptr 4
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$5
	call	f$print_string
	push	dword ptr 5
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$6
	call	f$print_string
	push	dword ptr 6
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$7
	call	f$print_string
	push	dword ptr 6
	push	dword ptr 6
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	pop	eax
	pop	ebx
	mov	cl,bl
	shr	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$8
	call	f$print_string
	push	dword ptr 5
	push	dword ptr 6
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	pop	eax
	pop	ebx
	mov	cl,bl
	shr	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$9
	call	f$print_string
	push	dword ptr 4
	push	dword ptr 6
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	pop	eax
	pop	ebx
	mov	cl,bl
	shr	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$10
	call	f$print_string
	push	dword ptr 3
	push	dword ptr 6
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	pop	eax
	pop	ebx
	mov	cl,bl
	shr	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$11
	call	f$print_string
	push	dword ptr 2
	push	dword ptr 6
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	pop	eax
	pop	ebx
	mov	cl,bl
	shr	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$12
	call	f$print_string
	push	dword ptr 1
	push	dword ptr 6
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	pop	eax
	pop	ebx
	mov	cl,bl
	shr	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$13
	call	f$print_string
	push	dword ptr 0
	push	dword ptr 6
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	pop	eax
	pop	ebx
	mov	cl,bl
	shr	eax,cl
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$14
	call	f$print_string

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc