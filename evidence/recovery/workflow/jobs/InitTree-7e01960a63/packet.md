# Recovery task _InitTree

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 28 bytes.

```asm
0000 push di
0001 mov es, word ptr [0xb8de]
0005 mov ax, 0x1000
0008 mov cx, 0x100
000b lea di, [0x501a]
000f rep stosw word ptr es:[di], ax
0011 lea di, [0x521a]
0015 mov cx, 0x1000
0018 rep stosw word ptr es:[di], ax
001a pop di
001b retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UnpackFileRead', 'offset': 42985, 'source': None, 'size': 99}
- {'symbol': '_UnpackFileClose', 'offset': 43084, 'source': None, 'size': 11}
- {'symbol': '_InsertNode', 'offset': 43124, 'source': None, 'size': 282}
- {'symbol': '_DeleteNode', 'offset': 43406, 'source': None, 'size': 189}
