include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp


@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc