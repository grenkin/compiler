include a1.inc

	real_const$1	dd	5.300000e+000
	real_const$2	dd	9.700000e+000
	string_const$1	db 	020h, "$"

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+10]
	@@l$x	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 3
	push	real_const$1
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fiadd	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	real_const$2
	call	f$print_float
	push	0
	push	offset string_const$1
	call	f$print_string
	push	@@l$x
	call	f$print_float

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc