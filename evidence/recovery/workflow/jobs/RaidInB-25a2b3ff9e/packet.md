# Recovery task _RaidInB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 235 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 6]
000c mov bx, si
000e shl bx, 6
0011 add bx, di
0013 mov word ptr [bp - 4], bx
0016 cmp byte ptr [bx + 0x48e8], 0x10
001b jb 0x359a
001d cmp byte ptr [bx + 0x48e8], 0x13
0022 ja 0x359a
0024 cmp byte ptr [bx + 0x48e8], 0x10
0029 jne 0x355e
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0030 mov bx, word ptr [bp - 4]
0033 mov byte ptr [bx + 0x48e8], al
0037 jmp 0x3562
0039 nop 
003a dec byte ptr [bx + 0x48e8]
003e mov es, word ptr [0xc362]
0042 cmp word ptr es:[0x9ea4], 0
0048 jle 0x3573
004a dec word ptr es:[0x9ea4]
004f mov es, word ptr [0xc350]
0053 mov bx, word ptr es:[0x9b6a]
0058 mov es, word ptr [0xc352]
005c mov byte ptr es:[bx + 0x3b22], 3
0062 or byte ptr es:[bx + 0x3d18], 8
0068 mov al, byte ptr es:[bx + 0x3d18]
006d mov bx, word ptr [bp - 4]
0070 mov byte ptr [bx - 0x7718], al
0074 jmp 0x3609
0076 push 3
0078 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 123, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
007d add sp, 2
0080 add al, byte ptr [bp + 0xa]
0083 sub al, 2
0085 and ax, 7
0088 push ax
0089 push di
008a push si
008b nop 
008c push cs
008d call 0x439e ; _TryMoveDirB
0090 add sp, 6
0093 or ax, ax
0095 jne 0x3609
0097 mov al, byte ptr [bp + 0xa]
009a and ax, 7
009d push ax
009e push di
009f push si
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetEnterDirB
00a5 add sp, 6
00a8 or ax, ax
00aa jge 0x35da
00ac push 8
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00b3 add sp, 2
00b6 push ax
00b7 push di
00b8 push si
00b9 nop 
00ba push cs
00bb call 0x439e ; _TryMoveDirB
00be add sp, 6
00c1 or ax, ax
00c3 jne 0x3609
00c5 mov <resolved loader operand; see bindings> ; [{'operand_offset': 198, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00c8 mov ds, ax
00ca mov <resolved loader operand; see bindings> ; [{'operand_offset': 203, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00cd mov es, ax
00cf mov bx, word ptr es:[0x9b6a]
00d4 mov byte ptr [bx + 0x3b22], 1
00d9 mov al, byte ptr [bx + 0x3d18]
00dd mov bx, word ptr [bp - 4]
00e0 mov byte ptr ss:[bx - 0x7718], al
00e5 push ss
00e6 pop ds
00e7 pop si
00e8 pop di
00e9 leave 
00ea retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_GetRandDir-2664e9d7f9.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far TryMoveDirB(int x, int y, int dir);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoAntSimB', 'offset': 11598, 'source': 'src/recovered/wf_DoAntSimB-84a2084e1a.c', 'size': 95}
- {'symbol': '_DoNestAntB', 'offset': 11694, 'source': None, 'size': None}
- {'symbol': '_RaidOutB', 'offset': 13840, 'source': 'src/recovered/wf_RaidOutB-794c50ee5a.c', 'size': 110}
- {'symbol': '_DoRestB', 'offset': 13950, 'source': None, 'size': 294}
