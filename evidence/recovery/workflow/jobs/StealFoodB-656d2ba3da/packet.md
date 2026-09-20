# Recovery task _StealFoodB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 67 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c mov bx, di
000e shl bx, 6
0011 add bx, si
0013 add bx, 0x48e8
0017 mov word ptr [bp - 2], bx
001a cmp byte ptr [bx], 0x10
001d jne 0x48e0
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0024 mov bx, word ptr [bp - 2]
0027 mov byte ptr [bx], al
0029 jmp 0x48e2
002b nop 
002c dec byte ptr [bx]
002e mov es, word ptr [0xc362]
0032 cmp word ptr es:[0x9ea4], 0
0038 jle 0x48f3
003a dec word ptr es:[0x9ea4]
003f pop si
0040 pop di
0041 leave 
0042 retf 
```

## Known declaration examples

- `extern int far SRand8(void);` — src/recovered/RandTurn.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_TryEatFoodB', 'offset': 18374, 'source': None, 'size': 126}
- {'symbol': '_EatFoodB', 'offset': 18500, 'source': None, 'size': 112}
- {'symbol': '_DecEatB', 'offset': 18680, 'source': 'src/recovered/DecEatB.c', 'size': 50}
- {'symbol': '_DoFoodInB', 'offset': 18730, 'source': None, 'size': 678}
