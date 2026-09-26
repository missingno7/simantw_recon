; Two adjacent byte-order helpers; operand order preserves the original XCHG encodings.
.186
_TEXT SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _FlipWord, _FlipLong
_FlipWord PROC FAR
    push bp
    mov bp, sp
    mov ax, [bp+6]
    xchg al, ah
    pop bp
    retf
_FlipWord ENDP
_FlipLong PROC FAR
    push bp
    mov bp, sp
    mov ax, [bp+8]
    xchg al, ah
    mov dx, [bp+6]
    xchg dl, dh
    pop bp
    retf
_FlipLong ENDP
_TEXT ENDS
END


