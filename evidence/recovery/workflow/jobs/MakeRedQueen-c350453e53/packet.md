# Recovery task _MakeRedQueen

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 194 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 0xa]
000c push di
000d push word ptr [bp + 6]
0010 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 19, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
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
0041 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 68, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
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
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
006e add sp, 4
0071 push 0
0073 push 9
0075 lea ax, [di + 0xe0]
0079 push ax
007a push word ptr [bp - 2]
007d push word ptr [bp + 6]
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToRList
0085 add sp, 0xa
0088 push 0
008a push 9
008c lea ax, [di + 0xe8]
0090 push ax
0091 mov es, word ptr [0xc5dc]
0095 mov al, byte ptr es:[si + 8]
009a cwde 
009b add ax, word ptr [bp - 2]
009e push ax
009f mov es, word ptr [0xc5de]
00a3 mov al, byte ptr es:[si]
00a8 cwde 
00a9 add ax, word ptr [bp + 6]
00ac push ax
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToRList
00b2 add sp, 0xa
00b5 mov es, word ptr [0xc5d6]
00b9 inc word ptr es:[0x79dc]
00be pop si
00bf pop di
00c0 leave 
00c1 retf 
```

## Known declaration examples

- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeBlkQueen', 'offset': 26394, 'source': None, 'size': 192}
- {'symbol': '_PlaceRedQueen', 'offset': 26586, 'source': None, 'size': 299}
- {'symbol': '_fracSIN', 'offset': 27080, 'source': 'src/recovered/wf_fracSIN-85445ba91f.c', 'size': 70}
- {'symbol': '_fracCOS', 'offset': 27150, 'source': 'src/recovered/wf_fracCOS-62316b393c.c', 'size': 74}
