# Recovery task _GetOutB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 314 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov bx, si
000b shl bx, 6
000e mov word ptr [bp - 2], bx
0011 cmp byte ptr [bx + 0x48e8], 0x18
0016 je 0x5225
0018 jmp 0x52c8
001b mov es, word ptr [0xc350]
001f mov bx, word ptr es:[0x9b6a]
0024 mov es, word ptr [0xc352]
0028 mov al, byte ptr es:[bx + 0x3d18]
002d sub ah, ah
002f mov di, ax
0031 mov byte ptr es:[bx + 0x3d18], ah
0036 mov es, word ptr [0xc380]
003a cmp byte ptr es:[si - 0x7d2e], ah
003f jne 0x5254
0041 push si
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MakeNewHoleB
0047 add sp, 2
004a mov es, word ptr [0xc350]
004e mov bx, word ptr es:[0x9b6a]
0053 mov es, word ptr [0xc352]
0057 mov al, byte ptr es:[bx + 0x3f0e]
005c sub ah, ah
005e push ax
005f mov al, byte ptr es:[bx + 0x3b22]
0064 push ax
0065 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 104, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
006a mov cx, di
006c and cx, 0xf8
0070 add ax, cx
0072 push ax
0073 push si
0074 mov es, word ptr [0xc380]
0078 mov al, byte ptr es:[si - 0x7d2e]
007d sub ah, ah
007f push ax
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ExitHole
0085 add sp, 0xa
0088 or ax, ax
008a je 0x52a6
008c mov bx, word ptr [bp - 2]
008f mov byte ptr [bx - 0x7717], 0
0094 mov ax, 1
0097 pop si
0098 pop di
0099 leave 
009a retf 
009b nop 
009c mov <resolved loader operand; see bindings> ; [{'operand_offset': 157, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
009f mov es, ax
00a1 mov <resolved loader operand; see bindings> ; [{'operand_offset': 162, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00a4 mov ds, ax
00a6 mov ax, di
00a8 mov bx, word ptr [0x9b6a]
00ac mov byte ptr es:[bx + 0x3d18], al
00b1 xor ax, ax
00b3 mov byte ptr es:[bx + 0x3b22], al
00b8 push ss
00b9 pop ds
00ba pop si
00bb pop di
00bc leave 
00bd retf 
00be mov <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00c1 mov es, ax
00c3 cmp byte ptr es:[bx + 0x3a4], 0
00c9 je 0x52da
00cb dec byte ptr es:[bx + 0x3a4]
00d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 211, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
00d5 or ax, ax
00d7 je 0x5304
00d9 or si, si
00db jle 0x532d
00dd mov bx, word ptr [bp - 2]
00e0 mov al, byte ptr [bx + 0x48a9]
00e4 sub ah, ah
00e6 push ax
00e7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 234, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItDirt
00ec add sp, 2
00ef or ax, ax
00f1 je 0x532d
00f3 push 1
00f5 lea ax, [si - 1]
00f8 jmp 0x5324
00fa cmp si, 0x3f
00fd jge 0x532d
00ff mov bx, word ptr [bp - 2]
0102 mov al, byte ptr [bx + 0x4929]
0106 sub ah, ah
0108 push ax
0109 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 268, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItDirt
010e add sp, 2
0111 or ax, ax
0113 je 0x532d
0115 push 1
0117 lea ax, [si + 1]
011a push ax
011b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 286, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileThemB
0120 add sp, 4
0123 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 294, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0128 push ax
0129 push 1
012b push si
012c nop 
012d push cs
012e call 0x439e ; _TryMoveDirB
0131 add sp, 6
0134 xor ax, ax
0136 pop si
0137 pop di
0138 leave 
0139 retf 
```

## Known declaration examples

- `extern int far DigTileThemB(int x, int y);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern void far MakeNewHoleB(int x);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirB-2bfd4e5303.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirR-414ecd2b67.c
- `extern int far SRand2(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far TryMoveDirB(int x, int y, int dir);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far TryMoveDirB(int x, int y, int dir);` — src/recovered/wf_DoRecruitN-cac1aa103b.c
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

- {'symbol': '_DoDigOutB', 'offset': 20144, 'source': None, 'size': 686}
- {'symbol': '_LeaveNestB', 'offset': 20830, 'source': None, 'size': 172}
- {'symbol': '_DoAntSimR', 'offset': 21316, 'source': 'src/recovered/wf_DoAntSimR-682e4ecadf.c', 'size': 95}
- {'symbol': '_DoNestAntR', 'offset': 21412, 'source': None, 'size': 1925}
