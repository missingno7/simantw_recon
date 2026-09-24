# Recovery task _CalcScore

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 1127 bytes.

```asm
0000 enter 0x18, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 xor ax, ax
000b mov es, word ptr [bp + 8]
000e mov cx, 8
0011 mov di, si
0013 rep stosw word ptr es:[di], ax
0015 mov es, word ptr [0xbeda]
0019 mov al, byte ptr es:[0x9e6e]
001d mov es, word ptr [0xbedc]
0021 mov dx, word ptr es:[0x8670]
0026 mov word ptr [bp - 0xe], dx
0029 sub al, dl
002b and ax, 0x3f
002e mov word ptr [bp - 0xc], ax
0031 mov cx, ax
0033 xor bx, bx
0035 mov word ptr [bp - 6], bx
0038 cmp dx, bx
003a jle 0x55a4
003c mov ax, dx
003e mov word ptr [bp - 4], ax
0041 add bx, ax
0043 mov word ptr [bp - 2], cx
0046 mov word ptr [bp - 0xa], bx
0049 mov si, cx
004b mov cx, dx
004d mov bx, word ptr [bp - 6]
0050 mov <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0053 mov ds, ax
0055 mov di, si
0057 shl di, 1
0059 add bx, word ptr [di - 0x60d0]
005d mov ax, si
005f inc al
0061 and ax, 0x3f
0064 mov si, ax
0066 dec cx
0067 jne 0x5585
0069 mov word ptr [bp - 6], bx
006c mov bx, word ptr [bp - 0xa]
006f mov si, word ptr [bp + 6]
0072 push ss
0073 pop ds
0074 or bx, bx
0076 jle 0x55b6
0078 mov ax, word ptr [bp - 6]
007b cdq 
007c idiv bx
007e mov es, word ptr [bp + 8]
0081 mov word ptr es:[si], ax
0084 jmp 0x55be
0086 mov es, word ptr [bp + 8]
0089 mov word ptr es:[si], 0
008e mov di, word ptr [bp - 0xc]
0091 xor cx, cx
0093 mov word ptr [bp - 6], cx
0096 mov word ptr [bp - 0xa], cx
0099 cmp word ptr [bp - 0xe], cx
009c jg 0x55f6
009e mov di, cx
00a0 add cx, di
00a2 mov word ptr [bp - 2], cx
00a5 or cx, cx
00a7 jle 0x5636
00a9 mov ax, cx
00ab cdq 
00ac push dx
00ad push ax
00ae mov ax, di
00b0 mov cx, 0x64
00b3 imul cx
00b5 push dx
00b6 push ax
00b7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 186, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00bc mov es, word ptr [bp + 8]
00bf mov word ptr es:[si + 2], ax
00c3 jmp 0x563f
00c5 nop 
00c6 mov es, word ptr [0xbedc]
00ca mov ax, word ptr es:[0x8670]
00ce mov word ptr [bp - 4], ax
00d1 mov word ptr [bp - 2], di
00d4 mov si, di
00d6 mov di, word ptr [bp - 6]
00d9 mov <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00dc mov ds, ax
00de mov <resolved loader operand; see bindings> ; [{'operand_offset': 223, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00e1 mov es, ax
00e3 mov bx, si
00e5 shl bx, 1
00e7 add di, word ptr [bx + 0x7c98]
00eb add cx, word ptr es:[bx + 0x7d76]
00f0 mov ax, si
00f2 inc al
00f4 and ax, 0x3f
00f7 mov si, ax
00f9 dec word ptr [bp - 4]
00fc jne 0x5613
00fe mov si, word ptr [bp + 6]
0101 push ss
0102 pop ds
0103 jmp 0x55d0
0105 nop 
0106 mov es, word ptr [bp + 8]
0109 mov word ptr es:[si + 2], 0
010f mov es, word ptr [0xbede]
0113 mov ax, word ptr es:[0x9af8]
0117 mov dx, word ptr es:[0x9afa]
011c mov word ptr [bp - 0x12], ax
011f mov word ptr [bp - 0x10], dx
0122 or dx, dx
0124 jl 0x5692
0126 jg 0x565c
0128 or ax, ax
012a je 0x5692
012c push word ptr [bp - 0x10]
012f push word ptr [bp - 0x12]
0132 push 0
0134 push 0x64
0136 mov ax, word ptr [bp - 0x12]
0139 mov dx, word ptr [bp - 0x10]
013c mov es, word ptr [0xbee0]
0140 sub ax, word ptr es:[0x7c1e]
0145 sbb dx, word ptr es:[0x7c20]
014a push dx
014b push ax
014c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 335, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0151 push dx
0152 push ax
0153 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 342, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0158 mov es, word ptr [bp + 8]
015b mov word ptr es:[si + 4], ax
015f jmp 0x569b
0161 nop 
0162 mov es, word ptr [bp + 8]
0165 mov word ptr es:[si + 4], 0x64
016b mov es, word ptr [0xbee2]
016f mov bx, word ptr es:[0x79e4]
0174 mov word ptr [bp - 0x14], bx
0177 mov es, word ptr [0xbee4]
017b add bx, word ptr es:[0xa0e4]
0180 or bx, bx
0182 jle 0x56c4
0184 imul ax, word ptr [bp - 0x14], 0x64
0188 cdq 
0189 idiv bx
018b mov es, word ptr [bp + 8]
018e mov word ptr es:[si + 6], ax
0192 jmp 0x56cd
0194 mov es, word ptr [bp + 8]
0197 mov word ptr es:[si + 6], 0x64
019d mov es, word ptr [0xbee6]
01a1 mov ax, word ptr es:[0x80b4]
01a5 mov word ptr [bp - 0x16], ax
01a8 cmp ax, 2
01ab je 0x56e2
01ad cmp ax, 3
01b0 jne 0x5716
01b2 mov es, word ptr [0xbee8]
01b6 mov di, word ptr es:[0x80d4]
01bb mov word ptr [bp - 0x18], di
01be mov es, word ptr [0xbeea]
01c2 add di, word ptr es:[0x9c80]
01c7 or di, di
01c9 jle 0x571c
01cb mov ax, di
01cd cdq 
01ce push dx
01cf push ax
01d0 mov ax, 0x64
01d3 imul word ptr [bp - 0x18]
01d6 push dx
01d7 push ax
01d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 475, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
01dd mov es, word ptr [bp + 8]
01e0 mov word ptr es:[si + 8], ax
01e4 jmp 0x5725
01e6 mov es, word ptr [bp + 8]
01e9 jmp 0x583d
01ec mov es, word ptr [bp + 8]
01ef mov word ptr es:[si + 8], 0x64
01f5 mov es, word ptr [0xbeec]
01f9 mov di, word ptr es:[0xa0dc]
01fe add di, word ptr [bp - 0x18]
0201 or di, di
0203 jle 0x5750
0205 mov ax, di
0207 cdq 
0208 push dx
0209 push ax
020a mov ax, 0x64
020d imul word ptr [bp - 0x18]
0210 push dx
0211 push ax
0212 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 533, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0217 mov es, word ptr [bp + 8]
021a mov word ptr es:[si + 0xa], ax
021e jmp 0x5759
0220 mov es, word ptr [bp + 8]
0223 mov word ptr es:[si + 0xa], 0x64
0229 xor dx, dx
022b mov word ptr [bp - 6], dx
022e mov <resolved loader operand; see bindings> ; [{'operand_offset': 559, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0231 mov ds, ax
0233 cmp dx, 5
0236 jl 0x576e
0238 mov cx, 2
023b jmp 0x5771
023d nop 
023e mov cx, 3
0241 cmp cx, 0xc
0244 jge 0x57a7
0246 mov bx, cx
0248 shl bx, 4
024b add bx, dx
024d add bx, 0xa4
0251 mov di, 0xc
0254 sub di, cx
0256 mov word ptr [bp - 2], di
0259 mov word ptr [bp - 4], dx
025c mov word ptr [bp - 0xa], cx
025f mov di, word ptr [bp - 6]
0262 mov cx, word ptr [bp - 2]
0265 cmp byte ptr [bx], 0
0268 je 0x579b
026a inc di
026b add bx, 0x10
026e dec cx
026f jne 0x5795
0271 mov word ptr [bp - 6], di
0274 mov dx, word ptr [bp - 4]
0277 inc dx
0278 cmp dx, 0x10
027b jl 0x5763
027d push ss
027e pop ds
027f mov di, word ptr [bp - 6]
0282 or di, di
0284 jle 0x57d2
0286 mov si, word ptr [bp + 6]
0289 push 0
028b push 0x9b
028e mov ax, di
0290 mov cx, 0x64
0293 imul cx
0295 push dx
0296 push ax
0297 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 666, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
029c mov word ptr es:[si + 0xc], ax
02a0 jmp 0x57db
02a2 mov si, word ptr [bp + 6]
02a5 mov word ptr es:[si + 0xc], 0
02ab xor di, di
02ad mov word ptr [bp - 4], di
02b0 mov <resolved loader operand; see bindings> ; [{'operand_offset': 689, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
02b3 mov ds, ax
02b5 xor cx, cx
02b7 mov bx, word ptr [bp - 4]
02ba add bx, 0xa4
02be cmp cx, 2
02c1 jl 0x57fe
02c3 cmp word ptr [bp - 4], 5
02c7 jge 0x580a
02c9 cmp cx, 3
02cc jge 0x580a
02ce cmp byte ptr [bx], 0
02d1 je 0x5804
02d3 inc di
02d4 add bx, 0x10
02d7 inc cx
02d8 jmp 0x57ee
02da inc word ptr [bp - 4]
02dd cmp word ptr [bp - 4], 0x10
02e1 jl 0x57e5
02e3 push ss
02e4 pop ds
02e5 or di, di
02e7 jle 0x5834
02e9 mov si, word ptr [bp + 6]
02ec push 0
02ee push 0x25
02f0 mov ax, di
02f2 mov cx, 0x64
02f5 imul cx
02f7 push dx
02f8 push ax
02f9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 764, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
02fe mov word ptr es:[si + 0xe], ax
0302 jmp 0x583d
0304 mov si, word ptr [bp + 6]
0307 mov word ptr es:[si + 0xe], 0
030d mov ax, word ptr [0xac8a] ; _MeHealth
0310 cdq 
0311 mov word ptr [bp - 4], ax
0314 mov word ptr [bp - 2], dx
0317 xor cx, cx
0319 mov di, si
031b mov word ptr [bp - 6], es
031e mov word ptr [bp - 0xa], cx
0321 mov si, cx
0323 push 0
0325 push 0x33
0327 mov al, byte ptr [si + 0x948]
032b cwde 
032c mov bx, di
032e add di, 2
0331 imul word ptr es:[bx]
0334 push dx
0335 push ax
0336 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 825, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
033b add word ptr [bp - 4], ax
033e adc word ptr [bp - 2], dx
0341 inc si
0342 cmp si, 8
0345 jl 0x5853
0347 cmp word ptr [bp - 0x16], 2
034b jne 0x5880
034d jmp 0x5910
0350 push 0
0352 push 0xa
0354 push 0
0356 push 0x1d
0358 push word ptr [bp - 2]
035b push word ptr [bp - 4]
035e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 865, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0363 push dx
0364 push ax
0365 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 872, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
036a mov word ptr [bp - 4], ax
036d mov word ptr [bp - 2], dx
0370 mov <resolved loader operand; see bindings> ; [{'operand_offset': 881, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0373 mov es, ax
0375 cmp word ptr es:[0x76aa], 0
037b jle 0x58b0
037d jmp 0x5984
0380 jl 0x58be
0382 cmp word ptr es:[0x76a8], 0x1004
0389 jb 0x58be
038b jmp 0x5984
038e push 0
0390 push 0x64
0392 push word ptr es:[0x76aa]
0397 push word ptr es:[0x76a8]
039c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 927, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
03a1 mov word ptr [bp - 8], ax
03a4 mov word ptr [bp - 6], dx
03a7 or dx, dx
03a9 jg 0x58eb
03ab jl 0x58e1
03ad or ax, ax
03af jne 0x58eb
03b1 mov word ptr [bp - 8], 1
03b6 mov word ptr [bp - 6], 0
03bb push 0
03bd push 0x29
03bf push word ptr [bp - 2]
03c2 push word ptr [bp - 4]
03c5 push word ptr [bp - 6]
03c8 push word ptr [bp - 8]
03cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 974, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
03d0 push dx
03d1 push ax
03d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 981, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
03d7 mov word ptr [bp - 4], ax
03da mov word ptr [bp - 2], dx
03dd jmp 0x5984
03df nop 
03e0 mov <resolved loader operand; see bindings> ; [{'operand_offset': 993, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
03e3 mov es, ax
03e5 cmp word ptr es:[0x76aa], 0
03eb jg 0x5977
03ed jl 0x5928
03ef cmp word ptr es:[0x76a8], 0x1fa4
03f6 jae 0x5977
03f8 push 0
03fa push 0x64
03fc push word ptr es:[0x76aa]
0401 push word ptr es:[0x76a8]
0406 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1033, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
040b mov word ptr [bp - 8], ax
040e mov word ptr [bp - 6], dx
0411 or dx, dx
0413 jg 0x5955
0415 jl 0x594b
0417 or ax, ax
0419 jne 0x5955
041b mov word ptr [bp - 8], 1
0420 mov word ptr [bp - 6], 0
0425 push 0
0427 push 0x51
0429 push word ptr [bp - 2]
042c push word ptr [bp - 4]
042f push word ptr [bp - 6]
0432 push word ptr [bp - 8]
0435 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1080, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
043a push dx
043b push ax
043c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1087, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0441 mov word ptr [bp - 4], ax
0444 mov word ptr [bp - 2], dx
0447 push 0
0449 push 5
044b lea ax, [bp - 4]
044e push ax
044f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1106, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFNaulmul,__aFNalmul
0454 mov ax, word ptr es:[0x76a8]
0458 mov dx, word ptr es:[0x76aa]
045d add ax, word ptr [bp - 4]
0460 adc dx, word ptr [bp - 2]
0463 pop si
0464 pop di
0465 leave 
0466 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int near MeHealth;` — src/recovered/wf_SetMyHealth-5d15d1e8e5.c
- `extern int near MeHealth;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near MeHealth;` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitApplicationWindows', 'offset': 21604, 'source': 'src/recovered/wf_InitApplicationWindows-84f4e064cb.c', 'size': 197}
- {'symbol': '_InitApplicationStuff', 'offset': 21802, 'source': 'src/initapp.c', 'size': 6}
- {'symbol': '_DoScenario', 'offset': 22936, 'source': 'src/recovered/wf_DoScenario-496dc7a0ac.c', 'size': 275}
- {'symbol': '_DoWinHelp', 'offset': 23212, 'source': 'src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c', 'size': 30}
