# Recovery task _InitInstance

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 325 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov word ptr [0xcc7c], di ; _hInst
000d push ds
000e push 0x62d
0011 push ds
0012 push 0x626
0015 push 0x2cf
0018 push 0
001a push 0
001c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0021 mov cx, 0x64
0024 cdq 
0025 idiv cx
0027 push ax
0028 push 1
002a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 43, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
002f mov cx, 0x64
0032 cdq 
0033 idiv cx
0035 push ax
0036 push 0
0038 push cx
0039 push 0
003b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 60, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0040 mov cx, 0x62
0043 imul cx
0045 push dx
0046 push ax
0047 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 74, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
004c push ax
004d push 0
004f push 0x64
0051 push 1
0053 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 84, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0058 mov cx, 0x5a
005b imul cx
005d push dx
005e push ax
005f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 98, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0064 push 0xc
0066 mov word ptr [bp - 0x12], ax
0069 mov word ptr [bp - 0x14], ax
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0071 sub ax, word ptr [bp - 0x14]
0074 neg ax
0076 push ax
0077 push 0
0079 push 0
007b push di
007c push 0
007e push 0
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 41}}]
0085 mov si, ax
0087 or si, si
0089 jne 0x3d1c
008b xor ax, ax
008d pop si
008e pop di
008f leave 
0090 retf 
0091 nop 
0092 push si
0093 push ds
0094 push 0x635
0097 push -1
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 154, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 26}}]
009e mov word ptr [0xcd7e], si ; _mainRootWnd
00a2 push si
00a3 mov ax, word ptr [bp + 8]
00a6 or al, 3
00a8 push ax
00a9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 42}}]
00ae push si
00af lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
00b4 push si
00b5 lea ax, [bp - 0x10]
00b8 push ss
00b9 push ax
00ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 33}}]
00bf mov ax, word ptr [bp - 0xc]
00c2 mov word ptr [0xcc7a], ax ; _screenWidth
00c5 mov ax, word ptr [bp - 0xa]
00c8 mov word ptr [0xce86], ax ; _screenHeight
00cb push word ptr [0xcd7e] ; _mainRootWnd
00cf lea ax, [bp - 8]
00d2 push ss
00d3 push ax
00d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 33}}]
00d9 push ds
00da push 0x64d
00dd push ds
00de push 0x63b
00e1 push 0x5200
00e4 push 0
00e6 push 0
00e8 push 0
00ea push word ptr [bp - 4]
00ed push 0
00ef push word ptr [0xcd7e] ; _mainRootWnd
00f3 push 0
00f5 push di
00f6 push 0
00f8 push 0
00fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 251, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 41}}]
00ff mov word ptr [0xcd76], ax ; _ribbonBarWnd
0102 push ds
0103 push 0x66d
0106 push ds
0107 push 0x65a
010a push 0x5200
010d push 0
010f push 0
0111 push 0
0113 push word ptr [bp - 4]
0116 push word ptr [bp - 2]
0119 push word ptr [0xcd7e] ; _mainRootWnd
011d push 0
011f push di
0120 push 0
0122 push 0
0124 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 293, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 41}}]
0129 mov word ptr [0xcd78], ax ; _rootWnd
012c push word ptr [0xcd76] ; _ribbonBarWnd
0130 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 305, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
0135 push word ptr [0xcd78] ; _rootWnd
0139 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 314, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
013e mov ax, 1
0141 pop si
0142 pop di
0143 leave 
0144 retf 
```

## Known declaration examples

- `extern int near hInst;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern int near ribbonBarWnd;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetFancyCursor', 'offset': 10368, 'source': None, 'size': 175}
- {'symbol': 'MAINWNDPROC', 'offset': 10544, 'source': None, 'size': 4953}
- {'symbol': '_InitApplication', 'offset': 15824, 'source': None, 'size': 315}
- {'symbol': '_PatchColorArrays', 'offset': 16140, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c', 'size': 206}
