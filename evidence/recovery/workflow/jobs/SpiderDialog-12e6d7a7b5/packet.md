# Recovery task _SpiderDialog

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 537 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 push 0x1a00
0009 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 12, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_LockWin
000e add sp, 2
0011 push 0x2ee0
0014 push 0x1a01
0017 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 26, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjBitmap
001c add sp, 4
001f push 0x1a00
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0027 add sp, 2
002a push word ptr [0xbcda]
002e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0033 add sp, 2
0036 mov word ptr [bp - 0xa], ax
0039 lea ax, [bp - 0x12]
003c push ss
003d push ax
003e push 0x1a01
0041 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 68, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0046 add sp, 6
0049 push 0x7e
004b xor si, si
004d push si
004e push 0x2d
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0055 add sp, 6
0058 nop 
0059 push cs
005a call 0x9694 ; _MacTickCount
005d nop 
005e push cs
005f call 0x9694 ; _MacTickCount
0062 add ax, 8
0065 adc dx, si
0067 mov word ptr [bp - 4], ax
006a mov word ptr [bp - 2], dx
006d push 8
006f nop 
0070 push cs
0071 call 0x9bfe ; _DialogWaitInit
0074 add sp, 2
0077 mov es, word ptr [0xbf02]
007b mov di, word ptr es:[0x87fc]
0080 add di, 0x2ee1
0084 add word ptr [bp - 0x12], 0x2e
0088 add word ptr [bp - 0x10], 0x4d
008c and byte ptr [0xce97], 0x7f ; _monoPat
0091 nop 
0092 push cs
0093 call 0x9c98 ; _DialogAbortOrCont
0096 or ax, ax
0098 jne 0x684e
009a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 157, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
009f or ax, ax
00a1 jne 0x684e
00a3 nop 
00a4 push cs
00a5 call 0x9694 ; _MacTickCount
00a8 cmp dx, word ptr [bp - 2]
00ab jl 0x6845
00ad jg 0x67ee
00af cmp ax, word ptr [bp - 4]
00b2 jb 0x6845
00b4 nop 
00b5 push cs
00b6 call 0x9694 ; _MacTickCount
00b9 add ax, 8
00bc adc dx, 0
00bf mov word ptr [bp - 4], ax
00c2 mov word ptr [bp - 2], dx
00c5 inc si
00c6 cmp si, 3
00c9 jle 0x6814
00cb push 0x7e
00cd xor si, si
00cf push si
00d0 push 0x2d
00d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00d7 add sp, 6
00da mov es, word ptr [0xbf02]
00de mov bx, si
00e0 shl bx, 1
00e2 mov di, word ptr es:[bx - 0x7804]
00e7 add di, 0x2ee1
00eb push word ptr [0xbcda]
00ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 242, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
00f4 add sp, 2
00f7 push di
00f8 push word ptr [bp - 0x10]
00fb push word ptr [bp - 0x12]
00fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 257, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMap
0103 add sp, 6
0106 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 265, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
010b nop 
010c push cs
010d call 0x9c98 ; _DialogAbortOrCont
0110 or ax, ax
0112 je 0x67d4
0114 nop 
0115 push cs
0116 call 0x9cd4 ; _DialogDone
0119 push 2
011b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 286, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0120 add sp, 2
0123 cmp ax, 1
0126 sbb si, si
0128 add si, 0x2740
012c or di, di
012e je 0x688a
0130 push word ptr [0xbcda]
0134 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0139 add sp, 2
013c push di
013d push word ptr [bp - 0x10]
0140 push word ptr [bp - 0x12]
0143 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 326, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawBitMap
0148 add sp, 6
014b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 334, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0150 nop 
0151 push cs
0152 call 0 ; _StopSimulation
0155 mov word ptr [bp - 2], 0
015a push si
015b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 350, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _LoadStringAnt
0160 add sp, 2
0163 mov word ptr [bp - 6], ax
0166 mov word ptr [bp - 4], dx
0169 or dx, ax
016b je 0x68cf
016d les bx, ptr [bp - 6]
0170 mov ax, word ptr es:[bx + 2]
0174 or ax, word ptr es:[bx]
0177 je 0x68cd
0179 mov word ptr [bp - 8], si
017c mov ds, word ptr [bp - 4]
017f mov cx, word ptr [bp - 2]
0182 inc cx
0183 add bx, 4
0186 mov ax, word ptr [bx + 2]
0189 or ax, word ptr [bx]
018b jne 0x68bc
018d mov word ptr [bp - 2], cx
0190 mov si, word ptr [bp - 8]
0193 push ss
0194 pop ds
0195 push 1
0197 push 0
0199 push word ptr [bp - 2]
019c push word ptr [bp - 4]
019f push word ptr [bp - 6]
01a2 nop 
01a3 push cs
01a4 call 0x62bc ; _PictureDialog
01a7 add sp, 0xa
01aa mov ax, word ptr [bp - 4]
01ad or ax, word ptr [bp - 6]
01b0 je 0x6905
01b2 push word ptr [bp - 4]
01b5 push word ptr [bp - 6]
01b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 443, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _free
01bd add sp, 4
01c0 push 4
01c2 push si
01c3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 454, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
01c8 add sp, 4
01cb nop 
01cc push cs
01cd call 0x34 ; _RestartSimulation
01d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 467, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
01d5 push 0x1a00
01d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 475, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_UnlockWin
01dd add sp, 2
01e0 cmp word ptr [bp - 0xa], 0
01e4 je 0x693a
01e6 push word ptr [bp - 0xa]
01e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 490, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
01ee or ax, ax
01f0 je 0x693a
01f2 push word ptr [bp - 0xa]
01f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 504, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
01fa add sp, 2
01fd jmp 0x693f
01ff nop 
0200 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 515, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
0205 push 0x1a00
0208 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 523, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
020d add sp, 2
0210 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 531, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UpdateAllWindows
0215 pop si
0216 pop di
0217 leave 
0218 retf 
```

## Known declaration examples

- `extern void far DialogDone(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern char far * far * far LoadStringAnt(int object);` — src/recovered/wf_PrepareStrings-9dd732cc1e.c
- `extern char far * far * far LoadStringAnt(int object);` — src/recovered/wf_initStuff-9712c2c2ff.c
- `extern char far * far * far LoadStringAnt(int object);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far PictureDialog(char far * far *strings, int count, int picture, int force);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far RestartSimulation(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_AddRocks-01eddceee1.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern void far StopSimulation(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far UpdateAllWindows(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far UpdateAllWindows(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far db_PurgeObject(int object, int kind);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void free(void far *block);` — src/recovered/mem_free_wrapper.c
- `extern void far free(void far *block);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern unsigned char near monoPat;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern char near monoPat;` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern char near monoPat;` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far win_Close(int objectNumber);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Close(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far win_DrawBitMap(unsigned int bitmapOffset, int bitmapArgument, int value);` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern int far win_DrawBitMap(unsigned int bitmap, unsigned int bitmapMask, int bitmapNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern int far win_Events(void);` — src/recovered/wf_myDelay-ac936e115a.c
- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int object, int x, int y);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawEndGameWindow', 'offset': 25812, 'source': None, 'size': 301}
- {'symbol': '_EndGameDialog', 'offset': 26114, 'source': None, 'size': 312}
- {'symbol': '_CustomerIDDialog', 'offset': 26964, 'source': None, 'size': 227}
- {'symbol': '_processEdit', 'offset': 27192, 'source': None, 'size': 1168}
