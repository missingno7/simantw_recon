; Faithful MASM instruction reconstruction of _PackWriteByte.
.186
_DATA SEGMENT WORD PUBLIC 'DATA'
_DATA ENDS
_BSS SEGMENT WORD PUBLIC 'BSS'
PackReadProc DD ?
PackBlockLimit DW ?
PackReadState DW ?
PackReadCount DW ?
PackReadBufferOffset DW ?
PackReadBufferSegment DW ?
PackWriteProc DD ?
PackReadNextOffset DW ?
PackReadNextSegment DW ?
PackFileState DW ?
PackWriteCount DW ?
PackSourceOffset DW ?
PackSourceSegment DW ?
PackOutputOffset DW ?
PackOutputSegment DW ?
PackWriteBufferOffset DW ?
PackWriteBufferSegment DW ?
_BSS ENDS
DGROUP GROUP _DATA, _BSS
SIMTWO_MODULE SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE, DS:DGROUP
PUBLIC _PackWriteByte
_PackWriteByte PROC FAR
    push bp
    mov bp, sp
    mov al, BYTE PTR [bp + 6]
    les bx, DWORD PTR [PackOutputOffset]
    mov byte ptr es:[bx], al
    inc word ptr [PackOutputOffset]
    mov ax, word ptr [PackBlockLimit]
    inc word ptr [PackWriteCount]
    cmp word ptr [PackWriteCount], ax
    jb L_003C
    push word ptr [PackWriteCount]
    mov ax, word ptr [PackWriteBufferOffset]
    mov dx, word ptr [PackWriteBufferSegment]
    mov word ptr [PackOutputOffset], ax
    mov word ptr [PackOutputSegment], dx
    push dx
    push ax
    call DWORD PTR [PackWriteProc]
    mov word ptr [PackWriteCount], 0
L_003C:
    mov sp, bp
    pop bp
    retf
_PackWriteByte ENDP
SIMTWO_MODULE ENDS
END
