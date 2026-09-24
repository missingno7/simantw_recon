# Recovery task _DropMyRock

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 1334 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov dx, word ptr [0xcc84] ; _MeType
000a cmp dx, 0x28
000d je 0x7c6c
000f cmp dx, 0x48
0012 je 0x7c6c
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
0033 mov di, ax
0035 or di, di
0037 jle 0x7c8e
0039 dec di
003a jmp 0x7c92
003c mov di, word ptr [0xcf50] ; _MeDir
0040 mov word ptr [bp - 6], 0
0045 mov word ptr [bp - 8], di
0048 mov di, word ptr [bp - 0xe]
004b mov si, word ptr [bp - 0xc]
004e cmp word ptr [bp - 6], 8
0052 jl 0x7ca9
0054 jmp 0x7f23
0057 mov es, word ptr [0xc4a2]
005b mov bx, word ptr [bp - 6]
005e mov bl, byte ptr es:[bx + 0x6c]
0063 add bl, byte ptr [bp - 8]
0066 and bx, 7
0069 mov word ptr [bp - 0x10], bx
006c mov es, word ptr [0xc47a]
0070 mov al, byte ptr es:[bx]
0075 cwde 
0076 mov di, ax
0078 add di, word ptr [bp + 8]
007b mov es, word ptr [0xc478]
007f mov al, byte ptr es:[bx + 8]
0084 cwde 
0085 mov si, ax
0087 add si, word ptr [bp + 0xa]
008a cmp word ptr [bp + 6], 1
008e jg 0x7cfa
0090 or di, di
0092 jl 0x7d0c
0094 cmp di, 0x7f
0097 jg 0x7d0c
0099 or si, si
009b jl 0x7d0c
009d cmp si, 0x3f
00a0 jg 0x7d0c
00a2 mov dx, 1
00a5 jmp 0x7d0e
00a7 nop 
00a8 or di, di
00aa jl 0x7d0c
00ac cmp di, 0x3f
00af jg 0x7d0c
00b1 or si, si
00b3 jl 0x7d0c
00b5 cmp si, 0x3f
00b8 jle 0x7cf4
00ba xor dx, dx
00bc or dx, dx
00be jne 0x7d15
00c0 jmp 0x7f17
00c3 mov dx, 0xffff
00c6 cmp word ptr [bp + 6], 1
00ca jg 0x7d36
00cc or di, di
00ce jl 0x7d48
00d0 cmp di, 0x7f
00d3 jg 0x7d48
00d5 or si, si
00d7 jl 0x7d48
00d9 cmp si, 0x3f
00dc jg 0x7d48
00de mov cx, 1
00e1 jmp 0x7d4a
00e3 nop 
00e4 or di, di
00e6 jl 0x7d48
00e8 cmp di, 0x3f
00eb jg 0x7d48
00ed or si, si
00ef jl 0x7d48
00f1 cmp si, 0x3f
00f4 jle 0x7d30
00f6 xor cx, cx
00f8 dec cx
00f9 jne 0x7d8c
00fb mov ax, word ptr [bp + 6]
00fe or ax, ax
0100 jl 0x7d85
0102 jo 0x7d85
0104 dec ax
0105 jle 0x7d62
0107 dec ax
0108 je 0x7d6e
010a dec ax
010b je 0x7d7a
010d jmp 0x7d85
010f nop 
0110 mov bx, di
0112 shl bx, 6
0115 mov dl, byte ptr [bx + si + 0x68e8]
0119 jmp 0x7d83
011b nop 
011c mov bx, di
011e shl bx, 6
0121 mov dl, byte ptr [bx + si - 0x7718]
0125 jmp 0x7d83
0127 nop 
0128 mov bx, di
012a shl bx, 6
012d mov dl, byte ptr [bx + si - 0x6718]
0131 sub dh, dh
0133 or dx, dx
0135 jne 0x7d8c
0137 mov dx, 0xffff
013a or dx, dx
013c jl 0x7d93
013e jmp 0x7f17
0141 push si
0142 push di
0143 push word ptr [bp + 6]
0146 nop 
0147 push cs
0148 call 0x5b2c ; _IsClearTile
014b add sp, 6
014e or ax, ax
0150 je 0x7da7
0152 jmp 0x7f12
0155 mov cx, 0xffff
0158 cmp word ptr [bp + 6], 1
015c jg 0x7dc8
015e or di, di
0160 jl 0x7dda
0162 cmp di, 0x7f
0165 jg 0x7dda
0167 or si, si
0169 jl 0x7dda
016b cmp si, 0x3f
016e jg 0x7dda
0170 mov dx, 1
0173 jmp 0x7ddc
0175 nop 
0176 or di, di
0178 jl 0x7dda
017a cmp di, 0x3f
017d jg 0x7dda
017f or si, si
0181 jl 0x7dda
0183 cmp si, 0x3f
0186 jle 0x7dc2
0188 xor dx, dx
018a dec dx
018b jne 0x7e17
018d mov ax, word ptr [bp + 6]
0190 or ax, ax
0192 jl 0x7e17
0194 jo 0x7e17
0196 dec ax
0197 jle 0x7df4
0199 dec ax
019a je 0x7e00
019c dec ax
019d je 0x7e0c
019f jmp 0x7e17
01a1 nop 
01a2 mov bx, di
01a4 shl bx, 6
01a7 mov cl, byte ptr [bx + si + 0x28e8]
01ab jmp 0x7e15
01ad nop 
01ae mov bx, di
01b0 shl bx, 6
01b3 mov cl, byte ptr [bx + si + 0x48e8]
01b7 jmp 0x7e15
01b9 nop 
01ba mov bx, di
01bc shl bx, 6
01bf mov cl, byte ptr [bx + si + 0x58e8]
01c3 sub ch, ch
01c5 mov word ptr [bp - 2], cx
01c8 cmp word ptr [bp + 6], 1
01cc jg 0x7e2e
01ce push cx
01cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 466, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItFood
01d4 add sp, 2
01d7 mov dx, ax
01d9 jmp 0x7e40
01db nop 
01dc cmp cx, 0x10
01df jl 0x7e3e
01e1 cmp cx, 0x13
01e4 jg 0x7e3e
01e6 mov dx, 1
01e9 jmp 0x7e40
01eb nop 
01ec xor dx, dx
01ee or dx, dx
01f0 je 0x7e47
01f2 jmp 0x7f17
01f5 cmp word ptr [bp + 6], 1
01f9 jg 0x7e60
01fb jne 0x7e6c
01fd cmp word ptr [bp - 2], 0x51
0201 jl 0x7e6c
0203 cmp word ptr [bp - 2], 0x53
0207 jg 0x7e6c
0209 mov dx, 1
020c jmp 0x7e6c
020e cmp word ptr [bp - 2], 0x30
0212 jl 0x7e6c
0214 cmp word ptr [bp - 2], 0x31
0218 jle 0x7e5b
021a or dx, dx
021c je 0x7e73
021e jmp 0x7f17
0221 cmp word ptr [bp + 6], 1
0225 jg 0x7e88
0227 push si
0228 push di
0229 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 556, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItHole
022e add sp, 4
0231 mov dx, ax
0233 jmp 0x7f08
0236 or si, si
0238 jg 0x7f08
023a mov cx, 0xffff
023d cmp word ptr [bp + 6], 1
0241 jg 0x7eae
0243 or di, di
0245 jl 0x7ec0
0247 cmp di, 0x7f
024a jg 0x7ec0
024c or si, si
024e jl 0x7ec0
0250 cmp si, 0x3f
0253 jg 0x7ec0
0255 mov dx, 1
0258 jmp 0x7ec0
025a nop 
025b nop 
025c or di, di
025e jl 0x7ec0
0260 cmp di, 0x3f
0263 jg 0x7ec0
0265 or si, si
0267 jl 0x7ec0
0269 cmp si, 0x3f
026c jle 0x7ea7
026e dec dx
026f jne 0x7efb
0271 mov ax, word ptr [bp + 6]
0274 or ax, ax
0276 jl 0x7efb
0278 jo 0x7efb
027a dec ax
027b jle 0x7ed8
027d dec ax
027e je 0x7ee4
0280 dec ax
0281 je 0x7ef0
0283 jmp 0x7efb
0285 nop 
0286 mov bx, di
0288 shl bx, 6
028b mov cl, byte ptr [bx + si + 0x28e8]
028f jmp 0x7ef9
0291 nop 
0292 mov bx, di
0294 shl bx, 6
0297 mov cl, byte ptr [bx + si + 0x48e8]
029b jmp 0x7ef9
029d nop 
029e mov bx, di
02a0 shl bx, 6
02a3 mov cl, byte ptr [bx + si + 0x58e8]
02a7 sub ch, ch
02a9 cmp cx, 0x18
02ac jne 0x7f06
02ae mov dx, 1
02b1 jmp 0x7f08
02b3 nop 
02b4 xor dx, dx
02b6 or dx, dx
02b8 jne 0x7f12
02ba cmp word ptr [bp - 2], 0x38
02be jne 0x7f17
02c0 mov word ptr [bp - 0xa], 1
02c5 inc word ptr [bp - 6]
02c8 cmp word ptr [bp - 0xa], 0
02cc jne 0x7f23
02ce jmp 0x7ca0
02d1 mov word ptr [bp - 0xc], si
02d4 mov word ptr [bp - 0xe], di
02d7 cmp word ptr [bp - 0xa], 0
02db je 0x7f32
02dd jmp 0x813c
02e0 mov ax, word ptr [bp - 8]
02e3 mov word ptr [bp - 0x10], ax
02e6 mov ax, word ptr [bp + 8]
02e9 mov word ptr [bp - 0xe], ax
02ec mov ax, word ptr [bp + 0xa]
02ef mov word ptr [bp - 0xc], ax
02f2 cmp word ptr [bp + 6], 1
02f6 jg 0x7f82
02f8 cmp word ptr [bp - 0xe], 0
02fc jl 0x7f60
02fe cmp word ptr [bp - 0xe], 0x7f
0302 jg 0x7f60
0304 or ax, ax
0306 jl 0x7f60
0308 cmp ax, 0x3f
030b jmp 0x7f98
030d nop 
030e xor dx, dx
0310 or dx, dx
0312 jne 0x7f69
0314 jmp 0x813c
0317 push word ptr [bp - 0xc]
031a push word ptr [bp - 0xe]
031d push word ptr [bp + 6]
0320 nop 
0321 push cs
0322 call 0x5b2c ; _IsClearTile
0325 add sp, 6
0328 or ax, ax
032a je 0x7fa0
032c jmp 0x8137
032f nop 
0330 cmp word ptr [bp - 0xe], 0
0334 jl 0x7f60
0336 cmp word ptr [bp - 0xe], 0x3f
033a jg 0x7f60
033c cmp word ptr [bp - 0xc], 0
0340 jl 0x7f60
0342 cmp word ptr [bp - 0xc], 0x3f
0346 jg 0x7f60
0348 mov dx, 1
034b jmp 0x7f62
034d nop 
034e mov cx, 0xffff
0351 cmp word ptr [bp + 6], 1
0355 jg 0x7fc6
0357 cmp word ptr [bp - 0xe], 0
035b jl 0x7fde
035d cmp word ptr [bp - 0xe], 0x7f
0361 jg 0x7fde
0363 cmp word ptr [bp - 0xc], 0
0367 jl 0x7fde
0369 cmp word ptr [bp - 0xc], 0x3f
036d jg 0x7fde
036f mov dx, 1
0372 jmp 0x7fe0
0374 cmp word ptr [bp - 0xe], 0
0378 jl 0x7fde
037a cmp word ptr [bp - 0xe], 0x3f
037e jg 0x7fde
0380 cmp word ptr [bp - 0xc], 0
0384 jl 0x7fde
0386 cmp word ptr [bp - 0xc], 0x3f
038a jle 0x7fc1
038c xor dx, dx
038e dec dx
038f jne 0x8027
0391 mov ax, word ptr [bp + 6]
0394 or ax, ax
0396 jl 0x8027
0398 jo 0x8027
039a dec ax
039b jle 0x7ff8
039d dec ax
039e je 0x8008
03a0 dec ax
03a1 je 0x8018
03a3 jmp 0x8027
03a5 nop 
03a6 mov si, word ptr [bp - 0xe]
03a9 shl si, 6
03ac mov bx, word ptr [bp - 0xc]
03af mov cl, byte ptr [bx + si + 0x28e8]
03b3 jmp 0x8025
03b5 nop 
03b6 mov si, word ptr [bp - 0xe]
03b9 shl si, 6
03bc mov bx, word ptr [bp - 0xc]
03bf mov cl, byte ptr [bx + si + 0x48e8]
03c3 jmp 0x8025
03c5 nop 
03c6 mov si, word ptr [bp - 0xe]
03c9 shl si, 6
03cc mov bx, word ptr [bp - 0xc]
03cf mov cl, byte ptr [bx + si + 0x58e8]
03d3 sub ch, ch
03d5 mov di, cx
03d7 cmp word ptr [bp + 6], 1
03db jg 0x803c
03dd push di
03de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 993, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItFood
03e3 add sp, 2
03e6 mov si, ax
03e8 jmp 0x804e
03ea cmp di, 0x10
03ed jl 0x804c
03ef cmp di, 0x13
03f2 jg 0x804c
03f4 mov si, 1
03f7 jmp 0x804e
03f9 nop 
03fa xor si, si
03fc or si, si
03fe je 0x8055
0400 jmp 0x813c
0403 cmp word ptr [bp + 6], 1
0407 jg 0x806c
0409 jne 0x8076
040b cmp di, 0x51
040e jl 0x8076
0410 cmp di, 0x53
0413 jg 0x8076
0415 mov dx, 1
0418 jmp 0x8078
041a cmp di, 0x30
041d jl 0x8076
041f cmp di, 0x31
0422 jle 0x8067
0424 xor dx, dx
0426 or dx, dx
0428 je 0x807f
042a jmp 0x813c
042d cmp word ptr [bp + 6], 1
0431 jg 0x8098
0433 push word ptr [bp - 0xc]
0436 push word ptr [bp - 0xe]
0439 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1084, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItHole
043e add sp, 4
0441 mov si, ax
0443 jmp 0x812e
0446 cmp word ptr [bp - 0xc], dx
0449 jle 0x80a0
044b jmp 0x812c
044e mov cx, 0xffff
0451 cmp word ptr [bp + 6], 1
0455 jg 0x80c4
0457 cmp word ptr [bp - 0xe], dx
045a jl 0x80da
045c cmp word ptr [bp - 0xe], 0x7f
0460 jg 0x80da
0462 cmp word ptr [bp - 0xc], dx
0465 jl 0x80da
0467 cmp word ptr [bp - 0xc], 0x3f
046b jg 0x80da
046d mov dx, 1
0470 jmp 0x80da
0472 cmp word ptr [bp - 0xe], dx
0475 jl 0x80da
0477 cmp word ptr [bp - 0xe], 0x3f
047b jg 0x80da
047d cmp word ptr [bp - 0xc], dx
0480 jl 0x80da
0482 cmp word ptr [bp - 0xc], 0x3f
0486 jle 0x80bf
0488 dec dx
0489 jne 0x8121
048b mov ax, word ptr [bp + 6]
048e or ax, ax
0490 jl 0x8121
0492 jo 0x8121
0494 dec ax
0495 jle 0x80f2
0497 dec ax
0498 je 0x8102
049a dec ax
049b je 0x8112
049d jmp 0x8121
049f nop 
04a0 mov bx, word ptr [bp - 0xc]
04a3 mov si, word ptr [bp - 0xe]
04a6 shl si, 6
04a9 mov cl, byte ptr [bx + si + 0x28e8]
04ad jmp 0x811f
04af nop 
04b0 mov bx, word ptr [bp - 0xc]
04b3 mov si, word ptr [bp - 0xe]
04b6 shl si, 6
04b9 mov cl, byte ptr [bx + si + 0x48e8]
04bd jmp 0x811f
04bf nop 
04c0 mov bx, word ptr [bp - 0xc]
04c3 mov si, word ptr [bp - 0xe]
04c6 shl si, 6
04c9 mov cl, byte ptr [bx + si + 0x58e8]
04cd sub ch, ch
04cf cmp cx, 0x18
04d2 jne 0x812c
04d4 mov si, 1
04d7 jmp 0x812e
04d9 nop 
04da xor si, si
04dc or si, si
04de jne 0x8137
04e0 cmp di, 0x38
04e3 jne 0x813c
04e5 mov word ptr [bp - 0xa], 1
04ea cmp word ptr [bp - 0xa], 0
04ee je 0x8181
04f0 mov ax, word ptr [bp - 0x10]
04f3 mov word ptr [0xcf50], ax ; _MeDir
04f6 push word ptr [bp - 0xc]
04f9 push word ptr [bp - 0xe]
04fc push word ptr [bp + 6]
04ff nop 
0500 push cs
0501 call 0x79bc ; _DropPebble
0504 add sp, 6
0507 push 0x10
0509 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1290, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
050e cmp word ptr [0xcc84], 0x28 ; _MeType
0513 je 0x816e
0515 cmp word ptr [0xcc84], 0x48 ; _MeType
051a jne 0x8173
051c sub word ptr [0xcc84], 0x18 ; _MeType
0521 push 0x7e
0523 push 0
0525 push 0x1e
0527 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1322, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
052c add sp, 6
052f mov ax, word ptr [bp - 0xa]
0532 pop si
0533 pop di
0534 leave 
0535 retf 
```

## Known declaration examples

- `extern int far GetDir(int a, int b, int c, int d);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far GetDir(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_0000_GetDefendDir_2_scaffold-cdac288ff9.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_IsClear3x3-f787045a5e.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far IsItFood(int tile);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int far IsItHole(int x, int y);` — src/recovered/wf_IsItAHole-fd9d6ad240.c
- `extern int near MeDir;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeDir;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near MeType;` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int near MeType;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_GetDir'], 'segment': 5, 'target_offset': 4300, 'caller_offsets': [45]}
- {'callee_names': ['_IsClearTile'], 'segment': 5, 'target_offset': 23340, 'caller_offsets': [328, 802]}
- {'callee_names': ['_DropPebble'], 'segment': 5, 'target_offset': 31164, 'caller_offsets': [1281]}

## Neighbors

- {'symbol': '_DropMyFood', 'offset': 30070, 'source': None, 'size': 1093}
- {'symbol': '_DropPebble', 'offset': 31164, 'source': None, 'size': 662}
- {'symbol': '_DropMyEgg', 'offset': 33160, 'source': None, 'size': 1126}
- {'symbol': '_PickupMyRock', 'offset': 34286, 'source': None, 'size': 692}
