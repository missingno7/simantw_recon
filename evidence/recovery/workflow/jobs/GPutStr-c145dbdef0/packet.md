# Recovery task _GPutStr

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 229 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 test byte ptr [0xcc7e], 1 ; _displayType
0009 jne 0x17c4
000b push word ptr [0xcf52] ; _clipDC
000f mov al, byte ptr [0xce8a] ; __backColor
0012 and ax, 0xf
0015 cdq 
0016 or dh, 1
0019 push dx
001a push ax
001b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 28, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 1}}]
0020 push word ptr [0xcf52] ; _clipDC
0024 mov al, byte ptr [0xcf4e] ; __foreColor
0027 and ax, 0xf
002a cdq 
002b or dh, 1
002e push dx
002f push ax
0030 jmp 0x17fa
0032 test byte ptr [0xce97], 0x80 ; _monoPat
0037 je 0x17e4
0039 push word ptr [0xcf52] ; _clipDC
003d push 0xff
0040 push -1
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 1}}]
0047 push word ptr [0xcf52] ; _clipDC
004b push 0
004d push 0
004f jmp 0x17fa
0051 nop 
0052 push word ptr [0xcf52] ; _clipDC
0056 push 0
0058 push 0
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 91, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 1}}]
005f push word ptr [0xcf52] ; _clipDC
0063 push 0xff
0066 push -1
0068 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 9}}]
006d push word ptr [0xcf52] ; _clipDC
0071 push 2
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 2}}]
0078 push word ptr [0xcf52] ; _clipDC
007c push 1
007e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 3}}]
0083 push word ptr [0xcf52] ; _clipDC
0087 push 0
0089 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 138, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 346}}]
008e push word ptr [0xcf52] ; _clipDC
0092 push word ptr [bp + 6]
0095 push word ptr [bp + 8]
0098 les di, ptr [bp + 0xa]
009b push es
009c push di
009d mov cx, 0xffff
00a0 xor ax, ax
00a2 repne scasb al, byte ptr es:[di]
00a4 not cx
00a6 dec cx
00a7 push cx
00a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 33}}]
00ad mov ax, word ptr [bp + 8]
00b0 mov es, word ptr [0xc6b4]
00b4 mov word ptr es:[0x7694], ax
00b8 push word ptr [0xcf52] ; _clipDC
00bc push word ptr [bp + 0xc]
00bf push word ptr [bp + 0xa]
00c2 push es
00c3 les di, ptr [bp + 0xa]
00c6 mov cx, 0xffff
00c9 xor ax, ax
00cb repne scasb al, byte ptr es:[di]
00cd not cx
00cf dec cx
00d0 pop es
00d1 push cx
00d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 211, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 91}}]
00d7 add ax, word ptr [bp + 6]
00da mov es, word ptr [0xc6b4]
00de mov word ptr es:[0x7692], ax
00e2 pop di
00e3 leave 
00e4 retf 
```

## Known declaration examples

- `extern int near _backColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near _backColor;` — src/recovered/wf_GRectFillOutline-24e4a6aa35.c
- `extern int near _backColor;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_GPatBox-b326d1b571.c
- `extern int near clipDC;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern unsigned char near monoPat;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern char near monoPat;` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern char near monoPat;` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GSetBigFont', 'offset': 5732, 'source': None, 'size': 259}
- {'symbol': '_GCloseFonts', 'offset': 5992, 'source': 'src/recovered/GCloseFonts.c', 'size': 42}
- {'symbol': '_PopMsg', 'offset': 6264, 'source': 'src/recovered/PopMsg.c', 'size': 26}
- {'symbol': '_Error', 'offset': 6290, 'source': 'src/recovered/Error.c', 'size': 26}
