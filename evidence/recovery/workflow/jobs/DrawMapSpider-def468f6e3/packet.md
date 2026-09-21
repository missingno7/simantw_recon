# Recovery task _DrawMapSpider

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 280 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c push word ptr [0x19aa] ; _mapBuf
0010 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 19, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0015 add sp, 2
0018 mov word ptr [bp - 4], ax
001b mov word ptr [bp - 2], dx
001e lea ax, [bp - 6]
0021 push ss
0022 push ax
0023 lea cx, [bp - 8]
0026 push ss
0027 push cx
0028 mov dx, word ptr [bp + 0xa]
002b add dx, 0x44c
002f push dx
0030 mov es, word ptr [0xc1e4]
0034 mov dx, word ptr es:[0x807c]
0039 shl dx, 7
003c push dx
003d mov es, word ptr [0xc1e2]
0041 mov dx, word ptr es:[0x8096]
0046 shl dx, 6
0049 push dx
004a mov dx, si
004c shl dx, 2
004f push dx
0050 shl di, 2
0053 push di
0054 push word ptr [bp - 2]
0057 push word ptr [bp - 4]
005a mov word ptr [bp - 0x16], dx
005d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 96, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DrawBitMapToBuffer
0062 add sp, 0x16
0065 push word ptr [0x19aa] ; _mapBuf
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
006e add sp, 2
0071 mov es, word ptr [0xc1f2]
0075 mov ax, word ptr es:[0x8112]
0079 add ax, word ptr [bp - 0x16]
007c mov word ptr [bp - 0xe], ax
007f add di, word ptr es:[0x8110]
0084 mov word ptr [bp - 0x10], di
0087 add di, word ptr [bp - 6]
008a mov word ptr [bp - 0xc], di
008d add ax, word ptr [bp - 8]
0090 mov word ptr [bp - 0xa], ax
0093 push word ptr [0xbca8]
0097 lea ax, [bp - 0x10]
009a push ss
009b push ax
009c push 0
009e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 159, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
00a3 sub si, 2
00a6 mov bx, 0x72ca
00a9 mov es, word ptr [0xc1e0]
00ad mov word ptr [bp - 0x14], bx
00b0 mov word ptr [bp - 0x12], es
00b3 cmp word ptr es:[bx], 0
00b7 je 0xd222
00b9 push word ptr es:[bx]
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
00c1 add sp, 2
00c4 mov di, ax
00c6 mov word ptr [bp - 2], dx
00c9 mov es, word ptr [0xc200]
00cd mov ax, word ptr es:[0x78ba]
00d1 imul si
00d3 add di, ax
00d5 lea ax, [si + 5]
00d8 mov word ptr [bp + 6], ax
00db cmp ax, si
00dd jle 0xd214
00df mov cx, ax
00e1 mov ds, word ptr [bp - 2]
00e4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 229, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00e7 mov es, ax
00e9 cmp si, 0x40
00ec jl 0xd200
00ee push ss
00ef pop ds
00f0 jmp 0xd214
00f2 or si, si
00f4 jl 0xd207
00f6 mov byte ptr [di], 0xff
00f9 mov ax, word ptr es:[0x78ba]
00fd add di, ax
00ff inc si
0100 cmp si, cx
0102 jl 0xd1f7
0104 jmp 0xd1fc
0106 les bx, ptr [bp - 0x14]
0109 push word ptr es:[bx]
010c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 271, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0111 add sp, 2
0114 pop si
0115 pop di
0116 leave 
0117 retf 
```

## Known declaration examples

- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawMap', 'offset': 52542, 'source': None, 'size': 264}
- {'symbol': '_win_DrawMapWindow', 'offset': 52806, 'source': None, 'size': 712}
- {'symbol': '_DrawMapFoot', 'offset': 53798, 'source': None, 'size': 484}
- {'symbol': '_MapToYellowAnt', 'offset': 54282, 'source': None, 'size': 105}
