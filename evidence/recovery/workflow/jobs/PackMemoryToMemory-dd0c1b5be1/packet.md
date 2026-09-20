# Recovery task _PackMemoryToMemory

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 78 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push word ptr [bp + 0xe]
0006 push word ptr [bp + 0xc]
0009 push word ptr [bp + 0xa]
000c push word ptr [bp + 8]
000f push word ptr [bp + 6]
0012 push cs
0013 call 0xa16c
0016 mov sp, bp
0018 mov ax, word ptr [bp + 0xe]
001b sub dx, dx
001d mov word ptr [0xcc28], ax
0020 mov word ptr [0xcc2a], dx
0024 mov word ptr [0xcc34], ax
0027 mov word ptr [0xcc2c], 0xa37c
002d mov <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetStrategy
0033 mov word ptr [0xcc3a], 0xa380
0039 mov <resolved loader operand; see bindings> ; [{'operand_offset': 61, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetStrategy
003f push cs
0040 call 0xa40b ; _Encode
0043 mov ax, word ptr [0xcc46]
0046 mov dx, word ptr [0xcc48]
004a mov sp, bp
004c pop bp
004d retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PackReadByte', 'offset': 41578, 'source': None, 'size': 81}
- {'symbol': '_PackFileToFile', 'offset': 41765, 'source': None, 'size': 87}
- {'symbol': '_Encode', 'offset': 41995, 'source': None, 'size': 542}
- {'symbol': '_UnpackInit', 'offset': 42538, 'source': None, 'size': 62}
