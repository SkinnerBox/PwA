INCLUDE Irvine32.inc
INCLUDE macros.inc
.data
	filename db "SAMPLE.TXT", 0

.code
asmMain PROC C
	mov ah, 43h
	mov al, 1
	mov cx, 3
	mov edx, offset filename
	INVOKE CloseHandle, eax
	ret
asmMain ENDP

END