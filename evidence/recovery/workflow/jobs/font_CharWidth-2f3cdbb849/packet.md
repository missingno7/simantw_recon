# Recovery task __font_CharWidth

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 99 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov cx, word ptr [bp + 6]
0009 lds bx, ptr [bp + 8]
000c mov word ptr [bp - 2], 0
0011 sub ch, ch
0013 cmp word ptr [bx + 0x26], 0
0017 je 0xadb4
0019 cmp word ptr [bx + 8], 0
001d jge 0xad80
001f mov di, 1
0022 jmp 0xad82
0024 xor di, di
0026 les si, ptr [bx + 0x22]
0029 mov ax, cx
002b shl ax, 1
002d add si, ax
002f mov ax, word ptr es:[si]
0032 mov word ptr [bp - 4], ax
0035 inc ax
0036 je 0xada0
0038 mov ax, word ptr [bp - 4]
003b sub ah, ah
003d mov word ptr [bp - 2], ax
0040 mov cx, ax
0042 jmp 0xadb0
0044 mov cx, word ptr [bp - 2]
0047 mov si, word ptr [bx + 0x22]
004a mov bx, word ptr [bx + 0x28]
004d shl bx, 1
004f mov cl, byte ptr es:[bx + si]
0052 sub ch, ch
0054 add cx, di
0056 jmp 0xadb7
0058 mov cx, word ptr [bx + 6]
005b mov ax, cx
005d push ss
005e pop ds
005f pop si
0060 pop di
0061 leave 
0062 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_font_DumpFont', 'offset': 44106, 'source': None, 'size': 123}
- {'symbol': '__font_StringWidth', 'offset': 44230, 'source': None, 'size': 150}
- {'symbol': '__font_FontHeight', 'offset': 44480, 'source': 'src/recovered/font_FontHeightNative.c', 'size': 13}
- {'symbol': '__font_LineHeight', 'offset': 44494, 'source': 'src/recovered/font_LineHeight.c', 'size': 17}
