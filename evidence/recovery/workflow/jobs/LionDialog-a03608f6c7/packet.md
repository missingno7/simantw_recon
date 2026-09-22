# Recovery task _LionDialog

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 449 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xbf42]
000a cmp word ptr es:[0x85f8], 0
0010 jne 0x80b5
0012 jmp 0x825d
0015 push 0x1a00
0018 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_LockWin
001d add sp, 2
0020 push 0x23f0
0023 push 0x1a01
0026 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjBitmap
002b add sp, 4
002e push 0x1a00
0031 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0036 add sp, 2
0039 push word ptr [0xbcda]
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0042 add sp, 2
0045 mov word ptr [bp - 0xe], ax
0048 lea ax, [bp - 0x16]
004b push ss
004c push ax
004d push 0x1a01
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0055 add sp, 6
0058 mov ax, word ptr [bp - 0x14]
005b mov word ptr [bp - 0xa], ax
005e mov di, word ptr [bp - 0x16]
0061 push 0x7e
0063 push 0
0065 push 0x26
0067 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 106, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
006c add sp, 6
006f mov word ptr [bp - 0xc], di
0072 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 117, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySoundIsDone
0077 or ax, ax
0079 je 0x8112
007b mov si, 1
007e nop 
007f push cs
0080 call 0x9694 ; _MacTickCount
0083 add ax, 0x12c
0086 adc dx, 0
0089 mov word ptr [bp - 4], ax
008c mov word ptr [bp - 2], dx
008f nop 
0090 push cs
0091 call 0x9694 ; _MacTickCount
0094 add ax, 0x1e
0097 adc dx, 0
009a mov word ptr [bp - 8], ax
009d mov word ptr [bp - 6], dx
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
00a5 and byte ptr [0xce97], 0x7f ; _monoPat
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
00af or ax, ax
00b1 je 0x8156
00b3 jmp 0x8219
00b6 nop 
00b7 push cs
00b8 call 0x9694 ; _MacTickCount
00bb cmp dx, word ptr [bp - 2]
00be jle 0x8163
00c0 jmp 0x8219
00c3 jl 0x816d
00c5 cmp ax, word ptr [bp - 4]
00c8 jb 0x816d
00ca jmp 0x8219
00cd push 0x1a00
00d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 211, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00d5 add sp, 2
00d8 or ax, ax
00da jne 0x817f
00dc jmp 0x8219
00df nop 
00e0 push cs
00e1 call 0x9694 ; _MacTickCount
00e4 cmp dx, word ptr [bp - 6]
00e7 jge 0x818c
00e9 jmp 0x820d
00ec jg 0x8193
00ee cmp ax, word ptr [bp - 8]
00f1 jb 0x820d
00f3 nop 
00f4 push cs
00f5 call 0x9694 ; _MacTickCount
00f8 add ax, 0x1e
00fb adc dx, 0
00fe mov word ptr [bp - 8], ax
0101 mov word ptr [bp - 6], dx
0104 push word ptr [0xbcda]
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
010d add sp, 2
0110 cmp byte ptr [0xcc7e], 0xa ; _displayType
0115 jne 0x81c4
0117 lea ax, [si + 0x23f0]
011b push ax
011c push word ptr [bp - 0xa]
011f push di
0120 jmp 0x81e3
0122 nop 
0123 nop 
0124 lea ax, [si + 0x23f0]
0128 push ax
0129 mov es, word ptr [0xbf6c]
012d mov bx, si
012f shl bx, 2
0132 mov ax, word ptr es:[bx - 0x76a2]
0137 add ax, word ptr [bp - 0xa]
013a push ax
013b mov ax, word ptr es:[bx - 0x76a4]
0140 add ax, di
0142 push ax
0143 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 326, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMap
0148 add sp, 6
014b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 334, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0150 test si, 1
0154 je 0x8204
0156 push 0x7e
0158 push 0
015a push 0x25
015c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 351, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0161 add sp, 6
0164 inc si
0165 cmp si, 3
0168 jle 0x820d
016a mov si, 2
016d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 368, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
0172 or ax, ax
0174 jne 0x8219
0176 jmp 0x8156
0179 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 380, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
017e push 0x1a00
0181 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 388, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_UnlockWin
0186 add sp, 2
0189 cmp word ptr [bp - 0xe], 0
018d je 0x8248
018f push word ptr [bp - 0xe]
0192 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 403, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
0197 or ax, ax
0199 je 0x8248
019b push word ptr [bp - 0xe]
019e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 417, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
01a3 add sp, 2
01a6 jmp 0x824d
01a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 427, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
01ad push 0x1a00
01b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 435, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
01b5 add sp, 2
01b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 443, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UpdateAllWindows
01bd pop si
01be pop di
01bf leave 
01c0 retf 
```

## Known declaration examples

- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far UpdateAllWindows(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern unsigned char near monoPat;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern char near monoPat;` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern char near monoPat;` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_SetAlarmDropState_2_scaffold-bb12a76f6c.c
- `extern int far mySoundIsDone(void);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
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
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_YellowDeath', 'offset': 30534, 'source': None, 'size': 1904}
- {'symbol': '_SpecialXfer', 'offset': 32438, 'source': None, 'size': 490}
- {'symbol': '_YellowDialog', 'offset': 33378, 'source': None, 'size': 523}
- {'symbol': '_DoTroph', 'offset': 33902, 'source': None, 'size': 93}
