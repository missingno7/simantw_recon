# Recovery task _GPatBox

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 205 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov bx, word ptr [bp + 0xc]
0009 mov cx, word ptr [bp + 6]
000c mov dx, word ptr [bp + 0xa]
000f mov di, word ptr [bp + 0xe]
0012 mov ax, dx
0014 cmp dx, cx
0016 jle 0x1acc
0018 mov dx, cx
001a mov word ptr [bp - 8], dx
001d mov dx, bx
001f cmp bx, word ptr [bp + 8]
0022 jle 0x1ad9
0024 mov bx, word ptr [bp + 8]
0027 mov word ptr [bp - 6], bx
002a cmp ax, cx
002c jge 0x1ae2
002e mov ax, cx
0030 inc ax
0031 mov word ptr [bp - 4], ax
0034 cmp dx, word ptr [bp + 8]
0037 jge 0x1aee
0039 mov dx, word ptr [bp + 8]
003c inc dx
003d mov word ptr [bp - 2], dx
0040 test byte ptr [0xcc7e], 1 ; _displayType
0045 jne 0x1b06
0047 mov ax, di
0049 and ax, 0xf
004c cdq 
004d or dh, 1
0050 push dx
0051 push ax
0052 jmp 0x1b5f
0054 mov ax, di
0056 and ax, 0x70
0059 test al, 0xf
005b jne 0x1b2c
005d shr ax, 3
0060 cmp ax, 0xc
0063 ja 0x1b2c
0065 xchg bx, ax
0066 jmp word ptr cs:[bx + 0x1b1e]
006b nop 
006c dw offset 0x1b34
006e dw offset 0x1b3a
0070 dw offset 0x1b42
0072 dw offset 0x1b4a
0074 dw offset 0x1b2c
0076 dw offset 0x1b52
0078 dw offset 0x1b5a
007a push 0xff
007d push -1
007f jmp 0x1b5f
0081 nop 
0082 push 0
0084 push 0
0086 jmp 0x1b5f
0088 push 0x60
008a push 0x6060
008d jmp 0x1b5f
008f nop 
0090 push 0x80
0093 push 0x8080
0096 jmp 0x1b5f
0098 push 0xa0
009b push 0xa0a0
009e jmp 0x1b5f
00a0 push 0xc0
00a3 push 0xc0c0
00a6 jmp 0x1b5f
00a8 push 0x20
00aa push 0x2020
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 174, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 66}}]
00b2 mov si, ax
00b4 push word ptr [0xcf52] ; _clipDC
00b8 lea ax, [bp - 8]
00bb push ss
00bc push ax
00bd push si
00be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 81}}]
00c3 push si
00c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
00c9 pop si
00ca pop di
00cb leave 
00cc retf 
```

## Known declaration examples

- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern int near clipDC;` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GSetAttrib', 'offset': 6580, 'source': 'src/recovered/wf_GSetAttrib-bba4337448.c', 'size': 50}
- {'symbol': '_GBoxFill', 'offset': 6630, 'source': None, 'size': 203}
- {'symbol': '_BitmapImageSize', 'offset': 7040, 'source': 'src/recovered/BitmapImageSize.c', 'size': 49}
- {'symbol': '_ConvertMaskBitmap', 'offset': 7090, 'source': None, 'size': 703}
