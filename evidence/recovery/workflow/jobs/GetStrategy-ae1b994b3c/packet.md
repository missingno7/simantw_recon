# Recovery task _GetStrategy

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 460 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 mov es, word ptr [0xc4be]
0009 mov word ptr es:[0x72ec], 0
0010 cmp word ptr [0xce80], 1 ; _MePlane
0015 je 0x1a
0017 jmp 0xcd
001a push 5
001c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 31, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0021 add sp, 2
0024 add ax, word ptr [0xcd88] ; _MeLocX
0028 sub ax, 2
002b mov bx, 0x9fe4
002e mov es, word ptr [0xc4c0]
0032 mov word ptr [bp - 4], bx
0035 mov word ptr [bp - 2], es
0038 mov word ptr es:[bx], ax
003b push 5
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0042 add sp, 2
0045 add ax, word ptr [0xce7e] ; _MeLocY
0049 sub ax, 2
004c mov es, word ptr [0xc4c2]
0050 mov word ptr es:[0x9fea], ax
0054 les bx, ptr [bp - 4]
0057 cmp word ptr es:[bx], 0
005b jge 0x62
005d mov word ptr es:[bx], 0
0062 mov <resolved loader operand; see bindings> ; [{'operand_offset': 99, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0065 mov ds, ax
0067 les bx, ptr [bp - 4]
006a cmp word ptr es:[bx], 0x7f
006e jle 0x75
0070 mov word ptr es:[bx], 0x7f
0075 cmp word ptr [0x9fea], 0
007a jge 0x82
007c mov word ptr [0x9fea], 0
0082 cmp word ptr [0x9fea], 0x3f
0087 jle 0x8f
0089 mov word ptr [0x9fea], 0x3f
008f mov <resolved loader operand; see bindings> ; [{'operand_offset': 144, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0092 mov es, ax
0094 cmp word ptr es:[0x9bd2], 0
009a je 0xcd
009c push ss
009d pop ds
009e push word ptr [0xce7e] ; _MeLocY
00a2 push word ptr [0xcd88] ; _MeLocX
00a6 mov ax, word ptr [0xac7e] ; _SpidY
00a9 sar ax, 4
00ac push ax
00ad mov ax, word ptr [0xac7c] ; _SpidX
00b0 sar ax, 4
00b3 push ax
00b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 183, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
00b9 add sp, 8
00bc cmp ax, 0x64
00bf jge 0xcd
00c1 mov <resolved loader operand; see bindings> ; [{'operand_offset': 194, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00c4 mov es, ax
00c6 mov word ptr es:[0x72ec], 1
00cd mov ax, word ptr ss:[0xcd88]
00d1 mov <resolved loader operand; see bindings> ; [{'operand_offset': 210, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00d4 mov es, cx
00d6 mov word ptr es:[0x9fe4], ax
00da cmp word ptr ss:[0xac86], 0xa
00e0 jge 0x105
00e2 mov bx, word ptr ss:[0xac84]
00e7 mov ax, word ptr ss:[0xac82]
00eb sar ax, 1
00ed cmp ax, bx
00ef jle 0x105
00f1 or bx, bx
00f3 jle 0x105
00f5 mov <resolved loader operand; see bindings> ; [{'operand_offset': 246, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00f8 mov es, ax
00fa cmp word ptr es:[0x79dc], 0
0100 jle 0x105
0102 jmp 0x195
0105 cmp word ptr ss:[0xac86], 0x1e
010b jge 0x11c
010d mov <resolved loader operand; see bindings> ; [{'operand_offset': 270, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0110 mov es, ax
0112 mov word ptr es:[0x9b8a], 5
0119 jmp 0x1b0
011c cmp word ptr ss:[0xac86], 0x32
0122 jge 0x134
0124 mov <resolved loader operand; see bindings> ; [{'operand_offset': 293, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0127 mov es, ax
0129 mov word ptr es:[0x9b8a], 4
0130 jmp 0x1b0
0132 nop 
0133 nop 
0134 mov di, word ptr ss:[0xac82]
0139 mov <resolved loader operand; see bindings> ; [{'operand_offset': 314, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
013c mov es, ax
013e cmp word ptr es:[0x72c8], di
0143 jge 0x154
0145 mov <resolved loader operand; see bindings> ; [{'operand_offset': 326, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0148 mov es, ax
014a mov word ptr es:[0x9b8a], 3
0151 jmp 0x1b0
0153 nop 
0154 mov ax, di
0156 shl ax, 1
0158 cmp word ptr es:[0x72c8], ax
015d jge 0x16e
015f mov <resolved loader operand; see bindings> ; [{'operand_offset': 352, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0162 mov es, ax
0164 mov word ptr es:[0x9b8a], 2
016b jmp 0x1b0
016d nop 
016e cmp di, 0x64
0171 jle 0x1a4
0173 mov bx, word ptr ss:[0xac84]
0178 or bx, bx
017a jle 0x1a4
017c mov <resolved loader operand; see bindings> ; [{'operand_offset': 381, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
017f mov es, ax
0181 cmp word ptr es:[0x79dc], 0
0187 jle 0x1a4
0189 mov ax, di
018b mov cx, 3
018e cdq 
018f idiv cx
0191 cmp ax, bx
0193 jle 0x1a4
0195 mov <resolved loader operand; see bindings> ; [{'operand_offset': 406, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0198 mov es, ax
019a mov word ptr es:[0x9b8a], 0
01a1 jmp 0x1b0
01a3 nop 
01a4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 421, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
01a7 mov es, ax
01a9 mov word ptr es:[0x9b8a], 1
01b0 push ss
01b1 pop ds
01b2 nop 
01b3 push cs
01b4 call 0x3c2 ; _GstrR
01b7 mov es, word ptr [0xc4c4]
01bb mov word ptr es:[0x7690], ax
01bf nop 
01c0 push cs
01c1 call 0x26e ; _SetCasteProd
01c4 nop 
01c5 push cs
01c6 call 0x326 ; _SetModeProd
01c9 pop di
01ca leave 
01cb retf 
```

## Known declaration examples

- `extern unsigned long far GetDis(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GstrB', 'offset': 460, 'source': 'src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c', 'size': 162}
- {'symbol': '_SetCasteProd', 'offset': 622, 'source': None, 'size': 183}
