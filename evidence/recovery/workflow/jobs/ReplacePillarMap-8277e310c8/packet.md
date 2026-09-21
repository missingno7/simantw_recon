# Recovery task _ReplacePillarMap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 104 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 8]
0008 mov si, word ptr [bp + 6]
000b push di
000c push si
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0012 add sp, 4
0015 dec ax
0016 jne 0x53d6
0018 mov es, word ptr [0xc5a0]
001c test byte ptr es:[0x9b1e], 1
0022 je 0x53b8
0024 mov ax, si
0026 mov cx, 6
0029 cdq 
002a idiv cx
002c mov es, word ptr [0xc5a6]
0030 mov bx, dx
0032 shl bx, 1
0034 mov al, byte ptr es:[bx + 0x7c0e]
0039 mov bx, si
003b shl bx, 6
003e mov byte ptr [bx + di + 0x28e8], al
0042 pop si
0043 pop di
0044 leave 
0045 retf 
0046 mov ax, di
0048 mov cx, 6
004b mov bx, di
004d cdq 
004e idiv cx
0050 mov es, word ptr [0xc5a6]
0054 mov di, dx
0056 shl di, 1
0058 mov al, byte ptr es:[di + 0x7c0e]
005d shl si, 6
0060 mov byte ptr [bx + si + 0x28e8], al
0064 pop si
0065 pop di
0066 leave 
0067 retf 
```

## Known declaration examples

- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoPillar', 'offset': 19676, 'source': None, 'size': 1576}
- {'symbol': '_StorePillarMap', 'offset': 21252, 'source': None, 'size': 110}
- {'symbol': '_MakeAPill', 'offset': 21466, 'source': None, 'size': 767}
- {'symbol': '_PlacePillTile', 'offset': 22234, 'source': None, 'size': 40}
