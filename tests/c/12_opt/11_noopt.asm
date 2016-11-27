include a1.inc

	real_const$1	dd	9.100000e+000
	real_const$2	dd	7.000000e+000
	real_const$3	dd	5.000000e+000
	real_const$4	dd	3.000000e+000

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	real_const$1
	push	real_const$2
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fdiv
	sub	esp,dword ptr 4
	fstp	dword ptr ss:[esp]
	push	real_const$3
	push	real_const$4
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fmul
	sub	esp,dword ptr 4
	fstp	dword ptr ss:[esp]
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fsub
	sub	esp,dword ptr 4
	fstp	dword ptr ss:[esp]
	add	esp,dword ptr 4

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc