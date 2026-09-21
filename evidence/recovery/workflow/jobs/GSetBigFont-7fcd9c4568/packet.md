# Recovery task _GSetBigFont

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 259 bytes.

```asm
0000 enter 0x20, 0
0004 push si
0005 cmp word ptr [0xba30], 0 ; _bigFontH
000a je 0x1673
000c jmp 0x1719
000f push ds
0010 push 0xba48
0013 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 119}}]
0018 or ax, ax
001a je 0x168f
001c push -1
001e push 0x1d
0020 push 0
0022 push 0
0024 push 0
0026 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 111}}]
002b push 0xe
002d push 8
002f push 0
0031 push 0
0033 push 0x190
0036 push 0
0038 push 0
003a push 0
003c push 0
003e push 2
0040 push 1
0042 push 2
0044 push 1
0046 push ds
0047 push 0xba54
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 56}}]
004f mov word ptr [0xba30], ax ; _bigFontH
0052 push word ptr [0xcd78] ; _rootWnd
0056 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 66}}]
005b mov si, ax
005d push si
005e push word ptr [0xba30] ; _bigFontH
0062 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 99, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 45}}]
0067 mov word ptr [0xcc54], ax
006a push si
006b lea ax, [bp - 0x20]
006e push ss
006f push ax
0070 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 113, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 93}}]
0075 mov al, byte ptr [bp - 0x18]
0078 add al, byte ptr [bp - 0x20]
007b mov byte ptr [0xcc57], al
007e mov ax, word ptr [bp - 0x16]
0081 add ax, word ptr [bp - 0x14]
0084 cdq 
0085 sub ax, dx
0087 sar ax, 1
0089 mov es, word ptr [0xc6b2]
008d mov byte ptr es:[0x7221], al
0091 push si
0092 push 0
0094 push 0
0096 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 151, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 349}}]
009b push si
009c push word ptr [0xcc54]
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 161, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 45}}]
00a5 push word ptr [0xcd78] ; _rootWnd
00a9 push si
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 171, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 68}}]
00af mov word ptr [0xcc54], 0
00b5 cmp word ptr [0xcf52], 0 ; _clipDC
00ba je 0x1753
00bc push word ptr [0xcf52] ; _clipDC
00c0 push 0
00c2 push 0
00c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 349}}]
00c9 cmp word ptr [0xcc54], 0
00ce jne 0x1746
00d0 push word ptr [0xcf52] ; _clipDC
00d4 push word ptr [0xba30] ; _bigFontH
00d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 217, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 45}}]
00dd mov word ptr [0xcc54], ax
00e0 jmp 0x1753
00e2 push word ptr [0xcf52] ; _clipDC
00e6 push word ptr [0xba30] ; _bigFontH
00ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 235, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 45}}]
00ef mov es, word ptr [0xc6b2]
00f3 mov al, byte ptr es:[0x7221]
00f7 mov byte ptr [0xce7c], al ; _fontWidth
00fa mov al, byte ptr [0xcc57]
00fd mov byte ptr [0xce90], al ; _fontHeight
0100 pop si
0101 leave 
0102 retf 
```

## Known declaration examples

- `extern int near bigFontH;` — src/recovered/GCloseFonts.c
- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern int near clipDC;` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern char near fontHeight;` — src/recovered/font_FontHeight.c
- `extern char near fontWidth;` — src/recovered/font_CharWidth.c
- `extern int near rootWnd;` — src/recovered/DoWinHelp.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_WindowsMemCpy', 'offset': 5390, 'source': 'src/recovered/WindowsMemCpy.c', 'size': 81}
- {'symbol': '_GSetSmallFont', 'offset': 5472, 'source': None, 'size': 259}
- {'symbol': '_GCloseFonts', 'offset': 5992, 'source': 'src/recovered/GCloseFonts.c', 'size': 42}
- {'symbol': '_GPutStr', 'offset': 6034, 'source': None, 'size': 229}
