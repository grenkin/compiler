include a1.inc

	string_const$1	db 	0ah, "$"
	string_const$2	db 	0ah, "$"
	string_const$3	db 	0ah, "$"
	string_const$4	db 	0ah, "$"

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,dword ptr 5
	xor	ecx,ecx
	test	eax,eax
	setz	cl
	push	ecx
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string
	mov	eax,dword ptr 1
	xor	ecx,ecx
	test	eax,eax
	setz	cl
	push	ecx
	call	f$print_int
	push	0
	push	offset string_const$2
	call	f$print_string
	mov	eax,dword ptr 0
	xor	ecx,ecx
	test	eax,eax
	setz	cl
	push	ecx
	call	f$print_int
	push	0
	push	offset string_const$3
	call	f$print_string
	mov	eax,dword ptr 0
	xor	ecx,ecx
	test	eax,eax
	setz	cl
	mov	eax,ecx
	xor	ecx,ecx
	test	eax,eax
	setz	cl
	push	ecx
	call	f$print_int
	push	0
	push	offset string_const$4
	call	f$print_string

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc