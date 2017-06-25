start:
	mov $0, #2	; 2
	inc $0		; 3
	mul $0, #8	; 24
	dec $0		; 23
	mov $1, $0	; 23, 23
	mod $1, #3	; 23, 2
	div $0, $1	; 11
	jmp finish
	zero $0
finish:
	zero $1
	end
