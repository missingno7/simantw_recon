# Recovery task _AddRandAntLion

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 285 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 xor di, di
0008 push 0x40
000a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
000f add sp, 2
0012 mov si, ax
0014 push 0x41
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
001b add sp, 2
001e add si, ax
0020 push 0x20
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0027 add sp, 2
002a push 0x21
002c mov word ptr [bp - 0xa], ax
002f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 50, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0034 add sp, 2
0037 add ax, word ptr [bp - 0xa]
003a mov word ptr [bp - 8], ax
003d push ax
003e push si
003f push 1
0041 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 68, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsClear3x3
0046 add sp, 6
0049 dec ax
004a je 0x428e
004c push word ptr [bp - 8]
004f push si
0050 push 1
0052 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 85, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsClearTile
0057 add sp, 6
005a dec ax
005b jne 0x4284
005d cmp di, 0x64
0060 jge 0x428e
0062 inc di
0063 cmp di, 0xc8
0067 jl 0x422a
0069 jmp 0x4339
006c push 0x38
006e push word ptr [bp - 8]
0071 push si
0072 push 1
0074 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 119, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMap
0079 add sp, 8
007c xor di, di
007e mov es, word ptr [0xc57e]
0082 mov al, byte ptr es:[di + 8]
0087 cwde 
0088 add ax, word ptr [bp - 8]
008b mov word ptr [bp - 2], ax
008e push ax
008f mov es, word ptr [0xc580]
0093 mov al, byte ptr es:[di]
0098 cwde 
0099 add ax, si
009b mov word ptr [bp - 4], ax
009e push ax
009f push 1
00a1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 164, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsClearTile
00a6 add sp, 6
00a9 dec ax
00aa jne 0x42e8
00ac mov al, byte ptr [di + 0x25e8]
00b0 sub ah, ah
00b2 add ax, 0x30
00b5 push ax
00b6 push word ptr [bp - 2]
00b9 push word ptr [bp - 4]
00bc push 1
00be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 193, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMap
00c3 add sp, 8
00c6 inc di
00c7 cmp di, 8
00ca jl 0x42a0
00cc mov <resolved loader operand; see bindings> ; [{'operand_offset': 205, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00cf mov ds, ax
00d1 mov ax, si
00d3 mov <resolved loader operand; see bindings> ; [{'operand_offset': 212, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00d6 mov es, cx
00d8 mov bx, word ptr [0x8a88]
00dc mov byte ptr es:[bx - 0x7f64], al
00e1 mov al, byte ptr [bp - 8]
00e4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 229, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00e7 mov es, cx
00e9 mov byte ptr es:[bx - 0x7f44], al
00ee xor al, al
00f0 mov <resolved loader operand; see bindings> ; [{'operand_offset': 241, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00f3 mov es, cx
00f5 mov byte ptr es:[bx + 0x7a68], al
00fa mov <resolved loader operand; see bindings> ; [{'operand_offset': 251, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00fd mov es, cx
00ff mov byte ptr es:[bx + 0x7d34], al
0104 mov <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0107 mov es, cx
0109 mov byte ptr es:[bx + 0x7d4e], al
010e cmp bx, 9
0111 jge 0x4339
0113 inc word ptr [0x8a88]
0117 push ss
0118 pop ds
0119 pop si
011a pop di
011b leave 
011c retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far SetMap(int plane, int x, int y, int value);` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoSow', 'offset': 16266, 'source': None, 'size': 315}
- {'symbol': '_InitAntLions', 'offset': 16582, 'source': None, 'size': 347}
- {'symbol': '_AddAntLion', 'offset': 17216, 'source': 'src/recovered/wf_AddAntLion-3b9ada1a24.c', 'size': 186}
- {'symbol': '_DoAntLions', 'offset': 17402, 'source': None, 'size': 1758}
