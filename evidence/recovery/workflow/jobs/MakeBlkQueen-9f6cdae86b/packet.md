# Recovery task _MakeBlkQueen

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 192 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 0xa]
000c push di
000d push word ptr [bp + 6]
0010 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 19, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
0015 add sp, 4
0018 mov es, word ptr [0xc5dc]
001c mov ax, si
001e xor si, 4
0021 mov cx, ax
0023 mov al, byte ptr es:[si + 8]
0028 cwde 
0029 mov dx, di
002b add di, ax
002d push di
002e mov es, word ptr [0xc5de]
0032 mov al, byte ptr es:[si]
0037 cwde 
0038 add ax, word ptr [bp + 6]
003b push ax
003c mov di, cx
003e mov word ptr [bp - 2], dx
0041 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 68, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
0046 add sp, 4
0049 mov es, word ptr [0xc5dc]
004d mov al, byte ptr es:[si + 8]
0052 cwde 
0053 shl ax, 1
0055 add ax, word ptr [bp - 2]
0058 push ax
0059 mov es, word ptr [0xc5de]
005d mov al, byte ptr es:[si]
0062 cwde 
0063 shl ax, 1
0065 add ax, word ptr [bp + 6]
0068 push ax
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
006e add sp, 4
0071 push 0
0073 push 9
0075 lea ax, [di + 0x60]
0078 push ax
0079 push word ptr [bp - 2]
007c push word ptr [bp + 6]
007f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToBList
0084 add sp, 0xa
0087 push 0
0089 push 9
008b lea ax, [di + 0x68]
008e push ax
008f mov es, word ptr [0xc5dc]
0093 mov al, byte ptr es:[si + 8]
0098 cwde 
0099 add ax, word ptr [bp - 2]
009c push ax
009d mov es, word ptr [0xc5de]
00a1 mov al, byte ptr es:[si]
00a6 cwde 
00a7 add ax, word ptr [bp + 6]
00aa push ax
00ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 174, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToBList
00b0 add sp, 0xa
00b3 mov es, word ptr [0xc5d4]
00b7 inc word ptr es:[0x78e8]
00bc pop si
00bd pop di
00be leave 
00bf retf 
```

## Known declaration examples

- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitYelloAnt', 'offset': 25746, 'source': None, 'size': 315}
- {'symbol': '_PlaceBlackQueen', 'offset': 26062, 'source': None, 'size': 332}
- {'symbol': '_PlaceRedQueen', 'offset': 26586, 'source': None, 'size': 299}
- {'symbol': '_MakeRedQueen', 'offset': 26886, 'source': None, 'size': 194}
