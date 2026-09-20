# Recovery task _MenuQuit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 66 bytes.

```asm
0000 cmp word ptr [0x164e], 0
0005 jne 0xd666
0007 push word ptr [0xcd78] ; _rootWnd
000b push ds
000c push 0x165c
000f push ds
0010 push 0x1650
0013 push 0x1123
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
001b dec ax
001c dec ax
001d je 0xd662
001f sub ax, 4
0022 je 0xd654
0024 mov ax, 1
0027 mov word ptr [0x164e], ax
002a retf 
002b nop 
002c push 0
002e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _SaveGame
0033 add sp, 2
0036 or ax, ax
0038 jne 0xd64c
003a xor ax, ax
003c retf 
003d nop 
003e mov ax, 1
0041 retf 
```

## Known declaration examples

- `extern int near rootWnd;` — src/recovered/DoWinHelp.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_LoadMonoPats', 'offset': 54532, 'source': None, 'size': 278}
- {'symbol': '_Quit', 'offset': 54810, 'source': 'src/recovered/Quit.c', 'size': 13}
- {'symbol': '_SetDefaultWindows', 'offset': 54890, 'source': None, 'size': 113}
- {'symbol': '_NewGame', 'offset': 55004, 'source': None, 'size': 691}
