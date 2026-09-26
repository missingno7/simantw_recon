; Expand each source cell through four successive lookup rows.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _Windows_MakeTable4x4
_Windows_MakeTable4x4 PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    lds si, [bp+6]
    les di, [bp+0Ah]
    mov cx, [bp+0Eh]
    mov dx, cx
    shl dx, 1
    dec dx
    dec dx
table_4x4_next:
    mov bx, 1A56h
    lodsb
    xor ah, ah
    shl ax, 1
    add bx, ax
    mov ax, WORD PTR ss:[bx]
    mov bp, di
    stosw
    add di, dx
    mov ax, WORD PTR ss:[bx+40h]
    stosw
    add di, dx
    mov ax, WORD PTR ss:[bx+80h]
    stosw
    add di, dx
    mov ax, WORD PTR ss:[bx+0C0h]
    stosw
    mov di, bp
    inc di
    inc di
    loop table_4x4_next
    pop es
    pop ds
    popa
    pop bp
    retf
_Windows_MakeTable4x4 ENDP
_TEXT ENDS
END
