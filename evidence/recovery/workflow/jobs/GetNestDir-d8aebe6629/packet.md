# Recovery task _GetNestDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 547 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c mov ax, di
000e sar ax, 1
0010 mov word ptr [bp - 0xe], ax
0013 mov ax, si
0015 sar ax, 1
0017 mov word ptr [bp - 0xc], ax
001a mov ax, word ptr [bp + 0xc]
001d sar ax, 7
0020 mov word ptr [bp - 8], ax
0023 or di, di
0025 jne 0xc82
0027 or si, si
0029 jne 0xc6a
002b push 3
002d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 48, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0032 add sp, 2
0035 add ax, 3
0038 jmp 0xcc8
003a cmp si, 0x3f
003d jne 0xc74
003f push 3
0041 jmp 0xc76
0043 nop 
0044 push 5
0046 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
004b add sp, 2
004e inc ax
004f jmp 0xcc8
0051 nop 
0052 or si, si
0054 jne 0xc9e
0056 cmp di, 0x7f
0059 jne 0xc9a
005b push 3
005d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 96, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0062 add sp, 2
0065 add ax, 5
0068 jmp 0xcc8
006a push 5
006c jmp 0xc5d
006e cmp di, 0x7f
0071 jne 0xcbc
0073 cmp si, 0x3f
0076 jne 0xcb8
0078 push 3
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
007f add sp, 2
0082 add ax, 7
0085 jmp 0xcc8
0087 nop 
0088 push 5
008a jmp 0xc8d
008c cmp si, 0x3f
008f jne 0xcc6
0091 push 5
0093 jmp 0xcaa
0095 nop 
0096 xor ax, ax
0098 mov word ptr [bp - 4], ax
009b or ax, ax
009d je 0xcdc
009f mov al, byte ptr [bp - 4]
00a2 dec al
00a4 and ax, 7
00a7 pop si
00a8 pop di
00a9 leave 
00aa retf 
00ab nop 
00ac cmp word ptr [bp - 8], 0
00b0 je 0xcfa
00b2 mov bx, word ptr [bp - 0xc]
00b5 mov di, word ptr [bp - 0xe]
00b8 mov <resolved loader operand; see bindings> ; [{'operand_offset': 185, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00bb mov ds, ax
00bd mov si, di
00bf shl si, 5
00c2 add si, bx
00c4 mov cl, byte ptr [si + 0x72d2]
00c8 jmp 0xd10
00ca mov bx, word ptr [bp - 0xc]
00cd mov di, word ptr [bp - 0xe]
00d0 mov <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00d3 mov ds, ax
00d5 mov si, di
00d7 shl si, 5
00da add si, bx
00dc mov cl, byte ptr [si + 0x62d2]
00e0 sub ch, ch
00e2 or cx, cx
00e4 jne 0xd19
00e6 jmp 0xdb4
00e9 xor cx, cx
00eb mov word ptr [bp - 6], cx
00ee mov word ptr [bp - 0xa], cx
00f1 mov si, cx
00f3 mov <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00f6 mov es, ax
00f8 mov al, byte ptr es:[si]
00fd cwde 
00fe mov di, ax
0100 add di, word ptr [bp - 0xe]
0103 and di, 0x3f
0106 mov <resolved loader operand; see bindings> ; [{'operand_offset': 263, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0109 mov es, ax
010b mov cl, byte ptr es:[si + 8]
0110 add cl, byte ptr [bp - 0xc]
0113 and cx, 0x1f
0116 cmp word ptr [bp - 8], 0
011a je 0xd5a
011c mov bx, di
011e shl bx, 5
0121 add bx, cx
0123 mov al, byte ptr [bx + 0x72d2]
0127 jmp 0xd65
0129 nop 
012a mov bx, di
012c shl bx, 5
012f add bx, cx
0131 mov al, byte ptr [bx + 0x62d2]
0135 sub ah, ah
0137 mov word ptr [bp - 2], ax
013a cmp ax, word ptr [bp - 6]
013d jle 0xd75
013f mov word ptr [bp - 6], ax
0142 mov word ptr [bp - 0xa], si
0145 inc si
0146 cmp si, 8
0149 jl 0xd23
014b push ss
014c pop ds
014d mov si, word ptr [bp + 0xa]
0150 mov di, word ptr [bp - 0xa]
0153 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 342, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
0158 or ax, ax
015a je 0xda0
015c mov es, word ptr [0xc4e6]
0160 mov bx, si
0162 shl bx, 3
0165 add bx, di
0167 mov al, byte ptr es:[bx + 0x24]
016c cwde 
016d jmp 0xda2
016f nop 
0170 mov ax, si
0172 mov word ptr [bp - 2], ax
0175 mov es, word ptr [0xc4e6]
0179 mov bx, ax
017b shl bx, 3
017e add bx, di
0180 jmp 0xe49
0183 nop 
0184 push ss
0185 pop ds
0186 cmp word ptr [bp - 8], 0
018a je 0xdf6
018c mov es, word ptr [0xc4e8]
0190 push word ptr es:[0x8360]
0195 push word ptr es:[0x835e]
019a push word ptr [bp + 8]
019d push word ptr [bp + 6]
01a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 419, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
01a5 add sp, 8
01a8 mov di, ax
01aa or di, di
01ac je 0xe36
01ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 433, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
01b3 or ax, ax
01b5 je 0xe36
01b7 mov es, word ptr [0xc4e6]
01bb mov bx, word ptr [bp + 0xa]
01be shl bx, 3
01c1 add bx, di
01c3 jmp 0xe2f
01c5 nop 
01c6 mov es, word ptr [0xc4ea]
01ca push word ptr es:[0x835c]
01cf push word ptr es:[0x835a]
01d4 push word ptr [bp + 8]
01d7 push word ptr [bp + 6]
01da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 477, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
01df add sp, 8
01e2 mov word ptr [bp - 2], ax
01e5 or ax, ax
01e7 je 0xe36
01e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 492, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
01ee or ax, ax
01f0 je 0xe36
01f2 mov es, word ptr [0xc4e6]
01f6 mov bx, word ptr [bp + 0xa]
01f9 shl bx, 3
01fc add bx, word ptr [bp - 2]
01ff mov al, byte ptr es:[bx + 0x23]
0204 jmp 0xe4e
0206 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 521, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
020b mov bx, ax
020d mov ax, word ptr [bp + 0xa]
0210 shl ax, 3
0213 add bx, ax
0215 mov es, word ptr [0xc4e6]
0219 mov al, byte ptr es:[bx + 0x24]
021e cwde 
021f pop si
0220 pop di
0221 leave 
0222 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirB-2bfd4e5303.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirR-414ecd2b67.c
- `extern int far SRand2(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_0000_DoDefendNest_5_scaffold-f75b17a9a4.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_8_scaffold-5f66a96585.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetNewModeR', 'offset': 2640, 'source': 'src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c', 'size': 95}
- {'symbol': '_GetForageDir', 'offset': 2736, 'source': None, 'size': 384}
- {'symbol': '_GetAlarmDir', 'offset': 3668, 'source': None, 'size': 286}
- {'symbol': '_GetRandDir', 'offset': 3954, 'source': 'src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c', 'size': 179}
