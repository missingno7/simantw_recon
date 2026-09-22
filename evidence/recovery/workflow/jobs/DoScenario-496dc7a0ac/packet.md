# Recovery task _DoScenario

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 275 bytes.

```asm
0000 enter 0x12, 0
0004 push si
0005 push 0x200
0008 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 11, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
000d add sp, 2
0010 push word ptr [0xbcaa]
0014 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0019 add sp, 2
001c mov si, ax
001e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
0023 nop 
0024 push cs
0025 call 0x9b9a ; _DialogClearWaitInit
0028 mov word ptr [bp - 2], si
002b lea ax, [bp - 0x12]
002e push ss
002f push ax
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetEvent
0035 add sp, 4
0038 or ax, ax
003a je 0x59db
003c cmp word ptr [bp - 6], 0x200
0041 jne 0x5a16
0043 nop 
0044 push cs
0045 call 0x9b6c ; _DialogClearWait
0048 nop 
0049 push cs
004a call 0x9c66 ; _DialogAbort
004d or ax, ax
004f jne 0x5a5a
0051 push 0xd
0053 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 84, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0058 test ah, 0x80
005b je 0x59c3
005d or si, si
005f jne 0x59fc
0061 jmp 0x5a90
0064 push si
0065 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 102, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
006a or ax, ax
006c jne 0x5a09
006e jmp 0x5a90
0071 push si
0072 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 117, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0077 add sp, 2
007a jmp 0x5a95
007d nop 
007e nop 
007f push cs
0080 call 0x9cd4 ; _DialogDone
0083 or si, si
0085 je 0x5a3e
0087 push si
0088 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 137, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
008d or ax, ax
008f je 0x5a3e
0091 push si
0092 push ds
0093 push 0x950
0096 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 151, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 25}}]
009b push si
009c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 159, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
00a1 add sp, 2
00a4 jmp 0x5a43
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
00ab push 0x200
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
00b3 add sp, 2
00b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 185, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UpdateAllWindows
00bb mov ax, word ptr [bp - 6]
00be pop si
00bf leave 
00c0 retf 
00c1 nop 
00c2 or si, si
00c4 je 0x5a74
00c6 push si
00c7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 200, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
00cc or ax, ax
00ce je 0x5a74
00d0 push si
00d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 212, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
00d6 add sp, 2
00d9 jmp 0x5a79
00db nop 
00dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 223, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
00e1 push 0x200
00e4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 231, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
00e9 add sp, 2
00ec nop 
00ed push cs
00ee call 0x9cd4 ; _DialogDone
00f1 mov ax, 0x205
00f4 pop si
00f5 leave 
00f6 retf 
00f7 nop 
00f8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 251, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
00fd push 0x200
0100 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 259, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
0105 add sp, 2
0108 nop 
0109 push cs
010a call 0x9cd4 ; _DialogDone
010d mov ax, 0x203
0110 pop si
0111 leave 
0112 retf 
```

## Known declaration examples

- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int flags);` — src/recovered/OpenMapWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitApplicationStuff', 'offset': 21802, 'source': 'src/initapp.c', 'size': 6}
- {'symbol': '_CalcScore', 'offset': 21808, 'source': None, 'size': 1127}
- {'symbol': '_DoWinHelp', 'offset': 23212, 'source': 'src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c', 'size': 30}
- {'symbol': '_win_DrawScoreWindow', 'offset': 23242, 'source': None, 'size': 480}
