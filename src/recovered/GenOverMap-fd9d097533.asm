; Render the 64-by-128 overlay map, stepping both far-source rows in lockstep.
.186
_DATA SEGMENT WORD PUBLIC 'DATA'
OverMapTileBase DW 0
OverMapFillBase DW 0
_DATA ENDS
DGROUP GROUP _DATA
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT, DS:DGROUP
PUBLIC _GenOverMap
_GenOverMap PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    les di, [bp+6]
    mov cx, [bp+0Ah]
    mov dx, [bp+0Ch]
    mov ax, [bp+0Eh]
    mov WORD PTR DS:[OverMapTileBase], ax
    mov ax, [bp+10h]
    mov WORD PTR DS:[OverMapFillBase], ax
    mov ax, [bp+12h]
    mov bp, ax
    cld
    mov bh, 40h
over_map_column:
    mov bl, 80h
over_map_cell:
    mov si, cx
    lodsb
    cmp al, 0
    je over_map_fill
    mov si, WORD PTR DS:[OverMapTileBase]
    xor ah, ah
    shr ax, 3
    add si, ax
    lodsb
    stosb
    jmp SHORT over_map_step
over_map_fill:
    cmp bp, 0
    jne over_map_skip
    mov si, dx
    lodsb
    xor ah, ah
    mov si, WORD PTR DS:[OverMapFillBase]
    add si, ax
    lodsb
    stosb
    jmp SHORT over_map_step
over_map_skip:
    inc di
over_map_step:
    add cx, 40h
    add dx, 40h
    dec bl
    jne over_map_cell
    sub cx, 1FFFh
    sub dx, 1FFFh
    dec bh
    jne over_map_column
    pop es
    pop ds
    popa
    pop bp
    retf
_GenOverMap ENDP
_TEXT ENDS
END
