# Recovery task _GetMyBestDirs

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 256 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 mov di, 0xffff
0009 push word ptr [bp + 0xe]
000c push word ptr [bp + 0xc]
000f push word ptr [bp + 0xa]
0012 push word ptr [bp + 8]
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
001a add sp, 8
001d mov word ptr [bp - 8], ax
0020 or ax, ax
0022 jg 0x884f
0024 jmp 0x8922
0027 mov word ptr [bp - 0xe], di
002a mov word ptr [bp - 0xc], 0xfffe
002f mov es, word ptr [0xc3ae]
0033 cmp word ptr es:[0x9bc4], 2
0039 jne 0x8868
003b mov ax, 1
003e jmp 0x886a
0040 xor ax, ax
0042 mov word ptr [bp - 0xa], ax
0045 xor si, si
0047 mov di, word ptr [bp + 6]
004a push word ptr [bp - 0xa]
004d mov es, word ptr [0xc3bc]
0051 push word ptr es:[0x80d2]
0056 mov es, word ptr [0xc3b8]
005a push word ptr es:[0x80c6]
005f mov es, word ptr [0xc3be]
0063 push word ptr es:[0x9be0]
0068 mov es, word ptr [0xc3c4]
006c mov al, byte ptr es:[si + 8]
0071 cwde 
0072 add ax, word ptr [bp + 0xa]
0075 mov word ptr [bp - 2], ax
0078 push ax
0079 mov es, word ptr [0xc3ca]
007d mov al, byte ptr es:[si]
0082 cwde 
0083 add ax, word ptr [bp + 8]
0086 mov word ptr [bp - 4], ax
0089 push ax
008a push di
008b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 142, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _TileCanBeMovedOn
0090 add sp, 0xe
0093 or ax, ax
0095 je 0x890f
0097 push word ptr [bp + 0xe]
009a push word ptr [bp + 0xc]
009d push word ptr [bp - 2]
00a0 push word ptr [bp - 4]
00a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 166, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
00a8 add sp, 8
00ab mov word ptr [bp - 6], ax
00ae cmp ax, word ptr [bp - 8]
00b1 jge 0x890f
00b3 push word ptr [bp - 2]
00b6 push word ptr [bp - 4]
00b9 push di
00ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetLife
00bf add sp, 6
00c2 or ax, ax
00c4 jg 0x8906
00c6 push word ptr [bp - 2]
00c9 push word ptr [bp - 4]
00cc push di
00cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 208, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsClearTile
00d2 add sp, 6
00d5 or ax, ax
00d7 je 0x8906
00d9 mov word ptr [bp - 0xe], si
00dc jmp 0x8909
00de mov word ptr [bp - 0xc], si
00e1 mov ax, word ptr [bp - 6]
00e4 mov word ptr [bp - 8], ax
00e7 inc si
00e8 cmp si, 8
00eb jge 0x8918
00ed jmp 0x8872
00f0 mov di, word ptr [bp - 0xe]
00f3 or di, di
00f5 jge 0x8922
00f7 mov di, word ptr [bp - 0xc]
00fa mov ax, di
00fc pop si
00fd pop di
00fe leave 
00ff retf 
```

## Known declaration examples

- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ExitNest', 'offset': 33956, 'source': None, 'size': 477}
- {'symbol': '_GetMyDis', 'offset': 34434, 'source': None, 'size': 421}
- {'symbol': '_GetMyRandDirs', 'offset': 35112, 'source': None, 'size': 536}
- {'symbol': '_CheckMyBestDirs', 'offset': 35648, 'source': None, 'size': 169}
