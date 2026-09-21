# Recovery task _GetRedBestDirs

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 220 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 0xc], 0xffff
000b push word ptr [bp + 0xe]
000e push word ptr [bp + 0xc]
0011 push word ptr [bp + 0xa]
0014 push word ptr [bp + 8]
0017 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 26, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
001c add sp, 8
001f mov word ptr [bp - 8], ax
0022 or ax, ax
0024 jg 0x9a41
0026 jmp 0x9ac8
0029 mov word ptr [bp - 0xa], 0xfffe
002e xor si, si
0030 mov di, word ptr [bp + 6]
0033 push 0
0035 push word ptr [bp + 0xe]
0038 push word ptr [bp + 0xc]
003b push di
003c mov es, word ptr [0xc648]
0040 mov al, byte ptr es:[si + 8]
0045 cwde 
0046 add ax, word ptr [bp + 0xa]
0049 mov word ptr [bp - 2], ax
004c push ax
004d mov es, word ptr [0xc64a]
0051 mov al, byte ptr es:[si]
0056 cwde 
0057 add ax, word ptr [bp + 8]
005a mov word ptr [bp - 4], ax
005d push ax
005e push di
005f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 98, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _TileCanBeMovedOn
0064 add sp, 0xe
0067 dec ax
0068 jne 0x9adb
006a push word ptr [bp + 0xe]
006d push word ptr [bp + 0xc]
0070 push word ptr [bp - 2]
0073 push word ptr [bp - 4]
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
007b add sp, 8
007e mov word ptr [bp - 6], ax
0081 cmp ax, word ptr [bp - 8]
0084 jge 0x9adb
0086 push word ptr [bp - 2]
0089 push word ptr [bp - 4]
008c push di
008d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 144, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetLife
0092 add sp, 6
0095 or ax, ax
0097 jg 0x9ad2
0099 push word ptr [bp - 2]
009c push word ptr [bp - 4]
009f push di
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsClearTile
00a5 add sp, 6
00a8 dec ax
00a9 jne 0x9ad2
00ab mov word ptr [bp - 0xc], si
00ae jmp 0x9ad5
00b0 mov dx, word ptr [bp - 0xc]
00b3 mov ax, dx
00b5 pop si
00b6 pop di
00b7 leave 
00b8 retf 
00b9 nop 
00ba mov word ptr [bp - 0xa], si
00bd mov ax, word ptr [bp - 6]
00c0 mov word ptr [bp - 8], ax
00c3 inc si
00c4 cmp si, 8
00c7 jge 0x9ae4
00c9 jmp 0x9a4b
00cc mov dx, word ptr [bp - 0xc]
00cf or dx, dx
00d1 jge 0x9aee
00d3 mov dx, word ptr [bp - 0xa]
00d6 mov ax, dx
00d8 pop si
00d9 pop di
00da leave 
00db retf 
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

- {'symbol': '_DoRedInitiator', 'offset': 38612, 'source': None, 'size': 619}
- {'symbol': '_GetNewRedTask', 'offset': 39232, 'source': None, 'size': 215}
