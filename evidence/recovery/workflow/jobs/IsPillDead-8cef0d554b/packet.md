# Recovery task _IsPillDead

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 168 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0009 mov es, ax
000b xor di, di
000d mov cx, word ptr es:[0x8a8c]
0012 dec cx
0013 mov ax, word ptr es:[0x8a8c]
0017 add ax, 2
001a cmp cx, ax
001c jge 0x57bf
001e mov word ptr [bp - 6], di
0021 mov ax, cx
0023 shl ax, 6
0026 mov word ptr [bp - 4], ax
0029 mov <resolved loader operand; see bindings> ; [{'operand_offset': 42, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
002c mov es, word ptr [0xc5a2]
0030 mov si, word ptr es:[0x8a8e]
0035 mov ax, si
0037 dec si
0038 add ax, 2
003b cmp si, ax
003d jge 0x57a8
003f mov di, word ptr [bp - 6]
0042 mov word ptr [bp - 2], cx
0045 push si
0046 push word ptr [bp - 2]
0049 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 76, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
004e add sp, 4
0051 or ax, ax
0053 jne 0x5784
0055 xor dx, dx
0057 jmp 0x578d
0059 nop 
005a mov bx, word ptr [bp - 4]
005d mov dl, byte ptr [bx + si + 0x68e8]
0061 sub dh, dh
0063 or dx, dx
0065 je 0x5792
0067 inc di
0068 mov es, word ptr [0xc5a2]
006c mov ax, word ptr es:[0x8a8e]
0070 add ax, 2
0073 inc si
0074 cmp ax, si
0076 jg 0x576f
0078 mov word ptr [bp - 6], di
007b mov cx, word ptr [bp - 2]
007e add word ptr [bp - 4], 0x40
0082 mov es, word ptr [0xc5a4]
0086 mov ax, word ptr es:[0x8a8c]
008a add ax, 2
008d inc cx
008e cmp ax, cx
0090 jg 0x5756
0092 mov di, word ptr [bp - 6]
0095 cmp di, 5
0098 jle 0x57cc
009a mov ax, 1
009d pop si
009e pop di
009f leave 
00a0 retf 
00a1 nop 
00a2 xor ax, ax
00a4 pop si
00a5 pop di
00a6 leave 
00a7 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PlacePillTile', 'offset': 22234, 'source': None, 'size': 40}
- {'symbol': '_PillGetLife', 'offset': 22274, 'source': 'src/recovered/PillGetLife.c', 'size': 40}
- {'symbol': '_MakePillFood', 'offset': 22482, 'source': None, 'size': 560}
- {'symbol': '_PillFoodTile', 'offset': 23042, 'source': None, 'size': 110}
