# Recovery task _DrawSimPayoff

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 401 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 nop 
0007 push cs
0008 call 0x9918 ; _MapToYard
000b cmp word ptr [0xce82], 0 ; _YardMode
0010 je 0xcdc4
0012 push 0
0014 nop 
0015 push cs
0016 call 0x9f94 ; _SetYardMode
0019 add sp, 2
001c cmp word ptr [0xcc76], 0 ; _MapPlane
0021 je 0xcdd5
0023 push 0
0025 nop 
0026 push cs
0027 call 0xa5ca ; _SetMapPlane
002a add sp, 2
002d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 48, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawYard
0032 push 0
0034 push 0x96
0037 nop 
0038 push cs
0039 call 0x9620 ; _myDelay
003c add sp, 4
003f push 0x1a00
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_LockWin
0047 add sp, 2
004a push 0x3f48
004d push 0x1a01
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjBitmap
0055 add sp, 4
0058 push 0x1a00
005b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0060 add sp, 2
0063 lea ax, [bp - 0x16]
0066 push ss
0067 push ax
0068 push 0x1a01
006b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 110, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0070 add sp, 6
0073 push 0x1a00
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_UnlockWin
007b add sp, 2
007e mov di, 0x4e23
0081 mov word ptr [bp - 0xc], 1
0086 nop 
0087 push cs
0088 call 0x9694 ; _MacTickCount
008b add ax, 0x1e
008e adc dx, 0
0091 mov word ptr [bp - 6], ax
0094 mov word ptr [bp - 4], dx
0097 nop 
0098 push cs
0099 call 0x9694 ; _MacTickCount
009c add ax, 0x258
009f adc dx, 0
00a2 mov word ptr [bp - 0xa], ax
00a5 mov word ptr [bp - 8], dx
00a8 push 0xa
00aa nop 
00ab push cs
00ac call 0x9bfe ; _DialogWaitInit
00af add sp, 2
00b2 nop 
00b3 push cs
00b4 call 0x9c98 ; _DialogAbortOrCont
00b7 or ax, ax
00b9 je 0xce66
00bb jmp 0xcf18
00be nop 
00bf push cs
00c0 call 0x9694 ; _MacTickCount
00c3 cmp dx, word ptr [bp - 8]
00c6 jle 0xce73
00c8 jmp 0xcf18
00cb jl 0xce7d
00cd cmp ax, word ptr [bp - 0xa]
00d0 jb 0xce7d
00d2 jmp 0xcf18
00d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 216, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySongIsDone
00da or ax, ax
00dc je 0xce98
00de cmp di, 0x4e25
00e2 jge 0xce98
00e4 push 0x7e
00e6 push di
00e7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 234, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
00ec add sp, 4
00ef inc di
00f0 nop 
00f1 push cs
00f2 call 0x9694 ; _MacTickCount
00f5 cmp dx, word ptr [bp - 4]
00f8 jl 0xcf0c
00fa jg 0xcea9
00fc cmp ax, word ptr [bp - 6]
00ff jb 0xcf0c
0101 mov word ptr [bp - 0xe], di
0104 nop 
0105 push cs
0106 call 0x9694 ; _MacTickCount
0109 add ax, 8
010c adc dx, 0
010f mov word ptr [bp - 6], ax
0112 mov word ptr [bp - 4], dx
0115 mov si, 0x15da
0118 mov di, word ptr [bp - 0x16]
011b add di, word ptr [si]
011d mov ax, word ptr [si - 2]
0120 add ax, word ptr [bp - 0x14]
0123 mov word ptr [bp - 2], ax
0126 push word ptr [0xbcda]
012a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 301, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
012f add sp, 2
0132 mov ax, word ptr [bp - 0xc]
0135 add ax, 0x3f52
0138 push ax
0139 push word ptr [bp - 2]
013c push di
013d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 320, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMap
0142 add sp, 6
0145 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 328, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
014a add si, 4
014d cmp si, 0x15f2
0151 jb 0xcec0
0153 inc word ptr [bp - 0xc]
0156 cmp word ptr [bp - 0xc], 3
015a jl 0xcf09
015c mov word ptr [bp - 0xc], 0
0161 mov di, word ptr [bp - 0xe]
0164 nop 
0165 push cs
0166 call 0x9c98 ; _DialogAbortOrCont
0169 or ax, ax
016b jne 0xcf18
016d jmp 0xce66
0170 nop 
0171 push cs
0172 call 0x9cd4 ; _DialogDone
0175 push 0
0177 push 0x12c
017a nop 
017b push cs
017c call 0x9620 ; _myDelay
017f add sp, 4
0182 push 0x1a00
0185 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 392, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
018a add sp, 2
018d pop si
018e pop di
018f leave 
0190 retf 
```

## Known declaration examples

- `extern void far DialogDone(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far MapToYard(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far SetYardMode(int mode);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far SetYardMode(int mode);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern int near YardMode;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far myBeginSong(unsigned int song, unsigned int priority);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSong(unsigned int song, unsigned int mode);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far myDelay(unsigned long ticks);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far win_Close(int objectNumber);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far win_DrawBitMap(unsigned int bitmapOffset, int bitmapArgument, int value);` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern int far win_DrawBitMap(unsigned int bitmap, unsigned int bitmapMask, int bitmapNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int flags);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetTriLatPoint', 'offset': 52134, 'source': None, 'size': 221}
- {'symbol': '_initControls', 'offset': 52356, 'source': 'src/recovered/wf_tu_simant_B324_initControls_1_scaffold-03091459d8.c', 'size': 291}
- {'symbol': '_AboutDialog', 'offset': 53050, 'source': None, 'size': 1192}
- {'symbol': '_ShowIntro', 'offset': 54242, 'source': None, 'size': 290}
