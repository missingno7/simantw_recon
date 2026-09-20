# Recovery task _KillTailR

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
000e mov byte ptr es:[si + 0x46e6], al
0013 mov bl, byte ptr es:[si + 0x42fa]
0018 mov si, word ptr es:[si + 0x4104]
001d and si, 0xff
0021 shl si, 6
0024 sub bh, bh
0026 mov byte ptr [bx + si - 0x6718], al
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

- {'symbol': '_QueenMoveR', 'offset': 26118, 'source': None, 'size': 246}
- {'symbol': '_MakeNewTailR', 'offset': 26364, 'source': None, 'size': 101}
- {'symbol': '_LostHeadR', 'offset': 26512, 'source': None, 'size': 94}
- {'symbol': '_LostTailR', 'offset': 26606, 'source': None, 'size': 98}
