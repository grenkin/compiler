include a1.inc

	real_const$1	dd	2.000000e+000
	real_const$2	dd	2.000000e+000
	real_const$3	dd	2.000000e+000
	real_const$4	dd	2.000000e+000

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 2
	push	real_const$1
	pop	float32
	fld	float32
	fchs
	fstp	float32
	push	float32
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fidiv	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	call	f$print_float
	push	dword ptr 2
	push	real_const$2
	pop	float32
	fld	float32
	fchs
	fstp	float32
	push	float32
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fimul	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	call	f$print_float
	push	dword ptr 2
	pop	eax
	neg	eax
	push	eax
	push	real_const$3
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fidivr	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	call	f$print_float
	push	dword ptr 2
	pop	eax
	neg	eax
	push	eax
	push	real_const$4
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fimul	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	call	f$print_float

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc