# Recovery task _CleanUp

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 186 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 push word ptr [0xcd78] ; _rootWnd
000a push 0
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 12}}]
0011 lea ax, [bp - 0x14]
0014 push ss
0015 push ax
0016 push 0
0018 push 0x113
001b push 0x113
001e push 3
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
0025 or ax, ax
0027 jne 0x61
0029 mov si, 0xbca6
002c mov di, word ptr [bp - 2]
002f cmp word ptr [si], 0
0032 je 0x9a
0034 push word ptr [si]
0036 push ds
0037 push 0x136
003a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 24}}]
003f push word ptr [si]
0041 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 53}}]
0046 mov word ptr [si], 0
004a add si, 2
004d cmp si, 0xbcf6
0051 jb 0x7f
0053 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _snd_Deinstall
0058 push word ptr [0xcd78] ; _rootWnd
005c push <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
005f push 0x76ac
0062 push 2
0064 push 0
0066 push 0
0068 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 171}}]
006d nop 
006e push cs
006f call 0x4c0c ; _ClosePalette
0072 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 117, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GCloseFonts
0077 push word ptr [0xcd78] ; _rootWnd
007b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 124, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 53}}]
0080 mov word ptr [0xcd78], 0 ; _rootWnd
0086 cmp word ptr [0xcd76], 0 ; _ribbonBarWnd
008b je 0xe3
008d mov word ptr [0xcd76], 0 ; _ribbonBarWnd
0093 push word ptr [0xcd7e] ; _mainRootWnd
0097 push ds
0098 push 0x13c
009b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 156, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 24}}]
00a0 push word ptr [0xcd7e] ; _mainRootWnd
00a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 165, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 53}}]
00a9 mov word ptr [0xcd7e], 0 ; _mainRootWnd
00af push 0
00b1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 178, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 6}}]
00b6 pop si
00b7 pop di
00b8 leave 
00b9 retf 
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

- {'symbol': '_StopSimulation', 'offset': 0, 'source': 'src/recovered/StopSimulation.c', 'size': 52}
- {'symbol': '_RestartSimulation', 'offset': 52, 'source': 'src/recovered/RestartSimulation.c', 'size': 28}
- {'symbol': '_DecodeString', 'offset': 266, 'source': None, 'size': 172}
- {'symbol': '_DoUserButtonUpdate', 'offset': 438, 'source': None, 'size': None}
