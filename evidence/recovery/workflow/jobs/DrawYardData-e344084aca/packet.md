# Recovery task _DrawYardData

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 460 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 push 0x2300
0009 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 12, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
000e add sp, 2
0011 or ax, ax
0013 jne 0xacf0
0015 jmp 0xaea0
0018 push word ptr [0xbcec]
001c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 31, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0021 add sp, 2
0024 mov di, 1
0027 cmp word ptr [0xac82], di ; _BpopT
002b jle 0xad09
002d mov di, word ptr [0xac82] ; _BpopT
0031 cmp word ptr [0xac84], di ; _RpopT
0035 jle 0xad13
0037 mov di, word ptr [0xac84] ; _RpopT
003b cmp word ptr [0xac84], 0 ; _RpopT
0040 jne 0xad1e
0042 xor si, si
0044 jmp 0xad22
0046 mov si, word ptr [0xac88] ; _HealthR
004a push 3
004c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 79, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0051 add sp, 2
0054 push word ptr [0xac82] ; _BpopT
0058 push ds
0059 push 0x18c2
005c push 0x231b
005f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 98, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
0064 add sp, 8
0067 push word ptr [0xac84] ; _RpopT
006b push ds
006c push 0x18c6
006f push 0x231c
0072 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 117, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
0077 add sp, 8
007a push 0
007c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0081 add sp, 2
0084 push 0
0086 push 0x64
0088 push word ptr [0xac8a] ; _MeHealth
008c push 0
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0093 push dx
0094 push ax
0095 push 0x231f
0098 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 155, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawHBar
009d add sp, 6
00a0 push 0
00a2 push 0x64
00a4 push word ptr [0xac86] ; _HealthB
00a8 push 0
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00af push dx
00b0 push ax
00b1 push 0x2320
00b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 183, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawHBar
00b9 add sp, 6
00bc mov ax, di
00be cdq 
00bf push dx
00c0 push ax
00c1 push word ptr [0xac82] ; _BpopT
00c5 push 0
00c7 mov word ptr [bp - 0xc], di
00ca mov word ptr [bp - 0xa], dx
00cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 208, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00d2 push dx
00d3 push ax
00d4 push 0x2322
00d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawHBar
00dc add sp, 6
00df push 0
00e1 push 0x64
00e3 push si
00e4 push 0
00e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 233, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00eb push dx
00ec push ax
00ed push 0x2321
00f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawHBar
00f5 add sp, 6
00f8 push word ptr [bp - 0xa]
00fb push di
00fc push word ptr [0xac84] ; _RpopT
0100 push 0
0102 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0107 push dx
0108 push ax
0109 push 0x2323
010c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 271, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawHBar
0111 add sp, 6
0114 lea ax, [bp - 8]
0117 push ss
0118 push ax
0119 push 0x2320
011c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 287, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0121 add sp, 6
0124 push word ptr [bp - 2]
0127 mov ax, word ptr [bp - 4]
012a sub ax, word ptr [bp - 8]
012d mov es, word ptr [0xc1b2]
0131 imul word ptr es:[0x769c]
0136 mov cx, 0x64
0139 cdq 
013a idiv cx
013c add ax, word ptr [bp - 8]
013f push ax
0140 push word ptr [bp - 6]
0143 push ax
0144 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 327, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GInvBox
0149 add sp, 8
014c lea ax, [bp - 8]
014f push ss
0150 push ax
0151 push 0x231f
0154 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 343, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0159 add sp, 6
015c push word ptr [bp - 2]
015f mov ax, word ptr [bp - 4]
0162 sub ax, word ptr [bp - 8]
0165 mov es, word ptr [0xc1b4]
0169 imul word ptr es:[0x9bec]
016e mov cx, 0x64
0171 cdq 
0172 idiv cx
0174 add ax, word ptr [bp - 8]
0177 push ax
0178 push word ptr [bp - 6]
017b push ax
017c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 383, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GInvBox
0181 add sp, 8
0184 mov ax, word ptr [0xac8c] ; _QueenStorageB
0187 or ax, ax
0189 jge 0xae65
018b xor ax, ax
018d push ax
018e push ds
018f push 0x18ca
0192 push 0x231a
0195 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 408, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
019a add sp, 8
019d push word ptr [0xac90] ; _ColonyTotalBlack
01a1 push ds
01a2 push 0x18cd
01a5 push 0x231d
01a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 427, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
01ad add sp, 8
01b0 push word ptr [0xac92] ; _ColonyTotalRed
01b4 push ds
01b5 push 0x18d0
01b8 push 0x231e
01bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 446, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
01c0 add sp, 8
01c3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 454, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
01c8 pop si
01c9 pop di
01ca leave 
01cb retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int near BpopT;` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void GInvBox(int,int,int,int);` — src/recovered/GRectInv.c
- `extern void far GInvBox(int a, int b, int c, int d);` — src/recovered/wf_GInvOutline-07520ef33f.c
- `extern void far GInvBox(int x1, int y1, int x2, int y2);` — src/recovered/wf_GRectInvOutline-81f8c3e9d1.c
- `extern int near HealthB;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int near HealthB;` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern int near HealthB;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near HealthR;` — src/recovered/wf_tu_simant1_5344_DoAntSimR_8_scaffold-5f66a96585.c
- `extern int near HealthR;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int near MeHealth;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeHealth;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near QueenStorageB;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageB;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern int near RpopT;` — src/recovered/wf_tu_simant1_5344_DoAntSimR_8_scaffold-5f66a96585.c
- `extern int near RpopT;` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawYardWindow', 'offset': 43488, 'source': None, 'size': 558}
- {'symbol': '_UpdateYardMessage', 'offset': 44046, 'source': 'src/recovered/wf_UpdateYardMessage-77b8db79c0.c', 'size': 202}
- {'symbol': '_DrawYard', 'offset': 44708, 'source': 'src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c', 'size': 56}
- {'symbol': '_UpdateYard', 'offset': 44764, 'source': 'src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c', 'size': 56}
