# Recovery task _DigTileB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 505 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c mov bx, di
000e shl bx, 6
0011 add bx, si
0013 mov word ptr [bp - 2], bx
0016 mov al, byte ptr [bx + 0x48e8]
001a sub ah, ah
001c push ax
001d nop 
001e push cs
001f call 0x1182 ; _IsItDirt
0022 add sp, 2
0025 or ax, ax
0027 jne 0x2010
0029 jmp 0x219b
002c nop 
002d push cs
002e call 0x15ee ; _SRand8
0031 mov bx, word ptr [bp - 2]
0034 mov byte ptr [bx + 0x48e8], al
0038 mov ax, di
003a cdq 
003b mov es, word ptr [0xc418]
003f add word ptr es:[0x8104], ax
0044 adc word ptr es:[0x8106], dx
0049 mov ax, si
004b cdq 
004c mov es, word ptr [0xc41a]
0050 add word ptr es:[0x811a], ax
0055 adc word ptr es:[0x811c], dx
005a mov es, word ptr [0xc41c]
005e inc word ptr es:[0x72c8]
0063 mov ax, word ptr es:[0x72c8]
0067 mov word ptr [bp - 4], ax
006a or ax, ax
006c jle 0x2097
006e cdq 
006f push dx
0070 push ax
0071 mov es, word ptr [0xc418]
0075 push word ptr es:[0x8106]
007a push word ptr es:[0x8104]
007f mov word ptr [bp - 8], ax
0082 mov word ptr [bp - 6], dx
0085 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 136, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
008a mov es, word ptr [0xc41e]
008e mov word ptr es:[0x7c48], ax
0092 push word ptr [bp - 6]
0095 push word ptr [bp - 8]
0098 mov es, word ptr [0xc41a]
009c push word ptr es:[0x811c]
00a1 push word ptr es:[0x811a]
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00ab mov es, word ptr [0xc420]
00af mov word ptr es:[0x7c90], ax
00b3 cmp si, 0x35
00b6 jg 0x209f
00b8 jmp 0x219b
00bb push 0x40
00bd nop 
00be push cs
00bf call 0x158a ; _SRand1
00c2 add sp, 2
00c5 or ax, ax
00c7 je 0x20b0
00c9 jmp 0x219b
00cc mov bx, word ptr [bp - 2]
00cf mov byte ptr [bx + 0x48e8], 0x14
00d4 mov al, byte ptr [bx + 0x58e8]
00d8 sub ah, ah
00da push ax
00db nop 
00dc push cs
00dd call 0x1182 ; _IsItDirt
00e0 add sp, 2
00e3 or ax, ax
00e5 jne 0x20ce
00e7 jmp 0x2155
00ea nop 
00eb push cs
00ec call 0x15ee ; _SRand8
00ef mov bx, word ptr [bp - 2]
00f2 mov byte ptr [bx + 0x58e8], al
00f6 mov ax, di
00f8 cdq 
00f9 mov es, word ptr [0xc40a]
00fd add word ptr es:[0x9ddc], ax
0102 adc word ptr es:[0x9dde], dx
0107 mov ax, si
0109 cdq 
010a mov es, word ptr [0xc40c]
010e add word ptr es:[0x9de2], ax
0113 adc word ptr es:[0x9de4], dx
0118 mov es, word ptr [0xc40e]
011c inc word ptr es:[0x7a56]
0121 mov ax, word ptr es:[0x7a56]
0125 mov word ptr [bp - 0xa], ax
0128 or ax, ax
012a jle 0x2155
012c cdq 
012d push dx
012e push ax
012f mov es, word ptr [0xc40a]
0133 push word ptr es:[0x9dde]
0138 push word ptr es:[0x9ddc]
013d mov word ptr [bp - 0xe], ax
0140 mov word ptr [bp - 0xc], dx
0143 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 326, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0148 mov es, word ptr [0xc410]
014c mov word ptr es:[0x9fba], ax
0150 push word ptr [bp - 0xc]
0153 push word ptr [bp - 0xe]
0156 mov es, word ptr [0xc40c]
015a push word ptr es:[0x9de4]
015f push word ptr es:[0x9de2]
0164 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 359, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0169 mov es, word ptr [0xc412]
016d mov word ptr es:[0x9fd2], ax
0171 lea ax, [si - 1]
0174 push ax
0175 push di
0176 nop 
0177 push cs
0178 call 0x26e4 ; _SmoothEdgesR
017b add sp, 4
017e push si
017f lea ax, [di + 1]
0182 push ax
0183 nop 
0184 push cs
0185 call 0x26e4 ; _SmoothEdgesR
0188 add sp, 4
018b lea ax, [si + 1]
018e push ax
018f push di
0190 nop 
0191 push cs
0192 call 0x26e4 ; _SmoothEdgesR
0195 add sp, 4
0198 push si
0199 lea ax, [di - 1]
019c push ax
019d nop 
019e push cs
019f call 0x26e4 ; _SmoothEdgesR
01a2 add sp, 4
01a5 push si
01a6 push di
01a7 nop 
01a8 push cs
01a9 call 0x2914 ; _FixExitMapR
01ac add sp, 4
01af mov bx, word ptr [bp - 2]
01b2 mov byte ptr [bx + 0x58e8], 0x14
01b7 lea ax, [si - 1]
01ba push ax
01bb push di
01bc nop 
01bd push cs
01be call 0x255a ; _SmoothEdgesB
01c1 add sp, 4
01c4 push si
01c5 lea ax, [di + 1]
01c8 push ax
01c9 nop 
01ca push cs
01cb call 0x255a ; _SmoothEdgesB
01ce add sp, 4
01d1 lea ax, [si + 1]
01d4 push ax
01d5 push di
01d6 nop 
01d7 push cs
01d8 call 0x255a ; _SmoothEdgesB
01db add sp, 4
01de push si
01df lea ax, [di - 1]
01e2 push ax
01e3 nop 
01e4 push cs
01e5 call 0x255a ; _SmoothEdgesB
01e8 add sp, 4
01eb push si
01ec push di
01ed nop 
01ee push cs
01ef call 0x284e ; _FixExitMapB
01f2 add sp, 4
01f5 pop si
01f6 pop di
01f7 leave 
01f8 retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far SmoothEdgesB(int x, int y);` — src/recovered/wf_FillDirtB-b73109489f.c
- `extern void far SmoothEdgesR(int x, int y);` — src/recovered/wf_FillDirtR-d16ac84868.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeNewHoleR', 'offset': 7426, 'source': None, 'size': 650}
- {'symbol': '_HoleBorder', 'offset': 8078, 'source': None, 'size': 86}
- {'symbol': '_DigTileR', 'offset': 8670, 'source': None, 'size': 245}
- {'symbol': '_DigTileThemB', 'offset': 8916, 'source': None, 'size': 328}
