# Recovery task _win_RectFill

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 264 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 les si, ptr [0xcc58]
0008 mov al, byte ptr es:[si + 3]
000c cmp byte ptr es:[si + 2], al
0010 jne 0xb55f
0012 jmp 0xb5f6
0015 test byte ptr [0xcc7e], 1 ; _displayType
001a je 0xb569
001c jmp 0xb5f6
001f mov bx, si
0021 mov al, byte ptr es:[bx]
0024 cwde 
0025 imul ax, ax, 0x101
0029 push ax
002a mov al, byte ptr es:[bx + 2]
002e cwde 
002f imul ax, ax, 0x101
0033 push ax
0034 mov al, byte ptr es:[bx + 3]
0038 cwde 
0039 imul ax, ax, 0x101
003d push ax
003e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 65, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
0043 add sp, 6
0046 mov es, word ptr [0xc6c6]
004a cmp word ptr es:[0xbd0a], 0
0050 je 0xb5b2
0052 mov si, word ptr [bp + 6]
0055 push 0
0057 mov es, word ptr [bp + 8]
005a mov ax, word ptr es:[si + 6]
005e dec ax
005f push ax
0060 mov ax, word ptr es:[si + 4]
0064 dec ax
0065 push ax
0066 jmp 0xb5c2
0068 mov si, word ptr [bp + 6]
006b push 0
006d mov es, word ptr [bp + 8]
0070 push word ptr es:[si + 6]
0074 push word ptr es:[si + 4]
0078 push word ptr es:[si + 2]
007c push word ptr es:[si]
007f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GPatBox
0084 add sp, 0xa
0087 les bx, ptr [0xcc58]
008b mov al, byte ptr es:[bx]
008e cwde 
008f imul ax, ax, 0x101
0093 push ax
0094 mov cx, ax
0096 mov al, byte ptr es:[bx + 2]
009a cwde 
009b imul ax, ax, 0x101
009f push ax
00a0 push cx
00a1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 164, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
00a6 add sp, 6
00a9 pop si
00aa leave 
00ab retf 
00ac mov es, word ptr [0xc6c6]
00b0 cmp word ptr es:[0xbd0a], 0
00b6 je 0xb624
00b8 mov si, word ptr [bp + 6]
00bb les bx, ptr [0xcc58]
00bf mov al, byte ptr es:[bx + 2]
00c3 cwde 
00c4 imul ax, ax, 0x101
00c8 push ax
00c9 mov es, word ptr [bp + 8]
00cc mov ax, word ptr es:[si + 6]
00d0 dec ax
00d1 push ax
00d2 mov ax, word ptr es:[si + 4]
00d6 dec ax
00d7 push ax
00d8 jmp 0xb640
00da mov si, word ptr [bp + 6]
00dd les bx, ptr [0xcc58]
00e1 mov al, byte ptr es:[bx + 2]
00e5 cwde 
00e6 imul ax, ax, 0x101
00ea push ax
00eb mov es, word ptr [bp + 8]
00ee push word ptr es:[si + 6]
00f2 push word ptr es:[si + 4]
00f6 push word ptr es:[si + 2]
00fa push word ptr es:[si]
00fd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 256, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GPatBox
0102 add sp, 0xa
0105 pop si
0106 leave 
0107 retf 
```

## Known declaration examples

- `extern void far GPatBox(int left, int top, int right, int bottom, unsigned int pattern);` — src/recovered/GCheckerBox.c
- `extern void far GPatBox(int left, int top, int right, int bottom, int pattern);` — src/recovered/GRectChecker.c
- `extern void far GPatBox(int left, int top, int right, int bottom, unsigned int pattern);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_win_SetColorFromObj-7570e08dca.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_SetColorFromObj', 'offset': 46146, 'source': 'src/recovered/wf_win_SetColorFromObj-7570e08dca.c', 'size': 111}
- {'symbol': '_win_SetColorFromObjNum', 'offset': 46258, 'source': None, 'size': 152}
- {'symbol': '_win_FillObjRect', 'offset': 46674, 'source': None, 'size': 35}
- {'symbol': '_win_RectFillOutline', 'offset': 46710, 'source': None, 'size': 40}
