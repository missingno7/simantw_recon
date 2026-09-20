# Recovery task _UnpackInit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 62 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 mov cx, 0xfee
0007 les di, ptr [0xb7be]
000b mov al, 0x20
000d rep stosb byte ptr es:[di], al
000f mov word ptr [0xb7ca], 0xfee
0015 mov word ptr [0xb7cc], 0
001b mov word ptr [0xb7d4], 0
0021 mov ax, word ptr [bp + 6]
0024 mov dx, word ptr [bp + 8]
0027 mov word ptr [0xb7c4], ax
002a mov word ptr [0xb7c6], dx
002e mov ax, word ptr [bp + 0xa]
0031 and ax, ax
0033 jns 0xa662
0035 mov ax, 0x7fff
0038 mov word ptr [0xb7c8], ax
003b pop di
003c pop bp
003d retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PackMemoryToMemory', 'offset': 41917, 'source': None, 'size': 78}
- {'symbol': '_Encode', 'offset': 41995, 'source': None, 'size': 542}
- {'symbol': '_Unpack', 'offset': 42600, 'source': None, 'size': 306}
- {'symbol': '_UnpackSetBuf', 'offset': 42906, 'source': None, 'size': 22}
