# Recovery task _FloodNestB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 60 bytes.

```asm
0000 push di
0001 push si
0002 xor di, di
0004 mov bx, 3
0007 mov si, di
0009 add si, bx
000b add si, 0x48e8
000f mov dl, byte ptr [si]
0011 sub dh, dh
0013 cmp dx, 0x20
0016 jl 0x29fc
0018 cmp dx, 0x2d
001b jg 0x29fc
001d add byte ptr [si], 0x31
0020 jmp 0x2a04
0022 cmp byte ptr [si], 0x13
0025 ja 0x2a04
0027 mov byte ptr [si], 0x50
002a inc bx
002b cmp bx, 0x40
002e jl 0x29e1
0030 add di, 0x40
0033 cmp di, 0x1000
0037 jl 0x29de
0039 pop si
003a pop di
003b retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FixExitMapB', 'offset': 10318, 'source': None, 'size': 198}
- {'symbol': '_FixExitMapR', 'offset': 10516, 'source': None, 'size': 198}
- {'symbol': '_CompactListA', 'offset': 10774, 'source': None, 'size': 99}
- {'symbol': '_CompactListB', 'offset': 10874, 'source': None, 'size': 99}
