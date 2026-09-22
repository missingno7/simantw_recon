# Recovery task _EndGameDialog

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 312 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 xor si, si
0008 mov es, word ptr [0xbefa]
000c cmp word ptr es:[0x85f4], si
0011 je 0x6635
0013 mov es, word ptr [0xbefe]
0017 cmp word ptr es:[0x9cea], si
001c jne 0x6628
001e push 0x7e
0020 push 0x271a
0023 jmp 0x662d
0025 nop 
0026 push 0x7e
0028 push 0x2718
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
0030 add sp, 4
0033 push 1
0035 push -1
0037 push -2
0039 push 0
003b push 0
003d nop 
003e push cs
003f call 0x92c0 ; _EditMessage
0042 add sp, 0xa
0045 push 0x400
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
004d add sp, 2
0050 push word ptr [0xbcae]
0054 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0059 add sp, 2
005c mov word ptr [bp - 4], ax
005f mov word ptr [bp - 2], 0
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 103, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UpdateAllWindows
0069 push 0x401
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelectable
0071 add sp, 2
0074 push 0x400
0077 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 122, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
007c add sp, 2
007f or ax, ax
0081 je 0x66d7
0083 mov di, word ptr [bp - 2]
0086 or si, si
0088 jne 0x66d7
008a lea ax, [bp - 0x14]
008d push ss
008e push ax
008f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetEvent
0094 add sp, 4
0097 or ax, ax
0099 je 0x66a7
009b cmp word ptr [bp - 8], 0x401
00a0 jne 0x66a7
00a2 mov si, 1
00a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 168, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySongIsDone
00aa or ax, ax
00ac je 0x66c8
00ae or di, di
00b0 jne 0x66c8
00b2 inc di
00b3 push 0x7e
00b5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 184, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
00ba add ax, 0x2713
00bd push ax
00be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 193, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
00c3 add sp, 4
00c6 push 0x400
00c9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 204, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00ce add sp, 2
00d1 or ax, ax
00d3 jne 0x6688
00d5 cmp word ptr [bp - 4], 0
00d9 je 0x6702
00db push word ptr [bp - 4]
00de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 223, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
00e3 or ax, ax
00e5 je 0x6702
00e7 push word ptr [bp - 4]
00ea push ds
00eb push 0x969
00ee lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 25}}]
00f3 push word ptr [bp - 4]
00f6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 249, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
00fb add sp, 2
00fe jmp 0x6707
0100 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 259, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
0105 push 0x400
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
010d add sp, 2
0110 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 275, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UpdateAllWindows
0115 nop 
0116 push cs
0117 call 0x9ce6 ; _DialogAbortAll
011a push 0
011c nop 
011d push cs
011e call 0xd6dc ; _NewGame
0121 add sp, 2
0124 or ax, ax
0126 jge 0x6736
0128 nop 
0129 push cs
012a call 0x50 ; _CleanUp
012d push 0
012f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 304, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 6}}]
0134 pop si
0135 pop di
0136 leave 
0137 retf 
```

## Known declaration examples

- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far EditMessage(int first,int second,int width,int fourth,int fifth);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirB-2bfd4e5303.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirR-414ecd2b67.c
- `extern int far SRand2(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far UpdateAllWindows(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far myBeginSong(unsigned int song, unsigned int priority);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSong(unsigned int song, unsigned int mode);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far win_Close(int objectNumber);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far win_GetEvent(struct DialogEvent far *event);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int flags);` — src/recovered/OpenMapWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PictureDialog', 'offset': 25276, 'source': None, 'size': 535}
- {'symbol': '_win_DrawEndGameWindow', 'offset': 25812, 'source': None, 'size': 301}
- {'symbol': '_SpiderDialog', 'offset': 26426, 'source': None, 'size': 537}
- {'symbol': '_CustomerIDDialog', 'offset': 26964, 'source': None, 'size': 227}
