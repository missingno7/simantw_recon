# Recovery task _PackWriteByte

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 64 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov al, byte ptr [bp + 6]
0006 les bx, ptr [0xcc4a]
000a mov byte ptr es:[bx], al
000d inc word ptr [0xcc4a]
0011 mov ax, word ptr [0xcc30]
0014 inc word ptr [0xcc44]
0018 cmp word ptr [0xcc44], ax
001c jb 0xa23d
001e push word ptr [0xcc44]
0022 mov ax, word ptr [0xcc4e]
0025 mov dx, word ptr [0xcc50]
0029 mov word ptr [0xcc4a], ax
002c mov word ptr [0xcc4c], dx
0030 push dx
0031 push ax
0032 lcall [0xcc3a]
0036 mov word ptr [0xcc44], 0
003c mov sp, bp
003e pop bp
003f retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_AddIndex', 'offset': 40726, 'source': None, 'size': 351}
- {'symbol': '_DeleteIndex', 'offset': 41078, 'source': None, 'size': 245}
- {'symbol': '_PackReadByte', 'offset': 41578, 'source': None, 'size': 81}
- {'symbol': '_PackFileToFile', 'offset': 41765, 'source': None, 'size': 87}
