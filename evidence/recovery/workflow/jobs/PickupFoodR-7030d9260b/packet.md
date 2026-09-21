# Recovery task _PickupFoodR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 98 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 6]
000c xor dx, dx
000e mov bx, si
0010 shl bx, 6
0013 add bx, di
0015 add bx, 0x58e8
0019 mov word ptr [bp - 4], bx
001c mov cl, byte ptr [bx]
001e sub ch, ch
0020 cmp cx, 0x10
0023 jne 0xfdc
0025 nop 
0026 push cs
0027 call 0x15ee ; _SRand8
002a mov bx, word ptr [bp - 4]
002d mov byte ptr [bx], al
002f mov word ptr [bp - 2], 1
0034 mov dx, word ptr [bp - 2]
0037 jmp 0xfeb
0039 nop 
003a cmp cx, 0x11
003d jl 0xfeb
003f cmp cx, 0x13
0042 jg 0xfeb
0044 mov dx, 1
0047 dec byte ptr [bx]
0049 dec dx
004a jne 0x1000
004c mov <resolved loader operand; see bindings> ; [{'operand_offset': 77, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
004f mov es, ax
0051 cmp word ptr es:[0x72de], 0
0057 jle 0x1000
0059 dec word ptr es:[0x72de]
005e pop si
005f pop di
0060 leave 
0061 retf 
```

## Known declaration examples

- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FoodFall', 'offset': 3754, 'source': None, 'size': 150}
- {'symbol': '_PickupFoodB', 'offset': 3904, 'source': None, 'size': 98}
- {'symbol': '_PlaceEggB', 'offset': 4100, 'source': None, 'size': 100}
- {'symbol': '_PlaceEggR', 'offset': 4200, 'source': None, 'size': 100}
