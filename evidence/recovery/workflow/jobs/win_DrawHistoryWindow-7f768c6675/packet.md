# Recovery task _win_DrawHistoryWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 80 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 test byte ptr [bp + 6], 2
000a je 0x8e74
000c push 0
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0013 add sp, 2
0016 push ax
0017 push 0x150e
001a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FillObjRect
001f add sp, 4
0022 xor di, di
0024 mov si, 0x8e54
0027 mov es, word ptr [0xc084]
002b mov ax, word ptr es:[si]
002e mov word ptr [bp - 2], ax
0031 cmp ax, 0x8000
0034 je 0x8e6a
0036 push di
0037 push 0
0039 push ax
003a nop 
003b push cs
003c call 0x8e78 ; _drawHistGraph
003f add sp, 6
0042 inc di
0043 add si, 2
0046 cmp si, 0x8e5c
004a jb 0x8e4f
004c pop si
004d pop di
004e leave 
004f retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ToggleHistButton', 'offset': 35692, 'source': None, 'size': 400}
- {'symbol': '_ClearHistory', 'offset': 36092, 'source': None, 'size': 299}
- {'symbol': '_drawHistGraph', 'offset': 36472, 'source': None, 'size': 777}
- {'symbol': '_HistUpdate', 'offset': 37250, 'source': None, 'size': 317}
