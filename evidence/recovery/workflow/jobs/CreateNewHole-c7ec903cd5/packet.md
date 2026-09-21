# Recovery task _CreateNewHole

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 506 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 cmp di, 1
000c jge 0x172b
000e jmp 0x1910
0011 cmp di, 0x7f
0014 jl 0x1733
0016 jmp 0x1910
0019 mov si, word ptr [bp + 8]
001c cmp si, 1
001f jge 0x173e
0021 jmp 0x1910
0024 cmp si, 0x3f
0027 jl 0x1746
0029 jmp 0x1910
002c mov es, word ptr [0xc3fc]
0030 cmp word ptr es:[0x9b6e], 0
0036 je 0x179c
0038 mov bx, di
003a shl bx, 6
003d mov byte ptr [bx + si + 0x28e8], 0x59
0042 cmp di, 0x40
0045 jl 0x1764
0047 jmp 0x1806
004a mov ax, di
004c mov es, word ptr [0xc402]
0050 mov byte ptr es:[si - 0x7d2e], al
0055 push 1
0057 push si
0058 nop 
0059 push cs
005a call 0x1fe4 ; _DigTileB
005d add sp, 4
0060 mov es, word ptr [0xc404]
0064 mov word ptr es:[0x835a], di
0069 mov word ptr es:[0x835c], si
006e mov es, word ptr [0xc406]
0072 mov word ptr es:[0x8352], si
0077 mov word ptr es:[0x8354], 0
007e pop si
007f pop di
0080 leave 
0081 retf 
0082 mov bx, di
0084 shl bx, 6
0087 mov byte ptr [bx + si + 0x28e8], 0x50
008c xor cx, cx
008e mov es, word ptr [0xc3fe]
0092 mov bx, cx
0094 mov al, byte ptr es:[bx + 8]
0099 cwde 
009a mov di, ax
009c add di, word ptr [bp + 8]
009f mov es, word ptr [0xc400]
00a3 mov al, byte ptr es:[bx]
00a8 cwde 
00a9 mov si, ax
00ab add si, word ptr [bp + 6]
00ae js 0x17f6
00b0 cmp si, 0x7f
00b3 jg 0x17f6
00b5 or di, di
00b7 jl 0x17f6
00b9 cmp di, 0x3f
00bc jg 0x17f6
00be mov bx, si
00c0 shl bx, 6
00c3 add bx, di
00c5 add bx, 0x28e8
00c9 mov word ptr [bp - 2], bx
00cc cmp byte ptr [bx], 0x50
00cf jae 0x17f6
00d1 mov bx, cx
00d3 mov al, byte ptr [bx + 0x230c]
00d7 mov bx, word ptr [bp - 2]
00da mov byte ptr [bx], al
00dc inc cx
00dd cmp cx, 8
00e0 jl 0x17a8
00e2 mov si, word ptr [bp + 8]
00e5 mov di, word ptr [bp + 6]
00e8 jmp 0x175c
00eb nop 
00ec mov ax, di
00ee mov es, word ptr [0xc408]
00f2 mov byte ptr es:[si - 0x7cee], al
00f7 mov bx, si
00f9 shl bx, 6
00fc add bx, 0x58e9
0100 mov word ptr [bp - 4], bx
0103 mov al, byte ptr [bx]
0105 sub ah, ah
0107 push ax
0108 nop 
0109 push cs
010a call 0x1182 ; _IsItDirt
010d add sp, 2
0110 or ax, ax
0112 jne 0x1831
0114 jmp 0x18b5
0117 nop 
0118 push cs
0119 call 0x15ee ; _SRand8
011c mov bx, word ptr [bp - 4]
011f mov byte ptr [bx], al
0121 mov ax, si
0123 cdq 
0124 mov es, word ptr [0xc40a]
0128 add word ptr es:[0x9ddc], ax
012d adc word ptr es:[0x9dde], dx
0132 mov es, word ptr [0xc40c]
0136 add word ptr es:[0x9de2], 1
013c adc word ptr es:[0x9de4], 0
0142 mov es, word ptr [0xc40e]
0146 inc word ptr es:[0x7a56]
014b mov ax, word ptr es:[0x7a56]
014f mov word ptr [bp - 6], ax
0152 or ax, ax
0154 jle 0x18b5
0156 cdq 
0157 push dx
0158 push ax
0159 mov es, word ptr [0xc40a]
015d push word ptr es:[0x9dde]
0162 push word ptr es:[0x9ddc]
0167 mov word ptr [bp - 0xa], ax
016a mov word ptr [bp - 8], dx
016d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 368, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0172 mov es, word ptr [0xc410]
0176 mov word ptr es:[0x9fba], ax
017a push word ptr [bp - 8]
017d push word ptr [bp - 0xa]
0180 mov es, word ptr [0xc40c]
0184 push word ptr es:[0x9de4]
0189 push word ptr es:[0x9de2]
018e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 401, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0193 mov es, word ptr [0xc412]
0197 mov word ptr es:[0x9fd2], ax
019b push 0
019d push si
019e nop 
019f push cs
01a0 call 0x26e4 ; _SmoothEdgesR
01a3 add sp, 4
01a6 push 1
01a8 lea ax, [si + 1]
01ab push ax
01ac nop 
01ad push cs
01ae call 0x26e4 ; _SmoothEdgesR
01b1 add sp, 4
01b4 push 2
01b6 push si
01b7 nop 
01b8 push cs
01b9 call 0x26e4 ; _SmoothEdgesR
01bc add sp, 4
01bf push 1
01c1 lea ax, [si - 1]
01c4 push ax
01c5 nop 
01c6 push cs
01c7 call 0x26e4 ; _SmoothEdgesR
01ca add sp, 4
01cd push 1
01cf push si
01d0 nop 
01d1 push cs
01d2 call 0x2914 ; _FixExitMapR
01d5 add sp, 4
01d8 mov es, word ptr [0xc414]
01dc mov word ptr es:[0x835e], di
01e1 mov word ptr es:[0x8360], si
01e6 mov es, word ptr [0xc416]
01ea mov word ptr es:[0x8356], si
01ef mov word ptr es:[0x8358], 0
01f6 pop si
01f7 pop di
01f8 leave 
01f9 retf 
```

## Known declaration examples

- `extern void far DigTileB(int x, int y);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far DigTileB(int x, int y);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
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

- {'symbol': '_SRand256', 'offset': 5774, 'source': None, 'size': 31}
- {'symbol': '_DigMyNewHole', 'offset': 5806, 'source': None, 'size': 107}
- {'symbol': '_DigMyTile', 'offset': 6420, 'source': None, 'size': 498}
- {'symbol': '_MakeNewHoleB', 'offset': 6918, 'source': None, 'size': 436}
