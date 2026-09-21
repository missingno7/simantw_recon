# Recovery task _win_Close

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 168 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov bx, di
000b sar bx, 8
000e mov word ptr [bp - 4], bx
0011 shl bx, 1
0013 add bx, 0xbca6
0017 mov word ptr [bp - 2], bx
001a cmp word ptr [bx], 0
001d jne 0xcfba
001f jmp 0xd03c
0022 mov bx, word ptr [bp - 4]
0025 shl bx, 2
0028 les bx, ptr [bx - 0x3166]
002c and byte ptr es:[bx + 0x1d], 0xfd
0031 mov bx, word ptr [bp - 2]
0034 push word ptr [bx]
0036 push 0
0038 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 57, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 42}}]
003d push word ptr [0xcd78] ; _rootWnd
0041 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 229}}]
0046 mov si, ax
0048 or si, si
004a jne 0xcfe8
004c xor di, di
004e jmp 0xd01c
0050 push si
0051 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 82, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
0056 or ax, ax
0058 jne 0xd000
005a push si
005b push 2
005d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 230}}]
0062 mov si, ax
0064 or si, si
0066 jne 0xcfe8
0068 or si, si
006a je 0xd01a
006c push si
006d push 4
006f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
0074 or ax, ax
0076 je 0xd01a
0078 push si
0079 push 4
007b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 124, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 262}}]
0080 mov si, ax
0082 mov di, si
0084 or di, di
0086 je 0xd03c
0088 push di
0089 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 138, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
008e push di
008f push 0x86
0092 mov es, word ptr [0xc6d8]
0096 push word ptr es:[0x34]
009b push 0
009d push 0
009f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 160, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 111}}]
00a4 pop si
00a5 pop di
00a6 leave 
00a7 retf 
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

- {'symbol': '_win_LoadAllWindows', 'offset': 51206, 'source': None, 'size': 552}
- {'symbol': '_win_Open', 'offset': 51758, 'source': None, 'size': 1385}
- {'symbol': '_win_Events', 'offset': 53312, 'source': None, 'size': 112}
- {'symbol': '_win_FindObject', 'offset': 53424, 'source': None, 'size': 101}
