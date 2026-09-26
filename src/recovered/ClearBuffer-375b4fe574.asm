; Clear the requested byte count through a far destination pointer, matching the odd SIMTWO entry.
.186
SIMTWO_MODULE SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE
PUBLIC _ClearBuffer
_ClearBuffer PROC FAR
    push bp
    mov bp, sp
    add bp, 6
    push es
    push ds
    push si
    push di
    les di, [bp]
    mov cx, [bp+4]
    xor ax, ax
    shr cx, 1
    rep stosw
    adc di, -1
    stosb
    pop di
    pop si
    pop ds
    pop es
    pop bp
    retf
_ClearBuffer ENDP
SIMTWO_MODULE ENDS
END
