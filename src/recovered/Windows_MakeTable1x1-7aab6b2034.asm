; Decode alternating source bytes through the two adjacent translation rows.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _Windows_MakeTable1x1
_Windows_MakeTable1x1 PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    lds si, [bp+6]
    les di, [bp+0Ah]
    mov bx, 1B56h
    mov cx, [bp+0Eh]
    shr cx, 1
table_1x1_next:
    lodsb
    xlat ss:[bx]
    mov ah, al
    lodsb
    add bx, WORD PTR 10h
    xlat ss:[bx]
    sub bx, WORD PTR 10h
    or al, ah
    stosb
    loop table_1x1_next
    pop es
    pop ds
    popa
    pop bp
    retf
_Windows_MakeTable1x1 ENDP
_TEXT ENDS
END
