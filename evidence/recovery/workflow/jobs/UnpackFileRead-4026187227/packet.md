# Recovery task _UnpackFileRead

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 99 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 sub sp, 2
0006 xor ax, ax
0008 mov word ptr [bp - 2], ax
000b cmp word ptr [0xb7c8], ax
000f jg 0xa81f
0011 push word ptr [0xb8d6]
0015 les bx, ptr [0xb8d8]
0019 mov word ptr [0xb7c4], bx
001d mov word ptr [0xb7c6], es
0021 push es
0022 push bx
0023 push word ptr [0xb8dc] ; _unpackHandle
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 42, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _read
002c add sp, 8
002f and ax, ax
0031 jle 0xa845
0033 mov word ptr [0xb7c8], ax
0036 mov ax, word ptr [bp + 0xa]
0039 sub ax, word ptr [bp - 2]
003c push ax
003d push word ptr [bp + 8]
0040 mov ax, word ptr [bp + 6]
0043 add ax, word ptr [bp - 2]
0046 push ax
0047 nop 
0048 push cs
0049 call 0xa668 ; _Unpack
004c add sp, 6
004f add word ptr [bp - 2], ax
0052 mov ax, word ptr [bp + 0xa]
0055 cmp word ptr [bp - 2], ax
0058 jne 0xa7fa
005a jmp 0xa848
005c mov ax, word ptr [bp - 2]
005f mov sp, bp
0061 pop bp
0062 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UnpackSetBuf', 'offset': 42906, 'source': None, 'size': 22}
- {'symbol': '_UnpackFileOpen', 'offset': 42928, 'source': None, 'size': 57}
- {'symbol': '_UnpackFileClose', 'offset': 43084, 'source': None, 'size': 11}
- {'symbol': '_InitTree', 'offset': 43096, 'source': None, 'size': 28}
