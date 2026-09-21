# Recovery task _hanim_RemoveAllAnimObjects

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 109 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 nop 
000a push cs
000b call 0x558e ; _mem_Lock
000e add sp, 2
0011 mov es, dx
0013 mov bx, ax
0015 mov di, ax
0017 mov word ptr [bp - 6], es
001a push word ptr es:[bx + 2]
001e nop 
001f push cs
0020 call 0x558e ; _mem_Lock
0023 add sp, 2
0026 mov es, word ptr [bp - 6]
0029 cmp word ptr es:[di], 0
002d jle 0x67ed
002f mov cx, word ptr es:[di]
0032 mov si, ax
0034 mov word ptr [bp - 8], di
0037 mov ds, dx
0039 mov al, 1
003b mov byte ptr [si + 3], al
003e mov byte ptr [si + 5], al
0041 mov byte ptr [si], 0
0044 add si, 0x2c
0047 dec cx
0048 jne 0x67d7
004a mov di, word ptr [bp - 8]
004d push ss
004e pop ds
004f mov es, word ptr [bp - 6]
0052 push word ptr es:[di + 2]
0056 nop 
0057 push cs
0058 call 0x559c ; _mem_Unlock
005b add sp, 2
005e push word ptr [bp + 6]
0061 nop 
0062 push cs
0063 call 0x559c ; _mem_Unlock
0066 add sp, 2
0069 pop si
006a pop di
006b leave 
006c retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_hanim_AddAnimObject', 'offset': 25616, 'source': None, 'size': 650}
- {'symbol': '_hanim_RemoveAnimObject', 'offset': 26266, 'source': None, 'size': 260}
- {'symbol': '_hanim_ActuallyRemoveAnimObjects', 'offset': 26636, 'source': None, 'size': 248}
- {'symbol': '_hanim_HideObject', 'offset': 26884, 'source': None, 'size': 179}
