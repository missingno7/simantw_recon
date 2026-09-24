# Recovery task _YellowBirth

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 936 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xe]
0009 nop 
000a push cs
000b call 0 ; _StopSimulation
000e mov es, word ptr [0xbf42]
0012 mov ax, word ptr es:[0x85f6]
0016 mov word ptr [bp - 8], ax
0019 mov ax, word ptr [0xcc84] ; _MeType
001c mov word ptr [bp - 6], ax
001f xor ax, ax
0021 mov word ptr es:[0x85f6], ax
0025 mov es, word ptr [0xbf0c]
0029 mov word ptr es:[0x9fe8], ax
002d cmp di, ax
002f jne 0x73e8
0031 mov word ptr [0xce92], 1 ; _MeEgg
0037 push 0xff
003a push word ptr [0xcf50] ; _MeDir
003e push ax
003f push word ptr [bp + 0xa]
0042 push word ptr [bp + 8]
0045 push word ptr [bp + 6]
0048 jmp 0x7419
004a push word ptr [0xcf50] ; _MeDir
004e push word ptr [0xcc84] ; _MeType
0052 push word ptr [0xce7e] ; _MeLocY
0056 push word ptr [0xcd88] ; _MeLocX
005a push word ptr [0xce80] ; _MePlane
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ClearMyLife
0063 add sp, 0xa
0066 push 0xff
0069 push word ptr [0xcf50] ; _MeDir
006d push 0x60
006f push word ptr [0xce7e] ; _MeLocY
0073 push word ptr [0xcd88] ; _MeLocX
0077 push word ptr [0xce80] ; _MePlane
007b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 126, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
0080 add sp, 0xc
0083 or di, di
0085 jne 0x742a
0087 nop 
0088 push cs
0089 call 0xa764 ; _GotoMyAnt
008c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 143, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DoEditAndMapUpdateDraw
0091 or di, di
0093 je 0x74a0
0095 push 0x7e
0097 push 0x4e20
009a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 157, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
009f add sp, 4
00a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 165, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
00a7 add ax, 0x12c
00aa adc dx, 0
00ad mov word ptr [bp - 4], ax
00b0 mov word ptr [bp - 2], dx
00b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 182, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySongIsDone
00b8 or ax, ax
00ba jne 0x7488
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
00c1 cmp dx, word ptr [bp - 2]
00c4 jg 0x7488
00c6 jl 0x746b
00c8 cmp ax, word ptr [bp - 4]
00cb jae 0x7488
00cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 208, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
00d2 or ax, ax
00d4 jne 0x7488
00d6 push ax
00d7 push 1
00d9 nop 
00da push cs
00db call 0x9620 ; _myDelay
00de add sp, 4
00e1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 228, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySongIsDone
00e6 or ax, ax
00e8 je 0x745a
00ea push 1
00ec push word ptr [bp + 0xa]
00ef push word ptr [bp + 8]
00f2 push word ptr [bp + 6]
00f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 248, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetLife
00fa add sp, 8
00fd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 256, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DoEditAndMapUpdateDraw
0102 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
0107 mov ax, word ptr [bp - 8]
010a mov es, word ptr [0xbf42]
010e mov word ptr es:[0x85f6], ax
0112 push 0x7e
0114 push 0
0116 push 0x1c
0118 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 283, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
011d add sp, 6
0120 push 0
0122 push 0x2d
0124 nop 
0125 push cs
0126 call 0x9620 ; _myDelay
0129 add sp, 4
012c mov ax, word ptr [0xce80] ; _MePlane
012f mov es, word ptr [0xbf1a]
0133 mov word ptr es:[0x9be0], ax
0137 mov ax, word ptr [0xcd88] ; _MeLocX
013a mov es, word ptr [0xbf38]
013e mov word ptr es:[0xa0d6], ax
0142 mov es, word ptr [0xbf1c]
0146 mov word ptr es:[0x80c6], ax
014a mov ax, word ptr [0xce7e] ; _MeLocY
014d mov es, word ptr [0xbf3a]
0151 mov word ptr es:[0xa0da], ax
0155 mov es, word ptr [0xbf1e]
0159 mov word ptr es:[0x80d2], ax
015d xor ax, ax
015f mov es, word ptr [0xbf10]
0163 mov word ptr es:[0x9bc4], ax
0167 mov es, word ptr [0xbf22]
016b mov word ptr es:[0x7d24], ax
016f mov es, word ptr [0xbf3c]
0173 mov word ptr es:[0x9fe2], ax
0177 mov es, word ptr [0xbf3e]
017b mov word ptr es:[0x80aa], ax
017f mov es, word ptr [0xbf40]
0183 mov word ptr es:[0x9c7e], ax
0187 mov es, word ptr [0xbf20]
018b mov word ptr es:[0x72e4], 0xfffe
0192 mov es, word ptr [0xbf44]
0196 mov word ptr es:[0x8a6c], 1
019d push 0x64
019f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 418, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyHealth
01a4 add sp, 2
01a7 cmp word ptr [bp + 0xe], 0
01ab jne 0x755c
01ad cmp word ptr [bp - 6], 0x60
01b1 jne 0x7556
01b3 mov ax, 2
01b6 jmp 0x7559
01b8 mov ax, 6
01bb mov word ptr [0xcf50], ax ; _MeDir
01be mov si, 2
01c1 nop 
01c2 push cs
01c3 call 0x9694 ; _MacTickCount
01c6 add ax, 0xa
01c9 adc dx, 0
01cc mov word ptr [bp - 4], ax
01cf mov word ptr [bp - 2], dx
01d2 cmp word ptr [bp + 0xe], 0
01d6 jne 0x759a
01d8 mov word ptr [0xce92], si ; _MeEgg
01dc push 0xff
01df push word ptr [0xcf50] ; _MeDir
01e3 push 0
01e5 push word ptr [0xce7e] ; _MeLocY
01e9 push word ptr [0xcd88] ; _MeLocX
01ed push word ptr [0xce80] ; _MePlane
01f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 500, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
01f6 add sp, 0xc
01f9 jmp 0x75ad
01fb nop 
01fc push si
01fd push word ptr [bp + 0xa]
0200 push word ptr [bp + 8]
0203 push word ptr [0xce80] ; _MePlane
0207 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 522, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetLife
020c add sp, 8
020f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 530, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DoEditUpdateDraw
0214 nop 
0215 push cs
0216 call 0x9694 ; _MacTickCount
0219 cmp dx, word ptr [bp - 2]
021c jg 0x75e8
021e jl 0x75c3
0220 cmp ax, word ptr [bp - 4]
0223 jae 0x75e8
0225 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 552, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
022a or ax, ax
022c jne 0x75e8
022e push ax
022f push 1
0231 nop 
0232 push cs
0233 call 0x9620 ; _myDelay
0236 add sp, 4
0239 nop 
023a push cs
023b call 0x9694 ; _MacTickCount
023e cmp dx, word ptr [bp - 2]
0241 jl 0x75c3
0243 jg 0x75e8
0245 cmp ax, word ptr [bp - 4]
0248 jb 0x75c3
024a inc si
024b cmp si, 7
024e jg 0x75f1
0250 jmp 0x755f
0253 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 598, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
0258 cmp word ptr [bp + 0xe], 0
025c je 0x761a
025e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 609, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySongIsDone
0263 or ax, ax
0265 jne 0x761a
0267 push 0
0269 push 5
026b nop 
026c push cs
026d call 0x9620 ; _myDelay
0270 add sp, 4
0273 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 630, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySongIsDone
0278 or ax, ax
027a je 0x7605
027c push 0x7e
027e push 0
0280 push 0x31
0282 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 645, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0287 add sp, 6
028a cmp word ptr [bp + 0xe], 0
028e jne 0x7650
0290 push 0xff
0293 push word ptr [0xcf50] ; _MeDir
0297 push word ptr [bp + 0xc]
029a push word ptr [0xce7e] ; _MeLocY
029e push word ptr [0xcd88] ; _MeLocX
02a2 push word ptr [0xce80] ; _MePlane
02a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 681, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
02ab add sp, 0xc
02ae jmp 0x76e6
02b1 nop 
02b2 push word ptr [0xcf50] ; _MeDir
02b6 push word ptr [0xcc84] ; _MeType
02ba push word ptr [0xce7e] ; _MeLocY
02be push word ptr [0xcd88] ; _MeLocX
02c2 push word ptr [0xce80] ; _MePlane
02c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 713, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ClearMyLife
02cb add sp, 0xa
02ce cmp word ptr [0xce80], 2 ; _MePlane
02d3 jne 0x768e
02d5 push word ptr [0xcf50] ; _MeDir
02d9 push word ptr [0xce7e] ; _MeLocY
02dd push word ptr [0xcd88] ; _MeLocX
02e1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 740, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _MakeBlkQueen
02e6 add sp, 6
02e9 inc word ptr [0xac9e]
02ed jmp 0x76a6
02ef nop 
02f0 push word ptr [0xcf50] ; _MeDir
02f4 push word ptr [0xce7e] ; _MeLocY
02f8 push word ptr [0xcd88] ; _MeLocX
02fc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 767, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _MakeRedQueen
0301 add sp, 6
0304 inc word ptr [0xacaa]
0308 push 0xff
030b mov ax, word ptr [0xcf50] ; _MeDir
030e xor al, 4
0310 push ax
0311 push word ptr [bp + 0xc]
0314 push word ptr [bp + 0xa]
0317 push word ptr [bp + 8]
031a push word ptr [0xce80] ; _MePlane
031e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 801, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
0323 add sp, 0xc
0326 cmp word ptr [0xce98], 0 ; _MeColor
032b jne 0x76da
032d inc word ptr [0xac96]
0331 dec word ptr [0xac9c]
0335 inc word ptr [0xac82] ; _BpopT
0339 jmp 0x76e6
033b nop 
033c inc word ptr [0xaca2]
0340 dec word ptr [0xaca8]
0344 inc word ptr [0xac84] ; _RpopT
0348 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 843, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DoEditUpdateDraw
034d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 848, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySoundIsDone
0352 or ax, ax
0354 jne 0x7709
0356 push 0
0358 push 5
035a nop 
035b push cs
035c call 0x9620 ; _myDelay
035f add sp, 4
0362 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 869, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySoundIsDone
0367 or ax, ax
0369 je 0x76f4
036b cmp word ptr [bp + 0xe], 0
036f je 0x7716
0371 push 0x7e
0373 push 0x4e21
0376 jmp 0x771b
0378 push 0x7e
037a push 0x2afd
037d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 896, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
0382 add sp, 4
0385 push 0
0387 nop 
0388 push cs
0389 call 0x96b0 ; _SetSimCursor
038c add sp, 2
038f mov ax, word ptr [bp + 0xe]
0392 inc ax
0393 push ax
0394 push 0x238d
0397 nop 
0398 push cs
0399 call 0x8262 ; _YellowDialog
039c add sp, 4
039f nop 
03a0 push cs
03a1 call 0x34 ; _RestartSimulation
03a4 pop si
03a5 pop di
03a6 leave 
03a7 retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near BpopT;` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern int near BpopT;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern void far ClearMyLife(int plane, int x, int y, int type, int dir);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern void far ClearMyLife(int plane, int x, int y, int type, int dir);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far DoEditUpdateDraw(void);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far DoEditUpdateDraw(void);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far GotoMyAnt(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near MeColor;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MeColor;` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern int near MeColor;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeDir;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeDir;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeType;` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int near MeType;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far RestartSimulation(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int near RpopT;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near RpopT;` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern int near RpopT;` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_SetQueenTail-103d1d54cd.c
- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far SetMyHealth(int health);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern void far SetMyHealth(int health);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far SetSimCursor(int cursor);` — src/recovered/wf_initStuff-9712c2c2ff.c
- `extern void far StopSimulation(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern void far myBeginSong(unsigned int song, unsigned int priority);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSong(unsigned int song, unsigned int mode);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far myDelay(unsigned long ticks);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int far mySoundIsDone(void);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int far win_Events(void);` — src/recovered/wf_myDelay-ac936e115a.c
- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ResetYellowVars', 'offset': 29370, 'source': 'src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c', 'size': 122}
- {'symbol': '_SetGoalsY', 'offset': 29492, 'source': None, 'size': 105}
- {'symbol': '_YellowDeath', 'offset': 30534, 'source': None, 'size': 1904}
- {'symbol': '_SpecialXfer', 'offset': 32438, 'source': None, 'size': 490}
