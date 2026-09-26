; Transfer color bytes while preserving destination pixels behind the key color.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
EXTRN __AHINCR:ABS
ASSUME CS:_TEXT
PUBLIC _XferLifeTileColor
_XferLifeTileColor PROC FAR
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
    je life_color_after_initial_wrap
    mov ax, es
life_color_wrap_forward:
    add ax, OFFSET __AHINCR
    dec dx
    jne life_color_wrap_forward
    mov es, ax
life_color_after_initial_wrap:
    mov ax, [bp+0Ah]
    mul word ptr [bp+10h]
    shr ax, 1
    add di, ax
    jae life_color_copy_setup
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
life_color_copy_setup:
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
life_color_outer:
    mov cl, dl
life_color_prepare_byte:
    xor ch, ch
life_color_byte:
    lodsb
    cmp al, 0DDh
    je life_color_skip
    mov ah, al
    and al, 0Fh
    cmp al, 0Dh
    jne life_color_high_nibble
    or ch, 0Fh
    and ah, 0F0h
life_color_high_nibble:
    mov al, ah
    and al, 0F0h
    cmp al, 0D0h
    jne life_color_merge
    or ch, 0F0h
    and ah, 0Fh
life_color_merge:
    mov al, es:[di]
    and al, ch
    or al, ah
    stosb
    jmp life_color_next_byte
life_color_skip:
    inc di
life_color_next_byte:
    dec cl
    jne life_color_prepare_byte
    cmp di, 0
    jne life_color_no_wrap
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
life_color_no_wrap:
    dec dh
    je life_color_done
    add di, bx
    jae life_color_row_continue
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
life_color_row_continue:
    jmp life_color_outer
life_color_done:
    pop es
    pop ds
    popa
    pop bp
    retf
_XferLifeTileColor ENDP
_TEXT ENDS
END
