# Recovery task _SetMyHealth

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 105 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov es, word ptr [0xc49a]
0007 cmp word ptr es:[0x8a5e], 0
000d jne 0x8c84
000f mov bx, word ptr [bp + 6]
0012 jmp 0x8c87
0014 mov bx, 0x64
0017 or bx, bx
0019 jle 0x8c96
001b mov es, word ptr [0xc49c]
001f mov word ptr es:[0x9cf0], 0
0026 cmp bx, 0x64
0029 jle 0x8ca0
002b mov bx, 0x64
002e jmp 0x8ca6
0030 or bx, bx
0032 jge 0x8ca6
0034 xor bx, bx
0036 mov es, word ptr [0xc49e]
003a cmp word ptr es:[0x9bec], bx
003f jge 0x8cc8
0041 cmp bx, 0xa
0044 jl 0x8cc8
0046 mov word ptr [0xac8a], bx ; _MeHealth
004a mov es, word ptr [0xc4a0]
004e mov word ptr es:[0x9af2], 0
0055 leave 
0056 retf 
0057 nop 
0058 mov word ptr [0xac8a], bx ; _MeHealth
005c mov es, word ptr [0xc4a0]
0060 mov word ptr es:[0x9af2], 1
0067 leave 
0068 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FindEggAt', 'offset': 34978, 'source': None, 'size': 499}
- {'symbol': '_FindLifeAt', 'offset': 35478, 'source': None, 'size': 473}
- {'symbol': '_EatMyFood', 'offset': 36058, 'source': None, 'size': 443}
- {'symbol': '_PickupMyEgg', 'offset': 36502, 'source': None, 'size': 181}
