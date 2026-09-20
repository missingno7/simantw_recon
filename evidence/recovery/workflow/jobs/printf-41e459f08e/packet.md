# Recovery task _printf

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 43 bytes.

```asm
0000 enter 0x200, 0
0004 lea cx, [bp - 0x200]
0008 push ss
0009 push cx
000a push word ptr [bp + 8]
000d push word ptr [bp + 6]
0010 lea dx, [bp + 0xa]
0013 push ss
0014 push dx
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 421}}]
001a lea ax, [bp - 0x200]
001e push ss
001f push ax
0020 push ds
0021 push 0x8fc
0024 nop 
0025 push cs
0026 call 0x62bc ; _WinPrintf
0029 leave 
002a retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_WinPrintf', 'offset': 25276, 'source': None, 'size': 101}
- {'symbol': '_DebugWinPrintf', 'offset': 25378, 'source': None, 'size': 101}
- {'symbol': '_SetDebugFlag', 'offset': 25524, 'source': 'src/recovered/SetDebugFlag.c', 'size': 7}
- {'symbol': '_hanim_PrintSet', 'offset': 25532, 'source': 'src/recovered/hanim_PrintSet.c', 'size': 13}
