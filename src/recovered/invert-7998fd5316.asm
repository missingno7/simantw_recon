; Invert COUNT bytes in place through a far pointer (hand-written assembly).
.286
SIMTWO_MODULE SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE
PUBLIC _invert
_invert PROC FAR
    push bp
    mov bp, sp
    push di
    mov cx, [bp+10]
    les di, [bp+6]
next:
    mov al, es:[di]
    not al
    stosb
    loop next
    pop di
    pop bp
    retf
_invert ENDP
SIMTWO_MODULE ENDS
END
