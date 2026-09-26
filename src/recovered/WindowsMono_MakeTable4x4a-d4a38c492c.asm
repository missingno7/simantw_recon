; Convert each source byte into the paired high/low nibbles of four rows.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _WindowsMono_MakeTable4x4a
_WindowsMono_MakeTable4x4a PROC FAR
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
    mov cx, 40h
table4x4a_next:
    xor ah, ah
    lodsb
    shl ax, 3
    add bx, ax
    mov dl, ss:[bx]
    and dl, 0F0h
    mov es:[di], dl
    mov dl, ss:[bx+1]
    and dl, 0F0h
    mov es:[di+40h], dl
    mov dl, ss:[bx+2]
    and dl, 0F0h
    mov es:[di+80h], dl
    mov dl, ss:[bx+3]
    and dl, 0F0h
    mov es:[di+0C0h], dl
    sub bx, ax
    xor ah, ah
    lodsb
    shl ax, 3
    add bx, ax
    mov dl, ss:[bx]
    and dl, 0Fh
    or es:[di], dl
    mov dl, ss:[bx+1]
    and dl, 0Fh
    or es:[di+40h], dl
    mov dl, ss:[bx+2]
    and dl, 0Fh
    or es:[di+80h], dl
    mov dl, ss:[bx+3]
    and dl, 0Fh
    or es:[di+0C0h], dl
    sub bx, ax
    inc di
    loop table4x4a_next
    pop es
    pop ds
    popa
    pop bp
    retf
_WindowsMono_MakeTable4x4a ENDP
_TEXT ENDS
END
