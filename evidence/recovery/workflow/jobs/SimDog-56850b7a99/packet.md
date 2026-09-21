# Recovery task _SimDog

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 946 bytes.

```asm
0000 enter 0x18, 0
0004 push di
0005 push si
0006 mov bx, 0x7a5a
0009 mov es, word ptr [0xc502]
000d mov word ptr [bp - 8], bx
0010 mov word ptr [bp - 6], es
0013 dec word ptr es:[bx]
0016 js 0x2dd7
0018 jmp 0x2f71
001b cmp word ptr [0xac6c], 0 ; _CatOn
0020 je 0x2e1c
0022 mov bx, 0x77b0
0025 mov es, word ptr [0xc55c]
0029 mov word ptr [bp - 0xc], bx
002c mov word ptr [bp - 0xa], es
002f cmp word ptr es:[bx], 5
0033 jge 0x2df8
0035 mov ax, 1
0038 jmp 0x2f61
003b nop 
003c les bx, ptr [bp - 0xc]
003f cmp word ptr es:[bx], 8
0043 jle 0x2e08
0045 mov ax, 3
0048 jmp 0x2f61
004b nop 
004c mov es, word ptr [0xc55e]
0050 cmp word ptr es:[0x789c], 0
0056 jg 0x2e17
0058 jmp 0x2f56
005b xor ax, ax
005d jmp 0x2f61
0060 mov es, word ptr [0xc50e]
0064 cmp word ptr es:[0x8a86], 0x26
006a jge 0x2e44
006c push 3
006e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 113, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0073 add sp, 2
0076 mov es, word ptr [0xc512]
007a add al, byte ptr es:[0x7d5a]
007f dec al
0081 and ax, 3
0084 jmp 0x2f65
0087 nop 
0088 mov es, word ptr [0xc55e]
008c mov si, word ptr es:[0x789c]
0091 mov es, word ptr [0xc508]
0095 sub si, word ptr es:[0x78d2]
009a mov es, word ptr [0xc55c]
009e mov ax, word ptr es:[0x77b0]
00a2 mov es, word ptr [0xc506]
00a6 sub ax, word ptr es:[0x78b0]
00ab mov word ptr [bp - 2], ax
00ae or ax, ax
00b0 jge 0x2e70
00b2 neg ax
00b4 mov word ptr [bp - 4], ax
00b7 or si, si
00b9 jge 0x2e7e
00bb mov di, si
00bd neg di
00bf jmp 0x2e80
00c1 nop 
00c2 mov di, si
00c4 cmp ax, 1
00c7 jl 0x2e88
00c9 jmp 0x2f27
00cc cmp di, 1
00cf jl 0x2e90
00d1 jmp 0x2f27
00d4 mov es, word ptr [0xc520]
00d8 cmp word ptr es:[0x7c92], 0
00de jne 0x2e9f
00e0 jmp 0x2f27
00e3 mov es, word ptr [0xc546]
00e7 cmp word ptr es:[0x8610], 0
00ed jne 0x2f27
00ef cmp word ptr [0xce82], 2 ; _YardMode
00f4 jge 0x2f27
00f6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 249, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00fb mov es, word ptr [0xc560]
00ff cmp dx, word ptr es:[0x9de8]
0104 jl 0x2f27
0106 jg 0x2ecb
0108 cmp ax, word ptr es:[0x9de6]
010d jbe 0x2f27
010f mov ax, 1
0112 dec ax
0113 je 0x2ee2
0115 dec ax
0116 je 0x2eda
0118 dec ax
0119 je 0x2eea
011b jmp 0x2ef8
011d nop 
011e push 0x7f
0120 push 0
0122 push 0x17
0124 jmp 0x2ef0
0126 push 0x7f
0128 push 0
012a push 0x15
012c jmp 0x2ef0
012e push 0x7f
0130 push 0
0132 push 0x16
0134 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0139 add sp, 6
013c push 0x1e
013e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 321, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0143 add sp, 2
0146 cdq 
0147 mov word ptr [bp - 0x10], ax
014a mov word ptr [bp - 0xe], dx
014d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 336, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0152 add ax, word ptr [bp - 0x10]
0155 adc dx, word ptr [bp - 0xe]
0158 add ax, 0x3c
015b adc dx, 0
015e mov es, word ptr [0xc560]
0162 mov word ptr es:[0x9de6], ax
0166 mov word ptr es:[0x9de8], dx
016b cmp word ptr [bp - 4], 2
016f jge 0x2f32
0171 cmp di, 2
0174 jl 0x2f56
0176 or si, si
0178 jge 0x2f3c
017a mov ax, 2
017d jmp 0x2f61
017f nop 
0180 cmp si, 1
0183 jle 0x2f44
0185 jmp 0x2e17
0188 cmp word ptr [bp - 2], 0
018c jge 0x2f4d
018e jmp 0x2df1
0191 cmp word ptr [bp - 2], 1
0195 jle 0x2f56
0197 jmp 0x2e01
019a mov es, word ptr [0xc52c]
019e mov al, byte ptr es:[0x7a5c]
01a2 and ax, 3
01a5 mov es, word ptr [0xc512]
01a9 mov word ptr es:[0x7d5a], ax
01ad les bx, ptr [bp - 8]
01b0 mov word ptr es:[bx], 4
01b5 mov bx, 0x7d5a
01b8 mov es, word ptr [0xc512]
01bc mov word ptr [bp - 0x14], bx
01bf mov word ptr [bp - 0x12], es
01c2 cmp word ptr es:[bx], 1
01c6 jne 0x2fa8
01c8 push 0xa
01ca lcall <resolved loader operand; see bindings> ; [{'operand_offset': 461, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
01cf add sp, 2
01d2 or ax, ax
01d4 jne 0x2fa8
01d6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 473, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
01db add ax, 4
01de les bx, ptr [bp - 0x14]
01e1 mov word ptr es:[bx], ax
01e4 les bx, ptr [bp - 8]
01e7 mov word ptr es:[bx], 6
01ec les bx, ptr [bp - 0x14]
01ef cmp word ptr es:[bx], 3
01f3 jle 0x2fc8
01f5 mov bx, word ptr es:[bx]
01f8 mov al, byte ptr [bx + 0x237a]
01fc cwde 
01fd mov si, ax
01ff mov es, word ptr [0xc52c]
0203 mov al, byte ptr es:[0x7a5c]
0207 and ax, 1
020a jmp 0x2fe6
020c mov es, word ptr [0xc52c]
0210 mov bl, byte ptr es:[0x7a5c]
0215 and bx, 3
0218 mov al, byte ptr [bx + 0x2376]
021c cwde 
021d mov si, ax
021f les bx, ptr [bp - 0x14]
0222 mov bx, word ptr es:[bx]
0225 mov al, byte ptr [bx + 0x237a]
0229 cwde 
022a add si, ax
022c les bx, ptr [bp - 0x14]
022f mov bx, word ptr es:[bx]
0232 mov al, byte ptr [bx + 0x2370]
0236 cwde 
0237 add word ptr [0xac5e], ax ; _DogY
023b mov ax, word ptr [0xac5e] ; _DogY
023e sub ax, 0x26
0241 mov cx, 0xa
0244 cdq 
0245 idiv cx
0247 mov di, 0x789c
024a mov es, word ptr [0xc55e]
024e mov word ptr [bp - 0x18], di
0251 mov word ptr [bp - 0x16], es
0254 mov word ptr es:[di], ax
0257 mov cx, 0x1c
025a mov dx, ax
025c mov al, byte ptr [bx + 0x236a]
0260 cwde 
0261 add word ptr [0xac5c], ax ; _DogX
0265 mov ax, word ptr [0xac5e] ; _DogY
0268 add ax, word ptr [0xac5c] ; _DogX
026c sub ax, 0xc8
026f mov bx, dx
0271 cdq 
0272 idiv cx
0274 mov di, 0x77b0
0277 mov es, word ptr [0xc55c]
027b mov word ptr [bp - 0xc], di
027e mov word ptr [bp - 0xa], es
0281 mov word ptr es:[di], ax
0284 or bx, bx
0286 jge 0x304c
0288 les bx, ptr [bp - 0x18]
028b mov word ptr es:[bx], 0
0290 les bx, ptr [bp - 0x18]
0293 cmp word ptr es:[bx], 0xf
0297 jle 0x305a
0299 mov word ptr es:[bx], 0xf
029e les bx, ptr [bp - 0xc]
02a1 cmp word ptr es:[bx], 0
02a5 jge 0x3068
02a7 mov word ptr es:[bx], 0
02ac cmp word ptr es:[bx], 0xb
02b0 jle 0x3073
02b2 mov word ptr es:[bx], 0xb
02b7 les bx, ptr [bp - 0x18]
02ba cmp word ptr es:[bx], 1
02be jge 0x3086
02c0 les bx, ptr [bp - 0x14]
02c3 mov word ptr es:[bx], 2
02c8 jmp 0x3094
02ca cmp word ptr es:[bx], 0xe
02ce jle 0x3094
02d0 les bx, ptr [bp - 0x14]
02d3 mov word ptr es:[bx], 0
02d8 les bx, ptr [bp - 0xc]
02db cmp word ptr es:[bx], 0xa
02df jle 0x30a8
02e1 les bx, ptr [bp - 0x14]
02e4 mov word ptr es:[bx], 3
02e9 jmp 0x30b6
02eb nop 
02ec cmp word ptr es:[bx], 4
02f0 jge 0x30b6
02f2 les bx, ptr [bp - 0x14]
02f5 mov word ptr es:[bx], 1
02fa mov word ptr [0xac60], si ; _DogFrame
02fe cmp si, 0x64
0301 jge 0x30c2
0303 jmp 0x316a
0306 cmp si, 0x67
0309 jle 0x30ca
030b jmp 0x316a
030e push 6
0310 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 787, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0315 add sp, 2
0318 or ax, ax
031a je 0x30db
031c jmp 0x316a
031f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 802, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
0324 mov si, ax
0326 mov es, word ptr [0xc546]
032a cmp word ptr es:[0x8610], 0
0330 jne 0x316a
0332 cmp word ptr [0xce82], 2 ; _YardMode
0337 jge 0x316a
0339 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 828, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
033e mov es, word ptr [0xc560]
0342 cmp dx, word ptr es:[0x9de8]
0347 jl 0x316a
0349 jg 0x310e
034b cmp ax, word ptr es:[0x9de6]
0350 jbe 0x316a
0352 mov ax, si
0354 or ax, ax
0356 je 0x3120
0358 dec ax
0359 je 0x3128
035b dec ax
035c je 0x3120
035e dec ax
035f je 0x3130
0361 jmp 0x313e
0363 nop 
0364 push 5
0366 push 0
0368 push 0x17
036a jmp 0x3136
036c push 5
036e push 0
0370 push 0x15
0372 jmp 0x3136
0374 push 5
0376 push 0
0378 push 0x16
037a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 893, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
037f add sp, 6
0382 push 0x1e
0384 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 903, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0389 add sp, 2
038c cdq 
038d mov si, ax
038f mov di, dx
0391 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 916, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0396 add si, ax
0398 adc di, dx
039a add si, 0x3c
039d adc di, 0
03a0 mov es, word ptr [0xc560]
03a4 mov word ptr es:[0x9de6], si
03a9 mov word ptr es:[0x9de8], di
03ae pop si
03af pop di
03b0 leave 
03b1 retf 
```

## Known declaration examples

- `extern int near CatOn;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near DogFrame;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near DogX;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near DogY;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern unsigned long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirB-2bfd4e5303.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirR-414ecd2b67.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SimBird', 'offset': 10410, 'source': None, 'size': 633}
- {'symbol': '_SimCat', 'offset': 11044, 'source': None, 'size': 663}
- {'symbol': '_FollowBoyDir', 'offset': 12654, 'source': None, 'size': 311}
- {'symbol': '_FollowCatDir', 'offset': 12966, 'source': None, 'size': 67}
