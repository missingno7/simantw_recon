# Recovery task _DrawSimColonies

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 247 bytes.

```asm
0000 enter 0x24, 0
0004 push di
0005 push si
0006 cmp word ptr [bp + 6], 2
000a je 0xbeb3
000c jmp 0xbf97
000f xor si, si
0011 mov word ptr [bp - 0x10], si
0014 xor dx, dx
0016 mov word ptr [bp - 8], dx
0019 mov word ptr [bp - 0xa], si
001c mov word ptr [bp - 0x12], si
001f mov word ptr [bp - 0xe], dx
0022 mov si, dx
0024 mov es, word ptr [0xc1da]
0028 mov bx, word ptr [bp - 0x10]
002b add bx, si
002d mov cl, byte ptr es:[bx + 0x164]
0032 sub ch, ch
0034 mov es, word ptr [0xc1dc]
0038 cmp byte ptr es:[bx + 0xa4], ch
003d jne 0xbef0
003f cmp cx, 1
0042 sbb ax, ax
0044 and ax, 1
0047 add ax, 2
004a jmp 0xbef6
004c cmp cx, 1
004f sbb ax, ax
0051 inc ax
0052 mov word ptr [bp - 0xc], ax
0055 mov es, word ptr [0xc1c4]
0059 mov ax, word ptr es:[0x8110]
005d add ax, word ptr [bp - 0xa]
0060 mov word ptr [bp - 6], ax
0063 mov ax, word ptr es:[0x8112]
0067 add ax, word ptr [bp - 8]
006a mov word ptr [bp - 4], ax
006d mov word ptr [bp - 2], 0
0072 mov word ptr [bp - 0xe], si
0075 mov bx, word ptr [bp - 2]
0078 mov dx, ax
007a mov cx, word ptr [bp - 6]
007d mov ax, word ptr [bx + 0x18a4]
0081 add ax, cx
0083 mov si, bx
0085 mov word ptr [bp + si - 0x24], ax
0088 mov ax, word ptr [bx + 0x18a6]
008c add ax, dx
008e mov word ptr [bp + si - 0x22], ax
0091 add bx, 4
0094 cmp bx, 0x10
0097 jl 0xbf21
0099 mov si, word ptr [bp - 0xe]
009c mov di, word ptr [bp - 0xc]
009f shl di, 1
00a1 push word ptr [di + 0x198a]
00a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 168, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
00aa add sp, 2
00ad push ax
00ae push word ptr [di + 0x1982]
00b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 181, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
00b7 add sp, 2
00ba push ax
00bb lea ax, [bp - 0x24]
00be push ss
00bf push ax
00c0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 195, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TrapFill
00c5 add sp, 8
00c8 sub word ptr [bp - 0xa], 0xa
00cc inc si
00cd add word ptr [bp - 8], 0xa
00d1 cmp word ptr [bp - 8], 0xa0
00d6 jge 0xbf7f
00d8 jmp 0xbec8
00db mov si, word ptr [bp - 0x12]
00de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 225, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myServiceSong
00e3 add word ptr [bp - 0x10], 0x10
00e7 add si, 0x1c
00ea cmp si, 0x150
00ee jge 0xbf97
00f0 jmp 0xbeb8
00f3 pop si
00f4 pop di
00f5 leave 
00f6 retf 
```

## Known declaration examples

- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_TooFar', 'offset': 48604, 'source': 'src/recovered/wf_TooFar-89685c4366.c', 'size': 39}
- {'symbol': '_InvertPatch', 'offset': 48644, 'source': None, 'size': 159}
- {'symbol': '_DrawColonyBars', 'offset': 49052, 'source': None, 'size': 253}
- {'symbol': '_YardArea', 'offset': 49306, 'source': None, 'size': 255}
