# Recovery task _win_IsWinExposed

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 155 bytes.

```asm
0000 enter 0x1c, 0
0004 push si
0005 mov si, word ptr [bp + 6]
0008 sar si, 8
000b shl si, 1
000d push word ptr [si - 0x435a]
0011 lea ax, [bp - 0xc]
0014 push ss
0015 push ax
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 33}}]
001b mov ax, word ptr [bp - 0xc]
001e mov word ptr [bp - 4], ax
0021 mov ax, word ptr [bp - 0xa]
0024 mov word ptr [bp - 2], ax
0027 push word ptr [si - 0x435a]
002b lea ax, [bp - 4]
002e push ss
002f push ax
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 28}}]
0035 mov ax, word ptr [bp - 4]
0038 mov word ptr [bp - 0xc], ax
003b mov ax, word ptr [bp - 2]
003e mov word ptr [bp - 0xa], ax
0041 mov ax, word ptr [bp - 8]
0044 mov word ptr [bp - 4], ax
0047 mov ax, word ptr [bp - 6]
004a mov word ptr [bp - 2], ax
004d push word ptr [si - 0x435a]
0051 lea ax, [bp - 4]
0054 push ss
0055 push ax
0056 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 28}}]
005b mov ax, word ptr [bp - 4]
005e mov word ptr [bp - 8], ax
0061 mov ax, word ptr [bp - 2]
0064 mov word ptr [bp - 6], ax
0067 push word ptr [0xcd78] ; _rootWnd
006b lea ax, [bp - 0x14]
006e push ss
006f push ax
0070 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 113, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 32}}]
0075 lea ax, [bp - 0x1c]
0078 push ss
0079 push ax
007a lea ax, [bp - 0xc]
007d push ss
007e push ax
007f lea ax, [bp - 0x14]
0082 push ss
0083 push ax
0084 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 79}}]
0089 lea ax, [bp - 0x1c]
008c push ss
008d push ax
008e lea ax, [bp - 0xc]
0091 push ss
0092 push ax
0093 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 148, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 244}}]
0098 pop si
0099 leave 
009a retf 
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

- {'symbol': '_win_PrintTextInObj', 'offset': 49288, 'source': 'src/recovered/win_PrintTextInObj.c', 'size': 41}
- {'symbol': '_MyGetTopWindow', 'offset': 49330, 'source': None, 'size': 79}
- {'symbol': '_win_IsWinInFront', 'offset': 49566, 'source': None, 'size': 107}
- {'symbol': '_win_FlushEvents', 'offset': 49674, 'source': 'src/recovered/wf_win_FlushEvents-3010537d93.c', 'size': 76}
