; Expand nested-map markers and source indices across the 64-by-64 display map.
.186
_DATA SEGMENT WORD PUBLIC 'DATA'
NestMapBitmapBase DW 0
NestMapSpecialTile DB 0
NestMapMarkedTile DB 0
NestMapOrdinaryTile DB 0
_DATA ENDS
DGROUP GROUP _DATA
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT, DS:DGROUP
PUBLIC _GenNestMap
_GenNestMap PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    les di, [bp+6]
    mov cx, [bp+0Ah]
    mov dx, [bp+0Ch]
    mov ax, [bp+0Eh]
    mov WORD PTR DS:[NestMapBitmapBase], ax
    mov al, [bp+10h]
    mov DS:[NestMapSpecialTile], al
    mov al, [bp+12h]
    mov DS:[NestMapMarkedTile], al
    mov al, [bp+14h]
    mov DS:[NestMapOrdinaryTile], al
    mov ax, [bp+16h]
    mov bp, ax
    cld
    mov bh, 40h
nest_map_column:
    mov bl, 40h
nest_map_cell:
    mov si, cx
    lodsb
    cmp al, 0
    je nest_map_fill
    cmp al, 0FEh
    je nest_map_special
    cmp al, 0FFh
    je nest_map_special
    test al, 80h
    je nest_map_tertiary
    mov al, DS:[NestMapMarkedTile]
    stosb
    jmp SHORT nest_map_step
nest_map_special:
    mov al, DS:[NestMapSpecialTile]
    stosb
    jmp SHORT nest_map_step
nest_map_tertiary:
    mov al, DS:[NestMapOrdinaryTile]
    stosb
    jmp SHORT nest_map_step
nest_map_fill:
    cmp bp, 0
    jne nest_map_skip
    mov si, dx
    lodsb
    xor ah, ah
    shr ax, 2
    mov si, WORD PTR DS:[NestMapBitmapBase]
    add si, ax
    lodsb
    stosb
    jmp SHORT nest_map_step
nest_map_skip:
    inc di
nest_map_step:
    add cx, 40h
    add dx, 40h
    dec bl
    jne nest_map_cell
    sub cx, 0FFFh
    sub dx, 0FFFh
    dec bh
    jne nest_map_column
    pop es
    pop ds
    popa
    pop bp
    retf
_GenNestMap ENDP
_TEXT ENDS
END
