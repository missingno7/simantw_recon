# Recovery task _RaidInR

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
0016 cmp byte ptr [bx + 0x58e8], 0x10
001b jb 0x5ba0
001d cmp byte ptr [bx + 0x58e8], 0x13
0022 ja 0x5ba0
0024 cmp byte ptr [bx + 0x58e8], 0x10
0029 jne 0x5b64
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0030 mov bx, word ptr [bp - 4]
0033 mov byte ptr [bx + 0x58e8], al
0037 jmp 0x5b68
0039 nop 
003a dec byte ptr [bx + 0x58e8]
003e mov es, word ptr [0xc394]
0042 cmp word ptr es:[0x72de], 0
0048 jle 0x5b79
004a dec word ptr es:[0x72de]
004f mov es, word ptr [0xc384]
0053 mov bx, word ptr es:[0x9b6a]
0058 mov es, word ptr [0xc386]
005c mov byte ptr es:[bx + 0x44f0], 3
0062 or byte ptr es:[bx + 0x46e6], 8
0068 mov al, byte ptr es:[bx + 0x46e6]
006d mov bx, word ptr [bp - 4]
0070 mov byte ptr [bx - 0x6718], al
0074 jmp 0x5c0f
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
008d call 0x6850 ; _TryMoveDirR
0090 add sp, 6
0093 or ax, ax
0095 jne 0x5c0f
0097 mov al, byte ptr [bp + 0xa]
009a and ax, 7
009d push ax
009e push di
009f push si
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetEnterDirR
00a5 add sp, 6
00a8 or ax, ax
00aa jge 0x5be0
00ac push 8
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00b3 add sp, 2
00b6 push ax
00b7 push di
00b8 push si
00b9 nop 
00ba push cs
00bb call 0x6850 ; _TryMoveDirR
00be add sp, 6
00c1 or ax, ax
00c3 jne 0x5c0f
00c5 mov <resolved loader operand; see bindings> ; [{'operand_offset': 198, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00c8 mov ds, ax
00ca mov <resolved loader operand; see bindings> ; [{'operand_offset': 203, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00cd mov es, ax
00cf mov bx, word ptr es:[0x9b6a]
00d4 mov byte ptr [bx + 0x44f0], 1
00d9 mov al, byte ptr [bx + 0x46e6]
00dd mov bx, word ptr [bp - 4]
00e0 mov byte ptr ss:[bx - 0x6718], al
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
- `extern int far TryMoveDirR(int x, int y, int dir);` — src/recovered/wf_RaidOutR-a39ba19d03.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoAntSimR', 'offset': 21316, 'source': 'src/recovered/wf_DoAntSimR-682e4ecadf.c', 'size': 95}
- {'symbol': '_DoNestAntR', 'offset': 21412, 'source': None, 'size': None}
- {'symbol': '_StayInR', 'offset': 23574, 'source': None, 'size': 249}
- {'symbol': '_RaidOutR', 'offset': 23824, 'source': 'src/recovered/wf_RaidOutR-a39ba19d03.c', 'size': 110}
