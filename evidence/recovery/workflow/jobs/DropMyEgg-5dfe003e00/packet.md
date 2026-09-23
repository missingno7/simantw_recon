# Recovery task _DropMyEgg

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 1126 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 cmp word ptr [0xcc84], 8 ; _MeType
000b je 0x819c
000d xor ax, ax
000f pop si
0010 pop di
0011 leave 
0012 retf 
0013 nop 
0014 mov word ptr [bp - 8], 0
0019 push word ptr [bp + 0xe]
001c push word ptr [bp + 0xc]
001f push word ptr [bp + 0xa]
0022 push word ptr [bp + 8]
0025 nop 
0026 push cs
0027 call 0x10cc ; _GetDir
002a add sp, 8
002d mov si, ax
002f or si, si
0031 jle 0x81be
0033 dec si
0034 jmp 0x81c2
0036 mov si, word ptr [0xcf50] ; _MeDir
003a mov word ptr [bp - 2], 0
003f mov word ptr [bp - 4], si
0042 mov si, word ptr [bp - 0xa]
0045 mov di, word ptr [bp - 6]
0048 cmp word ptr [bp - 2], 8
004c jl 0x81d9
004e jmp 0x835b
0051 mov es, word ptr [0xc4a2]
0055 mov bx, word ptr [bp - 2]
0058 mov bl, byte ptr es:[bx + 0x6c]
005d add bl, byte ptr [bp - 4]
0060 and bx, 7
0063 mov word ptr [bp - 0xc], bx
0066 mov es, word ptr [0xc47a]
006a mov al, byte ptr es:[bx]
006f cwde 
0070 mov si, ax
0072 add si, word ptr [bp + 8]
0075 mov es, word ptr [0xc478]
0079 mov al, byte ptr es:[bx + 8]
007e cwde 
007f mov di, ax
0081 add di, word ptr [bp + 0xa]
0084 cmp word ptr [bp + 6], 1
0088 jg 0x822a
008a or si, si
008c jl 0x823c
008e cmp si, 0x7f
0091 jg 0x823c
0093 or di, di
0095 jl 0x823c
0097 cmp di, 0x3f
009a jg 0x823c
009c mov dx, 1
009f jmp 0x823e
00a1 nop 
00a2 or si, si
00a4 jl 0x823c
00a6 cmp si, 0x3f
00a9 jg 0x823c
00ab or di, di
00ad jl 0x823c
00af cmp di, 0x3f
00b2 jle 0x8224
00b4 xor dx, dx
00b6 or dx, dx
00b8 jne 0x8245
00ba jmp 0x834f
00bd mov dx, 0xffff
00c0 cmp word ptr [bp + 6], 1
00c4 jg 0x8266
00c6 or si, si
00c8 jl 0x8278
00ca cmp si, 0x7f
00cd jg 0x8278
00cf or di, di
00d1 jl 0x8278
00d3 cmp di, 0x3f
00d6 jg 0x8278
00d8 mov cx, 1
00db jmp 0x827a
00dd nop 
00de or si, si
00e0 jl 0x8278
00e2 cmp si, 0x3f
00e5 jg 0x8278
00e7 or di, di
00e9 jl 0x8278
00eb cmp di, 0x3f
00ee jle 0x8260
00f0 xor cx, cx
00f2 dec cx
00f3 jne 0x82bc
00f5 mov ax, word ptr [bp + 6]
00f8 or ax, ax
00fa jl 0x82b5
00fc jo 0x82b5
00fe dec ax
00ff jle 0x8292
0101 dec ax
0102 je 0x829e
0104 dec ax
0105 je 0x82aa
0107 jmp 0x82b5
0109 nop 
010a mov bx, si
010c shl bx, 6
010f mov dl, byte ptr [bx + di + 0x68e8]
0113 jmp 0x82b3
0115 nop 
0116 mov bx, si
0118 shl bx, 6
011b mov dl, byte ptr [bx + di - 0x7718]
011f jmp 0x82b3
0121 nop 
0122 mov bx, si
0124 shl bx, 6
0127 mov dl, byte ptr [bx + di - 0x6718]
012b sub dh, dh
012d or dx, dx
012f jne 0x82bc
0131 mov dx, 0xffff
0134 or dx, dx
0136 jl 0x82c3
0138 jmp 0x834f
013b push di
013c push si
013d push word ptr [bp + 6]
0140 nop 
0141 push cs
0142 call 0x5b2c ; _IsClearTile
0145 add sp, 6
0148 or ax, ax
014a jne 0x834a
014c mov dx, 0xffff
014f cmp word ptr [bp + 6], 1
0153 jg 0x82f6
0155 or si, si
0157 jl 0x8308
0159 cmp si, 0x7f
015c jg 0x8308
015e or di, di
0160 jl 0x8308
0162 cmp di, 0x3f
0165 jg 0x8308
0167 mov cx, 1
016a jmp 0x830a
016c nop 
016d nop 
016e or si, si
0170 jl 0x8308
0172 cmp si, 0x3f
0175 jg 0x8308
0177 or di, di
0179 jl 0x8308
017b cmp di, 0x3f
017e jle 0x82ef
0180 xor cx, cx
0182 dec cx
0183 jne 0x8345
0185 mov ax, word ptr [bp + 6]
0188 or ax, ax
018a jl 0x8345
018c jo 0x8345
018e dec ax
018f jle 0x8322
0191 dec ax
0192 je 0x832e
0194 dec ax
0195 je 0x833a
0197 jmp 0x8345
0199 nop 
019a mov bx, si
019c shl bx, 6
019f mov dl, byte ptr [bx + di + 0x28e8]
01a3 jmp 0x8343
01a5 nop 
01a6 mov bx, si
01a8 shl bx, 6
01ab mov dl, byte ptr [bx + di + 0x48e8]
01af jmp 0x8343
01b1 nop 
01b2 mov bx, si
01b4 shl bx, 6
01b7 mov dl, byte ptr [bx + di + 0x58e8]
01bb sub dh, dh
01bd cmp dx, 0x38
01c0 jne 0x834f
01c2 mov word ptr [bp - 8], 1
01c7 inc word ptr [bp - 2]
01ca cmp word ptr [bp - 8], 0
01ce jne 0x835b
01d0 jmp 0x81d0
01d3 mov word ptr [bp - 0xa], si
01d6 mov word ptr [bp - 6], di
01d9 cmp word ptr [bp - 8], 0
01dd je 0x836a
01df jmp 0x8465
01e2 mov ax, word ptr [bp - 4]
01e5 mov word ptr [bp - 0xc], ax
01e8 mov ax, word ptr [bp + 8]
01eb mov word ptr [bp - 0xa], ax
01ee mov ax, word ptr [bp + 0xa]
01f1 mov word ptr [bp - 6], ax
01f4 cmp word ptr [bp + 6], 1
01f8 jg 0x83de
01fa cmp word ptr [bp - 0xa], 0
01fe jl 0x8398
0200 cmp word ptr [bp - 0xa], 0x7f
0204 jg 0x8398
0206 or ax, ax
0208 jl 0x8398
020a cmp ax, 0x3f
020d jmp 0x83f4
020f nop 
0210 xor dx, dx
0212 or dx, dx
0214 jne 0x83a1
0216 jmp 0x8465
0219 push word ptr [bp - 6]
021c push word ptr [bp - 0xa]
021f push word ptr [bp + 6]
0222 nop 
0223 push cs
0224 call 0x5b2c ; _IsClearTile
0227 add sp, 6
022a or ax, ax
022c je 0x83b9
022e jmp 0x8460
0231 mov dx, 0xffff
0234 cmp word ptr [bp + 6], 1
0238 jg 0x83fc
023a cmp word ptr [bp - 0xa], ax
023d jl 0x8412
023f cmp word ptr [bp - 0xa], 0x7f
0243 jg 0x8412
0245 cmp word ptr [bp - 6], ax
0248 jl 0x8412
024a cmp word ptr [bp - 6], 0x3f
024e jg 0x8412
0250 mov bx, 1
0253 jmp 0x8414
0255 nop 
0256 cmp word ptr [bp - 0xa], 0
025a jl 0x8398
025c cmp word ptr [bp - 0xa], 0x3f
0260 jg 0x8398
0262 cmp word ptr [bp - 6], 0
0266 jl 0x8398
0268 cmp word ptr [bp - 6], 0x3f
026c jg 0x8398
026e mov dx, 1
0271 jmp 0x839a
0273 nop 
0274 cmp word ptr [bp - 0xa], ax
0277 jl 0x8412
0279 cmp word ptr [bp - 0xa], 0x3f
027d jg 0x8412
027f cmp word ptr [bp - 6], ax
0282 jl 0x8412
0284 cmp word ptr [bp - 6], 0x3f
0288 jle 0x83d8
028a xor bx, bx
028c dec bx
028d jne 0x845b
028f mov ax, word ptr [bp + 6]
0292 or ax, ax
0294 jl 0x845b
0296 jo 0x845b
0298 dec ax
0299 jle 0x842c
029b dec ax
029c je 0x843c
029e dec ax
029f je 0x844c
02a1 jmp 0x845b
02a3 nop 
02a4 mov si, word ptr [bp - 0xa]
02a7 shl si, 6
02aa mov bx, word ptr [bp - 6]
02ad mov dl, byte ptr [bx + si + 0x28e8]
02b1 jmp 0x8459
02b3 nop 
02b4 mov si, word ptr [bp - 0xa]
02b7 shl si, 6
02ba mov bx, word ptr [bp - 6]
02bd mov dl, byte ptr [bx + si + 0x48e8]
02c1 jmp 0x8459
02c3 nop 
02c4 mov si, word ptr [bp - 0xa]
02c7 shl si, 6
02ca mov bx, word ptr [bp - 6]
02cd mov dl, byte ptr [bx + si + 0x58e8]
02d1 sub dh, dh
02d3 cmp dx, 0x38
02d6 jne 0x8465
02d8 mov word ptr [bp - 8], 1
02dd cmp word ptr [bp - 8], 0
02e1 jne 0x846e
02e3 jmp 0x8506
02e6 mov es, word ptr [0xc48c]
02ea mov ax, word ptr es:[0x8a6a]
02ee mov word ptr [bp - 2], ax
02f1 xor di, di
02f3 cmp word ptr [bp + 6], 1
02f7 jg 0x84a0
02f9 mov es, word ptr [0xc47c]
02fd cmp word ptr es:[0x80f0], 0x3e8
0304 jge 0x84ea
0306 push di
0307 push 8
0309 push ax
030a push word ptr [bp - 6]
030d push word ptr [bp - 0xa]
0310 nop 
0311 push cs
0312 call 0x2ef0 ; _AddAntToAList
0315 jmp 0x84e4
0317 nop 
0318 cmp word ptr [bp + 6], 2
031c jne 0x84c6
031e mov es, word ptr [0xc47e]
0322 cmp word ptr es:[0x99d4], 0x1f4
0329 jge 0x84ea
032b push di
032c push 8
032e push word ptr [bp - 2]
0331 push word ptr [bp - 6]
0334 push word ptr [bp - 0xa]
0337 nop 
0338 push cs
0339 call 0x2f4a ; _AddAntToBList
033c jmp 0x84e4
033e mov es, word ptr [0xc480]
0342 cmp word ptr es:[0x72cc], 0x1f4
0349 jge 0x84ea
034b push di
034c push 8
034e push word ptr [bp - 2]
0351 push word ptr [bp - 6]
0354 push word ptr [bp - 0xa]
0357 nop 
0358 push cs
0359 call 0x2fa4 ; _AddAntToRList
035c add sp, 0xa
035f mov di, 1
0362 cmp di, 1
0365 jne 0x8503
0367 push word ptr [bp - 2]
036a push word ptr [bp - 6]
036d push word ptr [bp - 0xa]
0370 push word ptr [bp + 6]
0373 nop 
0374 push cs
0375 call 0x5d18 ; _SetLife
0378 add sp, 8
037b mov word ptr [bp - 8], di
037e cmp word ptr [bp - 8], 0
0382 jne 0x850f
0384 jmp 0x85e7
0387 mov ax, word ptr [bp - 0xc]
038a mov word ptr [0xcf50], ax ; _MeDir
038d push 0x10
038f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 912, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0394 mov word ptr [0xcc84], 0x10 ; _MeType
039a mov es, word ptr [0xc48c]
039e mov word ptr es:[0x8a6a], 0xfd
03a5 mov ax, word ptr [0xce80] ; _MePlane
03a8 mov word ptr [bp - 2], ax
03ab mov si, word ptr [0xcd88] ; _MeLocX
03af mov di, word ptr [0xce7e] ; _MeLocY
03b3 mov word ptr [bp - 6], 0x10
03b8 mov ax, word ptr [0xcf50] ; _MeDir
03bb mov word ptr [bp - 4], ax
03be cmp word ptr [bp - 2], 1
03c2 jg 0x8564
03c4 or si, si
03c6 jl 0x8576
03c8 cmp si, 0x7f
03cb jg 0x8576
03cd or di, di
03cf jl 0x8576
03d1 cmp di, 0x3f
03d4 jg 0x8576
03d6 mov dx, 1
03d9 jmp 0x8578
03db nop 
03dc or si, si
03de jl 0x8576
03e0 cmp si, 0x3f
03e3 jg 0x8576
03e5 or di, di
03e7 jl 0x8576
03e9 cmp di, 0x3f
03ec jle 0x855e
03ee xor dx, dx
03f0 dec dx
03f1 jne 0x85d9
03f3 push 0xff
03f6 push di
03f7 push si
03f8 push word ptr [bp - 2]
03fb nop 
03fc push cs
03fd call 0x5d18 ; _SetLife
0400 add sp, 8
0403 cmp word ptr [bp - 6], 0x60
0407 jne 0x85bf
0409 push 0xfe
040c mov es, word ptr [0xc478]
0410 mov bx, word ptr [bp - 4]
0413 xor bl, 4
0416 mov al, byte ptr es:[bx + 8]
041b cwde 
041c add ax, di
041e push ax
041f mov es, word ptr [0xc47a]
0423 mov al, byte ptr es:[bx]
0428 cwde 
0429 add ax, si
042b push ax
042c push word ptr [bp - 2]
042f nop 
0430 push cs
0431 call 0x5d18 ; _SetLife
0434 add sp, 8
0437 mov word ptr [0xcd88], si ; _MeLocX
043b mov word ptr [0xce7e], di ; _MeLocY
043f mov ax, word ptr [bp - 4]
0442 mov word ptr [0xcf50], ax ; _MeDir
0445 mov ax, word ptr [bp - 6]
0448 mov word ptr [0xcc84], ax ; _MeType
044b mov ax, word ptr [bp - 2]
044e mov word ptr [0xce80], ax ; _MePlane
0451 push 0x7e
0453 push 0
0455 push 0x1c
0457 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1114, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
045c add sp, 6
045f mov ax, word ptr [bp - 8]
0462 pop si
0463 pop di
0464 leave 
0465 retf 
```

## Known declaration examples

- `extern void far AddAntToAList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far AddAntToAList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far AddAntToBList(int life, int column, int attribute, int state, int direction);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far AddAntToRList(int life, int column, int attribute, int state, int direction);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int far GetDir(int a, int b, int c, int d);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far GetDir(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_0000_GetDefendDir_2_scaffold-cdac288ff9.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_IsClear3x3-f787045a5e.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
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
- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_SetQueenTail-103d1d54cd.c
- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DropPebble', 'offset': 31164, 'source': None, 'size': 662}
- {'symbol': '_DropMyRock', 'offset': 31826, 'source': None, 'size': 1334}
- {'symbol': '_PickupMyRock', 'offset': 34286, 'source': None, 'size': 692}
- {'symbol': '_FindEggAt', 'offset': 34978, 'source': None, 'size': 499}
