include a1.inc

	string_const$1	db 	0ah, "$"
	string_const$2	db 	0ah, "$"
	string_const$3	db 	0ah, "$"
	string_const$4	db 	0ah, "$"
	string_const$5	db 	0ah, "$"
	string_const$6	db 	0ah, "$"
	string_const$7	db 	0ah, "$"

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 7
	push	dword ptr 9
	pop	eax
	pop	ebx
	and	eax,ebx
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string
	push	dword ptr 87
	push	dword ptr 90
	pop	eax
	pop	ebx
	and	eax,ebx
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$2
	call	f$print_string
	push	dword ptr 3
	call	f$print_int
	push	0
	push	offset string_const$3
	call	f$print_string
	push	dword ptr 3
	pop	eax
	neg	eax
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$4
	call	f$print_string
	push	dword ptr 3
	pop	eax
	neg	eax
	push	eax
	pop	eax
	neg	eax
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$5
	call	f$print_string
	push	dword ptr 3
	pop	eax
	neg	eax
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$6
	call	f$print_string
	push	dword ptr 5
	pop	eax
	not	eax
	push	eax
	pop	eax
	not	eax
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$7
	call	f$print_string

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc