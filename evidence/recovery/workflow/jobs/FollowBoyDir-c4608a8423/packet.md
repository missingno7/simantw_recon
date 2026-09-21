# Recovery task _FollowBoyDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 311 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc55e]
000a mov si, word ptr es:[0x789c]
000f mov es, word ptr [0xc508]
0013 sub si, word ptr es:[0x78d2]
0018 mov es, word ptr [0xc55c]
001c mov ax, word ptr es:[0x77b0]
0020 mov es, word ptr [0xc506]
0024 sub ax, word ptr es:[0x78b0]
0029 mov word ptr [bp - 2], ax
002c or ax, ax
002e jge 0x31a0
0030 neg ax
0032 mov word ptr [bp - 4], ax
0035 or si, si
0037 jge 0x31ae
0039 mov di, si
003b neg di
003d jmp 0x31b0
003f nop 
0040 mov di, si
0042 cmp ax, 1
0045 jl 0x31b8
0047 jmp 0x3257
004a cmp di, 1
004d jl 0x31c0
004f jmp 0x3257
0052 mov es, word ptr [0xc520]
0056 cmp word ptr es:[0x7c92], 0
005c jne 0x31cf
005e jmp 0x3257
0061 mov es, word ptr [0xc546]
0065 cmp word ptr es:[0x8610], 0
006b jne 0x3257
006d cmp word ptr [0xce82], 2 ; _YardMode
0072 jge 0x3257
0074 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 119, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0079 mov es, word ptr [0xc560]
007d cmp dx, word ptr es:[0x9de8]
0082 jl 0x3257
0084 jg 0x31fb
0086 cmp ax, word ptr es:[0x9de6]
008b jbe 0x3257
008d mov ax, 1
0090 dec ax
0091 je 0x3212
0093 dec ax
0094 je 0x320a
0096 dec ax
0097 je 0x321a
0099 jmp 0x3228
009b nop 
009c push 0x7f
009e push 0
00a0 push 0x17
00a2 jmp 0x3220
00a4 push 0x7f
00a6 push 0
00a8 push 0x15
00aa jmp 0x3220
00ac push 0x7f
00ae push 0
00b0 push 0x16
00b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 181, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00b7 add sp, 6
00ba push 0x1e
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00c1 add sp, 2
00c4 cdq 
00c5 mov word ptr [bp - 8], ax
00c8 mov word ptr [bp - 6], dx
00cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 206, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00d0 add ax, word ptr [bp - 8]
00d3 adc dx, word ptr [bp - 6]
00d6 add ax, 0x3c
00d9 adc dx, 0
00dc mov es, word ptr [0xc560]
00e0 mov word ptr es:[0x9de6], ax
00e4 mov word ptr es:[0x9de8], dx
00e9 cmp word ptr [bp - 4], 2
00ed jge 0x3262
00ef cmp di, 2
00f2 jl 0x3296
00f4 or si, si
00f6 jge 0x326e
00f8 mov ax, 2
00fb pop si
00fc pop di
00fd leave 
00fe retf 
00ff nop 
0100 cmp si, 1
0103 jle 0x327a
0105 xor ax, ax
0107 pop si
0108 pop di
0109 leave 
010a retf 
010b nop 
010c cmp word ptr [bp - 2], 0
0110 jge 0x3288
0112 mov ax, 1
0115 pop si
0116 pop di
0117 leave 
0118 retf 
0119 nop 
011a cmp word ptr [bp - 2], 1
011e jle 0x3296
0120 mov ax, 3
0123 pop si
0124 pop di
0125 leave 
0126 retf 
0127 nop 
0128 mov es, word ptr [0xc52c]
012c mov al, byte ptr es:[0x7a5c]
0130 and ax, 3
0133 pop si
0134 pop di
0135 leave 
0136 retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
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

- {'symbol': '_SimCat', 'offset': 11044, 'source': None, 'size': 663}
- {'symbol': '_SimDog', 'offset': 11708, 'source': None, 'size': 946}
- {'symbol': '_FollowCatDir', 'offset': 12966, 'source': None, 'size': 67}
- {'symbol': '_MakeBark', 'offset': 13034, 'source': None, 'size': 155}
