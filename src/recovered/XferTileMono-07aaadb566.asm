; Copy a mono tile row by row, advancing far destination selectors at wrap.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
EXTRN __AHINCR:ABS
ASSUME CS:_TEXT
PUBLIC _XferTileMono
_XferTileMono PROC FAR
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
    je mono_after_initial_wrap
    mov ax, es
mono_wrap_forward:
    ASSUME CS:NOTHING
    add ax, OFFSET __AHINCR
    ASSUME CS:_TEXT
    dec dx
    jne mono_wrap_forward
    mov es, ax
mono_after_initial_wrap:
    mov ax, [bp+0Ah]
    mul word ptr [bp+10h]
    shr ax, 3
    add di, ax
    jae mono_copy_setup
    mov ax, es
    ASSUME CS:NOTHING
    add ax, OFFSET __AHINCR
    ASSUME CS:_TEXT
    mov es, ax
mono_copy_setup:
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
    cld
mono_copy_row:
    mov cl, dl
    xor ch, ch
    rep movsb
    cmp di, 0
    jne mono_no_wrap
    mov ax, es
    ASSUME CS:NOTHING
    add ax, OFFSET __AHINCR
    ASSUME CS:_TEXT
    mov es, ax
mono_no_wrap:
    dec dh
    je mono_done
    sub di, bx
    jae mono_row_continue
    mov ax, es
    ASSUME CS:NOTHING
    sub ax, OFFSET __AHINCR
    ASSUME CS:_TEXT
    mov es, ax
mono_row_continue:
    jmp mono_copy_row
mono_done:
    pop es
    pop ds
    popa
    pop bp
    retf
_XferTileMono ENDP
_TEXT ENDS
END
