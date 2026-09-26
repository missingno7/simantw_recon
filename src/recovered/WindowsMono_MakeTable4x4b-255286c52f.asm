; Expand two bitmap source pixels through the high and low nibble lookup tables.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _WindowsMono_MakeTable4x4b
_WindowsMono_MakeTable4x4b PROC FAR
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
    mov cx, 20h
mono_table4_next:
    xor ah, ah
    lodsb
    shl ax, 3
    add bx, ax
    mov dl, ss:[bx]
    and dl, 0F0h
    mov es:[di], dl
    mov dl, ss:[bx+1]
    and dl, 0F0h
    mov es:[di+20h], dl
    mov dl, ss:[bx+2]
    and dl, 0F0h
    mov es:[di+40h], dl
    mov dl, ss:[bx+3]
    and dl, 0F0h
    mov es:[di+60h], dl
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
    or es:[di+20h], dl
    mov dl, ss:[bx+2]
    and dl, 0Fh
    or es:[di+40h], dl
    mov dl, ss:[bx+3]
    and dl, 0Fh
    or es:[di+60h], dl
    sub bx, ax
    inc di
    loop mono_table4_next
    pop es
    pop ds
    popa
    pop bp
    retf
_WindowsMono_MakeTable4x4b ENDP
_TEXT ENDS
END
