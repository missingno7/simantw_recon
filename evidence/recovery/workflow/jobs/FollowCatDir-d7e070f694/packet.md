# Recovery task _FollowCatDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 67 bytes.

```asm
0000 enter 2, 0
0004 mov es, word ptr [0xc55c]
0008 mov ax, word ptr es:[0x77b0]
000c mov word ptr [bp - 2], ax
000f cmp ax, 5
0012 jge 0x32c0
0014 mov ax, 1
0017 leave 
0018 retf 
0019 nop 
001a cmp word ptr [bp - 2], 8
001e jle 0x32cc
0020 mov ax, 3
0023 leave 
0024 retf 
0025 nop 
0026 mov es, word ptr [0xc55e]
002a cmp word ptr es:[0x789c], 0
0030 jle 0x32dc
0032 xor ax, ax
0034 leave 
0035 retf 
0036 mov es, word ptr [0xc52c]
003a mov al, byte ptr es:[0x7a5c]
003e and ax, 3
0041 leave 
0042 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SimDog', 'offset': 11708, 'source': None, 'size': 946}
- {'symbol': '_FollowBoyDir', 'offset': 12654, 'source': None, 'size': 311}
- {'symbol': '_MakeBark', 'offset': 13034, 'source': None, 'size': 155}
- {'symbol': '_FootFall', 'offset': 13190, 'source': None, 'size': 339}
