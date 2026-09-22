# Recovery task _YellowDialog

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 523 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xbf42]
000a cmp word ptr es:[0x85f8], 0
0010 jne 0x8277
0012 jmp 0x8469
0015 mov di, word ptr [bp + 6]
0018 push 0x1a00
001b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_LockWin
0020 add sp, 2
0023 push di
0024 push 0x1a01
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 42, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjBitmap
002c add sp, 4
002f push 0x1a00
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0037 add sp, 2
003a push word ptr [0xbcda]
003e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 65, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0043 add sp, 2
0046 mov word ptr [bp - 4], ax
0049 lea ax, [bp - 0xc]
004c push ss
004d push ax
004e push 0x1a01
0051 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 84, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0056 add sp, 6
0059 mov si, word ptr [bp - 0xa]
005c mov ax, word ptr [bp - 0xc]
005f mov word ptr [bp - 2], ax
0062 mov ax, di
0064 sub ax, 0x238c
0067 je 0x8321
0069 dec ax
006a je 0x82da
006c sub ax, 9
006f jne 0x82d6
0071 jmp 0x83dc
0074 jmp 0x837c
0077 nop 
0078 push word ptr [0xbcda]
007c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0081 add sp, 2
0084 push 4
0086 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 137, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
008b add sp, 2
008e mov bx, word ptr [bp + 8]
0091 shl bx, 2
0094 mov es, word ptr [0xbf66]
0098 les si, ptr es:[0x737a]
009d push word ptr es:[bx + si + 0x5e]
00a1 push word ptr es:[bx + si + 0x5c]
00a5 push 0x1a02
00a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 171, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
00ad add sp, 6
00b0 push 0
00b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 181, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
00b7 add sp, 2
00ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
00bf test byte ptr [0xcc7e], 1 ; _displayType
00c4 je 0x836f
00c6 push word ptr [0xbcda]
00ca lcall <resolved loader operand; see bindings> ; [{'operand_offset': 205, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
00cf add sp, 2
00d2 push 4
00d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 215, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
00d9 add sp, 2
00dc mov bx, word ptr [bp + 8]
00df shl bx, 2
00e2 mov es, word ptr [0xbf66]
00e6 les si, ptr es:[0x737a]
00eb push word ptr es:[bx + si + 0x5e]
00ef push word ptr es:[bx + si + 0x5c]
00f3 push 0x1a02
00f6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 249, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
00fb add sp, 6
00fe push 0
0100 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 259, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0105 add sp, 2
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
010d push 0
010f push 0x12c
0112 nop 
0113 push cs
0114 call 0x9620 ; _myDelay
0117 add sp, 4
011a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 285, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
011f or ax, ax
0121 je 0x8388
0123 jmp 0x844e
0126 push 3
0128 nop 
0129 push cs
012a call 0x9bfe ; _DialogWaitInit
012d add sp, 2
0130 mov si, word ptr [bp - 4]
0133 nop 
0134 push cs
0135 call 0x9c98 ; _DialogAbortOrCont
0138 or ax, ax
013a jne 0x83a7
013c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 319, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
0141 or ax, ax
0143 je 0x8395
0145 nop 
0146 push cs
0147 call 0x9cd4 ; _DialogDone
014a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 333, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
014f push 0x1a00
0152 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 341, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_UnlockWin
0157 add sp, 2
015a or si, si
015c jne 0x83c3
015e jmp 0x8454
0161 push si
0162 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 355, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
0167 or ax, ax
0169 jne 0x83d0
016b jmp 0x8454
016e push si
016f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 370, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0174 add sp, 2
0177 jmp 0x8459
0179 nop 
017a push 0x7e
017c push 0
017e push 0x2a
0180 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 387, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0185 add sp, 6
0188 push 0
018a push 0x2d
018c nop 
018d push cs
018e call 0x9620 ; _myDelay
0191 add sp, 4
0194 push 0x1a00
0197 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 410, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
019c add sp, 2
019f or ax, ax
01a1 je 0x8438
01a3 push word ptr [0xbcda]
01a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 426, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
01ac add sp, 2
01af and byte ptr [0xce97], 0x7f ; _monoPat
01b4 push 0x2397
01b7 mov es, word ptr [0xbf6e]
01bb add si, word ptr es:[0x896e]
01c0 push si
01c1 mov ax, word ptr es:[0x896c]
01c5 add ax, word ptr [bp - 2]
01c8 push ax
01c9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 460, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMap
01ce add sp, 6
01d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 468, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
01d6 push 0x7e
01d8 push 0
01da push 0x2d
01dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 479, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
01e1 add sp, 6
01e4 push 0
01e6 push 0x2d
01e8 jmp 0x8374
01eb nop 
01ec mov si, word ptr [bp - 4]
01ef jmp 0x83ac
01f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 501, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
01f7 push 0x1a00
01fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 509, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
01ff add sp, 2
0202 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 517, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UpdateAllWindows
0207 pop si
0208 pop di
0209 leave 
020a retf 
```

## Known declaration examples

- `extern void far DialogDone(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far UpdateAllWindows(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern unsigned char near monoPat;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern char near monoPat;` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern char near monoPat;` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_SetAlarmDropState_2_scaffold-bb12a76f6c.c
- `extern void far myDelay(unsigned long ticks);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far win_Close(int objectNumber);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far win_DrawBitMap(unsigned int bitmapOffset, int bitmapArgument, int value);` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern int far win_DrawBitMap(unsigned int bitmap, unsigned int bitmapMask, int bitmapNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern int far win_Events(void);` — src/recovered/wf_myDelay-ac936e115a.c
- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int flags);` — src/recovered/OpenMapWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SpecialXfer', 'offset': 32438, 'source': None, 'size': 490}
- {'symbol': '_LionDialog', 'offset': 32928, 'source': None, 'size': 449}
- {'symbol': '_DoTroph', 'offset': 33902, 'source': None, 'size': 93}
- {'symbol': '_SetAlarmDropState', 'offset': 33996, 'source': 'src/recovered/wf_tu_simant_6A38_SetAlarmDropState_2_scaffold-bb12a76f6c.c', 'size': 149}
