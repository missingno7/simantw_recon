# Recovery task _DropMyFood

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 1093 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov dx, word ptr [0xcc84] ; _MeType
000a cmp dx, 0x18
000d je 0x7590
000f cmp dx, 0x38
0012 je 0x7590
0014 xor ax, ax
0016 pop si
0017 pop di
0018 leave 
0019 retf 
001a mov word ptr [bp - 0xa], 0
001f push word ptr [bp + 0xe]
0022 push word ptr [bp + 0xc]
0025 push word ptr [bp + 0xa]
0028 push word ptr [bp + 8]
002b nop 
002c push cs
002d call 0x10cc ; _GetDir
0030 add sp, 8
0033 mov si, ax
0035 or si, si
0037 jle 0x75b6
0039 dec si
003a mov word ptr [bp - 6], si
003d jmp 0x75bc
003f nop 
0040 mov ax, word ptr [0xcf50] ; _MeDir
0043 mov word ptr [bp - 6], ax
0046 mov word ptr [bp - 4], 0
004b mov si, word ptr [bp - 0xe]
004e mov di, word ptr [bp - 0xc]
0051 cmp word ptr [bp - 4], 8
0055 jl 0x75d0
0057 jmp 0x7791
005a mov es, word ptr [0xc4a2]
005e mov bx, word ptr [bp - 4]
0061 mov bl, byte ptr es:[bx + 0x6c]
0066 add bl, byte ptr [bp - 6]
0069 and bx, 7
006c mov word ptr [bp - 0x10], bx
006f mov es, word ptr [0xc47a]
0073 mov al, byte ptr es:[bx]
0078 cwde 
0079 mov si, ax
007b add si, word ptr [bp + 8]
007e mov es, word ptr [0xc478]
0082 mov al, byte ptr es:[bx + 8]
0087 cwde 
0088 mov di, ax
008a add di, word ptr [bp + 0xa]
008d cmp word ptr [bp + 6], 1
0091 jg 0x7620
0093 or si, si
0095 jl 0x7632
0097 cmp si, 0x7f
009a jg 0x7632
009c or di, di
009e jl 0x7632
00a0 cmp di, 0x3f
00a3 jg 0x7632
00a5 mov dx, 1
00a8 jmp 0x7634
00aa or si, si
00ac jl 0x7632
00ae cmp si, 0x3f
00b1 jg 0x7632
00b3 or di, di
00b5 jl 0x7632
00b7 cmp di, 0x3f
00ba jle 0x761b
00bc xor dx, dx
00be or dx, dx
00c0 jne 0x763b
00c2 jmp 0x7785
00c5 mov dx, 0xffff
00c8 cmp word ptr [bp + 6], 1
00cc jg 0x765c
00ce or si, si
00d0 jl 0x766e
00d2 cmp si, 0x7f
00d5 jg 0x766e
00d7 or di, di
00d9 jl 0x766e
00db cmp di, 0x3f
00de jg 0x766e
00e0 mov cx, 1
00e3 jmp 0x7670
00e5 nop 
00e6 or si, si
00e8 jl 0x766e
00ea cmp si, 0x3f
00ed jg 0x766e
00ef or di, di
00f1 jl 0x766e
00f3 cmp di, 0x3f
00f6 jle 0x7656
00f8 xor cx, cx
00fa dec cx
00fb jne 0x76b2
00fd mov ax, word ptr [bp + 6]
0100 or ax, ax
0102 jl 0x76ab
0104 jo 0x76ab
0106 dec ax
0107 jle 0x7688
0109 dec ax
010a je 0x7694
010c dec ax
010d je 0x76a0
010f jmp 0x76ab
0111 nop 
0112 mov bx, si
0114 shl bx, 6
0117 mov dl, byte ptr [bx + di + 0x68e8]
011b jmp 0x76a9
011d nop 
011e mov bx, si
0120 shl bx, 6
0123 mov dl, byte ptr [bx + di - 0x7718]
0127 jmp 0x76a9
0129 nop 
012a mov bx, si
012c shl bx, 6
012f mov dl, byte ptr [bx + di - 0x6718]
0133 sub dh, dh
0135 or dx, dx
0137 jne 0x76b2
0139 mov dx, 0xffff
013c or dx, dx
013e jl 0x76b9
0140 jmp 0x7785
0143 mov cx, 0xffff
0146 cmp word ptr [bp + 6], 1
014a jg 0x76da
014c or si, si
014e jl 0x76ec
0150 cmp si, 0x7f
0153 jg 0x76ec
0155 or di, di
0157 jl 0x76ec
0159 cmp di, 0x3f
015c jg 0x76ec
015e mov dx, 1
0161 jmp 0x76ee
0163 nop 
0164 or si, si
0166 jl 0x76ec
0168 cmp si, 0x3f
016b jg 0x76ec
016d or di, di
016f jl 0x76ec
0171 cmp di, 0x3f
0174 jle 0x76d4
0176 xor dx, dx
0178 dec dx
0179 jne 0x7729
017b mov ax, word ptr [bp + 6]
017e or ax, ax
0180 jl 0x7729
0182 jo 0x7729
0184 dec ax
0185 jle 0x7706
0187 dec ax
0188 je 0x7712
018a dec ax
018b je 0x771e
018d jmp 0x7729
018f nop 
0190 mov bx, si
0192 shl bx, 6
0195 mov cl, byte ptr [bx + di + 0x28e8]
0199 jmp 0x7727
019b nop 
019c mov bx, si
019e shl bx, 6
01a1 mov cl, byte ptr [bx + di + 0x48e8]
01a5 jmp 0x7727
01a7 nop 
01a8 mov bx, si
01aa shl bx, 6
01ad mov cl, byte ptr [bx + di + 0x58e8]
01b1 sub ch, ch
01b3 mov word ptr [bp - 8], cx
01b6 cmp word ptr [bp + 6], 1
01ba jg 0x7740
01bc push cx
01bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 448, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItFood
01c2 add sp, 2
01c5 mov dx, ax
01c7 jmp 0x7752
01c9 nop 
01ca cmp cx, 0x10
01cd jl 0x7750
01cf cmp cx, 0x13
01d2 jg 0x7750
01d4 mov dx, 1
01d7 jmp 0x7752
01d9 nop 
01da xor dx, dx
01dc or dx, dx
01de je 0x7764
01e0 mov al, byte ptr [bp - 8]
01e3 and al, 3
01e5 cmp al, 3
01e7 jge 0x7764
01e9 inc word ptr [bp - 8]
01ec jmp 0x7780
01ee push di
01ef push si
01f0 push word ptr [bp + 6]
01f3 nop 
01f4 push cs
01f5 call 0x5b2c ; _IsClearTile
01f8 add sp, 6
01fb or ax, ax
01fd jne 0x777b
01ff cmp word ptr [bp - 8], 0x38
0203 jne 0x7785
0205 mov word ptr [bp - 8], 0x10
020a mov word ptr [bp - 0xa], 1
020f inc word ptr [bp - 4]
0212 cmp word ptr [bp - 0xa], 0
0216 jne 0x7791
0218 jmp 0x75c7
021b mov word ptr [bp - 0xe], si
021e mov si, word ptr [bp + 6]
0221 mov word ptr [bp - 0xc], di
0224 cmp word ptr [bp - 0xa], 0
0228 jne 0x7804
022a mov ax, word ptr [bp - 6]
022d mov word ptr [bp - 0x10], ax
0230 mov ax, word ptr [bp + 8]
0233 mov word ptr [bp - 0xe], ax
0236 mov ax, word ptr [bp + 0xa]
0239 mov word ptr [bp - 0xc], ax
023c cmp si, 1
023f jg 0x77d2
0241 cmp word ptr [bp - 0xe], 0
0245 jl 0x77ea
0247 cmp word ptr [bp - 0xe], 0x7f
024b jg 0x77ea
024d or ax, ax
024f jl 0x77ea
0251 cmp ax, 0x3f
0254 jg 0x77ea
0256 mov dx, 1
0259 jmp 0x77ec
025b nop 
025c cmp word ptr [bp - 0xe], 0
0260 jl 0x77ea
0262 cmp word ptr [bp - 0xe], 0x3f
0266 jg 0x77ea
0268 cmp word ptr [bp - 0xc], 0
026c jl 0x77ea
026e cmp word ptr [bp - 0xc], 0x3f
0272 jle 0x77cc
0274 xor dx, dx
0276 or dx, dx
0278 je 0x7804
027a mov cx, 0xffff
027d cmp si, 1
0280 jg 0x7822
0282 cmp word ptr [bp - 0xe], 0
0286 jl 0x780a
0288 cmp word ptr [bp - 0xe], 0x7f
028c jmp 0x782c
028e mov di, word ptr [bp - 8]
0291 jmp 0x78c6
0294 xor dx, dx
0296 dec dx
0297 jne 0x786f
0299 mov ax, si
029b or ax, ax
029d jl 0x786f
029f jo 0x786f
02a1 dec ax
02a2 jle 0x7840
02a4 dec ax
02a5 je 0x7850
02a7 dec ax
02a8 je 0x7860
02aa jmp 0x786f
02ac cmp word ptr [bp - 0xe], 0
02b0 jl 0x780a
02b2 cmp word ptr [bp - 0xe], 0x3f
02b6 jg 0x780a
02b8 cmp word ptr [bp - 0xc], 0
02bc jl 0x780a
02be cmp word ptr [bp - 0xc], 0x3f
02c2 jg 0x780a
02c4 mov dx, 1
02c7 jmp 0x780c
02c9 nop 
02ca mov bx, word ptr [bp - 0xc]
02cd mov di, word ptr [bp - 0xe]
02d0 shl di, 6
02d3 mov cl, byte ptr [bx + di + 0x28e8]
02d7 jmp 0x786d
02d9 nop 
02da mov bx, word ptr [bp - 0xc]
02dd mov di, word ptr [bp - 0xe]
02e0 shl di, 6
02e3 mov cl, byte ptr [bx + di + 0x48e8]
02e7 jmp 0x786d
02e9 nop 
02ea mov bx, word ptr [bp - 0xc]
02ed mov di, word ptr [bp - 0xe]
02f0 shl di, 6
02f3 mov cl, byte ptr [bx + di + 0x58e8]
02f7 sub ch, ch
02f9 mov di, cx
02fb cmp si, 1
02fe jg 0x7884
0300 push di
0301 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 772, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItFood
0306 add sp, 2
0309 mov dx, ax
030b jmp 0x7896
030d nop 
030e cmp di, 0x10
0311 jl 0x7894
0313 cmp di, 0x13
0316 jg 0x7894
0318 mov dx, 1
031b jmp 0x7896
031d nop 
031e xor dx, dx
0320 or dx, dx
0322 je 0x78a6
0324 mov ax, di
0326 and al, 3
0328 cmp al, 3
032a jge 0x78a6
032c inc di
032d jmp 0x78c1
032f nop 
0330 push word ptr [bp - 0xc]
0333 push word ptr [bp - 0xe]
0336 push si
0337 nop 
0338 push cs
0339 call 0x5b2c ; _IsClearTile
033c add sp, 6
033f or ax, ax
0341 jne 0x78be
0343 cmp di, 0x38
0346 jne 0x78c6
0348 mov di, 0x10
034b mov word ptr [bp - 0xa], 1
0350 cmp word ptr [bp - 0xa], 0
0354 jne 0x78cf
0356 jmp 0x79b4
0359 mov ax, word ptr [bp - 0x10]
035c mov word ptr [0xcf50], ax ; _MeDir
035f cmp si, 1
0362 jg 0x78ec
0364 push word ptr [bp - 0xc]
0367 push word ptr [bp - 0xe]
036a nop 
036b push cs
036c call 0xd86 ; _DropFoodA
036f add sp, 4
0372 jmp 0x7999
0375 nop 
0376 cmp si, 1
0379 jg 0x790e
037b cmp word ptr [bp - 0xe], 0
037f jl 0x7926
0381 cmp word ptr [bp - 0xe], 0x7f
0385 jg 0x7926
0387 cmp word ptr [bp - 0xc], 0
038b jl 0x7926
038d cmp word ptr [bp - 0xc], 0x3f
0391 jg 0x7926
0393 mov dx, 1
0396 jmp 0x7928
0398 cmp word ptr [bp - 0xe], 0
039c jl 0x7926
039e cmp word ptr [bp - 0xe], 0x3f
03a2 jg 0x7926
03a4 cmp word ptr [bp - 0xc], 0
03a8 jl 0x7926
03aa cmp word ptr [bp - 0xc], 0x3f
03ae jle 0x7909
03b0 xor dx, dx
03b2 dec dx
03b3 jne 0x7980
03b5 mov ax, si
03b7 or ax, ax
03b9 jl 0x7971
03bb jo 0x7971
03bd dec ax
03be jle 0x793e
03c0 dec ax
03c1 je 0x7950
03c3 dec ax
03c4 je 0x7962
03c6 jmp 0x7971
03c8 mov ax, di
03ca mov bx, word ptr [bp - 0xe]
03cd shl bx, 6
03d0 add bx, word ptr [bp - 0xc]
03d3 mov byte ptr [bx + 0x28e8], al
03d7 jmp 0x7971
03d9 nop 
03da mov ax, di
03dc mov bx, word ptr [bp - 0xe]
03df shl bx, 6
03e2 add bx, word ptr [bp - 0xc]
03e5 mov byte ptr [bx + 0x48e8], al
03e9 jmp 0x7971
03eb nop 
03ec mov ax, di
03ee mov bx, word ptr [bp - 0xc]
03f1 mov di, word ptr [bp - 0xe]
03f4 shl di, 6
03f7 mov byte ptr [bx + di + 0x58e8], al
03fb push word ptr [bp - 0xc]
03fe push word ptr [bp - 0xe]
0401 push si
0402 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1029, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
0407 add sp, 6
040a cmp si, 2
040d jne 0x7990
040f mov es, word ptr [0xc4a4]
0413 inc word ptr es:[0x9ea4]
0418 jmp 0x7999
041a mov es, word ptr [0xc4a6]
041e inc word ptr es:[0x72de]
0423 push 0x10
0425 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1062, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
042a and word ptr [0xcc84], 0xf7 ; _MeType
0430 push 0x7e
0432 push 0
0434 push 0x1d
0436 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1081, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
043b add sp, 6
043e mov ax, word ptr [bp - 0xa]
0441 pop si
0442 pop di
0443 leave 
0444 retf 
```

## Known declaration examples

- `extern int far GetDir(int a, int b, int c, int d);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far GetDir(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_0000_GetDefendDir_2_scaffold-cdac288ff9.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_IsClear3x3-f787045a5e.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far IsItFood(int tile);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near MeDir;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeDir;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near MeType;` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int near MeType;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_AddWater-d30012f385.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ExchangeLives', 'offset': 26540, 'source': 'src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c', 'size': 149}
- {'symbol': '_DoLifeExchange', 'offset': 26690, 'source': None, 'size': 3379}
- {'symbol': '_DropPebble', 'offset': 31164, 'source': None, 'size': 662}
- {'symbol': '_DropMyRock', 'offset': 31826, 'source': None, 'size': 1334}
