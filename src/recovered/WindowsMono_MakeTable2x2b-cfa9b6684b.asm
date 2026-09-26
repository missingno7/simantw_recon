; Split four two-bit planes from each packed source byte into adjacent rows.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _WindowsMono_MakeTable2x2b
_WindowsMono_MakeTable2x2b PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    mov bx, [bp+10h]
    and bx, 7
    add bx, 26A0h
    lds si, [bp+6]
    les di, [bp+0Ah]
    mov cx, 10h
table2x2b_next:
    xor ah, ah
    lodsb
    shl ax, 3
    add bx, ax
    mov dl, ss:[bx]
    and dl, 0C0h
    mov es:[di], dl
    mov dl, ss:[bx+1]
    and dl, 0C0h
    mov es:[di+10h], dl
    sub bx, ax
    xor ah, ah
    lodsb
    shl ax, 3
    add bx, ax
    mov dl, ss:[bx]
    and dl, 30h
    or es:[di], dl
    mov dl, ss:[bx+1]
    and dl, 30h
    or es:[di+10h], dl
    sub bx, ax
    xor ah, ah
    lodsb
    shl ax, 3
    add bx, ax
    mov dl, ss:[bx]
    and dl, 0Ch
    or es:[di], dl
    mov dl, ss:[bx+1]
    and dl, 0Ch
    or es:[di+10h], dl
    sub bx, ax
    xor ah, ah
    lodsb
    shl ax, 3
    add bx, ax
    mov dl, ss:[bx]
    and dl, 3
    or es:[di], dl
    mov dl, ss:[bx+1]
    and dl, 3
    or es:[di+10h], dl
    sub bx, ax
    inc di
    loop table2x2b_next
    pop es
    pop ds
    popa
    pop bp
    retf
_WindowsMono_MakeTable2x2b ENDP
_TEXT ENDS
END
