# Recovery task _DoDrownB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 210 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov bx, di
000b shl bx, 6
000e add bx, word ptr [bp + 8]
0011 mov word ptr [bp - 4], bx
0014 cmp byte ptr [bx + 0x48e8], 0x14
0019 jae 0x37e8
001b mov al, byte ptr [bp + 0xa]
001e and ax, 0x78
0021 sar ax, 3
0024 push ax
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
002a add sp, 2
002d mov es, word ptr [0xc350]
0031 mov bx, word ptr es:[0x9b6a]
0036 mov es, word ptr [0xc352]
003a mov byte ptr es:[bx + 0x3b22], al
003f pop si
0040 pop di
0041 leave 
0042 retf 
0043 nop 
0044 mov si, word ptr [bp + 0xa]
0047 push 3
0049 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 76, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
004e add sp, 2
0051 mov cx, si
0053 add al, cl
0055 dec al
0057 and ax, 7
005a and cx, 0xf8
005e or ax, cx
0060 mov si, ax
0062 mov es, word ptr [0xc350]
0066 mov bx, word ptr es:[0x9b6a]
006b mov es, word ptr [0xc352]
006f mov byte ptr es:[bx + 0x3d18], al
0074 mov bx, word ptr [bp - 4]
0077 mov byte ptr [bx - 0x7718], al
007b push 0x64
007d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 128, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0082 add sp, 2
0085 or ax, ax
0087 jne 0x3872
0089 xor al, al
008b mov bx, word ptr [bp - 4]
008e mov byte ptr [bx - 0x7718], al
0092 mov es, word ptr [0xc350]
0096 mov bx, word ptr es:[0x9b6a]
009b mov es, word ptr [0xc352]
009f mov byte ptr es:[bx + 0x3d18], al
00a4 mov ax, si
00a6 test al, 0x80
00a8 je 0x3862
00aa mov es, word ptr [0xc35c]
00ae add word ptr es:[0x9fc6], 1
00b4 adc word ptr es:[0x9fc8], 0
00ba pop si
00bb pop di
00bc leave 
00bd retf 
00be mov es, word ptr [0xc356]
00c2 add word ptr es:[0x9b26], 1
00c8 adc word ptr es:[0x9b28], 0
00ce pop si
00cf pop di
00d0 leave 
00d1 retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RaidOutB', 'offset': 13840, 'source': 'src/recovered/wf_RaidOutB-794c50ee5a.c', 'size': 110}
- {'symbol': '_DoRestB', 'offset': 13950, 'source': None, 'size': 294}
- {'symbol': '_DoRandB', 'offset': 14454, 'source': None, 'size': 246}
- {'symbol': '_DoRecruitN', 'offset': 14700, 'source': None, 'size': 232}
