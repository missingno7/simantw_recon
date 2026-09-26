; Copy selected live-pixel bits from each source row into a far destination.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
EXTRN __AHINCR:ABS
ASSUME CS:_TEXT
PUBLIC _XferLifeTileMono
_XferLifeTileMono PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    mov ax, [bp+14h]
    mul word ptr [bp+10h]
    add ax, 1Fh
    shr ax, 5
    shl ax, 2
    mov bx, ax
    les di, [bp+6]
    mov ax, [bp+12h]
    sub ax, [bp+0Ch]
    mul word ptr [bp+0Eh]
    dec ax
    mul bx
    add di, ax
    cmp dx, 0
    je life_mono_after_initial_wrap
    mov ax, es
life_mono_wrap_forward:
    add ax, OFFSET __AHINCR
    dec dx
    jne life_mono_wrap_forward
    mov es, ax
life_mono_after_initial_wrap:
    mov ax, [bp+0Ah]
    mul word ptr [bp+10h]
    shr ax, 3
    add di, ax
    jae life_mono_copy_setup
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
life_mono_copy_setup:
    lds si, [bp+18h]
    mov ax, [bp+16h]
    shl ax, 5
    add si, ax
    mov ax, [bp+10h]
    shr ax, 3
    mov dx, ax
    add bx, dx
    mov ax, [bp+0Eh]
    mov dh, al
    mov ax, [bp+16h]
    and ax, 0FF80h
    shl ax, 5
    mov bp, ax
    mov ax, 3000h
    sub ax, bp
    mov bp, ax
    cld
life_mono_outer:
    mov cl, dl
    xor ch, ch
life_mono_pixels:
    add si, bp
    mov ch, [si]
    sub si, bp
    not ch
    lodsb
    xor al, es:[di]
    and al, ch
    xor es:[di], al
    inc di
    dec cl
    jne life_mono_pixels
    cmp di, 0
    jne life_mono_no_wrap
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
life_mono_no_wrap:
    dec dh
    je life_mono_done
    sub di, bx
    jae life_mono_row_continue
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
life_mono_row_continue:
    jmp life_mono_outer
life_mono_done:
    pop es
    pop ds
    popa
    pop bp
    retf
_XferLifeTileMono ENDP
_TEXT ENDS
END
