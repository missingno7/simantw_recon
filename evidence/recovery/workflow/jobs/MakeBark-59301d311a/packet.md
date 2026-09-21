# Recovery task _MakeBark

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 155 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov es, word ptr [0xc546]
0009 cmp word ptr es:[0x8610], 0
000f je 0x32fe
0011 jmp 0x3381
0014 cmp word ptr [0xce82], 2 ; _YardMode
0019 jge 0x3381
001b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0020 mov es, word ptr [0xc560]
0024 cmp dx, word ptr es:[0x9de8]
0029 jl 0x3381
002b jg 0x331e
002d cmp ax, word ptr es:[0x9de6]
0032 jbe 0x3381
0034 mov ax, word ptr [bp + 6]
0037 or ax, ax
0039 je 0x3332
003b dec ax
003c je 0x333c
003e dec ax
003f je 0x3332
0041 dec ax
0042 je 0x3346
0044 jmp 0x3355
0046 nop 
0047 nop 
0048 push word ptr [bp + 8]
004b push 0
004d push 0x17
004f jmp 0x334d
0051 nop 
0052 push word ptr [bp + 8]
0055 push 0
0057 push 0x15
0059 jmp 0x334d
005b nop 
005c push word ptr [bp + 8]
005f push 0
0061 push 0x16
0063 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 102, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0068 add sp, 6
006b push 0x1e
006d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0072 add sp, 2
0075 cdq 
0076 mov si, ax
0078 mov di, dx
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
007f add si, ax
0081 adc di, dx
0083 add si, 0x3c
0086 adc di, 0
0089 mov es, word ptr [0xc560]
008d mov word ptr es:[0x9de6], si
0092 mov word ptr es:[0x9de8], di
0097 pop si
0098 pop di
0099 leave 
009a retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern int near YardMode;` — src/recovered/wf_DrawYard-bff77801c5.c
- `extern int near YardMode;` — src/recovered/wf_UpdateYard-32751811c5.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FollowBoyDir', 'offset': 12654, 'source': None, 'size': 311}
- {'symbol': '_FollowCatDir', 'offset': 12966, 'source': None, 'size': 67}
- {'symbol': '_FootFall', 'offset': 13190, 'source': None, 'size': 339}
- {'symbol': '_MowerFall', 'offset': 13530, 'source': None, 'size': 166}
