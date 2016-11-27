include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,dword ptr 5
	and	eax,dword ptr 0
	push	eax
	call	f$print_int
	mov	eax,dword ptr 0
	and	eax,dword ptr 5
	push	eax
	call	f$print_int
	mov	eax,dword ptr 5
	or	eax,dword ptr 0
	push	eax
	call	f$print_int
	mov	eax,dword ptr 0
	or	eax,dword ptr 5
	push	eax
	call	f$print_int
	mov	eax,dword ptr 5
	xor	eax,dword ptr 0
	push	eax
	call	f$print_int
	mov	eax,dword ptr 0
	xor	eax,dword ptr 5
	push	eax
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc