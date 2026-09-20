# Recovery task _YellowHelp

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 62 bytes.

```asm
0000 push word ptr [0xcd78] ; _rootWnd
0004 push <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0007 push 0x76ac
000a push 1
000c mov es, word ptr [0xbf0c]
0010 cmp word ptr es:[0x9fe8], 0
0016 jne 0x8a5c
0018 cmp word ptr [0xcc84], 0x40 ; _MeType
001d jne 0x8a54
001f mov ax, 0x100
0022 mov dx, 3
0025 jmp 0x8a62
0027 nop 
0028 mov ax, 0x100
002b mov dx, 1
002e jmp 0x8a62
0030 mov ax, 0x100
0033 mov dx, 2
0036 push dx
0037 push ax
0038 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 57, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 171}}]
003d retf 
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

- {'symbol': '_YellowCommandKey', 'offset': 34146, 'source': None, 'size': None}
- {'symbol': '_YellowCommand', 'offset': 34746, 'source': None, 'size': None}
- {'symbol': '_OpenHistoryWindow', 'offset': 35434, 'source': 'src/recovered/OpenHistoryWindow.c', 'size': 12}
- {'symbol': '_ProcHistoryEvent', 'offset': 35446, 'source': None, 'size': 245}
