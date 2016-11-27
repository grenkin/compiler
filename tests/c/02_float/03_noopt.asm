include a1.inc

	real_const$1	dd	3.000000e+000
	string_const$1	db 	0ah, "$"
	string_const$2	db 	0ah, "$"
	string_const$3	db 	0ah, "$"
	string_const$4	db 	0ah, "$"

include a2.inc

f$f proc
	@@result	equ dword ptr ss:[ebp+10]
	@@p$x	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	@@p$x
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string
	push	@@p$x
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	call	f$print_float
	push	0
	push	offset string_const$2
	call	f$print_string

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	4
f$f endp

f$g proc
	@@result	equ dword ptr ss:[ebp+10]
	@@p$x	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	@@p$x
	fld	dword ptr ss:[esp]
	fistp	dword ptr ss:[esp]
	call	f$print_int
	push	0
	push	offset string_const$3
	call	f$print_string
	push	@@p$x
	call	f$print_float
	push	0
	push	offset string_const$4
	call	f$print_string

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	4
f$g endp

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
	push	dword ptr 3
	pop	eax
	neg	eax
	push	eax
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	real_const$1
	pop	float32
	fld	float32
	fchs
	fstp	float32
	push	float32
	fld	dword ptr ss:[esp]
	fistp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@l$x
	fld	dword ptr ss:[esp]
	fistp	dword ptr ss:[esp]
	call	f$f
	push	@@l$y
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	call	f$g

@@lbl_exit:
	pop	ebp
	add	esp,8
	ret	0
f$main endp

include b.inc