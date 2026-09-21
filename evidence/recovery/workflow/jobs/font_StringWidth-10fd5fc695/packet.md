# Recovery task _font_StringWidth

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 78 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov ax, word ptr [0x1688]
000c or ax, word ptr [0x1686] ; _curFontPtr
0010 jne 0x6104
0012 mov al, byte ptr [0xce7c] ; _fontWidth
0015 cwde 
0016 mov cx, ax
0018 mov es, word ptr [bp + 8]
001b mov dx, cx
001d mov word ptr [bp - 2], cx
0020 mov di, si
0022 mov cx, 0xffff
0025 xor ax, ax
0027 repne scasb al, byte ptr es:[di]
0029 not cx
002b dec cx
002c mov ax, cx
002e imul word ptr [bp - 2]
0031 pop si
0032 pop di
0033 leave 
0034 retf 
0035 nop 
0036 push word ptr [0x1688]
003a push word ptr [0x1686] ; _curFontPtr
003e push word ptr [bp + 8]
0041 push si
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; __font_StringWidth
0047 add sp, 8
004a pop si
004b pop di
004c leave 
004d retf 
```

## Known declaration examples

- `extern struct FarAddress near curFontPtr;` — src/recovered/font_CharWidth.c
- `extern struct FarAddress near curFontPtr;` — src/recovered/font_FontHeight.c
- `extern char near fontWidth;` — src/recovered/font_CharWidth.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_font_CharWidth', 'offset': 24714, 'source': 'src/recovered/font_CharWidth.c', 'size': 36}
- {'symbol': '_font_FontHeight', 'offset': 24750, 'source': 'src/recovered/font_FontHeight.c', 'size': 31}
- {'symbol': '_font_SetFont', 'offset': 24860, 'source': None, 'size': 80}
- {'symbol': '_font_InitFonts', 'offset': 24940, 'source': None, 'size': 169}
