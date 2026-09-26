; Faithful MASM instruction reconstruction of _UnpackFileClose.
.186
EXTRN _close:FAR
EXTRN _unpackHandle:WORD
_DATA SEGMENT WORD PUBLIC 'DATA'
_DATA ENDS
DGROUP GROUP _DATA
SIMTWO_MODULE SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE, DS:DGROUP
PUBLIC _UnpackFileClose
_UnpackFileClose PROC FAR
    push word ptr _unpackHandle
    call FAR PTR _close
    pop ax
    retf
_UnpackFileClose ENDP
SIMTWO_MODULE ENDS
END
