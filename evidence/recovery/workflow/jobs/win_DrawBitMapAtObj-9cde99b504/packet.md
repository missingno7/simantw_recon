# Recovery task _win_DrawBitMapAtObj

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 64 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov si, word ptr [bp + 6]
0007 mov es, word ptr [bp + 8]
000a test byte ptr es:[si + 0x24], 1
000f je 0xbe6d
0011 push word ptr [bp + 0xa]
0014 push word ptr es:[si + 2]
0018 push word ptr es:[si]
001b nop 
001c push cs
001d call 0xbd5a ; _win_DrawBitMap
0020 add sp, 6
0023 or ax, ax
0025 jne 0xbe6d
0027 mov al, byte ptr [0xce97] ; _monoPat
002a cwde 
002b or ax, word ptr [0xcf4e] ; __foreColor
002f push ax
0030 mov ax, word ptr [bp + 8]
0033 push ax
0034 push si
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
003a add sp, 6
003d pop si
003e leave 
003f retf 
```

## Known declaration examples

- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/win_RectHOutline.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawTitle', 'offset': 48280, 'source': None, 'size': 193}
- {'symbol': '_win_DrawBitMap', 'offset': 48474, 'source': None, 'size': 214}
- {'symbol': '_win_DrawBitMapAtObjNum', 'offset': 48752, 'source': None, 'size': 98}
- {'symbol': '_win_PrintTextInRect', 'offset': 48850, 'source': None, 'size': 438}
