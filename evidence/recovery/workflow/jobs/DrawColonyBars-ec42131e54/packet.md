# Recovery task _DrawColonyBars

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 253 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 6], 0
000b mov word ptr [bp - 4], 0xa8
0010 xor si, si
0012 mov di, si
0014 mov es, word ptr [0xc1dc]
0018 mov bx, word ptr [bp - 6]
001b add bx, di
001d mov al, byte ptr es:[bx + 0xa4]
0022 sub ah, ah
0024 add ax, 3
0027 sar ax, 2
002a mov word ptr [bp - 2], ax
002d or ax, ax
002f jle 0xc00e
0031 mov es, word ptr [0xc1c4]
0035 mov ax, word ptr es:[0x8110]
0039 sub ax, si
003b add ax, word ptr [bp - 4]
003e mov word ptr [bp - 0x10], ax
0041 mov cx, word ptr es:[0x8112]
0046 add cx, si
0048 add cx, 0x47
004b mov word ptr [bp - 0xa], cx
004e sub cx, word ptr [bp - 2]
0051 mov word ptr [bp - 0xe], cx
0054 add ax, 9
0057 mov word ptr [bp - 0xc], ax
005a push 0xf
005c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 95, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0061 add sp, 2
0064 push ax
0065 lea ax, [bp - 0x10]
0068 push ss
0069 push ax
006a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
006f add sp, 6
0072 mov es, word ptr [0xc1da]
0076 mov bx, word ptr [bp - 6]
0079 add bx, di
007b mov al, byte ptr es:[bx + 0x164]
0080 sub ah, ah
0082 add ax, 3
0085 sar ax, 2
0088 mov word ptr [bp - 2], ax
008b or ax, ax
008d jle 0xc071
008f mov es, word ptr [0xc1c4]
0093 mov ax, word ptr es:[0x8110]
0097 sub ax, si
0099 add ax, word ptr [bp - 4]
009c add ax, 0xc
009f mov word ptr [bp - 0x10], ax
00a2 mov cx, word ptr es:[0x8112]
00a7 add cx, si
00a9 add cx, 0x47
00ac mov word ptr [bp - 0xa], cx
00af sub cx, word ptr [bp - 2]
00b2 mov word ptr [bp - 0xe], cx
00b5 add ax, 9
00b8 mov word ptr [bp - 0xc], ax
00bb push 3
00bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 192, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
00c2 add sp, 2
00c5 or al, 0x20
00c7 push ax
00c8 lea ax, [bp - 0x10]
00cb push ss
00cc push ax
00cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 208, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
00d2 add sp, 6
00d5 inc di
00d6 add si, 0xa
00d9 cmp si, 0xa0
00dd jge 0xc07e
00df jmp 0xbfb0
00e2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 229, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myServiceSong
00e7 add word ptr [bp - 6], 0x10
00eb add word ptr [bp - 4], 0x1c
00ef cmp word ptr [bp - 4], 0x1f8
00f4 jge 0xc095
00f6 jmp 0xbfac
00f9 pop si
00fa pop di
00fb leave 
00fc retf 
```

## Known declaration examples

- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far GRectFill(struct BitmapObject far *object, int color);` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern void far GRectFill(void far *object, int color);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InvertPatch', 'offset': 48644, 'source': None, 'size': 159}
- {'symbol': '_DrawSimColonies', 'offset': 48804, 'source': None, 'size': 247}
- {'symbol': '_YardArea', 'offset': 49306, 'source': None, 'size': 255}
- {'symbol': '_DeinitMapFunctions', 'offset': 49562, 'source': 'src/recovered/DeinitMapFunctions.c', 'size': 1}
