include a1.inc


include a2.inc

f$f proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,dword ptr 1
	mov	@@result,eax
	jmp	@@lbl_exit

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$f endp

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	call	f$f
	call	f$f
	call	f$f
	call	f$f
	push	dword ptr 10
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc