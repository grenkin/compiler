include a1.inc

	real_const$1	dd	3.000000e+000
	real_const$2	dd	2.000000e+000
	real_const$3	dd	3.000000e+000
	real_const$4	dd	2.000000e+000

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	real_const$1
	push	real_const$2
	pop	float32
	fld	float32
	fchs
	fstp	float32
	push	float32
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fsub
	sub	esp,dword ptr 4
	fstp	dword ptr ss:[esp]
	call	f$print_float
	push	real_const$3
	push	real_const$4
	pop	float32
	fld	float32
	fchs
	fstp	float32
	push	float32
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fadd
	sub	esp,dword ptr 4
	fstp	dword ptr ss:[esp]
	call	f$print_float
	push	dword ptr 2
	push	dword ptr 2
	pop	eax
	neg	eax
	push	eax
	pop	eax
	pop	ebx
	sub	eax,ebx
	push	eax
	call	f$print_int
	push	dword ptr 5
	push	dword ptr 3
	pop	eax
	neg	eax
	push	eax
	pop	eax
	pop	ebx
	add	eax,ebx
	push	eax
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc