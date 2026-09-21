# Recovery task _font_SetFont

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 80 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov si, word ptr [bp + 6]
0007 mov ax, si
0009 or ax, ax
000b je 0x6154
000d dec ax
000e je 0x615c
0010 cmp si, 5
0013 jg 0x6135
0015 or si, si
0017 jge 0x6138
0019 mov si, 2
001c mov es, word ptr [0xc16a]
0020 shl si, 2
0023 mov ax, word ptr es:[si - 0x71a8]
0028 mov dx, word ptr es:[si - 0x71a6]
002d mov word ptr [0x1686], ax ; _curFontPtr
0030 mov word ptr [0x1688], dx
0034 pop si
0035 leave 
0036 retf 
0037 nop 
0038 nop 
0039 push cs
003a call 0x1664 ; _GSetBigFont
003d jmp 0x6161
003f nop 
0040 nop 
0041 push cs
0042 call 0x1560 ; _GSetSmallFont
0045 sub ax, ax
0047 mov word ptr [0x1688], ax
004a mov word ptr [0x1686], ax ; _curFontPtr
004d pop si
004e leave 
004f retf 
```

## Known declaration examples

- `extern struct FarAddress near curFontPtr;` — src/recovered/font_CharWidth.c
- `extern struct FarAddress near curFontPtr;` — src/recovered/font_FontHeight.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_font_FontHeight', 'offset': 24750, 'source': 'src/recovered/font_FontHeight.c', 'size': 31}
- {'symbol': '_font_StringWidth', 'offset': 24782, 'source': None, 'size': 78}
- {'symbol': '_font_InitFonts', 'offset': 24940, 'source': None, 'size': 169}
- {'symbol': '_font_PrintStr', 'offset': 25110, 'source': None, 'size': 165}
