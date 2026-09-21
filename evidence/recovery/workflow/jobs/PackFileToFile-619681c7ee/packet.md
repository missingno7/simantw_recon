# Recovery task _PackFileToFile

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 87 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov ax, 0x400
0006 push ax
0007 sub ax, ax
0009 push ax
000a push ax
000b push ax
000c push ax
000d push cs
000e call 0xa16c
0011 mov sp, bp
0013 mov word ptr [0xcc2c], 0xa2bb
0019 mov <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetStrategy
001f mov word ptr [0xcc3a], 0xa301
0025 mov <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetStrategy
002b mov ax, word ptr [bp + 6]
002e mov word ptr [0xcc32], ax
0031 mov ax, word ptr [bp + 8]
0034 mov word ptr [0xcc42], ax
0037 mov ax, word ptr [bp + 0xa]
003a mov dx, word ptr [bp + 0xc]
003d mov word ptr [0xcc28], ax
0040 mov word ptr [0xcc2a], dx
0044 push cs
0045 call 0xa40b ; _Encode
0048 push cs
0049 call 0xa1e2
004c mov ax, word ptr [0xcc46]
004f mov dx, word ptr [0xcc48]
0053 mov sp, bp
0055 pop bp
0056 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PackWriteByte', 'offset': 41473, 'source': None, 'size': 64}
- {'symbol': '_PackReadByte', 'offset': 41578, 'source': None, 'size': 81}
- {'symbol': '_PackMemoryToMemory', 'offset': 41917, 'source': None, 'size': 78}
- {'symbol': '_Encode', 'offset': 41995, 'source': None, 'size': 542}
