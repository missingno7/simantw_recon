# Recovery task _SetQueenTail

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 70 bytes.

```asm
0000 enter 2, 0
0004 mov dx, word ptr [bp + 0xe]
0007 cmp dx, 0xff
000b jne 0x6504
000d mov word ptr [bp - 2], 0xfe
0012 jmp 0x6507
0014 mov word ptr [bp - 2], dx
0017 push word ptr [bp - 2]
001a mov es, word ptr [0xc478]
001e mov bx, word ptr [bp + 0xc]
0021 xor bl, 4
0024 mov al, byte ptr es:[bx + 8]
0029 cwde 
002a add ax, word ptr [bp + 0xa]
002d push ax
002e mov es, word ptr [0xc47a]
0032 mov al, byte ptr es:[bx]
0037 cwde 
0038 add ax, word ptr [bp + 8]
003b push ax
003c push word ptr [bp + 6]
003f nop 
0040 push cs
0041 call 0x5d18 ; _SetLife
0044 leave 
0045 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ClearLife', 'offset': 25116, 'source': None, 'size': 258}
- {'symbol': '_ClearMyLife', 'offset': 25374, 'source': None, 'size': 465}
- {'symbol': '_SetMyLife', 'offset': 25910, 'source': None, 'size': 196}
- {'symbol': '_MoveMyLife', 'offset': 26106, 'source': None, 'size': 217}
