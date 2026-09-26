; Faithful instruction-level reconstruction of the masked member.
.186
_DATA SEGMENT WORD PUBLIC 'DATA'
_DATA ENDS
DGROUP GROUP _DATA
EXTRN _ELayerMode:WORD
EXTRN _MapPlane:WORD
EXTRN _MeBase:WORD
EXTRN _MeDir:WORD
EXTRN _MeEgg:WORD
EXTRN _MeType:WORD
EXTRN _PherMapAPtr:DWORD
EXTRN _PherMapBNPtr:DWORD
EXTRN _PherMapBTPtr:DWORD
EXTRN _PherMapRNPtr:DWORD
EXTRN _PherMapRTPtr:DWORD
EXTRN _grndTile:BYTE
EXTRN _lifeTile:WORD
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT, DS:DGROUP
PUBLIC _DoCalcTile
_DoCalcTile PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    xor bx, bx
    mov byte ptr DGROUP:_grndTile, bl
    mov word ptr DGROUP:_lifeTile, bx
    mov cx, WORD PTR [bp + 6]
    mov dx, WORD PTR [bp + 8]
    mov ax, word ptr DGROUP:_MapPlane
    cmp ax, 0
    je L_0030
    dec ax
    je L_0030
    dec ax
    je L_002A
    dec ax
    je L_002D
    jmp NEAR PTR L_01F0
L_002A:
    jmp NEAR PTR L_0106
L_002D:
    jmp NEAR PTR L_017D
L_0030:
    and cx, 7Fh
    mov ax, word ptr DGROUP:_ELayerMode
    cmp ax, 0
    je L_0049
    dec ax
    je L_004F
    dec ax
    je L_0055
    dec ax
    je L_005B
    dec ax
    je L_0061
    jmp SHORT L_008E
L_0049:
    les di, DGROUP:_PherMapAPtr
    jmp SHORT L_0065
L_004F:
    les di, DGROUP:_PherMapBNPtr
    jmp SHORT L_0065
L_0055:
    les di, DGROUP:_PherMapBTPtr
    jmp SHORT L_0065
L_005B:
    les di, DGROUP:_PherMapRNPtr
    jmp SHORT L_0065
L_0061:
    les di, DGROUP:_PherMapRTPtr
L_0065:
    mov ax, cx
    shr ax, 1
    shl ax, 5
    add di, ax
    mov ax, dx
    shr ax, 1
    add di, ax
    xor bh, bh
    mov bl, es:[di]
    cmp bl, 10h
    jbe L_008E
    shr bx, 4
    and bx, 1Fh
    add bx, 0F0h
    mov byte ptr DGROUP:_grndTile, bl
    jmp SHORT L_009F
L_008E:
    mov ax, cx
    shl ax, 6
    add ax, dx
    add ax, 28E8h
    mov si, ax
    mov al, ds:[si]
    mov byte ptr DGROUP:_grndTile, al
L_009F:
    mov ax, cx
    shl ax, 6
    add ax, dx
    add ax, 68E8h
    mov si, ax
    mov bl, ds:[si]
    xor bh, bh
    cmp bx, 0
    je L_0103
    cmp bx, 0FFh
    jne L_00E0
    mov ax, 380h
    add ax, word ptr DGROUP:_MeBase
    add ax, word ptr DGROUP:_MeType
    cmp word ptr DGROUP:_MeType, 8
    jb L_00D6
    add ax, word ptr DGROUP:_MeDir
    mov word ptr DGROUP:_lifeTile, ax
    jmp NEAR PTR L_01F0
L_00D6:
    add ax, word ptr DGROUP:_MeEgg
    mov word ptr DGROUP:_lifeTile, ax
    jmp NEAR PTR L_01F0
L_00E0:
    cmp bx, 0FEh
    jne L_00FB
    mov ax, 388h
    add ax, word ptr DGROUP:_MeType
    add ax, word ptr DGROUP:_MeBase
    add ax, word ptr DGROUP:_MeDir
    mov word ptr DGROUP:_lifeTile, ax
    jmp NEAR PTR L_01F0
L_00FB:
    add bx, 100h
    mov word ptr DGROUP:_lifeTile, bx
L_0103:
    jmp NEAR PTR L_01F0
L_0106:
    and cx, 3Fh
    mov ax, cx
    shl ax, 6
    add ax, dx
    mov bx, ax
    add ax, 48E8h
    mov si, ax
    mov al, ds:[si]
    add al, 90h
    mov byte ptr DGROUP:_grndTile, al
    add bx, 88E8h
    mov si, bx
    mov bl, ds:[si]
    xor bh, bh
    cmp bx, 0
    je L_017B
    cmp bx, 0FFh
    jne L_0159
    mov ax, 300h
    add ax, word ptr DGROUP:_MeBase
    add ax, word ptr DGROUP:_MeType
    cmp word ptr DGROUP:_MeType, 8
    jb L_014F
    add ax, word ptr DGROUP:_MeDir
    mov word ptr DGROUP:_lifeTile, ax
    jmp NEAR PTR L_01F0
L_014F:
    add ax, word ptr DGROUP:_MeEgg
    mov word ptr DGROUP:_lifeTile, ax
    jmp NEAR PTR L_01F0
L_0159:
    cmp bx, 0FEh
    jne L_0173
    mov ax, 308h
    add ax, word ptr DGROUP:_MeType
    add ax, word ptr DGROUP:_MeBase
    add ax, word ptr DGROUP:_MeDir
    mov word ptr DGROUP:_lifeTile, ax
    jmp SHORT L_01F0
L_0173:
    add bx, 200h
    mov word ptr DGROUP:_lifeTile, bx
L_017B:
    jmp SHORT L_01F0
L_017D:
    and cx, 3Fh
    mov ax, cx
    shl ax, 6
    add ax, dx
    mov bx, ax
    add ax, 58E8h
    mov si, ax
    mov al, ds:[si]
    add al, 90h
    mov byte ptr DGROUP:_grndTile, al
    add bx, 98E8h
    mov si, bx
    mov bl, ds:[si]
    xor bh, bh
    cmp bx, 0
    je L_01F0
    cmp bx, 0FFh
    jne L_01CE
    mov ax, 300h
    add ax, word ptr DGROUP:_MeBase
    add ax, word ptr DGROUP:_MeType
    cmp word ptr DGROUP:_MeType, 8
    jb L_01C5
    add ax, word ptr DGROUP:_MeDir
    mov word ptr DGROUP:_lifeTile, ax
    jmp SHORT L_01F0
L_01C5:
    add ax, word ptr DGROUP:_MeEgg
    mov word ptr DGROUP:_lifeTile, ax
    jmp SHORT L_01F0
L_01CE:
    cmp bx, 0FEh
    jne L_01E8
    mov ax, 308h
    add ax, word ptr DGROUP:_MeType
    add ax, word ptr DGROUP:_MeBase
    add ax, word ptr DGROUP:_MeDir
    mov word ptr DGROUP:_lifeTile, ax
    jmp SHORT L_01F0
L_01E8:
    add bx, 200h
    mov word ptr DGROUP:_lifeTile, bx
L_01F0:
    pop es
    pop ds
    popa
    pop bp
    retf
_DoCalcTile ENDP
_TEXT ENDS
END