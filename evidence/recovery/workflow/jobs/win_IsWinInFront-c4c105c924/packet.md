# Recovery task _win_IsWinInFront

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 107 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 push word ptr [0xcd78] ; _rootWnd
0008 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 229}}]
000d mov si, ax
000f or si, si
0011 jne 0xc1b6
0013 xor cx, cx
0015 jmp 0xc1ea
0017 nop 
0018 push si
0019 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 26, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
001e or ax, ax
0020 jne 0xc1ce
0022 push si
0023 push 2
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 230}}]
002a mov si, ax
002c or si, si
002e jne 0xc1b6
0030 or si, si
0032 je 0xc1e8
0034 push si
0035 push 4
0037 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
003c or ax, ax
003e je 0xc1e8
0040 push si
0041 push 4
0043 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 68, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
0048 mov si, ax
004a mov cx, si
004c or cx, cx
004e je 0xc204
0050 push cx
0051 push ds
0052 push 0xbd0c
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 25}}]
005a cmp ax, word ptr [bp + 6]
005d jne 0xc204
005f mov ax, 1
0062 pop si
0063 leave 
0064 retf 
0065 nop 
0066 xor ax, ax
0068 pop si
0069 leave 
006a retf 
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

- {'symbol': '_MyGetTopWindow', 'offset': 49330, 'source': None, 'size': 79}
- {'symbol': '_win_IsWinExposed', 'offset': 49410, 'source': None, 'size': 155}
- {'symbol': '_win_FlushEvents', 'offset': 49674, 'source': 'src/recovered/wf_win_FlushEvents-3010537d93.c', 'size': 76}
- {'symbol': '_win_IsWinOpen', 'offset': 49750, 'source': None, 'size': 49}
