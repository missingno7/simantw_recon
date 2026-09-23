# Recovery task _CountAnts

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 725 bytes.

```asm
0000 push di
0001 push si
0002 xor ax, ax
0004 mov word ptr [0xaca0], ax ; _CastePopR
0007 mov word ptr [0xac94], ax ; _CastePopB
000a mov es, word ptr [0xc2d2]
000e mov cx, 0x20
0011 mov di, 0x7c4e
0014 rep stosw word ptr es:[di], ax
0016 mov es, word ptr [0xc2d4]
001a mov si, word ptr es:[0x80f0]
001f or si, si
0021 jle 0x529
0023 mov <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0026 mov es, ax
0028 mov <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
002b mov ds, ax
002d dec si
002e mov al, byte ptr [si + 0x2f62]
0032 sub ah, ah
0034 mov di, ax
0036 or di, di
0038 je 0x523
003a and di, 0xfffb
003d sar di, 2
0040 inc word ptr es:[di + 0x7c4e]
0045 or si, si
0047 jg 0x50b
0049 push ss
004a pop ds
004b mov es, word ptr [0xc2d6]
004f mov si, word ptr es:[0x99d4]
0054 or si, si
0056 jle 0x55e
0058 mov <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
005b mov es, ax
005d mov <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0060 mov ds, ax
0062 dec si
0063 mov al, byte ptr [si + 0x3d18]
0067 sub ah, ah
0069 mov di, ax
006b or di, di
006d je 0x558
006f and di, 0xfffb
0072 sar di, 2
0075 inc word ptr es:[di + 0x7c4e]
007a or si, si
007c jg 0x540
007e push ss
007f pop ds
0080 mov es, word ptr [0xc2d8]
0084 mov si, word ptr es:[0x72cc]
0089 or si, si
008b jle 0x593
008d mov <resolved loader operand; see bindings> ; [{'operand_offset': 142, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0090 mov es, ax
0092 mov <resolved loader operand; see bindings> ; [{'operand_offset': 147, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0095 mov ds, ax
0097 dec si
0098 mov al, byte ptr [si + 0x46e6]
009c sub ah, ah
009e mov di, ax
00a0 or di, di
00a2 je 0x58d
00a4 and di, 0xfffb
00a7 sar di, 2
00aa inc word ptr es:[di + 0x7c4e]
00af or si, si
00b1 jg 0x575
00b3 push ss
00b4 pop ds
00b5 mov es, word ptr [0xc2da]
00b9 cmp word ptr es:[0x9fe8], 0
00bf jne 0x5ca
00c1 cmp word ptr [0xce98], 0 ; _MeColor
00c6 jne 0x5b4
00c8 mov es, word ptr [0xc2d2]
00cc mov bx, word ptr [0xcc84] ; _MeType
00d0 and bl, 0xfb
00d3 jmp 0x5c2
00d5 nop 
00d6 mov es, word ptr [0xc2d2]
00da mov bx, word ptr [0xcc84] ; _MeType
00de and bl, 0xfb
00e1 or bl, 0x80
00e4 sar bx, 2
00e7 inc word ptr es:[bx + 0x7c4e]
00ec mov es, word ptr [0xc2d2]
00f0 mov ax, word ptr es:[0x7c4e]
00f4 mov word ptr [0xac94], ax ; _CastePopB
00f7 mov ax, word ptr es:[0x7c50]
00fb add ax, word ptr es:[0x7c52]
0100 add ax, word ptr es:[0x7c54]
0105 add ax, word ptr es:[0x7c58]
010a mov word ptr [0xac96], ax
010d mov ax, word ptr es:[0x7c5a]
0111 add ax, word ptr es:[0x7c5c]
0116 add ax, word ptr es:[0x7c60]
011b mov word ptr [0xac98], ax
011e mov ax, word ptr es:[0x7c56]
0122 mov word ptr [0xac9a], ax
0125 mov ax, word ptr es:[0x7c5e]
0129 mov word ptr [0xac9c], ax
012c cmp word ptr [0xac9e], 0
0131 je 0x672
0133 cmp word ptr es:[0x7c66], 0
0139 jne 0x672
013b mov es, word ptr [0xc2dc]
013f cmp word ptr es:[0x9c70], 0
0145 jne 0x672
0147 push 0x7e
0149 push 0x2b0c
014c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 335, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
0151 add sp, 4
0154 push 1
0156 push 0x271a
0159 push 0
015b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 350, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
0160 add sp, 6
0163 mov es, word ptr [0xc2de]
0167 cmp word ptr es:[0x80b4], 1
016d jg 0x672
016f push 1
0171 push 0x271b
0174 push 0
0176 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 377, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
017b add sp, 6
017e mov es, word ptr [0xc2e0]
0182 mov word ptr es:[0x9dda], 1
0189 mov es, word ptr [0xc2e2]
018d mov word ptr es:[0x9cea], 0
0194 mov es, word ptr [0xc2d2]
0198 mov ax, word ptr es:[0x7c66]
019c mov word ptr [0xac9e], ax
019f mov ax, word ptr es:[0x7c6e]
01a3 mov word ptr [0xaca0], ax ; _CastePopR
01a6 mov ax, word ptr es:[0x7c70]
01aa add ax, word ptr es:[0x7c72]
01af add ax, word ptr es:[0x7c74]
01b4 add ax, word ptr es:[0x7c78]
01b9 mov word ptr [0xaca2], ax
01bc mov ax, word ptr es:[0x7c7a]
01c0 add ax, word ptr es:[0x7c7c]
01c5 add ax, word ptr es:[0x7c80]
01ca mov word ptr [0xaca4], ax
01cd mov ax, word ptr es:[0x7c76]
01d1 mov word ptr [0xaca6], ax
01d4 mov ax, word ptr es:[0x7c7e]
01d8 mov word ptr [0xaca8], ax
01db cmp word ptr [0xacaa], 0
01e0 jne 0x6c3
01e2 jmp 0x771
01e5 cmp word ptr es:[0x7c86], 0
01eb je 0x6ce
01ed jmp 0x771
01f0 mov es, word ptr [0xc2dc]
01f4 cmp word ptr es:[0x9c70], 0
01fa je 0x6dd
01fc jmp 0x771
01ff push 0x7e
0201 push 0x2b0d
0204 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 519, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
0209 add sp, 4
020c push 1
020e push 0x271c
0211 push 0
0213 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 534, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
0218 add sp, 6
021b mov es, word ptr [0xc2de]
021f cmp word ptr es:[0x80b4], 1
0225 jg 0x727
0227 push 1
0229 push 0x271d
022c push 0
022e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 561, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
0233 add sp, 6
0236 mov ax, 1
0239 mov es, word ptr [0xc2e0]
023d mov word ptr es:[0x9dda], ax
0241 mov es, word ptr [0xc2e2]
0245 mov word ptr es:[0x9cea], ax
0249 mov <resolved loader operand; see bindings> ; [{'operand_offset': 586, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
024c mov es, ax
024e cmp word ptr es:[0x80b4], 2
0254 jne 0x751
0256 cmp word ptr ss:[0xac92], 1
025c jne 0x751
025e mov <resolved loader operand; see bindings> ; [{'operand_offset': 607, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0261 mov es, ax
0263 cmp word ptr es:[0x7a60], 0xb
0269 jne 0x751
026b cmp word ptr es:[0x7a62], 8
0271 je 0x756
0273 push ss
0274 pop ds
0275 jmp 0x771
0277 nop 
0278 push ss
0279 pop ds
027a push 6
027c nop 
027d push cs
027e call 0x158a ; _SRand1
0281 add sp, 2
0284 mov bx, ax
0286 shl bx, 4
0289 mov es, word ptr [0xc2e4]
028d mov byte ptr es:[bx + 0x184], 0x14
0293 mov ax, word ptr [0xac96]
0296 add ax, word ptr [0xac98]
029a add ax, word ptr [0xac9a]
029e add ax, word ptr [0xac9c]
02a2 add ax, word ptr [0xac9e]
02a6 mov word ptr [0xac82], ax ; _BpopT
02a9 mov es, word ptr [0xc2d2]
02ad mov ax, word ptr es:[0x7c86]
02b1 mov word ptr [0xacaa], ax
02b4 add ax, word ptr [0xaca2]
02b8 add ax, word ptr [0xaca4]
02bc add ax, word ptr [0xaca6]
02c0 add ax, word ptr [0xaca8]
02c4 mov word ptr [0xac84], ax ; _RpopT
02c7 mov es, word ptr [0xc2dc]
02cb mov word ptr es:[0x9c70], 0
02d2 pop si
02d3 pop di
02d4 retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near BpopT;` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern int near BpopT;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near CastePopB[];` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near CastePopR[];` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int near MeColor;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MeColor;` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern int near MeColor;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int near MeType;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near RpopT;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near RpopT;` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern int near RpopT;` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_AddRocks-01eddceee1.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far myBeginSong(unsigned int song, unsigned int priority);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSong(unsigned int song, unsigned int mode);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_LoadStringAnt', 'offset': 1012, 'source': None, 'size': 231}
- {'symbol': '_CreateSimPats', 'offset': 1244, 'source': 'src/recovered/CreateSimPats.c', 'size': 1}
- {'symbol': '_FullCount', 'offset': 1972, 'source': 'src/recovered/FullCount.c', 'size': 11}
- {'symbol': '_CountUpdate', 'offset': 1984, 'source': 'src/countupd.c', 'size': 6}
