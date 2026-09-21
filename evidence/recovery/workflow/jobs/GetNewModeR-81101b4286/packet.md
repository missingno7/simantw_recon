# Recovery task _GetNewModeR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 95 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov si, word ptr [bp + 6]
0007 cmp si, 2
000a jne 0xa7c
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0011 mov es, word ptr [0xc4c4]
0015 mov bx, word ptr es:[0x7690]
001a shl bx, 3
001d add bx, ax
001f mov es, word ptr [0xc4da]
0023 mov al, byte ptr es:[bx - 0x761a]
0028 cwde 
0029 pop si
002a leave 
002b retf 
002c cmp si, 6
002f jne 0xaa2
0031 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0036 mov es, word ptr [0xc4c4]
003a mov bx, word ptr es:[0x7690]
003f shl bx, 3
0042 add bx, ax
0044 mov es, word ptr [0xc4dc]
0048 mov al, byte ptr es:[bx - 0x75ea]
004d cwde 
004e pop si
004f leave 
0050 retf 
0051 nop 
0052 mov es, word ptr [0xc4de]
0056 mov al, byte ptr es:[si - 0x75ba]
005b cwde 
005c pop si
005d leave 
005e retf 
```

## Known declaration examples

- `extern int far SRand8(void);` — src/recovered/RandTurn.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetNewMode', 'offset': 2320, 'source': None, 'size': 192}
- {'symbol': '_GetNewModeB', 'offset': 2512, 'source': None, 'size': 127}
- {'symbol': '_GetForageDir', 'offset': 2736, 'source': None, 'size': 384}
- {'symbol': '_GetNestDir', 'offset': 3120, 'source': None, 'size': 547}
