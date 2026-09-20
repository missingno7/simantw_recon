# Recovery task _CanBeHouseHole

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 72 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov dx, word ptr [bp + 6]
0006 or dx, dx
0008 jne 0x1cca
000a mov ax, 0x86
000d leave 
000e retf 
000f nop 
0010 cmp dx, 2
0013 jne 0x1cd4
0015 mov ax, 0x8a
0018 leave 
0019 retf 
001a cmp dx, 3
001d je 0x1ccf
001f cmp dx, 0x5e
0022 jl 0x1cfe
0024 cmp dx, 0x62
0027 jge 0x1cea
0029 mov ax, dx
002b add ax, 0x22
002e leave 
002f retf 
0030 cmp dx, 0x66
0033 jne 0x1cf4
0035 mov ax, 0x85
0038 leave 
0039 retf 
003a cmp dx, 0x68
003d jne 0x1cfe
003f mov ax, 0x84
0042 leave 
0043 retf 
0044 xor ax, ax
0046 leave 
0047 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DigMyTile', 'offset': 6420, 'source': None, 'size': 498}
- {'symbol': '_MakeNewHoleB', 'offset': 6918, 'source': None, 'size': 436}
- {'symbol': '_MakeNewHoleR', 'offset': 7426, 'source': None, 'size': 650}
- {'symbol': '_HoleBorder', 'offset': 8078, 'source': None, 'size': 86}
