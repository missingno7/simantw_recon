# Recovery task _DigOutBNest

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 218 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov si, 4
0009 mov ax, 1
000c mov word ptr [bp - 6], ax
000f push ax
0010 mov ax, 0x20
0013 mov word ptr [bp - 4], ax
0016 push ax
0017 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 26, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
001c add sp, si
001e cmp word ptr [bp + 6], 0
0022 jne 0x6305
0024 jmp 0x63b4
0027 push 5
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
002e add sp, 2
0031 mov cx, si
0033 add al, cl
0035 sub al, 3
0037 and ax, 7
003a mov si, ax
003c mov es, word ptr [0xc5de]
0040 mov al, byte ptr es:[si]
0045 cwde 
0046 add ax, word ptr [bp - 4]
0049 mov word ptr [bp - 2], ax
004c mov es, word ptr [0xc5dc]
0050 mov cx, ax
0052 mov al, byte ptr es:[si + 8]
0057 cwde 
0058 mov di, ax
005a add di, word ptr [bp - 6]
005d cmp cx, 1
0060 jge 0x634a
0062 mov word ptr [bp - 2], 1
0067 mov si, 2
006a jmp 0x6357
006c cmp cx, 0x3e
006f jle 0x6357
0071 mov word ptr [bp - 2], 0x3e
0076 mov si, 6
0079 cmp di, 2
007c jge 0x6366
007e mov di, 1
0081 mov word ptr [bp - 8], 4
0086 jmp 0x6376
0088 mov word ptr [bp - 8], si
008b cmp di, 0x3e
008e jle 0x6376
0090 mov di, 0x3e
0093 mov word ptr [bp - 8], 0
0098 push di
0099 push word ptr [bp - 2]
009c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 159, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileThemB
00a1 add sp, 4
00a4 dec ax
00a5 jne 0x63a8
00a7 mov ax, word ptr [bp - 2]
00aa mov word ptr [bp - 4], ax
00ad mov word ptr [bp - 6], di
00b0 dec di
00b1 jne 0x63a8
00b3 mov es, word ptr [0xc5ba]
00b7 mov bx, ax
00b9 cmp byte ptr es:[bx - 0x7d2e], 0
00bf jne 0x63a8
00c1 push ax
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MakeNewHoleB
00c7 add sp, 2
00ca dec word ptr [bp + 6]
00cd je 0x63b4
00cf mov si, word ptr [bp - 8]
00d2 jmp 0x6305
00d5 nop 
00d6 pop si
00d7 pop di
00d8 leave 
00d9 retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RandYard', 'offset': 24710, 'source': None, 'size': 476}
- {'symbol': '_GenerateTutorial', 'offset': 25186, 'source': None, 'size': 124}
- {'symbol': '_DigOutRNest', 'offset': 25528, 'source': None, 'size': 218}
- {'symbol': '_InitYelloAnt', 'offset': 25746, 'source': None, 'size': 315}
