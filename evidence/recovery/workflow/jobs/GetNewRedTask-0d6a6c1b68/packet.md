# Recovery task _GetNewRedTask

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 215 bytes.

```asm
0000 push si
0001 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 4, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UnRecruitRed
0006 cmp word ptr [0xce80], 1 ; _MePlane
000b jne 0x9994
000d push 0x20
000f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0014 add sp, 2
0017 add ax, 0x40
001a cmp ax, word ptr [0xcd88] ; _MeLocX
001e jge 0x9994
0020 push 0xa
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0027 add sp, 2
002a mov es, word ptr [0xc63c]
002e cmp ax, word ptr es:[0x9e7a]
0033 jge 0x9994
0035 mov es, word ptr [0xc63a]
0039 mov word ptr es:[0x9d74], 2
0040 mov es, word ptr [0xc63c]
0044 push word ptr es:[0x9e7a]
0049 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 76, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _RecruitRed
004e add sp, 2
0051 pop si
0052 retf 
0053 nop 
0054 mov <resolved loader operand; see bindings> ; [{'operand_offset': 85, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0057 mov es, ax
0059 mov ax, word ptr es:[0x836c]
005d mov <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0060 mov ds, cx
0062 mov word ptr [0x9c22], ax
0065 mov ax, word ptr es:[0x836a]
0069 mov <resolved loader operand; see bindings> ; [{'operand_offset': 106, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
006c mov es, cx
006e mov word ptr es:[0x9bee], ax
0072 cmp ax, 0x1e
0075 jle 0x99c2
0077 mov ax, cx
0079 sub word ptr es:[0x9bee], 5
007f jmp 0x99e2
0081 nop 
0082 mov <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0085 mov ds, ax
0087 cmp word ptr [0x9c22], 0x14
008c jge 0x99d6
008e add word ptr [0x9c22], 5
0093 jmp 0x99e2
0095 nop 
0096 cmp word ptr [0x9c22], 0x28
009b jle 0x99e2
009d sub word ptr [0x9c22], 5
00a2 mov si, word ptr ss:[0xaca2]
00a7 add si, word ptr ss:[0xaca4]
00ac cmp si, 0x14
00af jge 0x99fc
00b1 push ss
00b2 pop ds
00b3 mov ax, si
00b5 sar ax, 2
00b8 push ax
00b9 jmp 0x9a02
00bb nop 
00bc push ss
00bd pop ds
00be sar si, 3
00c1 push si
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _RecruitRed
00c7 add sp, 2
00ca mov es, word ptr [0xc63a]
00ce mov word ptr es:[0x9d74], 1
00d5 pop si
00d6 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeRedInitiator', 'offset': 38524, 'source': None, 'size': 88}
- {'symbol': '_DoRedInitiator', 'offset': 38612, 'source': None, 'size': 619}
- {'symbol': '_GetRedBestDirs', 'offset': 39448, 'source': None, 'size': 220}
