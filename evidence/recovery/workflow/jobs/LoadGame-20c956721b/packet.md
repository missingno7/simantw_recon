# Recovery task _LoadGame

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 669 bytes.

```asm
0000 enter 0x6e, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 8], 0
000b mov es, word ptr [0xc190]
000f cmp word ptr es:[0x8370], 0
0015 je 0x9fee
0017 xor si, si
0019 push word ptr [0xcd78] ; _rootWnd
001d push ds
001e push 0x17f7
0021 push ds
0022 push 0x17eb
0025 push 0x1123
0028 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
002d dec ax
002e dec ax
002f jne 0x9fd4
0031 jmp 0xa056
0034 sub ax, 4
0037 jne 0x9fe7
0039 push 0
003b nop 
003c push cs
003d call 0xa23e ; _SaveGame
0040 add sp, 2
0043 or ax, ax
0045 je 0x9fea
0047 mov si, 1
004a or si, si
004c je 0x9fb9
004e push 0
0050 lea ax, [bp - 0x6c]
0053 push ss
0054 push ax
0055 nop 
0056 push cs
0057 call 0x9920 ; _FileSelect
005a add sp, 6
005d or ax, ax
005f je 0xa05c
0061 mov bx, 0x9520
0064 mov <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0067 push ds
0068 lea di, [bp - 0x6c]
006b mov si, bx
006d mov cx, ss
006f mov es, cx
0071 mov ds, ax
0073 mov cx, 0xffff
0076 xor ax, ax
0078 repne scasb al, byte ptr es:[di]
007a not cx
007c sub di, cx
007e xchg si, di
0080 push ds
0081 push es
0082 pop ds
0083 pop es
0084 shr cx, 1
0086 rep movsw word ptr es:[di], word ptr [si]
0088 adc cx, cx
008a rep movsb byte ptr es:[di], byte ptr [si]
008c pop ds
008d mov es, word ptr [0xc190]
0091 mov word ptr es:[0x8370], ax
0095 push 0x5c
0097 lea ax, [bp - 0x6c]
009a push ss
009b push ax
009c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 159, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strrchr
00a1 add sp, 6
00a4 mov word ptr [bp - 4], ax
00a7 mov word ptr [bp - 2], dx
00aa or dx, ax
00ac je 0xa062
00ae inc word ptr [bp - 4]
00b1 mov si, word ptr [bp - 4]
00b4 jmp 0xa06a
00b6 xor ax, ax
00b8 pop si
00b9 pop di
00ba leave 
00bb retf 
00bc mov di, word ptr [bp - 8]
00bf jmp 0xa237
00c2 lea ax, [bp - 0x6c]
00c5 mov si, ax
00c7 mov word ptr [bp - 2], ss
00ca mov es, word ptr [0xc172]
00ce les bx, ptr es:[0x7294]
00d3 push word ptr es:[bx + 2]
00d7 push word ptr es:[bx]
00da push word ptr [bp - 2]
00dd push si
00de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 225, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _stricmp,_strcmpi
00e3 add sp, 8
00e6 cmp ax, 1
00e9 sbb di, di
00eb neg di
00ed or di, di
00ef je 0xa0c0
00f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GenerateTutorial
00f6 push ds
00f7 push 0x17dd
00fa nop 
00fb push cs
00fc call 0x1b06 ; _SetEditWinTitle
00ff add sp, 4
0102 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _InitSimVars
0107 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 266, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SeedSRand
010c push 1
010e push -1
0110 push -2
0112 push 0
0114 push 0
0116 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 281, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _EditMessage
011b add sp, 0xa
011e jmp 0xa0cd
0120 mov ax, word ptr [bp - 2]
0123 push ax
0124 push si
0125 nop 
0126 push cs
0127 call 0x1b06 ; _SetEditWinTitle
012a add sp, 4
012d or di, di
012f je 0xa0f8
0131 mov di, 1
0134 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetDefaultWindows
0139 mov ax, word ptr [0xcc76] ; _MapPlane
013c cmp word ptr [0xce80], ax ; _MePlane
0140 je 0xa0e5
0142 jmp 0xa217
0145 push word ptr [0xce7e] ; _MeLocY
0149 push word ptr [0xcd88] ; _MeLocX
014d nop 
014e push cs
014f call 0x1620 ; _CenterEdit
0152 add sp, 4
0155 jmp 0xa217
0158 lea ax, [bp - 0x6c]
015b push ss
015c push ax
015d push 0
015f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 352, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 85}}]
0164 mov word ptr [bp - 6], ax
0167 or ax, ax
0169 jg 0xa128
016b mov bx, word ptr [0xacf8] ; _errno
016f shl bx, 2
0172 push word ptr [bx - 0x5092]
0176 push word ptr [bx - 0x5094]
017a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 381, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Error
017f add sp, 4
0182 mov di, word ptr [bp - 8]
0185 jmp 0xa20e
0188 xor di, di
018a mov <resolved loader operand; see bindings> ; [{'operand_offset': 395, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
018d mov es, ax
018f mov ax, 0x9570
0192 mov cx, es
0194 mov bx, ax
0196 mov ds, cx
0198 cmp word ptr es:[0x9572], di
019d je 0xa14f
019f mov ax, word ptr [bx + 2]
01a2 imul word ptr [bx]
01a4 add di, ax
01a6 add bx, 8
01a9 cmp word ptr [bx + 2], 0
01ad jne 0xa13f
01af push ss
01b0 pop ds
01b1 mov es, word ptr [0xc174]
01b5 mov word ptr es:[0x9c70], 1
01bc mov es, word ptr [0xc176]
01c0 sub ax, ax
01c2 mov word ptr es:[0x8070], ax
01c6 mov word ptr es:[0x806e], ax
01ca mov es, word ptr [0xc178]
01ce mov word ptr es:[0x9b10], 0x12c
01d5 mov word ptr es:[0x9b12], ax
01d9 mov es, word ptr [0xc17a]
01dd mov word ptr es:[0x9ea0], ax
01e1 mov word ptr es:[0x9e9e], ax
01e5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 488, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _RandYard
01ea mov ax, 0x9570
01ed mov <resolved loader operand; see bindings> ; [{'operand_offset': 494, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01f0 mov si, ax
01f2 mov word ptr [bp - 2], cx
01f5 mov es, word ptr [0xc170]
01f9 cmp word ptr es:[0x9572], 0
01ff je 0xa1f2
0201 push word ptr [bp - 6]
0204 mov es, word ptr [bp - 2]
0207 push word ptr es:[si + 6]
020b push word ptr es:[si + 4]
020f mov ax, word ptr es:[si + 2]
0213 imul word ptr es:[si]
0216 push ax
0217 mov word ptr [bp - 0x6e], ax
021a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 539, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 82}}]
021f mov di, ax
0221 cmp word ptr [bp - 0x6e], di
0224 jne 0xa1d6
0226 add si, 8
0229 mov es, word ptr [bp - 2]
022c cmp word ptr es:[si + 2], 0
0231 jne 0xa1a1
0233 jmp 0xa1f2
0235 nop 
0236 push ds
0237 push 0x1821
023a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 573, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Error
023f add sp, 4
0242 mov es, word ptr [0xc192]
0246 mov word ptr es:[0x80b4], 0xffff
024d mov di, word ptr [bp - 8]
0250 jmp 0xa206
0252 mov di, 1
0255 push di
0256 push -1
0258 push -2
025a push 0
025c push 0
025e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 609, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _EditMessage
0263 add sp, 0xa
0266 push word ptr [bp - 6]
0269 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 618, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 81}}]
026e or di, di
0270 je 0xa237
0272 nop 
0273 push cs
0274 call 0x9dbe ; _DoLoadInitializations
0277 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 634, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMenuEntries
027c push 1
027e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 641, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PauseGame
0283 add sp, 2
0286 mov es, word ptr [0xc194]
028a cmp word ptr es:[0x85f4], 0
0290 jne 0xa237
0292 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 661, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _StopSong
0297 mov ax, di
0299 pop si
029a pop di
029b leave 
029c retf 
```

## Known declaration examples

- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_tu_simant_9D04_SetMapPlane_1_scaffold-47a07d4d6a.c
- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far EditMessage(int first,int second,int width,int fourth,int fifth);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far GenerateTutorial(void);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far InitSimVars(void);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far InitSimVars(void);` — src/recovered/wf_initStuff-9712c2c2ff.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far PauseGame(int paused);` — src/recovered/wf_StartLifeTransfer-f7103d3305.c
- `extern void far PauseGame(int paused);` — src/recovered/wf_TargetAnt-2205775a54.c
- `extern void far PauseGame(int paused);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far RandYard(void);` — src/recovered/wf_DoPreLoadInits-ed37124107.c
- `extern void far RandYard(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far SeedSRand(void);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far SeedSRand(void);` — src/recovered/wf_initStuff-9712c2c2ff.c
- `extern void far SetEditWinTitle(char far *title);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern int far stricmp(const char far *a, const char far *b);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern char far * far strrchr(const char far *text, int character);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_CenterEdit'], 'segment': 3, 'target_offset': 5664, 'caller_offsets': [335]}
- {'callee_names': ['_SetEditWinTitle'], 'segment': 3, 'target_offset': 6918, 'caller_offsets': [252, 295]}
- {'callee_names': ['_FileSelect'], 'segment': 3, 'target_offset': 39200, 'caller_offsets': [87]}
- {'callee_names': ['_DoLoadInitializations'], 'segment': 3, 'target_offset': 40382, 'caller_offsets': [628]}
- {'callee_names': ['_SaveGame'], 'segment': 3, 'target_offset': 41534, 'caller_offsets': [61]}

## Neighbors

- {'symbol': '_DoPreLoadInits', 'offset': 40324, 'source': 'src/recovered/wf_DoPreLoadInits-ed37124107.c', 'size': 58}
- {'symbol': '_DoLoadInitializations', 'offset': 40382, 'source': None, 'size': 481}
- {'symbol': '_SaveGame', 'offset': 41534, 'source': None, 'size': 626}
- {'symbol': '_ClearLastFileName', 'offset': 42160, 'source': 'src/recovered/ClearLastFileName.c', 'size': 11}
