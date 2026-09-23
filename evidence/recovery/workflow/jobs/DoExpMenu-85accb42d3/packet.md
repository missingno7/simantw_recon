# Recovery task _DoExpMenu

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 320 bytes.

```asm
0000 enter 0x18, 0
0004 push di
0005 push si
0006 mov si, 0xffff
0009 mov es, word ptr [0xc256]
000d mov di, word ptr es:[0x9c28]
0012 mov ax, word ptr [bp + 6]
0015 mov word ptr [bp - 8], ax
0018 mov ax, word ptr [bp + 8]
001b mov word ptr [bp - 6], ax
001e cmp word ptr [0xcd76], 0 ; _ribbonBarWnd
0023 jne 0x6f2c
0025 push word ptr [0xcd78] ; _rootWnd
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _MyGetTopWindow
002e add sp, 2
0031 push ax
0032 lea ax, [bp - 8]
0035 push ss
0036 push ax
0037 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 28}}]
003c push word ptr [0xcd78] ; _rootWnd
0040 lea ax, [bp - 8]
0043 push ss
0044 push ax
0045 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 70, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 29}}]
004a push word ptr [bp - 6]
004d push word ptr [bp - 8]
0050 push 0x900
0053 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0058 add sp, 6
005b push word ptr [0xbcb8]
005f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 98, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0064 add sp, 2
0067 mov es, word ptr [0xc258]
006b mov ax, word ptr es:[0x79e2]
006f add ax, 0x902
0072 push ax
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; __win_SetProxItem
0078 add sp, 2
007b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 126, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ButtonHeldInit
0080 push 1
0082 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetPause
0087 add sp, 2
008a mov word ptr [bp - 4], di
008d mov word ptr [bp - 2], si
0090 push 0x900
0093 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 150, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0098 add sp, 2
009b or ax, ax
009d je 0x6fce
009f lea ax, [bp - 0x18]
00a2 push ss
00a3 push ax
00a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 167, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetEvent
00a9 add sp, 4
00ac or ax, ax
00ae je 0x6f72
00b0 cmp word ptr [0x1bbc], -1 ; _openSub
00b5 jne 0x6faa
00b7 cmp word ptr [bp - 0xc], 0x902
00bc jb 0x6fd3
00be mov si, word ptr [bp - 0xc]
00c1 sub si, 0x902
00c5 jmp 0x6fd3
00c7 nop 
00c8 test byte ptr [bp - 0xc], 0xff
00cc je 0x6fd3
00ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetProxEvent
00d3 mov si, ax
00d5 and si, 0xff
00d9 sub si, 2
00dc mov al, byte ptr [bp - 0xc]
00df sub al, 2
00e1 mov es, word ptr [0xc25a]
00e5 mov byte ptr es:[si - 0x7a00], al
00ea jmp 0x6fd3
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ButtonHeldEnd
00f1 push di
00f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 245, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetPause
00f7 add sp, 2
00fa push 1
00fc push -1
00fe push -2
0100 push 0
0102 push 0
0104 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 263, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _EditMessage
0109 add sp, 0xa
010c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 271, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
0111 cmp word ptr [0x1bbc], -1 ; _openSub
0116 je 0x7006
0118 push word ptr [0x1bbc] ; _openSub
011c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 287, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
0121 add sp, 2
0124 push 0x900
0127 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 298, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
012c add sp, 2
012f mov es, word ptr [0xc25c]
0133 mov word ptr es:[0xbe10], 0xffff
013a mov ax, si
013c pop si
013d pop di
013e leave 
013f retf 
```

## Known declaration examples

- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far EditMessage(int first,int second,int width,int fourth,int fifth);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far SetPause(int pause);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near ribbonBarWnd;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern void far win_Close(int objectNumber);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far win_GetEvent(struct DialogEvent far *event);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int flags);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoHealthSetY', 'offset': 28274, 'source': None, 'size': 86}
- {'symbol': '_DoTab', 'offset': 28360, 'source': 'src/recovered/DoTab.c', 'size': 26}
- {'symbol': '_processExp', 'offset': 28706, 'source': None, 'size': 604}
- {'symbol': '_DoTool', 'offset': 29310, 'source': 'src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c', 'size': 358}
