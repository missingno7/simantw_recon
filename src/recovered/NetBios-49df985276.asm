; Forward the supplied NCB to the Windows KERNEL NetBIOS entry point.
.186
EXTRN NETBIOSCALL:FAR
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _NetBios
_NetBios PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    les bx, [bp+6]
    mov ax, 100h
    call FAR PTR NETBIOSCALL
_NetBios ENDP
_TEXT ENDS
END
