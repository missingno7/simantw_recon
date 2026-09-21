# Recovery task _TryEatFoodR

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
0013 add bx, 0x58e8
0017 mov word ptr [bp - 2], bx
001a mov dl, byte ptr [bx]
001c sub dh, dh
001e cmp dx, 0x10
0021 jl 0x6bb2
0023 cmp dx, 0x13
0026 jg 0x6bb2
0028 cmp dx, 0x10
002b jne 0x6b72
002d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 48, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0032 mov bx, word ptr [bp - 2]
0035 mov byte ptr [bx], al
0037 jmp 0x6b74
0039 nop 
003a dec byte ptr [bx]
003c mov es, word ptr [0xc394]
0040 cmp word ptr es:[0x72de], 0
0046 jle 0x6b85
0048 dec word ptr es:[0x72de]
004d mov ax, word ptr [0xac84] ; _RpopT
0050 add ax, word ptr [0xaca4]
0054 sar ax, 4
0057 mov es, word ptr [0xc3a4]
005b add word ptr es:[0x7c8e], 5
0061 cmp ax, word ptr es:[0x7c8e]
0066 jge 0x6bb2
0068 mov word ptr es:[0x7c8e], 0
006f cmp word ptr [0xac88], 0x64 ; _HealthR
0074 jge 0x6bb2
0076 inc word ptr [0xac88] ; _HealthR
007a pop si
007b pop di
007c leave 
007d retf 
```

## Known declaration examples

- `extern int near HealthR;` — src/recovered/DecEatR.c
- `extern int near RpopT;` — src/recovered/DecEatR.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutR-a39ba19d03.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_TryMoveDirR', 'offset': 26704, 'source': None, 'size': 186}
- {'symbol': '_DoNestingR', 'offset': 26890, 'source': None, 'size': 557}
- {'symbol': '_EatFoodR', 'offset': 27574, 'source': None, 'size': 112}
- {'symbol': '_StealFoodR', 'offset': 27686, 'source': None, 'size': 67}
