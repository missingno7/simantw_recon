; Complete byte-preserving exchange of two far byte arrays.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _exchange
_exchange PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    mov cx, [bp+0Eh]
    les di, [bp+6]
    lds si, [bp+0Ah]
exchange_next:
    lodsb
    mov ah, es:[di]
    stosb
    mov [si-1], ah
    loop exchange_next
    pop es
    pop ds
    popa
    pop bp
    retf
_exchange ENDP
_TEXT ENDS
END
