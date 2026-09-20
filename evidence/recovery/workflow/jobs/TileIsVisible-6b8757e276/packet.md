# Recovery task _TileIsVisible

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 74 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov ax, word ptr [0xcc76] ; _MapPlane
0006 cmp word ptr [bp + 6], ax
0009 jne 0x970e
000b mov bx, word ptr [bp + 8]
000e mov <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0011 mov es, ax
0013 cmp word ptr es:[0x7d2e], bx
0018 jg 0x970e
001a mov ax, word ptr es:[0x7d2e]
001e add ax, word ptr [0xcc80] ; _editWidth
0022 cmp ax, bx
0024 jle 0x970e
0026 mov bx, word ptr [bp + 0xa]
0029 cmp word ptr es:[0x7d30], bx
002e jg 0x970e
0030 mov ax, word ptr es:[0x7d30]
0034 add ax, word ptr [0xcd7a] ; _editHeight
0038 cmp ax, bx
003a jle 0x970e
003c mov dx, 1
003f mov ax, dx
0041 leave 
0042 retf 
0043 nop 
0044 xor dx, dx
0046 mov ax, dx
0048 leave 
0049 retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near editHeight;` — src/recovered/BalloonIsVisible.c
- `extern int near editWidth;` — src/recovered/BalloonIsVisible.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ScrollLeft', 'offset': 38598, 'source': 'src/recovered/ScrollLeft.c', 'size': 1}
- {'symbol': '_MakeDMap', 'offset': 38600, 'source': 'src/recovered/MakeDMap.c', 'size': 1}
- {'symbol': '_ABS', 'offset': 38676, 'source': 'src/recovered/ABS.c', 'size': 20}
- {'symbol': '_ErrorLog', 'offset': 38696, 'source': 'src/recovered/ErrorLog.c', 'size': 1}
