# Recovery task _GSetAttrib

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 50 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 test byte ptr [0xcc7e], 1 ; _displayType
0008 je 0x19d2
000a mov ax, word ptr [bp + 6]
000d cmp word ptr [bp + 8], ax
0010 jne 0x19d2
0012 mov ax, word ptr [bp + 0xa]
0015 mov word ptr [0xcf4e], ax ; __foreColor
0018 mov word ptr [0xce8a], ax ; __backColor
001b jmp 0x19de
001d nop 
001e mov ax, word ptr [bp + 8]
0021 mov word ptr [0xce8a], ax ; __backColor
0024 mov ax, word ptr [bp + 6]
0027 mov word ptr [0xcf4e], ax ; __foreColor
002a mov al, byte ptr [bp + 0xa]
002d mov byte ptr [0xce97], al ; _monoPat
0030 leave 
0031 retf 
```

## Known declaration examples

- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/win_RectHOutline.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CreateMonoSolidBrush', 'offset': 6402, 'source': 'src/recovered/CreateMonoSolidBrush.c', 'size': None}
- {'symbol': '_GInvBox', 'offset': 6502, 'source': None, 'size': 78}
- {'symbol': '_GBoxFill', 'offset': 6630, 'source': None, 'size': None}
- {'symbol': '_GPatBox', 'offset': 6834, 'source': None, 'size': None}
