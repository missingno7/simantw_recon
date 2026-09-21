# Recovery task _MySetCapture

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 88 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 6]
0008 mov es, word ptr [0xc6b8]
000c mov word ptr es:[0x36], di
0011 mov es, word ptr [0xc6ba]
0015 cmp word ptr es:[0x34], 0
001b je 0x45ac
001d push word ptr [0xcd7e] ; _mainRootWnd
0021 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 31}}]
0026 or ax, ax
0028 jne 0x45ac
002a push di
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 18}}]
0030 jmp 0x45b1
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 236}}]
0037 mov si, ax
0039 or si, si
003b je 0x45cc
003d push si
003e push ds
003f push 0xbadc
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 25}}]
0047 or ax, ax
0049 je 0x45cc
004b mov ax, si
004d pop si
004e pop di
004f leave 
0050 retf 
0051 nop 
0052 xor ax, ax
0054 pop si
0055 pop di
0056 leave 
0057 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GUnpackPic', 'offset': 16596, 'source': None, 'size': 186}
- {'symbol': '_DrawBitMapToBuffer', 'offset': 16782, 'source': None, 'size': 1004}
- {'symbol': '_MyReleaseCapture', 'offset': 17874, 'source': 'src/recovered/MyReleaseCapture.c', 'size': 29}
- {'symbol': '_MyGetCapture', 'offset': 17904, 'source': 'src/recovered/MyGetCapture.c', 'size': 9}
