# Recovery task _DigTileThemB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 328 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 6]
000c cmp di, 0x3f
000f jge 0x2300
0011 mov bx, si
0013 shl bx, 6
0016 mov al, byte ptr [bx + di + 0x48e9]
001a sub ah, ah
001c push ax
001d nop 
001e push cs
001f call 0x1182 ; _IsItDirt
0022 add sp, 2
0025 or ax, ax
0027 jne 0x2300
0029 jmp 0x2416
002c cmp di, 2
002f jle 0x2320
0031 mov bx, si
0033 shl bx, 6
0036 mov al, byte ptr [bx + di + 0x48e7]
003a sub ah, ah
003c push ax
003d nop 
003e push cs
003f call 0x1182 ; _IsItDirt
0042 add sp, 2
0045 or ax, ax
0047 jne 0x2320
0049 jmp 0x2416
004c or si, si
004e jne 0x2327
0050 jmp 0x2416
0053 cmp si, 0x3e
0056 jle 0x232f
0058 jmp 0x2416
005b or di, di
005d jne 0x2348
005f mov bx, si
0061 shl bx, 6
0064 mov byte ptr [bx + di + 0x48e8], 0x18
0069 push si
006a nop 
006b push cs
006c call 0x1b06 ; _MakeNewHoleB
006f add sp, 2
0072 jmp 0x2356
0074 nop 
0075 push cs
0076 call 0x15ee ; _SRand8
0079 mov bx, si
007b shl bx, 6
007e mov byte ptr [bx + di + 0x48e8], al
0082 mov ax, si
0084 cdq 
0085 mov es, word ptr [0xc418]
0089 add word ptr es:[0x8104], ax
008e adc word ptr es:[0x8106], dx
0093 mov ax, di
0095 cdq 
0096 mov es, word ptr [0xc41a]
009a add word ptr es:[0x811a], ax
009f adc word ptr es:[0x811c], dx
00a4 mov es, word ptr [0xc41c]
00a8 inc word ptr es:[0x72c8]
00ad mov ax, word ptr es:[0x72c8]
00b1 mov word ptr [bp - 2], ax
00b4 or ax, ax
00b6 jle 0x23d1
00b8 cdq 
00b9 push dx
00ba push ax
00bb mov es, word ptr [0xc418]
00bf push word ptr es:[0x8106]
00c4 push word ptr es:[0x8104]
00c9 mov word ptr [bp - 6], ax
00cc mov word ptr [bp - 4], dx
00cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 210, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00d4 mov es, word ptr [0xc41e]
00d8 mov word ptr es:[0x7c48], ax
00dc push word ptr [bp - 4]
00df push word ptr [bp - 6]
00e2 mov es, word ptr [0xc41a]
00e6 push word ptr es:[0x811c]
00eb push word ptr es:[0x811a]
00f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00f5 mov es, word ptr [0xc420]
00f9 mov word ptr es:[0x7c90], ax
00fd lea ax, [di - 1]
0100 push ax
0101 push si
0102 nop 
0103 push cs
0104 call 0x255a ; _SmoothEdgesB
0107 add sp, 4
010a push di
010b lea ax, [si + 1]
010e push ax
010f nop 
0110 push cs
0111 call 0x255a ; _SmoothEdgesB
0114 add sp, 4
0117 lea ax, [di + 1]
011a push ax
011b push si
011c nop 
011d push cs
011e call 0x255a ; _SmoothEdgesB
0121 add sp, 4
0124 push di
0125 lea ax, [si - 1]
0128 push ax
0129 nop 
012a push cs
012b call 0x255a ; _SmoothEdgesB
012e add sp, 4
0131 push di
0132 push si
0133 nop 
0134 push cs
0135 call 0x284e ; _FixExitMapB
0138 add sp, 4
013b mov ax, 1
013e pop si
013f pop di
0140 leave 
0141 retf 
0142 xor ax, ax
0144 pop si
0145 pop di
0146 leave 
0147 retf 
```

## Known declaration examples

- `extern void far MakeNewHoleB(int x);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern void far SmoothEdgesB(int x, int y);` — src/recovered/wf_FillDirtB-b73109489f.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DigTileB', 'offset': 8164, 'source': None, 'size': 505}
- {'symbol': '_DigTileR', 'offset': 8670, 'source': None, 'size': 245}
- {'symbol': '_DigTileThemR', 'offset': 9244, 'source': None, 'size': 318}
- {'symbol': '_SmoothEdgesB', 'offset': 9562, 'source': None, 'size': 362}
