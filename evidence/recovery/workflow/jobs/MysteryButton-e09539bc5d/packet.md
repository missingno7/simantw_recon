# Recovery task _MysteryButton

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 616 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 push 0xf
0008 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 11, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _RRand
000d add sp, 2
0010 cmp ax, 0xe
0013 jbe 0xb0d4
0015 jmp 0xb320
0018 shl ax, 1
001a xchg bx, ax
001b jmp word ptr cs:[bx - 0x4f24]
0020 dw offset 0xb0fa
0022 dw offset 0xb0fa
0024 dw offset 0xb164
0026 dw offset 0xb1c6
0028 dw offset 0xb1de
002a dw offset 0xb1ec
002c dw offset 0xb1fc
002e dw offset 0xb252
0030 dw offset 0xb25c
0032 dw offset 0xb274
0034 dw offset 0xb28c
0036 dw offset 0xb2a0
0038 dw offset 0xb2c6
003a dw offset 0xb2de
003c dw offset 0xb306
003e mov es, word ptr [0xc0da]
0042 mov cx, word ptr es:[0x80f0]
0047 cmp cx, 0x3e8
004b jge 0xb128
004d mov es, word ptr [0xc0dc]
0051 cmp word ptr es:[0x85e2], 1
0057 jne 0xb11e
0059 sub cx, 0x3e8
005d neg cx
005f push cx
0060 jmp 0xb120
0062 push 0x20
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 103, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _AddRedAnts
0069 add sp, 2
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FullCount
0071 mov es, word ptr [0xc0da]
0075 mov cx, word ptr es:[0x80f0]
007a cmp cx, 0x3e8
007e jge 0xb15c
0080 mov es, word ptr [0xc0dc]
0084 cmp word ptr es:[0x85e2], 1
008a jne 0xb152
008c sub cx, 0x3e8
0090 neg cx
0092 push cx
0093 jmp 0xb154
0095 nop 
0096 push 0x20
0098 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 155, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _AddRedAnts
009d add sp, 2
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FullCount
00a5 jmp 0xb320
00a8 mov es, word ptr [0xc0da]
00ac mov cx, word ptr es:[0x80f0]
00b1 cmp cx, 0x3e8
00b5 jge 0xb192
00b7 mov es, word ptr [0xc0dc]
00bb cmp word ptr es:[0x85e2], 1
00c1 jne 0xb188
00c3 sub cx, 0x3e8
00c7 neg cx
00c9 push cx
00ca jmp 0xb18a
00cc push 0x20
00ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _AddBlackAnts
00d3 add sp, 2
00d6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 217, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FullCount
00db mov es, word ptr [0xc0da]
00df mov cx, word ptr es:[0x80f0]
00e4 cmp cx, 0x3e8
00e8 jge 0xb15c
00ea mov es, word ptr [0xc0dc]
00ee cmp word ptr es:[0x85e2], 1
00f4 jne 0xb1bc
00f6 sub cx, 0x3e8
00fa neg cx
00fc push cx
00fd jmp 0xb1be
00ff nop 
0100 push 0x20
0102 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _AddBlackAnts
0107 jmp 0xb159
0109 nop 
010a push 0
010c nop 
010d push cs
010e call 0x9d5e ; _KillSomeAnts
0111 add sp, 2
0114 push 0
0116 nop 
0117 push cs
0118 call 0x9d5e ; _KillSomeAnts
011b add sp, 2
011e jmp 0xb320
0121 nop 
0122 push 1
0124 nop 
0125 push cs
0126 call 0x9d5e ; _KillSomeAnts
0129 add sp, 2
012c push 1
012e jmp 0xb1d2
0130 push 1
0132 push 0x96
0135 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 312, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _AddFood
013a add sp, 4
013d jmp 0xb320
0140 push 0x7e
0142 push 0
0144 push 0x20
0146 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 329, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSoundReverse
014b add sp, 6
014e xor di, di
0150 xor si, si
0152 mov bx, di
0154 add bx, si
0156 add bx, 0x28e8
015a mov word ptr [bp - 4], bx
015d mov al, byte ptr [bx]
015f sub ah, ah
0161 push ax
0162 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 357, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItFood
0167 add sp, 2
016a dec ax
016b jne 0xb233
016d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 368, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
0172 mov bx, word ptr [bp - 4]
0175 mov byte ptr [bx], al
0177 inc si
0178 cmp si, 0x40
017b jl 0xb20e
017d add di, 0x40
0180 cmp di, 0x2000
0184 jl 0xb20c
0186 mov es, word ptr [0xc0e0]
018a mov word ptr es:[0x9e84], 0
0191 pop si
0192 pop di
0193 leave 
0194 retf 
0195 nop 
0196 push 0
0198 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 411, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSoundList
019d jmp 0xb1d7
01a0 xor si, si
01a2 push si
01a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 422, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MakeNewHoleR
01a8 add sp, 2
01ab add si, 2
01ae cmp si, 0x40
01b1 jl 0xb25e
01b3 pop si
01b4 pop di
01b5 leave 
01b6 retf 
01b7 nop 
01b8 xor si, si
01ba push si
01bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 446, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MakeNewHoleB
01c0 add sp, 2
01c3 add si, 2
01c6 cmp si, 0x40
01c9 jl 0xb276
01cb pop si
01cc pop di
01cd leave 
01ce retf 
01cf nop 
01d0 xor ax, ax
01d2 mov es, word ptr [0xc118]
01d6 mov word ptr es:[0x8a60], ax
01da mov word ptr [0xac86], ax ; _HealthB
01dd mov word ptr [0xac88], ax ; _HealthR
01e0 pop si
01e1 pop di
01e2 leave 
01e3 retf 
01e4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 485, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01e7 mov es, ax
01e9 cmp word ptr es:[0x8a5c], 1
01ef sbb ax, ax
01f1 neg ax
01f3 mov word ptr es:[0x8a5c], ax
01f7 or ax, ax
01f9 je 0xb2be
01fb push 0x7e
01fd push 0
01ff jmp 0xb316
0201 nop 
0202 push 0x7e
0204 push 0
0206 push 1
0208 jmp 0xb318
020a mov <resolved loader operand; see bindings> ; [{'operand_offset': 523, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
020d mov es, ax
020f cmp word ptr es:[0x8a5a], 1
0215 sbb ax, ax
0217 neg ax
0219 mov word ptr es:[0x8a5a], ax
021d pop si
021e pop di
021f leave 
0220 retf 
0221 nop 
0222 push 0
0224 push 0x2726
0227 push 0
0229 nop 
022a push cs
022b call 0x615a ; _PictStrnDialog
022e add sp, 6
0231 push 1
0233 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 566, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSoundList
0238 add sp, 2
023b push 0
023d push 0x2728
0240 push 0
0242 nop 
0243 push cs
0244 call 0x615a ; _PictStrnDialog
0247 jmp 0xb31d
0249 nop 
024a mov es, word ptr [0xc11a]
024e mov word ptr es:[0x7d60], 8
0255 push 0x7e
0257 push 0x2b77
025a push 2
025c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 607, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0261 add sp, 6
0264 pop si
0265 pop di
0266 leave 
0267 retf 
```

## Known declaration examples

- `extern void far AddBlackAnts(int count);` — src/recovered/wf_AddSomeAnts-f71da72a1c.c
- `extern void far AddBlackAnts(int count);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far AddFood(int a, int b);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far AddRedAnts(int count);` — src/recovered/wf_AddSomeAnts-f71da72a1c.c
- `extern void far AddRedAnts(int count);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern void far FullCount(void);` — src/recovered/wf_AddSomeAnts-f71da72a1c.c
- `extern void far FullCount(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near HealthB;` — src/recovered/DecEatB.c
- `extern int near HealthB;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int near HealthB;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near HealthR;` — src/recovered/DecEatR.c
- `extern int near HealthR;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far IsItFood(int tile);` — src/recovered/wf_IsLiftable-91a4e99057.c
- `extern int far IsItFood(int tile);` — src/recovered/wf_IsThisFood-26910209bd.c
- `extern void far MakeNewHoleB(int x);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far MakeNewHoleR(int x);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far RRand(int range);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int far RRand(int range);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_XferPatch', 'offset': 43920, 'source': None, 'size': 385}
- {'symbol': '_PlaceQueenInYard', 'offset': 44306, 'source': None, 'size': 937}
- {'symbol': '_InitTriVars', 'offset': 45860, 'source': 'src/recovered/wf_InitTriVars-e97b7c6f72.c', 'size': 152}
- {'symbol': '_win_CasteControlChanged', 'offset': 46012, 'source': None, 'size': 500}
