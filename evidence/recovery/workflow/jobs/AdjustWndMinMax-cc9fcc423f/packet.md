# Recovery task _AdjustWndMinMax

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 457 bytes.

```asm
0000 enter 0x2c, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xbe8e]
000a push word ptr es:[0x1450]
000f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Size
0014 add sp, 2
0017 push -1
0019 push -1
001b mov si, ax
001d mov di, dx
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 32, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 25}}]
0024 add si, ax
0026 adc di, dx
0028 mov ax, si
002a mov dx, di
002c shl si, 1
002e rcl di, 1
0030 add si, ax
0032 adc di, dx
0034 sar di, 1
0036 rcr si, 1
0038 sar di, 1
003a rcr si, 1
003c mov word ptr [bp - 6], si
003f mov word ptr [bp - 4], di
0042 push 0x20
0044 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0049 push 0x10
004b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 76, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0050 push 0x21
0052 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0057 push 0x11
0059 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
005e push 0xf
0060 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0065 push word ptr [0xcd78] ; _rootWnd
0069 lea ax, [bp - 0x10]
006c push ss
006d push ax
006e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 33}}]
0073 push word ptr [0xbca6] ; _win_hwnd
0077 lea ax, [bp - 0x18]
007a push ss
007b push ax
007c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 32}}]
0081 push 0x20
0083 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0088 mov si, ax
008a shl si, 1
008c add si, word ptr [bp - 0xc]
008f push 0x21
0091 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0096 shl ax, 1
0098 add ax, word ptr [bp - 0xa]
009b mov word ptr [bp - 8], ax
009e test byte ptr [0xcc7e], 1 ; _displayType
00a3 jne 0x1b8e
00a5 imul si
00a7 sar dx, 1
00a9 rcr ax, 1
00ab cmp dx, word ptr [bp - 4]
00ae jl 0x1b8e
00b0 jg 0x1b25
00b2 cmp ax, word ptr [bp - 6]
00b5 jbe 0x1b8e
00b7 mov ax, word ptr [bp - 6]
00ba mov dx, word ptr [bp - 4]
00bd shl ax, 1
00bf rcl dx, 1
00c1 mov word ptr [bp - 0x22], dx
00c4 mov word ptr [bp - 0x24], ax
00c7 wait <resolved loader operand; see bindings> ; [{'operand_offset': 199, 'type': 5, 'target': {'kind': 'os_fixup', 'reserved': 0, 'type': 5}}]
00c8 fild dword ptr [bp - 0x24]
00cb wait <resolved loader operand; see bindings> ; [{'operand_offset': 203, 'type': 5, 'target': {'kind': 'os_fixup', 'reserved': 0, 'type': 5}}]
00cc fst qword ptr [bp - 0x2c]
00cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 210, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFCIsqrt
00d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 215, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __ftol,__aFftol
00d9 mov word ptr [bp - 2], ax
00dc cmp ax, word ptr [bp - 8]
00df jg 0x1b5a
00e1 cmp ax, si
00e3 jg 0x1b5a
00e5 mov si, ax
00e7 mov di, ax
00e9 jmp 0x1b91
00eb nop 
00ec cmp word ptr [bp - 8], si
00ef jle 0x1b74
00f1 mov ax, si
00f3 sar ax, 1
00f5 cdq 
00f6 push dx
00f7 push ax
00f8 push word ptr [bp - 4]
00fb push word ptr [bp - 6]
00fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 257, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0103 jmp 0x1b55
0105 nop 
0106 mov di, word ptr [bp - 8]
0109 mov ax, di
010b cdq 
010c push dx
010d push ax
010e push word ptr [bp - 4]
0111 push word ptr [bp - 6]
0114 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 279, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0119 mov si, ax
011b shl si, 1
011d jmp 0x1b91
011f nop 
0120 mov di, word ptr [bp - 8]
0123 mov ax, word ptr [bp - 0x14]
0126 sub ax, word ptr [bp - 0x18]
0129 cmp ax, si
012b jge 0x1b9d
012d mov ax, si
012f les bx, ptr [bp + 6]
0132 mov word ptr es:[bx + 4], ax
0136 mov word ptr es:[bx + 0x10], ax
013a mov ax, word ptr [bp - 0x12]
013d sub ax, word ptr [bp - 0x16]
0140 cmp ax, di
0142 jge 0x1bb4
0144 mov ax, di
0146 mov word ptr es:[bx + 6], ax
014a mov word ptr es:[bx + 0x12], ax
014e push 0x20
0150 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 337, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0155 neg ax
0157 les bx, ptr [bp + 6]
015a mov word ptr es:[bx + 8], ax
015e push 0x21
0160 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 353, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0165 neg ax
0167 les bx, ptr [bp + 6]
016a mov word ptr es:[bx + 0xa], ax
016e lea ax, [bp - 0x20]
0171 push ss
0172 push ax
0173 push 0x13
0175 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 376, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
017a add sp, 6
017d push 2
017f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 384, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0184 push 0x20
0186 mov si, ax
0188 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 393, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
018d add si, ax
018f shl si, 1
0191 add si, word ptr [bp - 0x1c]
0194 add si, word ptr [bp - 0x1a]
0197 les bx, ptr [bp + 6]
019a mov word ptr es:[bx + 0xc], si
019e push 3
01a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 417, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
01a5 push 0x21
01a7 mov si, ax
01a9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 426, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
01ae add si, ax
01b0 shl si, 1
01b2 push 4
01b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 437, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
01b9 add si, ax
01bb add si, word ptr [bp - 0x1a]
01be les bx, ptr [bp + 6]
01c1 mov word ptr es:[bx + 0xe], si
01c5 pop si
01c6 pop di
01c7 leave 
01c8 retf 
```

## Known declaration examples

- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd[];` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near win_hwnd[];` — src/recovered/wf_DoScenario-496dc7a0ac.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoNextWindow', 'offset': 6188, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c', 'size': 74}
- {'symbol': '_DoMenuEntry', 'offset': 6262, 'source': None, 'size': 503}
- {'symbol': 'MYENUMFUNC', 'offset': 7224, 'source': None, 'size': 48}
- {'symbol': '_RedrawWindows', 'offset': 7272, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c', 'size': 86}
