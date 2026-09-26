; LZSS tree update routines share the PACK selector loaded from _unpackHandle.
.186
EXTRN _unpackHandle:DWORD
EXTRN _match_position:WORD
EXTRN _match_length:WORD
PACK_TEXT_BUF EQU 0004h
PACK_LSON EQU 1016h
PACK_RSON EQU 3018h
PACK_DAD EQU 521Ah
SIMTWO_MODULE SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE
PUBLIC _DeleteNode
_DeleteNode PROC FAR
    push bp
    mov bp, sp
    sub sp, 2
    push si
    push di
    push ds
    mov ds, WORD PTR _unpackHandle+2
    mov bx, word ptr [bp + 6]
    shl bx, 1
    mov ax, 1000h
    cmp word ptr [bx + PACK_DAD], ax
    jne L_DeleteNode_001E
    jmp NEAR PTR L_DeleteNode_00B6
L_DeleteNode_001E:
    cmp word ptr [bx + PACK_RSON], ax
    jne L_DeleteNode_002E
    mov cx, word ptr [bx + PACK_LSON]
    mov si, cx
    add si, si
    jmp SHORT L_DeleteNode_0094
L_DeleteNode_002E:
    cmp word ptr [bx + PACK_LSON], ax
    jne L_DeleteNode_003E
    mov cx, word ptr [bx + PACK_RSON]
    mov si, cx
    add si, si
    jmp SHORT L_DeleteNode_0094
L_DeleteNode_003E:
    mov cx, word ptr [bx + PACK_LSON]
    mov si, cx
    shl si, 1
    cmp word ptr [si + PACK_RSON], 1000h
    je L_DeleteNode_0086
L_DeleteNode_004E:
    mov si, word ptr [si + PACK_RSON]
    add si, si
    cmp word ptr [si + PACK_RSON], 1000h
    jne L_DeleteNode_004E
    mov dx, word ptr [si + PACK_LSON]
    mov di, word ptr [si + PACK_DAD]
    mov cx, di
    shl di, 1
    mov word ptr [di + PACK_RSON], dx
    mov di, dx
    shl di, 1
    mov word ptr [di + PACK_DAD], cx
    mov di, word ptr [bx + PACK_LSON]
    mov word ptr [si + PACK_LSON], di
    mov cx, si
    shr cx, 1
    shl di, 1
    mov word ptr [di + PACK_DAD], cx
L_DeleteNode_0086:
    mov di, word ptr [bx + PACK_RSON]
    mov word ptr [si + PACK_RSON], di
    add di, di
    mov word ptr [di + PACK_DAD], cx
L_DeleteNode_0094:
    mov di, word ptr [bx + PACK_DAD]
    mov word ptr [si + PACK_DAD], di
    add di, di
    mov dx, bx
    shr dx, 1
    cmp word ptr [di + PACK_RSON], dx
    jne L_DeleteNode_00AE
    mov word ptr [di + PACK_RSON], cx
    jmp SHORT L_DeleteNode_00B2
L_DeleteNode_00AE:
    mov word ptr [di + PACK_LSON], cx
L_DeleteNode_00B2:
    mov word ptr [bx + PACK_DAD], ax
L_DeleteNode_00B6:
    pop ds
    pop di
    pop si
    mov sp, bp
    pop bp
    retf
_DeleteNode ENDP
SIMTWO_MODULE ENDS
END
