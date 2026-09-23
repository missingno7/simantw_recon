# Recovery task _SimBird

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 633 bytes.

```asm
0000 enter 0xa, 0
0004 cmp word ptr ss:[0xac64], 0
000a jne 0x28b9
000c jmp 0x2a64
000f cmp word ptr ss:[0xac64], 1
0015 jne 0x28c6
0017 mov ax, 0x10
001a jmp 0x28c9
001c mov ax, 8
001f add word ptr ss:[0xac66], ax
0024 cmp word ptr ss:[0xac64], 1
002a jne 0x2916
002c mov <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
002f mov es, ax
0031 mov bx, word ptr es:[0x78d8]
0036 sub bx, word ptr ss:[0xac68]
003b je 0x291c
003d mov ax, bx
003f cdq 
0040 xor ax, dx
0042 sub ax, dx
0044 cmp ax, 4
0047 jl 0x2906
0049 or bx, bx
004b jle 0x28fc
004d mov ax, 4
0050 jmp 0x28ff
0052 mov ax, 0xfffc
0055 add word ptr ss:[0xac68], ax
005a jmp 0x291c
005c or bx, bx
005e jle 0x2910
0060 mov ax, 1
0063 jmp 0x28ff
0065 nop 
0066 mov ax, 0xffff
0069 jmp 0x28ff
006b nop 
006c sub word ptr ss:[0xac68], 8
0072 mov al, byte ptr ss:[0xac62]
0076 sub al, 0xff
0078 and ax, 1
007b mov word ptr ss:[0xac62], ax
007f cmp word ptr ss:[0xac66], 0
0085 jge 0x2934
0087 jmp 0x2a3a
008a cmp word ptr ss:[0xac66], 0x1ff
0091 jle 0x2940
0093 jmp 0x2a3a
0096 cmp word ptr ss:[0xac68], 0
009c jge 0x294b
009e jmp 0x2a3a
00a1 cmp word ptr ss:[0xac68], 0xff
00a8 jle 0x2957
00aa jmp 0x2a3a
00ad cmp word ptr ss:[0xac64], 1
00b3 je 0x2962
00b5 jmp 0x2a32
00b8 mov <resolved loader operand; see bindings> ; [{'operand_offset': 185, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00bb mov es, ax
00bd mov ax, word ptr es:[0x78bc]
00c1 cmp word ptr ss:[0xac66], ax
00c6 jge 0x2975
00c8 jmp 0x2a32
00cb mov <resolved loader operand; see bindings> ; [{'operand_offset': 204, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00ce mov es, ax
00d0 mov ax, word ptr es:[0x78d8]
00d4 mov word ptr [bp - 2], ax
00d7 sub ax, 4
00da cmp ax, word ptr ss:[0xac68]
00df jle 0x298e
00e1 jmp 0x2a32
00e4 mov ax, word ptr [bp - 2]
00e7 add ax, 4
00ea cmp ax, word ptr ss:[0xac68]
00ef jge 0x299e
00f1 jmp 0x2a32
00f4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 245, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00f7 mov ds, ax
00f9 cmp word ptr [0x807a], 0
00fe jle 0x29b7
0100 mov ax, word ptr [0x807a]
0103 add ax, 7
0106 sar ax, 3
0109 sub word ptr [0x807a], ax
010d cmp word ptr ss:[0xac8c], 0
0113 jle 0x2a36
0115 push ss
0116 pop ds
0117 mov ax, word ptr [0xac8c] ; _QueenStorageB
011a add ax, 7
011d sar ax, 3
0120 sub word ptr [0xac8c], ax ; _QueenStorageB
0124 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 295, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _InvalQueenStorageDisp
0129 mov bx, 0x9c26
012c mov es, word ptr [0xc54c]
0130 cmp word ptr es:[bx], 0
0134 jle 0x29ec
0136 mov ax, word ptr es:[bx]
0139 add ax, 7
013c sar ax, 3
013f sub word ptr es:[bx], ax
0142 cmp word ptr [0xac8e], 0 ; _QueenStorageR
0147 jle 0x2a00
0149 mov ax, word ptr [0xac8e] ; _QueenStorageR
014c add ax, 7
014f sar ax, 3
0152 sub word ptr [0xac8e], ax ; _QueenStorageR
0156 mov es, word ptr [0xc546]
015a cmp word ptr es:[0x8610], 0
0160 jne 0x2a29
0162 cmp word ptr [0xce82], 2 ; _YardMode
0167 jge 0x2a29
0169 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 364, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
016e or ax, ax
0170 jne 0x2a29
0172 push 6
0174 push ax
0175 push 7
0177 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 378, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
017c add sp, 6
017f mov word ptr [0xac64], 2 ; _BirdOn
0185 leave 
0186 retf 
0187 nop 
0188 push ss
0189 pop ds
018a leave 
018b retf 
018c push ss
018d pop ds
018e jmp 0x29d3
0190 push ss
0191 pop ds
0192 mov word ptr [0xac64], 0 ; _BirdOn
0198 mov es, word ptr [0xc54e]
019c mov ax, word ptr es:[0x9b2c]
01a0 mov dx, word ptr es:[0x9b2e]
01a5 add ax, 0x1e
01a8 adc dx, 0
01ab mov es, word ptr [0xc4fc]
01af mov word ptr es:[0x9fbc], ax
01b3 mov word ptr es:[0x9fbe], dx
01b8 leave 
01b9 retf 
01ba push ss
01bb pop ds
01bc mov es, word ptr [0xc54e]
01c0 mov ax, word ptr es:[0x9b2c]
01c4 mov dx, word ptr es:[0x9b2e]
01c9 mov word ptr [bp - 0xa], ax
01cc mov word ptr [bp - 8], dx
01cf mov es, word ptr [0xc4fc]
01d3 cmp dx, word ptr es:[0x9fbe]
01d8 jge 0x2a87
01da jmp 0x2b21
01dd jg 0x2a93
01df cmp ax, word ptr es:[0x9fbc]
01e4 ja 0x2a93
01e6 jmp 0x2b21
01e9 mov ax, word ptr [bp - 0xa]
01ec mov dx, word ptr [bp - 8]
01ef add ax, 0x14
01f2 adc dx, 0
01f5 mov word ptr es:[0x9fbc], ax
01f9 mov word ptr es:[0x9fbe], dx
01fe mov es, word ptr [0xc548]
0202 cmp word ptr es:[0x7a60], 5
0208 jl 0x2b21
020a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 525, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
020f or ax, ax
0211 jne 0x2b21
0213 mov es, word ptr [0xc550]
0217 cmp word ptr es:[0x807a], ax
021c jg 0x2ad3
021e mov es, word ptr [0xc54c]
0222 cmp word ptr es:[0x9c26], ax
0227 jle 0x2b21
0229 mov es, word ptr [0xc548]
022d imul ax, word ptr es:[0x7a60], 0x1c
0233 mov cx, word ptr es:[0x7a62]
0238 mov dx, cx
023a shl cx, 2
023d add cx, dx
023f shl cx, 1
0241 sub ax, cx
0243 add ax, 0xb2
0246 mov es, word ptr [0xc552]
024a mov word ptr es:[0x78bc], ax
024e add cx, 0x2e
0251 mov es, word ptr [0xc554]
0255 mov word ptr es:[0x78d8], cx
025a mov word ptr [0xac64], 1 ; _BirdOn
0260 mov word ptr [0xac66], 0 ; _BirdX
0266 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 617, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand64
026b add ax, 4
026e mov word ptr [0xac68], ax ; _BirdY
0271 mov word ptr [0xac62], 0 ; _BirdFrame
0277 leave 
0278 retf 
```

## Known declaration examples

- `extern int near BirdFrame;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int near BirdFrame;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near BirdOn;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near BirdX;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int near BirdY;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern void far InvalQueenStorageDisp(void);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int near QueenStorageB;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageB;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near QueenStorageB;` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int near QueenStorageR;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageR;` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int near QueenStorageR;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirB-2bfd4e5303.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirR-414ecd2b67.c
- `extern int far SRand2(void);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far SRand64(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int far SRand64(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitGrassMap', 'offset': 8342, 'source': 'src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c', 'size': 32}
- {'symbol': '_SimKidInside', 'offset': 8374, 'source': None, 'size': 2036}
- {'symbol': '_SimCat', 'offset': 11044, 'source': 'src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c', 'size': 663}
- {'symbol': '_SimDog', 'offset': 11708, 'source': None, 'size': 946}
