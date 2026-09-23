# Recovery task _DoWater

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 773 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 cmp word ptr [0xac72], 0 ; _RainOn
000b jne 0x7d6
000d jmp 0x960
0010 mov es, word ptr [0xc2e6]
0014 cmp word ptr es:[0x9b6e], 0
001a je 0x7e5
001c jmp 0x960
001f push 0x32
0021 nop 
0022 push cs
0023 call 0x158a ; _SRand1
0026 add sp, 2
0029 or ax, ax
002b jne 0x800
002d push 0x40
002f push ax
0030 push 0x29
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0037 add sp, 6
003a mov es, word ptr [0xc2e8]
003e mov word ptr es:[0x8a66], 1
0045 push 0xa
0047 nop 
0048 push cs
0049 call 0x158a ; _SRand1
004c add sp, 2
004f or ax, ax
0051 je 0x81c
0053 jmp 0x8f7
0056 mov bx, 0x99d8
0059 mov es, word ptr [0xc2ea]
005d mov word ptr [bp - 0xc], bx
0060 mov word ptr [bp - 0xa], es
0063 cmp word ptr es:[bx], 4
0067 jg 0x832
0069 jmp 0x8f7
006c dec word ptr es:[bx]
006f mov di, word ptr es:[bx]
0072 push di
0073 nop 
0074 push cs
0075 call 0x2d16 ; _DrownBList
0078 add sp, 2
007b push di
007c nop 
007d push cs
007e call 0x2d66 ; _DrownRList
0081 add sp, 2
0084 xor si, si
0086 mov word ptr [bp - 8], di
0089 mov word ptr [bp - 2], di
008c mov bx, si
008e shl bx, 6
0091 mov ax, si
0093 shl ax, 6
0096 add ax, di
0098 sub bx, ax
009a add bx, word ptr [bp - 8]
009d mov al, byte ptr [bx + di + 0x48e8]
00a1 sub ah, ah
00a3 cmp ax, 0x20
00a6 jge 0x874
00a8 mov ax, 0x4e
00ab jmp 0x877
00ad nop 
00ae add ax, 0x2f
00b1 mov word ptr [bp - 6], ax
00b4 mov bx, si
00b6 shl bx, 6
00b9 mov ax, si
00bb shl ax, 6
00be add ax, di
00c0 sub bx, ax
00c2 add bx, word ptr [bp - 8]
00c5 mov al, byte ptr [bp - 6]
00c8 mov byte ptr [bx + di + 0x48e8], al
00cc mov bx, si
00ce shl bx, 6
00d1 mov ax, si
00d3 shl ax, 6
00d6 add ax, di
00d8 sub bx, ax
00da add bx, word ptr [bp - 8]
00dd mov al, byte ptr [bx + di + 0x58e8]
00e1 sub ah, ah
00e3 cmp ax, 0x20
00e6 jge 0x8b4
00e8 mov ax, 0x4e
00eb jmp 0x8b7
00ed nop 
00ee add ax, 0x2f
00f1 mov word ptr [bp - 6], ax
00f4 mov bx, si
00f6 shl bx, 6
00f9 mov ax, si
00fb shl ax, 6
00fe add ax, di
0100 sub bx, ax
0102 add bx, word ptr [bp - 8]
0105 mov al, byte ptr [bp - 6]
0108 mov byte ptr [bx + di + 0x58e8], al
010c push di
010d push si
010e push 2
0110 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 275, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
0115 add sp, 6
0118 push di
0119 push si
011a push 3
011c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 287, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
0121 add sp, 6
0124 add word ptr [bp - 8], 0x40
0128 inc si
0129 cmp si, 0x40
012c jge 0x8f7
012e jmp 0x852
0131 xor si, si
0133 mov es, word ptr [0xc2ec]
0137 mov al, byte ptr es:[si + 0x7a72]
013c sub ah, ah
013e mov di, ax
0140 mov es, word ptr [0xc2ee]
0144 mov bl, byte ptr es:[si + 0x79e6]
0149 sub bh, bh
014b mov word ptr [bp - 2], bx
014e shl bx, 6
0151 mov cl, byte ptr [bx + di + 0x28e8]
0155 sub ch, ch
0157 cmp cx, 0x74
015a jl 0x934
015c cmp cx, 0x77
015f jge 0x934
0161 mov bx, word ptr [bp - 2]
0164 shl bx, 6
0167 inc byte ptr [bx + di + 0x28e8]
016b jmp 0x956
016d nop 
016e cmp cx, 0x77
0171 jne 0x94d
0173 push 0xe
0175 nop 
0176 push cs
0177 call 0x158a ; _SRand1
017a add sp, 2
017d mov bx, word ptr [bp - 2]
0180 shl bx, 6
0183 mov byte ptr [bx + di + 0x28e8], al
0187 push si
0188 nop 
0189 push cs
018a call 0xacc ; _PlaceDrop
018d add sp, 2
0190 inc si
0191 cmp si, 0x64
0194 jl 0x8f9
0196 pop si
0197 pop di
0198 leave 
0199 retf 
019a mov <resolved loader operand; see bindings> ; [{'operand_offset': 411, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
019d mov es, ax
019f cmp word ptr es:[0x9b6e], 0
01a5 je 0x970
01a7 jmp 0xa2e
01aa mov <resolved loader operand; see bindings> ; [{'operand_offset': 427, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01ad mov es, ax
01af cmp word ptr es:[0x8a66], 1
01b5 je 0x980
01b7 jmp 0xa34
01ba xor si, si
01bc mov word ptr es:[0x8a66], si
01c1 push ss
01c2 pop ds
01c3 mov es, word ptr [0xc2ec]
01c7 mov al, byte ptr es:[si + 0x7a72]
01cc sub ah, ah
01ce mov di, ax
01d0 mov es, word ptr [0xc2ee]
01d4 mov bl, byte ptr es:[si + 0x79e6]
01d9 sub bh, bh
01db mov word ptr [bp - 2], bx
01de shl bx, 6
01e1 mov cl, byte ptr [bx + di + 0x28e8]
01e5 sub ch, ch
01e7 cmp cx, 0x74
01ea jl 0x9cb
01ec cmp cx, 0x77
01ef jg 0x9cb
01f1 push 0xe
01f3 nop 
01f4 push cs
01f5 call 0x158a ; _SRand1
01f8 add sp, 2
01fb mov bx, word ptr [bp - 2]
01fe shl bx, 6
0201 mov byte ptr [bx + di + 0x28e8], al
0205 inc si
0206 cmp si, 0x64
0209 jl 0x989
020b mov bx, 0x99d8
020e mov es, word ptr [0xc2ea]
0212 mov word ptr [bp - 0xc], bx
0215 mov word ptr [bp - 0xa], es
0218 cmp word ptr es:[bx], 0x40
021c jl 0x9e7
021e jmp 0xac7
0221 push 0xa
0223 nop 
0224 push cs
0225 call 0x158a ; _SRand1
0228 add sp, 2
022b or ax, ax
022d je 0x9f8
022f jmp 0xac7
0232 xor si, si
0234 les bx, ptr [bp - 0xc]
0237 mov di, word ptr es:[bx]
023a mov word ptr [bp - 8], di
023d mov word ptr [bp - 2], di
0240 mov bx, si
0242 shl bx, 6
0245 mov ax, si
0247 shl ax, 6
024a add ax, di
024c sub bx, ax
024e add bx, word ptr [bp - 8]
0251 mov al, byte ptr [bx + di + 0x48e8]
0255 sub ah, ah
0257 cmp ax, 0x4e
025a jne 0xa38
025c push 8
025e nop 
025f push cs
0260 call 0x158a ; _SRand1
0263 add sp, 2
0266 jmp 0xa3b
0268 push ss
0269 pop ds
026a pop si
026b pop di
026c leave 
026d retf 
026e push ss
026f pop ds
0270 jmp 0x9d1
0272 sub ax, 0x2f
0275 mov word ptr [bp - 6], ax
0278 mov bx, si
027a shl bx, 6
027d mov ax, si
027f shl ax, 6
0282 add ax, di
0284 sub bx, ax
0286 add bx, word ptr [bp - 8]
0289 mov al, byte ptr [bp - 6]
028c mov byte ptr [bx + di + 0x48e8], al
0290 mov bx, si
0292 shl bx, 6
0295 mov ax, si
0297 shl ax, 6
029a add ax, di
029c sub bx, ax
029e add bx, word ptr [bp - 8]
02a1 mov al, byte ptr [bx + di + 0x58e8]
02a5 sub ah, ah
02a7 cmp ax, 0x4e
02aa jne 0xa7e
02ac push 8
02ae nop 
02af push cs
02b0 call 0x158a ; _SRand1
02b3 add sp, 2
02b6 jmp 0xa81
02b8 sub ax, 0x2f
02bb mov word ptr [bp - 6], ax
02be mov bx, si
02c0 shl bx, 6
02c3 mov ax, si
02c5 shl ax, 6
02c8 add ax, di
02ca sub bx, ax
02cc add bx, word ptr [bp - 8]
02cf mov al, byte ptr [bp - 6]
02d2 mov byte ptr [bx + di + 0x58e8], al
02d6 push di
02d7 push si
02d8 push 2
02da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 733, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
02df add sp, 6
02e2 push di
02e3 push si
02e4 push 3
02e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 745, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
02eb add sp, 6
02ee add word ptr [bp - 8], 0x40
02f2 inc si
02f3 cmp si, 0x40
02f6 jge 0xac1
02f8 jmp 0xa06
02fb les bx, ptr [bp - 0xc]
02fe inc word ptr es:[bx]
0301 pop si
0302 pop di
0303 leave 
0304 retf 
```

## Known declaration examples

- `extern void far DrownBList(int y);` — src/recovered/wf_AddWater-d30012f385.c
- `extern void far DrownRList(int y);` — src/recovered/wf_AddWater-d30012f385.c
- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern void far PlaceDrop(int value);` — src/recovered/InitWater.c
- `extern int near RainOn;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_AddRocks-01eddceee1.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_AddWater-d30012f385.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
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

- {'symbol': '_FullCount', 'offset': 1972, 'source': 'src/recovered/FullCount.c', 'size': 11}
- {'symbol': '_CountUpdate', 'offset': 1984, 'source': 'src/countupd.c', 'size': 6}
- {'symbol': '_PlaceDrop', 'offset': 2764, 'source': None, 'size': 170}
- {'symbol': '_InitWater', 'offset': 2934, 'source': 'src/recovered/InitWater.c', 'size': 20}
