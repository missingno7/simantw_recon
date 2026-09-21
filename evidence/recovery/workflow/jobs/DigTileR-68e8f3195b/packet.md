# Recovery task _DigTileR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 245 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c mov bx, di
000e shl bx, 6
0011 add bx, si
0013 add bx, 0x58e8
0017 mov word ptr [bp - 2], bx
001a mov al, byte ptr [bx]
001c sub ah, ah
001e push ax
001f nop 
0020 push cs
0021 call 0x1182 ; _IsItDirt
0024 add sp, 2
0027 or ax, ax
0029 jne 0x220c
002b jmp 0x2291
002e nop 
002f push cs
0030 call 0x15ee ; _SRand8
0033 mov bx, word ptr [bp - 2]
0036 mov byte ptr [bx], al
0038 mov ax, di
003a cdq 
003b mov es, word ptr [0xc40a]
003f add word ptr es:[0x9ddc], ax
0044 adc word ptr es:[0x9dde], dx
0049 mov ax, si
004b cdq 
004c mov es, word ptr [0xc40c]
0050 add word ptr es:[0x9de2], ax
0055 adc word ptr es:[0x9de4], dx
005a mov es, word ptr [0xc40e]
005e inc word ptr es:[0x7a56]
0063 mov ax, word ptr es:[0x7a56]
0067 mov word ptr [bp - 4], ax
006a or ax, ax
006c jle 0x2291
006e cdq 
006f push dx
0070 push ax
0071 mov es, word ptr [0xc40a]
0075 push word ptr es:[0x9dde]
007a push word ptr es:[0x9ddc]
007f mov word ptr [bp - 8], ax
0082 mov word ptr [bp - 6], dx
0085 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 136, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
008a mov es, word ptr [0xc410]
008e mov word ptr es:[0x9fba], ax
0092 push word ptr [bp - 6]
0095 push word ptr [bp - 8]
0098 mov es, word ptr [0xc40c]
009c push word ptr es:[0x9de4]
00a1 push word ptr es:[0x9de2]
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00ab mov es, word ptr [0xc412]
00af mov word ptr es:[0x9fd2], ax
00b3 lea ax, [si - 1]
00b6 push ax
00b7 push di
00b8 nop 
00b9 push cs
00ba call 0x26e4 ; _SmoothEdgesR
00bd add sp, 4
00c0 push si
00c1 lea ax, [di + 1]
00c4 push ax
00c5 nop 
00c6 push cs
00c7 call 0x26e4 ; _SmoothEdgesR
00ca add sp, 4
00cd lea ax, [si + 1]
00d0 push ax
00d1 push di
00d2 nop 
00d3 push cs
00d4 call 0x26e4 ; _SmoothEdgesR
00d7 add sp, 4
00da push si
00db lea ax, [di - 1]
00de push ax
00df nop 
00e0 push cs
00e1 call 0x26e4 ; _SmoothEdgesR
00e4 add sp, 4
00e7 push si
00e8 push di
00e9 nop 
00ea push cs
00eb call 0x2914 ; _FixExitMapR
00ee add sp, 4
00f1 pop si
00f2 pop di
00f3 leave 
00f4 retf 
```

## Known declaration examples

- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_GetRandDir-2664e9d7f9.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern void far SmoothEdgesR(int x, int y);` — src/recovered/wf_FillDirtR-d16ac84868.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_HoleBorder', 'offset': 8078, 'source': None, 'size': 86}
- {'symbol': '_DigTileB', 'offset': 8164, 'source': None, 'size': 505}
- {'symbol': '_DigTileThemB', 'offset': 8916, 'source': None, 'size': 328}
- {'symbol': '_DigTileThemR', 'offset': 9244, 'source': None, 'size': 318}
