# Recovery task _processSpider

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 290 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 cmp word ptr [bp + 0xa], 1
000a jge 0x71e0
000c mov es, word ptr [0xbf2a]
0010 cmp word ptr es:[0x7c22], 0xb
0016 je 0x71e0
0018 mov es, word ptr [0xbf2c]
001c mov word ptr es:[0x7a5e], 0xfffe
0023 mov es, word ptr [0xbf2e]
0027 mov word ptr es:[0x80a8], 0xffff
002e mov es, word ptr [0xbf30]
0032 mov word ptr es:[0x729e], 0
0039 mov ax, word ptr [bp + 6]
003c mov es, word ptr [0xbf32]
0040 mov word ptr es:[0x78b8], ax
0044 jmp 0x72a0
0047 nop 
0048 mov di, word ptr [bp + 6]
004b mov bx, di
004d shl bx, 6
0050 add bx, word ptr [bp + 8]
0053 mov al, byte ptr [bx + 0x68e8]
0057 sub ah, ah
0059 mov si, ax
005b or si, si
005d je 0x7258
005f push si
0060 push word ptr [bp + 8]
0063 push di
0064 push 1
0066 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindAntIndex
006b add sp, 8
006e or ax, ax
0070 jl 0x7258
0072 mov es, word ptr [0xbf2e]
0076 mov word ptr es:[0x80a8], si
007b mov es, word ptr [0xbf2c]
007f mov word ptr es:[0x7a5e], ax
0083 mov es, word ptr [0xbf30]
0087 mov word ptr es:[0x729e], 2
008e mov es, word ptr [0xbf2a]
0092 cmp word ptr es:[0x7c22], 0xb
0098 je 0x7235
009a jmp 0x72b6
009d push 0x7e
009f push 0
00a1 push 0xf
00a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 166, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00a8 add sp, 6
00ab mov es, word ptr [0xbf36]
00af mov word ptr es:[0x7d60], 6
00b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 185, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _EndTargetMode
00bb pop si
00bc pop di
00bd leave 
00be retf 
00bf nop 
00c0 mov es, word ptr [0xbf2a]
00c4 cmp word ptr es:[0x7c22], 0xb
00ca jne 0x7276
00cc push 0x7e
00ce push 0
00d0 push 1
00d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00d7 add sp, 6
00da pop si
00db pop di
00dc leave 
00dd retf 
00de mov es, word ptr [0xbf2c]
00e2 mov word ptr es:[0x7a5e], 0xfffe
00e9 mov es, word ptr [0xbf2e]
00ed mov word ptr es:[0x80a8], 0xffff
00f4 mov es, word ptr [0xbf30]
00f8 mov word ptr es:[0x729e], 0
00ff mov es, word ptr [0xbf32]
0103 mov word ptr es:[0x78b8], di
0108 mov ax, word ptr [bp + 8]
010b mov es, word ptr [0xbf34]
010f mov word ptr es:[0x78ea], ax
0113 mov ax, word ptr [bp + 0xa]
0116 mov es, word ptr [0xbf10]
011a mov word ptr es:[0x9bc4], ax
011e pop si
011f pop di
0120 leave 
0121 retf 
```

## Known declaration examples

- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_SetAlarmDropState_2_scaffold-bb12a76f6c.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_processEdit', 'offset': 27192, 'source': None, 'size': 1168}
- {'symbol': '_DoLaserFire', 'offset': 28360, 'source': None, 'size': 719}
- {'symbol': '_ResetYellowVars', 'offset': 29370, 'source': None, 'size': 122}
- {'symbol': '_SetGoalsY', 'offset': 29492, 'source': None, 'size': 105}
