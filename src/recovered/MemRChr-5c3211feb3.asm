; Search COUNT bytes backwards from a far pointer for a byte value; return a far
; pointer to the match, or NULL (hand-written assembly: STD / REPNE SCASB / CLD).
.286
SIMTWO_MODULE SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE
PUBLIC _MemRChr
_MemRChr PROC FAR
    push bp
    mov bp, sp
    push di
    std
    les di, [bp+6]
    mov al, [bp+10]
    mov cx, [bp+12]
    repne scasb
    cld
    jne notfound
    mov dx, es
    mov ax, di
    inc ax
    jmp short done
notfound:
    xor dx, dx
    xor ax, ax
done:
    pop di
    pop bp
    retf
_MemRChr ENDP
SIMTWO_MODULE ENDS
END
