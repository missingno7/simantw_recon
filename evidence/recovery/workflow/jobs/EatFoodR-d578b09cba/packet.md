# Recovery task _EatFoodR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 112 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c mov bx, di
000e shl bx, 6
0011 add bx, si
0013 add bx, 0x58e8
0017 mov word ptr [bp - 2], bx
001a cmp byte ptr [bx], 0x10
001d jne 0x6be2
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0024 mov bx, word ptr [bp - 2]
0027 mov byte ptr [bx], al
0029 jmp 0x6be4
002b nop 
002c dec byte ptr [bx]
002e mov es, word ptr [0xc394]
0032 cmp word ptr es:[0x72de], 0
0038 jle 0x6bf5
003a dec word ptr es:[0x72de]
003f mov ax, word ptr [0xac84] ; _RpopT
0042 add ax, word ptr [0xaca4]
0046 sar ax, 4
0049 mov es, word ptr [0xc3a4]
004d add word ptr es:[0x7c8e], 5
0053 cmp ax, word ptr es:[0x7c8e]
0058 jge 0x6c22
005a mov word ptr es:[0x7c8e], 0
0061 cmp word ptr [0xac88], 0x64 ; _HealthR
0066 jge 0x6c22
0068 inc word ptr [0xac88] ; _HealthR
006c pop si
006d pop di
006e leave 
006f retf 
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

- {'symbol': '_DoNestingR', 'offset': 26890, 'source': None, 'size': 557}
- {'symbol': '_TryEatFoodR', 'offset': 27448, 'source': None, 'size': 126}
- {'symbol': '_StealFoodR', 'offset': 27686, 'source': None, 'size': 67}
- {'symbol': '_DecEatR', 'offset': 27754, 'source': 'src/recovered/DecEatR.c', 'size': 34}
