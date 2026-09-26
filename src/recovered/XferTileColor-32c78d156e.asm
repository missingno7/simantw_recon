; Transfer a color tile with selector adjustment when the far destination wraps.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
EXTRN __AHINCR:ABS
ASSUME CS:_TEXT
PUBLIC _XferTileColor
_XferTileColor PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    mov ax, [bp+14h]
    mul word ptr [bp+10h]
    shl ax, 2
    add ax, 1Fh
    shr ax, 5
    shl ax, 2
    mov bx, ax
    les di, [bp+6]
    mov ax, [bp+12h]
    sub ax, [bp+0Ch]
    dec ax
    mul word ptr [bp+0Eh]
    mul bx
    add di, ax
    cmp dx, 0
    je color_after_initial_wrap
    mov ax, es
color_wrap_forward:
    add ax, OFFSET __AHINCR
    dec dx
    jne color_wrap_forward
    mov es, ax
color_after_initial_wrap:
    mov ax, [bp+0Ah]
    mul word ptr [bp+10h]
    shr ax, 1
    add di, ax
    jae color_copy_setup
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
color_copy_setup:
    lds si, [bp+18h]
    mov ax, [bp+16h]
    shl ax, 7
    add si, ax
    mov ax, [bp+10h]
    shr ax, 1
    mov dx, ax
    sub bx, dx
    mov ax, [bp+0Eh]
    mov dh, al
    cld
color_copy_row:
    mov cl, dl
    xor ch, ch
    rep movsb
    cmp di, 0
    jne color_no_wrap
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
color_no_wrap:
    dec dh
    je color_done
    add di, bx
    jae color_row_continue
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
color_row_continue:
    jmp color_copy_row
color_done:
    pop es
    pop ds
    popa
    pop bp
    retf
_XferTileColor ENDP
_TEXT ENDS
END
