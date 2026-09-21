# Recovery task _GetWinner

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 241 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov es, word ptr [0xc33a]
0009 cmp word ptr es:[0x8a5c], 1
000f jne 0x2728
0011 mov es, word ptr [0xc33c]
0015 add word ptr es:[0x9e96], 1
001b adc word ptr es:[0x9e98], 0
0021 mov bx, word ptr [bp + 4]
0024 test bl, 0x80
0027 jne 0x2720
0029 jmp 0x27df
002c mov ax, word ptr [bp + 6]
002f pop si
0030 pop di
0031 leave 
0032 ret 
0033 nop 
0034 mov di, word ptr [bp + 4]
0037 mov bl, byte ptr [bp + 6]
003a and bx, 0x78
003d sar bx, 3
0040 mov al, byte ptr [bx + 0x22c6]
0044 sub ah, ah
0046 mov bx, di
0048 and bx, 0x78
004b sar bx, 3
004e mov bl, byte ptr [bx + 0x22c6]
0052 sub bh, bh
0054 shl bx, 2
0057 add bx, ax
0059 mov al, byte ptr [bx + 0x22d6]
005d mov si, ax
005f push 0xa
0061 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _RRand
0066 add sp, 2
0069 cmp ax, si
006b jge 0x27a2
006d test di, 0x80
0071 je 0x2782
0073 mov es, word ptr [0xc33e]
0077 inc word ptr es:[0x79e4]
007c mov es, word ptr [0xc340]
0080 add word ptr es:[0x99e0], 1
0086 adc word ptr es:[0x99e2], 0
008c jmp 0x279b
008e mov es, word ptr [0xc342]
0092 inc word ptr es:[0xa0e4]
0097 mov es, word ptr [0xc33c]
009b add word ptr es:[0x9e96], 1
00a1 adc word ptr es:[0x9e98], 0
00a7 mov ax, di
00a9 pop si
00aa pop di
00ab leave 
00ac ret 
00ad nop 
00ae mov bx, word ptr [bp + 6]
00b1 test bl, 0x80
00b4 je 0x27c6
00b6 mov es, word ptr [0xc33e]
00ba inc word ptr es:[0x79e4]
00bf mov es, word ptr [0xc340]
00c3 add word ptr es:[0x99e0], 1
00c9 adc word ptr es:[0x99e2], 0
00cf jmp 0x27df
00d1 nop 
00d2 mov es, word ptr [0xc342]
00d6 inc word ptr es:[0xa0e4]
00db mov es, word ptr [0xc33c]
00df add word ptr es:[0x9e96], 1
00e5 adc word ptr es:[0x9e98], 0
00eb mov ax, bx
00ed pop si
00ee pop di
00ef leave 
00f0 ret 
```

## Known declaration examples

- `extern int far RRand(int range);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GoInNest', 'offset': 9594, 'source': None, 'size': 240}
- {'symbol': '_StartFightA', 'offset': 9834, 'source': 'src/recovered/wf_StartFightA-b2f3e31b2f.c', 'size': 137}
- {'symbol': '_DoFightA', 'offset': 10214, 'source': None, 'size': 217}
- {'symbol': '_DeadAntHere', 'offset': 10432, 'source': None, 'size': 353}
