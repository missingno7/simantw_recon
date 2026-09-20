# Recovery task _KillTailB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 45 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0007 mov es, ax
0009 mov si, word ptr [bp + 6]
000c xor al, al
000e mov byte ptr es:[si + 0x3d18], al
0013 mov bl, byte ptr es:[si + 0x392c]
0018 mov si, word ptr es:[si + 0x3736]
001d and si, 0xff
0021 shl si, 6
0024 sub bh, bh
0026 mov byte ptr [bx + si - 0x7718], al
002a pop si
002b leave 
002c retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_QueenMoveB', 'offset': 16724, 'source': None, 'size': 246}
- {'symbol': '_MakeNewTailB', 'offset': 16970, 'source': None, 'size': 101}
- {'symbol': '_LostHeadB', 'offset': 17118, 'source': None, 'size': 94}
- {'symbol': '_LostTailB', 'offset': 17212, 'source': None, 'size': 98}
