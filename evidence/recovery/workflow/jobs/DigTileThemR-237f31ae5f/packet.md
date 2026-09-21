# Recovery task _DigTileThemR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 318 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 8]
0009 mov di, word ptr [bp + 6]
000c cmp si, 0x3f
000f jge 0x244c
0011 mov bx, di
0013 shl bx, 6
0016 mov al, byte ptr [bx + si + 0x58e9]
001a sub ah, ah
001c push ax
001d nop 
001e push cs
001f call 0x1182 ; _IsItDirt
0022 add sp, 2
0025 or ax, ax
0027 jne 0x244c
0029 xor ax, ax
002b pop si
002c pop di
002d leave 
002e retf 
002f nop 
0030 cmp si, 2
0033 jle 0x2469
0035 mov bx, di
0037 shl bx, 6
003a mov al, byte ptr [bx + si + 0x58e7]
003e sub ah, ah
0040 push ax
0041 nop 
0042 push cs
0043 call 0x1182 ; _IsItDirt
0046 add sp, 2
0049 or ax, ax
004b je 0x2445
004d or di, di
004f je 0x2445
0051 cmp di, 0x3e
0054 jg 0x2445
0056 or si, si
0058 jne 0x248c
005a mov bx, di
005c shl bx, 6
005f mov byte ptr [bx + si + 0x58e8], 0x18
0064 push di
0065 nop 
0066 push cs
0067 call 0x1d02 ; _MakeNewHoleR
006a add sp, 2
006d jmp 0x249a
006f nop 
0070 nop 
0071 push cs
0072 call 0x15ee ; _SRand8
0075 mov bx, di
0077 shl bx, 6
007a mov byte ptr [bx + si + 0x58e8], al
007e mov ax, di
0080 cdq 
0081 mov es, word ptr [0xc40a]
0085 add word ptr es:[0x9ddc], ax
008a adc word ptr es:[0x9dde], dx
008f mov ax, si
0091 cdq 
0092 mov es, word ptr [0xc40c]
0096 add word ptr es:[0x9de2], ax
009b adc word ptr es:[0x9de4], dx
00a0 mov es, word ptr [0xc40e]
00a4 inc word ptr es:[0x7a56]
00a9 mov ax, word ptr es:[0x7a56]
00ad mov word ptr [bp - 2], ax
00b0 or ax, ax
00b2 jle 0x2515
00b4 cdq 
00b5 push dx
00b6 push ax
00b7 mov es, word ptr [0xc40a]
00bb push word ptr es:[0x9dde]
00c0 push word ptr es:[0x9ddc]
00c5 mov word ptr [bp - 6], ax
00c8 mov word ptr [bp - 4], dx
00cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 206, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00d0 mov es, word ptr [0xc410]
00d4 mov word ptr es:[0x9fba], ax
00d8 push word ptr [bp - 4]
00db push word ptr [bp - 6]
00de mov es, word ptr [0xc40c]
00e2 push word ptr es:[0x9de4]
00e7 push word ptr es:[0x9de2]
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00f1 mov es, word ptr [0xc412]
00f5 mov word ptr es:[0x9fd2], ax
00f9 lea ax, [si - 1]
00fc push ax
00fd push di
00fe nop 
00ff push cs
0100 call 0x26e4 ; _SmoothEdgesR
0103 add sp, 4
0106 push si
0107 lea ax, [di + 1]
010a push ax
010b nop 
010c push cs
010d call 0x26e4 ; _SmoothEdgesR
0110 add sp, 4
0113 lea ax, [si + 1]
0116 push ax
0117 push di
0118 nop 
0119 push cs
011a call 0x26e4 ; _SmoothEdgesR
011d add sp, 4
0120 push si
0121 lea ax, [di - 1]
0124 push ax
0125 nop 
0126 push cs
0127 call 0x26e4 ; _SmoothEdgesR
012a add sp, 4
012d push si
012e push di
012f nop 
0130 push cs
0131 call 0x2914 ; _FixExitMapR
0134 add sp, 4
0137 mov ax, 1
013a pop si
013b pop di
013c leave 
013d retf 
```

## Known declaration examples

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

- {'symbol': '_DigTileR', 'offset': 8670, 'source': None, 'size': 245}
- {'symbol': '_DigTileThemB', 'offset': 8916, 'source': None, 'size': 328}
- {'symbol': '_SmoothEdgesB', 'offset': 9562, 'source': None, 'size': 362}
- {'symbol': '_RIsItDirt', 'offset': 9924, 'source': 'src/recovered/wf_RIsItDirt-6adf524aef.c', 'size': 31}
