include a1.inc

	real_const$1	dd	5.500000e+000

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 3
	call	f$print_int
	push	real_const$1
	pop	float32
	fld	float32
	fchs
	fstp	float32
	push	float32
	call	f$print_float
	mov	eax,dword ptr 3
	neg	eax
	push	eax
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc