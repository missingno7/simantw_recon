# Recovery task _DigMyTile

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 498 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 0xa]
000c push si
000d push di
000e push word ptr [bp + 6]
0011 nop 
0012 push cs
0013 call 0x95c6 ; _IsItDigable
0016 add sp, 6
0019 or ax, ax
001b jne 0x1934
001d jmp 0x1b02
0020 cmp word ptr [bp + 6], 2
0024 jne 0x1964
0026 cmp si, 1
0029 jg 0x195a
002b mov bx, di
002d shl bx, 6
0030 mov byte ptr [bx + 0x48e8], 0x18
0035 push di
0036 nop 
0037 push cs
0038 call 0x1b06 ; _MakeNewHoleB
003b add sp, 2
003e cmp si, 1
0041 je 0x195a
0043 jmp 0x1b02
0046 push si
0047 push di
0048 nop 
0049 push cs
004a call 0x1fe4 ; _DigTileB
004d jmp 0x1aff
0050 cmp si, 1
0053 jle 0x196c
0055 jmp 0x1a1a
0058 mov bx, di
005a shl bx, 6
005d mov word ptr [bp - 2], bx
0060 mov byte ptr [bx + 0x58e8], 0x18
0065 push di
0066 nop 
0067 push cs
0068 call 0x1d02 ; _MakeNewHoleR
006b add sp, 2
006e cmp si, 1
0071 je 0x198a
0073 jmp 0x1b02
0076 mov bx, word ptr [bp - 2]
0079 add bx, si
007b add bx, 0x58e8
007f mov word ptr [bp - 4], bx
0082 mov al, byte ptr [bx]
0084 sub ah, ah
0086 push ax
0087 nop 
0088 push cs
0089 call 0x1182 ; _IsItDirt
008c add sp, 2
008f or ax, ax
0091 jne 0x19aa
0093 jmp 0x1ac4
0096 nop 
0097 push cs
0098 call 0x15ee ; _SRand8
009b mov bx, word ptr [bp - 4]
009e mov byte ptr [bx], al
00a0 mov ax, di
00a2 cdq 
00a3 mov es, word ptr [0xc40a]
00a7 add word ptr es:[0x9ddc], ax
00ac adc word ptr es:[0x9dde], dx
00b1 mov ax, si
00b3 cdq 
00b4 mov es, word ptr [0xc40c]
00b8 add word ptr es:[0x9de2], ax
00bd adc word ptr es:[0x9de4], dx
00c2 mov es, word ptr [0xc40e]
00c6 inc word ptr es:[0x7a56]
00cb mov ax, word ptr es:[0x7a56]
00cf mov word ptr [bp - 6], ax
00d2 or ax, ax
00d4 jg 0x19ed
00d6 jmp 0x1ac4
00d9 cdq 
00da push dx
00db push ax
00dc mov es, word ptr [0xc40a]
00e0 push word ptr es:[0x9dde]
00e5 push word ptr es:[0x9ddc]
00ea mov word ptr [bp - 0xa], ax
00ed mov word ptr [bp - 8], dx
00f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00f5 mov es, word ptr [0xc410]
00f9 mov word ptr es:[0x9fba], ax
00fd push word ptr [bp - 8]
0100 push word ptr [bp - 0xa]
0103 jmp 0x1aa9
0106 mov bx, di
0108 shl bx, 6
010b mov word ptr [bp - 2], bx
010e add bx, si
0110 add bx, 0x58e8
0114 mov word ptr [bp - 4], bx
0117 mov al, byte ptr [bx]
0119 sub ah, ah
011b push ax
011c nop 
011d push cs
011e call 0x1182 ; _IsItDirt
0121 add sp, 2
0124 or ax, ax
0126 jne 0x1a3f
0128 jmp 0x1ac4
012b nop 
012c push cs
012d call 0x15ee ; _SRand8
0130 mov bx, word ptr [bp - 4]
0133 mov byte ptr [bx], al
0135 mov ax, di
0137 cdq 
0138 mov es, word ptr [0xc40a]
013c add word ptr es:[0x9ddc], ax
0141 adc word ptr es:[0x9dde], dx
0146 mov ax, si
0148 cdq 
0149 mov es, word ptr [0xc40c]
014d add word ptr es:[0x9de2], ax
0152 adc word ptr es:[0x9de4], dx
0157 mov es, word ptr [0xc40e]
015b inc word ptr es:[0x7a56]
0160 mov ax, word ptr es:[0x7a56]
0164 mov word ptr [bp - 6], ax
0167 or ax, ax
0169 jle 0x1ac4
016b cdq 
016c push dx
016d push ax
016e mov es, word ptr [0xc40a]
0172 push word ptr es:[0x9dde]
0177 push word ptr es:[0x9ddc]
017c mov word ptr [bp - 0xe], ax
017f mov word ptr [bp - 0xc], dx
0182 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 389, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0187 mov es, word ptr [0xc410]
018b mov word ptr es:[0x9fba], ax
018f push word ptr [bp - 0xc]
0192 push word ptr [bp - 0xe]
0195 mov es, word ptr [0xc40c]
0199 push word ptr es:[0x9de4]
019e push word ptr es:[0x9de2]
01a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 422, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
01a8 mov es, word ptr [0xc412]
01ac mov word ptr es:[0x9fd2], ax
01b0 lea ax, [si - 1]
01b3 push ax
01b4 push di
01b5 nop 
01b6 push cs
01b7 call 0x26e4 ; _SmoothEdgesR
01ba add sp, 4
01bd push si
01be lea ax, [di + 1]
01c1 push ax
01c2 nop 
01c3 push cs
01c4 call 0x26e4 ; _SmoothEdgesR
01c7 add sp, 4
01ca lea ax, [si + 1]
01cd push ax
01ce push di
01cf nop 
01d0 push cs
01d1 call 0x26e4 ; _SmoothEdgesR
01d4 add sp, 4
01d7 push si
01d8 lea ax, [di - 1]
01db push ax
01dc nop 
01dd push cs
01de call 0x26e4 ; _SmoothEdgesR
01e1 add sp, 4
01e4 push si
01e5 push di
01e6 nop 
01e7 push cs
01e8 call 0x2914 ; _FixExitMapR
01eb add sp, 4
01ee pop si
01ef pop di
01f0 leave 
01f1 retf 
```

## Known declaration examples

- `extern void far DigTileB(int x, int y);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far DigTileB(int x, int y);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern void far MakeNewHoleB(int x);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern void far MakeNewHoleR(int x);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far SmoothEdgesR(int x, int y);` — src/recovered/wf_FillDirtR-d16ac84868.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DigMyNewHole', 'offset': 5806, 'source': None, 'size': 107}
- {'symbol': '_CreateNewHole', 'offset': 5914, 'source': None, 'size': 506}
- {'symbol': '_MakeNewHoleB', 'offset': 6918, 'source': None, 'size': 436}
- {'symbol': '_CanBeHouseHole', 'offset': 7354, 'source': 'src/recovered/wf_CanBeHouseHole-987878d5ee.c', 'size': 72}
