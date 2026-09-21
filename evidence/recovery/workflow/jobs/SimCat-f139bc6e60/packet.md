# Recovery task _SimCat

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 663 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov bx, word ptr [0xac6c] ; _CatOn
0009 or bx, bx
000b jne 0x2b34
000d jmp 0x2d46
0010 mov <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0013 mov es, ax
0015 mov ax, word ptr es:[0x72b6]
0019 inc ax
001a and ah, 0xf
001d mov word ptr es:[0x72b6], ax
0021 cmp bx, 1
0024 je 0x2b4d
0026 jmp 0x2cc4
0029 mov es, word ptr [0xc556]
002d mov bx, word ptr es:[0x72bc]
0032 mov es, word ptr [0xc558]
0036 mov al, byte ptr es:[bx]
003b cwde 
003c mov si, ax
003e shl si, 2
0041 add si, word ptr [0xac6e] ; _CatX
0045 mov es, word ptr [0xc55a]
0049 mov al, byte ptr es:[bx + 8]
004e cwde 
004f mov di, ax
0051 shl di, 2
0054 add di, word ptr [0xac70] ; _CatY
0058 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 91, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
005d or ax, ax
005f je 0x2bb8
0061 mov <resolved loader operand; see bindings> ; [{'operand_offset': 98, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0064 mov es, ax
0066 cmp si, 0xfc
006a jl 0x2bbd
006c cmp si, 0x1ef
0070 jg 0x2bbd
0072 mov word ptr ss:[0xac6e], si
0077 mov word ptr ss:[0xac70], di
007c inc word ptr ss:[0xac6a]
0081 cmp word ptr es:[0x72bc], 2
0087 jne 0x2bce
0089 cmp word ptr ss:[0xac6a], 3
008f jl 0x2bee
0091 jmp 0x2be7
0093 nop 
0094 mov <resolved loader operand; see bindings> ; [{'operand_offset': 149, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0097 mov es, ax
0099 cmp word ptr es:[0x72bc], 2
009f jne 0x2be0
00a1 mov word ptr es:[0x72bc], 6
00a8 jmp 0x2bd6
00aa cmp word ptr ss:[0xac6a], 6
00b0 jl 0x2bee
00b2 mov word ptr ss:[0xac6a], 4
00b9 jmp 0x2bee
00bb nop 
00bc mov word ptr es:[0x72bc], 2
00c3 mov word ptr ss:[0xac6a], 1
00ca mov <resolved loader operand; see bindings> ; [{'operand_offset': 203, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00cd mov es, ax
00cf cmp word ptr es:[0x8610], 0
00d5 jne 0x2c20
00d7 cmp word ptr ss:[0xce82], 2
00dd jge 0x2c20
00df push ss
00e0 pop ds
00e1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 228, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand64
00e6 or ax, ax
00e8 jne 0x2c22
00ea push 5
00ec push ax
00ed push 0xd
00ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 242, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00f4 add sp, 6
00f7 pop si
00f8 pop di
00f9 leave 
00fa retf 
00fb nop 
00fc push ss
00fd pop ds
00fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 257, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
0103 or ax, ax
0105 jne 0x2c62
0107 mov es, word ptr [0xc510]
010b cmp word ptr es:[0x72b6], 0x64
0111 jle 0x2c62
0113 mov es, word ptr [0xc512]
0117 cmp word ptr es:[0x7d5a], 2
011d jne 0x2c62
011f cmp word ptr [0xac74], ax ; _BoyHere
0123 jne 0x2c62
0125 mov word ptr [0xac6c], 2 ; _CatOn
012b mov es, word ptr [0xc510]
012f mov word ptr es:[0x72b6], ax
0133 mov word ptr [0xac6a], 0xa ; _CatFrame
0139 pop si
013a pop di
013b leave 
013c retf 
013d nop 
013e mov es, word ptr [0xc510]
0142 cmp word ptr es:[0x72b6], 0x32
0148 jg 0x2c71
014a jmp 0x2db7
014d push word ptr [0xac5e] ; _DogY
0151 push word ptr [0xac5c] ; _DogX
0155 push word ptr [0xac70] ; _CatY
0159 push word ptr [0xac6e] ; _CatX
015d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 352, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
0162 add sp, 8
0165 or dx, dx
0167 je 0x2c90
0169 jmp 0x2db7
016c cmp ax, 0x960
016f jbe 0x2c98
0171 jmp 0x2db7
0174 mov word ptr [0xac6c], 3 ; _CatOn
017a mov word ptr [0xac6a], 0x14 ; _CatFrame
0180 mov es, word ptr [0xc546]
0184 cmp word ptr es:[0x8610], dx
0189 je 0x2cb2
018b jmp 0x2db7
018e cmp word ptr [0xce82], 2 ; _YardMode
0193 jl 0x2cbc
0195 jmp 0x2db7
0198 push 5
019a push dx
019b push 0xe
019d jmp 0x2c13
01a0 cmp bx, 2
01a3 jne 0x2d14
01a5 inc word ptr [0xac6a] ; _CatFrame
01a9 cmp word ptr [0xac6a], 0xd ; _CatFrame
01ae jl 0x2cda
01b0 mov word ptr [0xac6a], 0xb ; _CatFrame
01b6 mov es, word ptr [0xc510]
01ba inc word ptr es:[0x72b6]
01bf cmp word ptr es:[0x72b6], 0x1e
01c5 jg 0x2cee
01c7 jmp 0x2db7
01ca mov word ptr es:[0x72b6], 0
01d1 mov word ptr [0xac6c], 1 ; _CatOn
01d7 mov es, word ptr [0xc556]
01db cmp word ptr es:[0x72bc], bx
01e0 jne 0x2d0a
01e2 xor ax, ax
01e4 jmp 0x2d0d
01e6 mov ax, 3
01e9 mov word ptr [0xac6a], ax ; _CatFrame
01ec pop si
01ed pop di
01ee leave 
01ef retf 
01f0 inc word ptr [0xac6a] ; _CatFrame
01f4 cmp word ptr [0xac6a], 0x1e ; _CatFrame
01f9 jge 0x2d22
01fb jmp 0x2db7
01fe xor ax, ax
0200 mov word ptr [0xac6a], ax ; _CatFrame
0203 mov word ptr [0xac6c], ax ; _CatOn
0206 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 521, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
020b add ax, 0x258
020e adc dx, 0
0211 mov es, word ptr [0xc4fe]
0215 mov word ptr es:[0x737e], ax
0219 mov word ptr es:[0x7380], dx
021e pop si
021f pop di
0220 leave 
0221 retf 
0222 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 549, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0227 mov es, word ptr [0xc4fe]
022b cmp dx, word ptr es:[0x7380]
0230 jl 0x2db7
0232 jg 0x2d5f
0234 cmp ax, word ptr es:[0x737e]
0239 jbe 0x2db7
023b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 574, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0240 add ax, 0xc8
0243 adc dx, 0
0246 mov es, word ptr [0xc4fe]
024a mov word ptr es:[0x737e], ax
024e mov word ptr es:[0x7380], dx
0253 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 598, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
0258 or ax, ax
025a je 0x2d8d
025c mov es, word ptr [0xc530]
0260 cmp word ptr es:[0x7866], 0x8d
0267 jne 0x2db7
0269 mov word ptr [0xac6c], 1 ; _CatOn
026f mov word ptr [0xac6e], 0xfc ; _CatX
0275 mov word ptr [0xac70], 0x19 ; _CatY
027b mov es, word ptr [0xc556]
027f mov word ptr es:[0x72bc], 2
0286 xor ax, ax
0288 mov word ptr [0xac6a], ax ; _CatFrame
028b mov es, word ptr [0xc510]
028f mov word ptr es:[0x72b6], ax
0293 pop si
0294 pop di
0295 leave 
0296 retf 
```

## Known declaration examples

- `extern int near BoyHere;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near CatFrame;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near CatOn;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near DogX;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near DogY;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SimKidInside', 'offset': 8374, 'source': None, 'size': None}
- {'symbol': '_SimBird', 'offset': 10410, 'source': None, 'size': 633}
- {'symbol': '_SimDog', 'offset': 11708, 'source': None, 'size': 946}
- {'symbol': '_FollowBoyDir', 'offset': 12654, 'source': None, 'size': 311}
