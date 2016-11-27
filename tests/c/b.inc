
start:
	mov	ax,@data
	mov	ds,ax

	finit
	call	f$main

	mov	ax, 4c00h
	int	21h
end start