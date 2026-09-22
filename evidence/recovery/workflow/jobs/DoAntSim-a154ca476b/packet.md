# Recovery task _DoAntSim

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 762 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 mov bx, 0x75fc
0008 mov <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
000b mov es, ax
000d mov word ptr [bp - 4], bx
0010 mov word ptr [bp - 2], es
0013 inc word ptr es:[bx]
0016 cmp word ptr es:[bx], 0x1000
001b jle 0x22
001d mov word ptr es:[bx], 0
0022 mov <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0025 mov es, ax
0027 add word ptr es:[0x76a8], 1
002d adc word ptr es:[0x76aa], 0
0033 mov <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0036 mov es, ax
0038 cmp word ptr es:[0x85fc], 1
003e jne 0xa0
0040 xor ax, ax
0042 mov <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0045 mov es, cx
0047 mov word ptr es:[0x7404], ax
004b mov <resolved loader operand; see bindings> ; [{'operand_offset': 76, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
004e mov es, cx
0050 mov word ptr es:[0xa07e], ax
0054 mov <resolved loader operand; see bindings> ; [{'operand_offset': 85, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0057 mov es, cx
0059 mov word ptr es:[0x8122], ax
005d mov <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0060 mov es, cx
0062 mov word ptr es:[0x7d44], ax
0066 mov <resolved loader operand; see bindings> ; [{'operand_offset': 103, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0069 mov ds, ax
006b mov ax, 0xffff
006e mov word ptr [0x9fb8], ax
0071 mov word ptr [0x9fb6], ax
0074 mov dx, ax
0076 mov <resolved loader operand; see bindings> ; [{'operand_offset': 119, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0079 mov es, cx
007b mov word ptr es:[0x72c4], ax
007f mov word ptr es:[0x72c6], dx
0084 mov <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0087 mov es, cx
0089 mov word ptr es:[0x79de], ax
008d mov word ptr es:[0x79e0], dx
0092 mov <resolved loader operand; see bindings> ; [{'operand_offset': 147, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0095 mov es, cx
0097 mov word ptr es:[0x80f4], ax
009b mov word ptr es:[0x80f6], dx
00a0 les bx, ptr [bp - 4]
00a3 test byte ptr es:[bx], 0x3f
00a7 je 0xac
00a9 jmp 0x13a
00ac mov <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00af mov es, ax
00b1 cmp word ptr es:[0x8a60], 0
00b7 jne 0xc7
00b9 dec word ptr ss:[0xac86]
00be jns 0xc7
00c0 mov word ptr ss:[0xac86], 0
00c7 dec word ptr ss:[0xac88]
00cc jns 0xd5
00ce mov word ptr ss:[0xac88], 0
00d5 mov <resolved loader operand; see bindings> ; [{'operand_offset': 214, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00d8 mov es, ax
00da cmp word ptr es:[0x80b4], 3
00e0 je 0x13a
00e2 mov <resolved loader operand; see bindings> ; [{'operand_offset': 227, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00e5 mov es, ax
00e7 mov ax, word ptr es:[0x8a62]
00eb mov <resolved loader operand; see bindings> ; [{'operand_offset': 236, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00ee mov es, cx
00f0 cmp word ptr es:[0x9e84], ax
00f5 jge 0x13a
00f7 push ss
00f8 pop ds
00f9 push 1
00fb push 0x96
00fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 257, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _AddFood
0103 add sp, 4
0106 push 0x32
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
010d add sp, 2
0110 inc ax
0111 mov es, word ptr [0xc2fe]
0115 mov word ptr es:[0x8a62], ax
0119 les bx, ptr [bp - 4]
011c test byte ptr es:[bx], 0x1f
0120 jne 0x170
0122 mov al, byte ptr es:[bx]
0125 and ax, 0x60
0128 sar ax, 5
012b or ax, ax
012d je 0x13e
012f dec ax
0130 je 0x152
0132 dec ax
0133 je 0x143
0135 dec ax
0136 je 0x162
0138 jmp 0x170
013a push ss
013b pop ds
013c jmp 0x119
013e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 321, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _CompactListA
0143 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 326, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FullCount
0148 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 331, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _HistUpdate
014d call 0xffff9380
0150 jmp 0x170
0152 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 341, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _CompactListB
0157 call 0xffff91de
015a call 0xffff92aa
015d call 0xffff9306
0160 jmp 0x170
0162 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 357, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _CompactListR
0167 call 0xffff9244
016a call 0xffff92d8
016d call 0xffff9344
0170 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 371, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _DoSimYard
0175 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 376, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DoWater
017a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 381, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _DoAntLions
017f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 386, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MoveSpider
0184 les bx, ptr [bp - 4]
0187 test byte ptr es:[bx], 1
018b je 0x192
018d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 400, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _DoPillar
0192 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 405, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetStrategy
0197 xor ax, ax
0199 mov es, word ptr [0xc300]
019d mov cx, 0x14
01a0 mov di, 0x7be4
01a3 rep stosw word ptr es:[di], ax
01a5 mov es, word ptr [0xc302]
01a9 mov cx, 0x14
01ac mov di, 0x786a
01af rep stosw word ptr es:[di], ax
01b1 mov <resolved loader operand; see bindings> ; [{'operand_offset': 434, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
01b4 mov ds, ax
01b6 cmp word ptr [0x7c44], 0
01bb je 0x1c1
01bd dec word ptr [0x7c44]
01c1 mov <resolved loader operand; see bindings> ; [{'operand_offset': 450, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
01c4 mov es, ax
01c6 cmp word ptr es:[0x8078], 0
01cc je 0x1d3
01ce dec word ptr es:[0x8078]
01d3 push ss
01d4 pop ds
01d5 call 0x4d8 ; _DoAntSimA
01d8 nop 
01d9 push cs
01da call 0x2d4e ; _DoAntSimB
01dd nop 
01de push cs
01df call 0x5344 ; _DoAntSimR
01e2 nop 
01e3 push cs
01e4 call 0x7cf6 ; _DoAntSimY
01e7 mov es, word ptr [0xc302]
01eb mov ax, word ptr es:[0x786e]
01ef add ax, word ptr es:[0x7870]
01f4 mov es, word ptr [0xc304]
01f8 mov word ptr es:[0x9e70], ax
01fc mov es, word ptr [0xc302]
0200 mov ax, word ptr es:[0x7872]
0204 add ax, word ptr es:[0x7874]
0209 mov es, word ptr [0xc304]
020d mov word ptr es:[0x9e72], ax
0211 mov es, word ptr [0xc302]
0215 mov ax, word ptr es:[0x786c]
0219 mov es, word ptr [0xc304]
021d mov word ptr es:[0x9e74], ax
0221 mov es, word ptr [0xc302]
0225 mov ax, word ptr es:[0x7878]
0229 mov es, word ptr [0xc304]
022d mov word ptr es:[0x9e76], ax
0231 mov es, word ptr [0xc302]
0235 mov ax, word ptr es:[0x7882]
0239 mov es, word ptr [0xc304]
023d mov word ptr es:[0x9e78], ax
0241 mov es, word ptr [0xc302]
0245 mov ax, word ptr es:[0x7876]
0249 mov es, word ptr [0xc304]
024d mov word ptr es:[0x9e7a], ax
0251 mov es, word ptr [0xc300]
0255 mov ax, word ptr es:[0x7be8]
0259 add ax, word ptr es:[0x7bea]
025e mov es, word ptr [0xc306]
0262 mov word ptr es:[0xa084], ax
0266 mov es, word ptr [0xc300]
026a mov ax, word ptr es:[0x7bec]
026e add ax, word ptr es:[0x7bee]
0273 mov es, word ptr [0xc306]
0277 mov word ptr es:[0xa086], ax
027b mov es, word ptr [0xc300]
027f mov ax, word ptr es:[0x7be6]
0283 mov es, word ptr [0xc306]
0287 mov word ptr es:[0xa088], ax
028b mov es, word ptr [0xc300]
028f mov ax, word ptr es:[0x7bf2]
0293 mov es, word ptr [0xc306]
0297 mov word ptr es:[0xa08a], ax
029b mov es, word ptr [0xc300]
029f mov ax, word ptr es:[0x7bfc]
02a3 mov es, word ptr [0xc306]
02a7 mov word ptr es:[0xa08c], ax
02ab mov es, word ptr [0xc300]
02af mov ax, word ptr es:[0x7bf0]
02b3 mov es, word ptr [0xc306]
02b7 mov word ptr es:[0xa08e], ax
02bb mov es, word ptr [0xc300]
02bf cmp word ptr es:[0x7c0a], 1
02c5 jge 0x2cc
02c7 nop 
02c8 push cs
02c9 call 0xffff967c
02cc nop 
02cd push cs
02ce call 0x75f4 ; _DoAntMoveY
02d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 724, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _Feedback
02d6 mov es, word ptr [0xc308]
02da cmp word ptr es:[0x9dda], 0
02e0 je 0x2ec
02e2 push 0
02e4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 743, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _EndGameDialog
02e9 add sp, 2
02ec mov es, word ptr [0xc30a]
02f0 mov word ptr es:[0x8370], 1
02f7 pop di
02f8 leave 
02f9 retf 
```

## Known declaration examples

- `extern void far AddFood(int a, int b);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern void far Feedback(void);` — src/countupd.c
- `extern void far Feedback(void);` — src/recovered/FullCount.c
- `extern void far FullCount(void);` — src/recovered/wf_AddSomeAnts-f71da72a1c.c
- `extern void far FullCount(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
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

- {'symbol': '_DoSmells', 'offset': 762, 'source': None, 'size': 79}
- {'symbol': '_ClrModePop', 'offset': 842, 'source': None, 'size': 67}
