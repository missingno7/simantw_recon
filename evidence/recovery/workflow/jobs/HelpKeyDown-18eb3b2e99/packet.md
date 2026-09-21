# Recovery task _HelpKeyDown

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 166 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov bx, word ptr [bp + 8]
0006 cmp bx, 0x70
0009 jne 0xe38
000b push 0x10
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 14, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
0012 test ah, 0x80
0015 je 0xe1e
0017 cmp word ptr [0x10], 1 ; _bHelp
001c sbb ax, ax
001e neg ax
0020 mov word ptr [0x10], ax ; _bHelp
0023 or ax, ax
0025 je 0xe4a
0027 mov es, word ptr [0xbe86]
002b push word ptr es:[0x72d0]
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 69}}]
0035 jmp 0xe33
0037 nop 
0038 push word ptr [0xcd78] ; _rootWnd
003c push <resolved loader operand; see bindings> ; [{'operand_offset': 61, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
003f push 0x76ac
0042 push 3
0044 push 0
0046 push 0
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 171}}]
004d mov ax, 1
0050 leave 
0051 retf 
0052 cmp bx, 0x1b
0055 jne 0xe58
0057 cmp word ptr [0x10], 0 ; _bHelp
005c je 0xe58
005e mov word ptr [0x10], 0 ; _bHelp
0064 push word ptr [bp + 6]
0067 push -0xc
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 106, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 129}}]
006e push ax
006f jmp 0xe16
0071 nop 
0072 cmp bx, 0x2e
0075 jne 0xe88
0077 cmp word ptr [0x10], 1 ; _bHelp
007c sbb ax, ax
007e neg ax
0080 mov word ptr [0x10], ax ; _bHelp
0083 or ax, ax
0085 je 0xe78
0087 mov es, word ptr [0xbe86]
008b push word ptr es:[0x72d0]
0090 jmp 0xe83
0092 push word ptr [bp + 6]
0095 push -0xc
0097 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 129}}]
009c push ax
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 69}}]
00a2 xor ax, ax
00a4 leave 
00a5 retf 
```

## Known declaration examples

- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int near rootWnd;` — src/recovered/DoWinHelp.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawRibbonMessage', 'offset': 2854, 'source': 'src/recovered/wf_DrawRibbonMessage-0779d6fc14.c', 'size': 156}
- {'symbol': '_DoEvent', 'offset': 3010, 'source': None, 'size': 548}
- {'symbol': '_DoKeyDown', 'offset': 3724, 'source': None, 'size': 1385}
- {'symbol': '_DoMouse', 'offset': 5110, 'source': None, 'size': None}
