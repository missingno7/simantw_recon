# Recovery task _SpecialXfer

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 490 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xbf60]
000a mov bx, word ptr es:[0x7a60]
000f shl bx, 4
0012 add bx, word ptr es:[0x7a62]
0017 mov es, word ptr [0xbf62]
001b mov byte ptr es:[bx + 0xa4], 0
0021 push 0x1900
0024 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
0029 add sp, 2
002c or ax, ax
002e jne 0x7f05
0030 push 0x1900
0033 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0038 add sp, 2
003b or ax, ax
003d jne 0x7efa
003f nop 
0040 push cs
0041 call 0x9918 ; _MapToYard
0044 push 0x1900
0047 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 74, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_ToTop
004c add sp, 2
004f push word ptr [0xbcd8]
0053 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0058 add sp, 2
005b push 2
005d nop 
005e push cs
005f call 0x9f94 ; _SetYardMode
0062 add sp, 2
0065 mov es, word ptr [0xbf64]
0069 mov word ptr es:[0x8a68], 1
0070 push 0
0072 nop 
0073 push cs
0074 call 0xa5ca ; _SetMapPlane
0077 add sp, 2
007a push 1
007c push -1
007e push -2
0080 mov bx, 0x737a
0083 mov es, word ptr [0xbf66]
0087 mov word ptr [bp - 0x16], bx
008a mov word ptr [bp - 0x14], es
008d les bx, ptr es:[bx]
0090 push word ptr es:[bx + 0x52]
0094 push word ptr es:[bx + 0x50]
0098 nop 
0099 push cs
009a call 0x92c0 ; _EditMessage
009d add sp, 0xa
00a0 mov word ptr [bp - 2], 0
00a5 lea ax, [bp - 0x12]
00a8 push ss
00a9 push ax
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetEvent
00af add sp, 4
00b2 or ax, ax
00b4 jne 0x7f6f
00b6 jmp 0x807c
00b9 push 0x1900
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
00c1 add sp, 2
00c4 or ax, ax
00c6 jne 0x7f9d
00c8 push 0x1900
00cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 206, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00d0 add sp, 2
00d3 or ax, ax
00d5 jne 0x7f92
00d7 nop 
00d8 push cs
00d9 call 0x9918 ; _MapToYard
00dc push 0x1900
00df lcall <resolved loader operand; see bindings> ; [{'operand_offset': 226, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_ToTop
00e4 add sp, 2
00e7 mov ax, word ptr [bp - 8]
00ea mov es, word ptr [0xbf68]
00ee sub ax, word ptr es:[0x1896]
00f3 mov es, word ptr [0xbf26]
00f7 sub ax, word ptr es:[0x8112]
00fc mov cx, 0xa
00ff cdq 
0100 idiv cx
0102 mov si, ax
0104 mov dx, ax
0106 shl ax, 2
0109 add ax, dx
010b shl ax, 1
010d mov es, word ptr [0xbf68]
0111 sub ax, word ptr es:[0x1894]
0116 mov es, word ptr [0xbf26]
011a sub ax, word ptr es:[0x8110]
011f add ax, word ptr [bp - 0xa]
0122 mov dx, 0x1c
0125 mov bx, dx
0127 cdq 
0128 idiv bx
012a mov di, ax
012c or di, di
012e jl 0x8052
0130 or si, si
0132 jl 0x8052
0134 cmp di, 0xb
0137 jg 0x8052
0139 cmp si, 0xf
013c jg 0x8052
013e mov es, word ptr [0xbf62]
0142 mov bx, di
0144 shl bx, 4
0147 add bx, si
0149 cmp byte ptr es:[bx + 0xa4], ch
014e je 0x802e
0150 push 0x7e
0152 push 0x2afb
0155 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 344, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
015a add sp, 4
015d mov es, word ptr [0xbf6a]
0161 mov word ptr es:[0x789e], di
0166 mov word ptr es:[0x78a0], si
016b nop 
016c push cs
016d call 0xab90 ; _XferPatch
0170 mov word ptr [bp - 2], 1
0175 jmp 0x807c
0177 nop 
0178 push 0x7e
017a push 0
017c push 1
017e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 385, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0183 add sp, 6
0186 push 1
0188 push 0
018a push 0x78
018c les bx, ptr [bp - 0x16]
018f les bx, ptr es:[bx]
0192 push word ptr es:[bx + 0x4e]
0196 push word ptr es:[bx + 0x4c]
019a jmp 0x8074
019c push 0x7e
019e push 0
01a0 push 1
01a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 421, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
01a7 add sp, 6
01aa push 1
01ac push 0
01ae push 0x78
01b0 les bx, ptr [bp - 0x16]
01b3 les bx, ptr es:[bx]
01b6 push word ptr es:[bx + 0x2a]
01ba push word ptr es:[bx + 0x28]
01be nop 
01bf push cs
01c0 call 0x92c0 ; _EditMessage
01c3 add sp, 0xa
01c6 cmp word ptr [bp - 2], 0
01ca jne 0x8085
01cc jmp 0x7f5b
01cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 466, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
01d4 push 1
01d6 push -1
01d8 push -2
01da push 0
01dc push 0
01de nop 
01df push cs
01e0 call 0x92c0 ; _EditMessage
01e3 add sp, 0xa
01e6 pop si
01e7 pop di
01e8 leave 
01e9 retf 
```

## Known declaration examples

- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far EditMessage(int first,int second,int width,int fourth,int fifth);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far MapToYard(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetMapModeAnt-f674ac382e.c
- `extern void far SetYardMode(int mode);` — src/recovered/wf_SetMapModeAnt-f674ac382e.c
- `extern void far myBeginSong(unsigned int song, unsigned int priority);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSong(unsigned int song, unsigned int mode);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_SetAlarmDropState_2_scaffold-bb12a76f6c.c
- `extern int far win_GetEvent(struct DialogEvent far *event);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far win_ToTop(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_YellowBirth', 'offset': 29598, 'source': None, 'size': 936}
- {'symbol': '_YellowDeath', 'offset': 30534, 'source': None, 'size': 1904}
- {'symbol': '_LionDialog', 'offset': 32928, 'source': None, 'size': 449}
- {'symbol': '_YellowDialog', 'offset': 33378, 'source': None, 'size': 523}
