# Recovery task _TryEatFoodB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 126 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 6]
000c mov bx, si
000e shl bx, 6
0011 add bx, di
0013 add bx, 0x48e8
0017 mov word ptr [bp - 2], bx
001a mov dl, byte ptr [bx]
001c sub dh, dh
001e cmp dx, 0x10
0021 jl 0x4840
0023 cmp dx, 0x13
0026 jg 0x4840
0028 cmp dx, 0x10
002b jne 0x4800
002d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 48, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0032 mov bx, word ptr [bp - 2]
0035 mov byte ptr [bx], al
0037 jmp 0x4802
0039 nop 
003a dec byte ptr [bx]
003c mov es, word ptr [0xc362]
0040 cmp word ptr es:[0x9ea4], 0
0046 jle 0x4813
0048 dec word ptr es:[0x9ea4]
004d mov ax, word ptr [0xac82] ; _BpopT
0050 add ax, word ptr [0xac98]
0054 sar ax, 4
0057 mov es, word ptr [0xc374]
005b add word ptr es:[0x7402], 5
0061 cmp ax, word ptr es:[0x7402]
0066 jge 0x4840
0068 mov word ptr es:[0x7402], 0
006f cmp word ptr [0xac86], 0x64 ; _HealthB
0074 jge 0x4840
0076 inc word ptr [0xac86] ; _HealthB
007a pop si
007b pop di
007c leave 
007d retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/DecEatB.c
- `extern int near HealthB;` — src/recovered/DecEatB.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutR-a39ba19d03.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_TryMoveDirB', 'offset': 17310, 'source': None, 'size': 266}
- {'symbol': '_DoNestingB', 'offset': 17576, 'source': None, 'size': 797}
- {'symbol': '_EatFoodB', 'offset': 18500, 'source': None, 'size': 112}
- {'symbol': '_StealFoodB', 'offset': 18612, 'source': None, 'size': 67}
