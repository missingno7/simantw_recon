# Recovery task _UnpackFileOpen

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 57 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 les bx, ptr [bp + 6]
0006 mov ax, 0x8000
0009 push ax
000a push es
000b push bx
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _open
0011 add sp, 6
0014 mov word ptr [0xb8dc], ax ; _unpackHandle
0017 and ax, ax
0019 jg 0xa7d0
001b mov ax, 0
001e jmp 0xa7e7
0020 mov ax, word ptr [0xb8d8]
0023 mov dx, word ptr [0xb8da]
0027 xor bx, bx
0029 push bx
002a push dx
002b push ax
002c nop 
002d push cs
002e call 0xa62a ; _UnpackInit
0031 add sp, 6
0034 mov ax, 1
0037 pop bp
0038 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Unpack', 'offset': 42600, 'source': None, 'size': 306}
- {'symbol': '_UnpackSetBuf', 'offset': 42906, 'source': None, 'size': 22}
- {'symbol': '_UnpackFileRead', 'offset': 42985, 'source': None, 'size': 99}
- {'symbol': '_UnpackFileClose', 'offset': 43084, 'source': None, 'size': 11}
