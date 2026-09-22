# Recovery task _win_DrawEndGameWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 301 bytes.

```asm
0000 enter 0x1c, 0
0004 push di
0005 push si
0006 test byte ptr [bp + 6], 2
000a jne 0x64e3
000c jmp 0x65fd
000f lea ax, [bp - 0x18]
0012 push ss
0013 push ax
0014 nop 
0015 push cs
0016 call 0x5530 ; _CalcScore
0019 add sp, 4
001c mov word ptr [bp - 4], ax
001f mov word ptr [bp - 2], dx
0022 mov bx, 0x80b4
0025 mov es, word ptr [0xbee6]
0029 mov word ptr [bp - 0x1c], bx
002c mov word ptr [bp - 0x1a], es
002f cmp word ptr es:[bx], 2
0033 jne 0x6514
0035 push 0
0037 push 5
0039 push dx
003a push ax
003b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0040 mov word ptr [bp - 8], ax
0043 mov word ptr [bp - 6], dx
0046 cmp dx, 3
0049 jg 0x652a
004b jl 0x6526
004d cmp ax, 0x44cc
0050 jae 0x652a
0052 xor si, si
0054 jmp 0x6563
0056 cmp dx, 6
0059 jg 0x653c
005b jl 0x6536
005d cmp ax, 0x8998
0060 jae 0x653c
0062 mov si, 1
0065 jmp 0x6563
0067 nop 
0068 cmp dx, 9
006b jg 0x654e
006d jl 0x6548
006f cmp ax, 0xce64
0072 jae 0x654e
0074 mov si, 2
0077 jmp 0x6563
0079 nop 
007a cmp dx, 0xd
007d jg 0x6560
007f jl 0x655a
0081 cmp ax, 0x1330
0084 jae 0x6560
0086 mov si, 3
0089 jmp 0x6563
008b nop 
008c mov si, 4
008f mov es, word ptr [0xbefe]
0093 cmp word ptr es:[0x9cea], 0
0099 jne 0x6572
009b add si, 5
009e push 4
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
00a5 add sp, 2
00a8 les bx, ptr [bp - 0x1c]
00ab cmp word ptr es:[bx], 0
00af jl 0x65a4
00b1 cmp word ptr es:[bx], 3
00b5 jg 0x65a4
00b7 mov bx, word ptr es:[bx]
00ba shl bx, 2
00bd mov es, word ptr [0xbef2]
00c1 les di, ptr es:[0x7a4a]
00c6 push word ptr es:[bx + di + 2]
00ca push word ptr es:[bx + di]
00cd jmp 0x65b5
00cf nop 
00d0 mov es, word ptr [0xbef2]
00d4 les bx, ptr es:[0x7a4a]
00d9 push word ptr es:[bx + 0xa]
00dd push word ptr es:[bx + 8]
00e1 push 0x402
00e4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 231, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
00e9 add sp, 6
00ec push word ptr [bp - 2]
00ef push word ptr [bp - 4]
00f2 push ds
00f3 push 0x965
00f6 push 0x403
00f9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 252, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
00fe add sp, 0xa
0101 mov es, word ptr [0xbf00]
0105 les bx, ptr es:[0x78ac]
010a shl si, 2
010d push word ptr es:[bx + si + 2]
0111 push word ptr es:[bx + si]
0114 push 0x404
0117 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 282, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
011c add sp, 6
011f push 0
0121 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 292, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0126 add sp, 2
0129 pop si
012a pop di
012b leave 
012c retf 
```

## Known declaration examples

- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawPictureWindow', 'offset': 25078, 'source': 'src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c', 'size': 198}
- {'symbol': '_PictureDialog', 'offset': 25276, 'source': None, 'size': 535}
- {'symbol': '_EndGameDialog', 'offset': 26114, 'source': None, 'size': 312}
- {'symbol': '_SpiderDialog', 'offset': 26426, 'source': None, 'size': 537}
