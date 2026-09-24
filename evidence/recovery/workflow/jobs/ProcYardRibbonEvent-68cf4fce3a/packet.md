# Recovery task _ProcYardRibbonEvent

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 714 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov si, word ptr [bp + 6]
0007 mov es, word ptr [bp + 8]
000a mov ax, word ptr es:[si + 0xc]
000e sub ax, 0x2302
0011 cmp ax, 0x22
0014 jbe 0xa6e7
0016 jmp 0xa995
0019 shl ax, 1
001b xchg bx, ax
001c jmp word ptr cs:[bx - 0x5910]
0021 nop 
0022 dw offset 0xa736
0024 dw offset 0xa758
0026 dw offset 0xa78e
0028 dw offset 0xa7ac
002a dw offset 0xa7ca
002c dw offset 0xa872
002e dw offset 0xa8ea
0030 dw offset 0xa8f6
0032 dw offset 0xa90a
0034 dw offset 0xa918
0036 dw offset 0xa918
0038 dw offset 0xa918
003a dw offset 0xa918
003c dw offset 0xa918
003e dw offset 0xa918
0040 dw offset 0xa918
0042 dw offset 0xa918
0044 dw offset 0xa92e
0046 dw offset 0xa92e
0048 dw offset 0xa92e
004a dw offset 0xa92e
004c dw offset 0xa92e
004e dw offset 0xa92e
0050 dw offset 0xa92e
0052 dw offset 0xa995
0054 dw offset 0xa995
0056 dw offset 0xa995
0058 dw offset 0xa995
005a dw offset 0xa995
005c dw offset 0xa995
005e dw offset 0xa995
0060 dw offset 0xa995
0062 dw offset 0xa995
0064 dw offset 0xa995
0066 dw offset 0xa93e
0068 push 0x1900
006b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 110, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0070 add sp, 2
0073 or ax, ax
0075 jne 0xa750
0077 push 0x1900
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
007f add sp, 2
0082 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YardToMap
0087 jmp 0xa995
008a push 0x1900
008d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 144, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0092 add sp, 2
0095 or ax, ax
0097 jne 0xa772
0099 push 0x1900
009c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 159, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
00a1 add sp, 2
00a4 cmp word ptr [0xce82], 2 ; _YardMode
00a9 jge 0xa78a
00ab mov ax, word ptr [0xce82] ; _YardMode
00ae xor al, 1
00b0 push ax
00b1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 180, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetYardMode
00b6 add sp, 2
00b9 pop si
00ba leave 
00bb retf 
00bc push 0
00be jmp 0xa77f
00c0 push 0x1900
00c3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 198, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00c8 add sp, 2
00cb or ax, ax
00cd jne 0xa7a8
00cf push 0x1900
00d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
00d7 add sp, 2
00da push 2
00dc jmp 0xa77f
00de push 0x1900
00e1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 228, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00e6 add sp, 2
00e9 or ax, ax
00eb jne 0xa7c6
00ed push 0x1900
00f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
00f5 add sp, 2
00f8 push 3
00fa jmp 0xa77f
00fc mov es, word ptr [0xc196]
0100 cmp word ptr es:[0x80b4], 2
0106 je 0xa808
0108 push 0x7e
010a push 0
010c push 1
010e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0113 add sp, 6
0116 push 1
0118 push 0
011a push 0xb4
011d mov es, word ptr [0xc198]
0121 les bx, ptr es:[0x737a]
0126 push word ptr es:[bx + 0x3e]
012a push word ptr es:[bx + 0x3c]
012e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 305, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _EditMessage
0133 add sp, 0xa
0136 pop si
0137 leave 
0138 retf 
0139 nop 
013a mov dx, word ptr [0xac9a]
013e add dx, word ptr [0xac9c]
0142 mov bx, word ptr [0xcc84] ; _MeType
0146 cmp bx, 0x40
0149 je 0xa81e
014b cmp bx, 0x20
014e jne 0xa81f
0150 dec dx
0151 or dx, dx
0153 jg 0xa84c
0155 push 0x7e
0157 push 0
0159 push 1
015b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 350, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0160 add sp, 6
0163 push 1
0165 push 0
0167 push 0xb4
016a mov es, word ptr [0xc198]
016e les bx, ptr es:[0x737a]
0173 push word ptr es:[bx + 0x16]
0177 push word ptr es:[bx + 0x14]
017b jmp 0xa7fc
017d nop 
017e mov es, word ptr [0xc19a]
0182 mov word ptr es:[0x7c44], 0xc8
0189 push 1
018b push 0
018d push 0xb4
0190 mov es, word ptr [0xc198]
0194 les bx, ptr es:[0x737a]
0199 push word ptr es:[bx + 0x1a]
019d push word ptr es:[bx + 0x18]
01a1 jmp 0xa7fc
01a3 nop 
01a4 push 0x1900
01a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 426, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01ac add sp, 2
01af or ax, ax
01b1 jne 0xa88c
01b3 push 0x1900
01b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 441, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
01bb add sp, 2
01be push 0x230a
01c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 452, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelected
01c6 add sp, 2
01c9 push 0x2307
01cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 463, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelected
01d1 add sp, 2
01d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 471, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PlaceQueenInYard
01d9 push 0x1900
01dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 479, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01e1 add sp, 2
01e4 or ax, ax
01e6 je 0xa8de
01e8 push 1
01ea push word ptr [0xce82] ; _YardMode
01ee nop 
01ef push cs
01f0 call 0xb462 ; _Draw_SimYard
01f3 add sp, 4
01f6 mov word ptr [0x18b4], 0
01fc push word ptr [0xbcd8]
0200 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 513, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
0205 mov word ptr [0x18b4], 1
020b nop 
020c push cs
020d call 0xacd8 ; _DrawYardData
0210 push 0x2307
0213 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 534, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjUnselected
0218 jmp 0xa784
021b nop 
021c push 0x2308
021f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 546, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoWinHelp
0224 jmp 0xa784
0227 nop 
0228 mov es, word ptr [0xc19c]
022c mov word ptr es:[0x836e], 1
0233 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 566, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _UpdateLayQueenModeDisplay
0238 pop si
0239 leave 
023a retf 
023b nop 
023c mov es, word ptr [0xc19c]
0240 mov word ptr es:[0x836e], 0
0247 jmp 0xa901
0249 nop 
024a mov ax, word ptr es:[si + 0xc]
024e mov cx, ax
0250 sub ax, 0x230b
0253 push ax
0254 push cx
0255 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 600, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoUserButton
025a add sp, 4
025d pop si
025e leave 
025f retf 
0260 mov ax, word ptr es:[si + 0xc]
0264 sub ax, 0x2313
0267 push ax
0268 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 619, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoBookMark
026d jmp 0xa784
0270 push 0x231f
0273 mov ax, si
0275 mov dx, es
0277 add ax, 8
027a push dx
027b push ax
027c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 639, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsPointInObj
0281 add sp, 6
0284 or ax, ax
0286 je 0xa968
0288 push 0x231f
028b push word ptr [bp + 8]
028e push si
028f nop 
0290 push cs
0291 call 0x6e72 ; _DoHealthSetY
0294 add sp, 6
0297 pop si
0298 leave 
0299 retf 
029a push 0x2320
029d mov ax, si
029f mov dx, word ptr [bp + 8]
02a2 add ax, 8
02a5 push dx
02a6 push ax
02a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 682, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsPointInObj
02ac add sp, 6
02af or ax, ax
02b1 je 0xa990
02b3 push 0x2320
02b6 mov ax, word ptr [bp + 8]
02b9 push ax
02ba push si
02bb nop 
02bc push cs
02bd call 0x6e1c ; _DoWarnSetB
02c0 jmp 0xa962
02c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 709, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DrawCastePopUp
02c7 pop si
02c8 leave 
02c9 retf 
```

## Known declaration examples

- `extern void far DoHealthSetY(struct EditEvent far *event, int mode);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far DoWarnSetB(struct EditEvent far *event, int mode);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far DoWinHelp(int mode);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far DrawYardData(void);` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far Draw_SimYard(int mode, int selector);` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far EditMessage(int first,int second,int width,int fourth,int fifth);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern int near MeType;` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int near MeType;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far SetYardMode(int mode);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far SetYardMode(int mode);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far YardToMap(void);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern void far YardToMap(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_MakeObjSelected(int object);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far win_MakeObjSelected(int object);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int object, int x, int y);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CheckRainArray', 'offset': 42172, 'source': 'src/recovered/wf_CheckRainArray-5188fd7161.c', 'size': 97}
- {'symbol': '_ProcYardEvent', 'offset': 42270, 'source': None, 'size': 432}
- {'symbol': '_DrawYardCursor', 'offset': 43416, 'source': 'src/recovered/wf_tu_antedit_A998_DrawYardCursor_3_scaffold-c71c8e4e09.c', 'size': 36}
- {'symbol': '_EraseYardCursor', 'offset': 43452, 'source': 'src/recovered/wf_tu_antedit_A998_DrawYardCursor_3_scaffold-c71c8e4e09.c', 'size': 36}
