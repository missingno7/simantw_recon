# Recovery task _QueenMoveB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 246 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov es, word ptr [0xc37a]
000d push word ptr es:[0x7c90]
0012 mov es, word ptr [0xc37c]
0016 push word ptr es:[0x7c48]
001b push di
001c push word ptr [bp + 6]
001f push 2
0021 nop 
0022 push cs
0023 call 0x405e ; _GetBestDir
0026 add sp, 0xa
0029 mov si, ax
002b or si, si
002d jge 0x4190
002f inc si
0030 jne 0x4189
0032 jmp 0x4244
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
003a mov si, ax
003c cmp di, 3
003f jge 0x41a5
0041 cmp si, 5
0044 jle 0x419d
0046 jmp 0x4244
0049 cmp si, 3
004c jge 0x41a5
004e jmp 0x4244
0051 mov word ptr [bp - 2], si
0054 push si
0055 push di
0056 push word ptr [bp + 6]
0059 nop 
005a push cs
005b call 0x439e ; _TryMoveDirB
005e add sp, 6
0061 or ax, ax
0063 jne 0x41bc
0065 jmp 0x4244
0068 mov es, word ptr [0xc364]
006c mov bl, byte ptr [bp + 0xa]
006f xor bl, 0xfc
0072 and bx, 7
0075 mov al, byte ptr es:[bx + 8]
007a cwde 
007b mov cx, bx
007d mov bx, ax
007f add bx, di
0081 mov es, word ptr [0xc366]
0085 mov si, cx
0087 mov al, byte ptr es:[si]
008c cwde 
008d mov si, ax
008f add si, word ptr [bp + 6]
0092 mov word ptr [bp - 4], si
0095 shl si, 6
0098 mov byte ptr [bx + si - 0x7718], 0
009d mov al, byte ptr [bp + 0xa]
00a0 and ax, 7
00a3 add ax, 0x68
00a6 push ax
00a7 push bx
00a8 push word ptr [bp - 4]
00ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 174, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
00b0 add sp, 6
00b3 mov si, ax
00b5 or si, si
00b7 jl 0x423d
00b9 mov <resolved loader operand; see bindings> ; [{'operand_offset': 186, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00bc mov es, ax
00be cmp byte ptr es:[si + 0x3d18], 0
00c4 je 0x423d
00c6 mov al, byte ptr [bp + 6]
00c9 mov byte ptr es:[si + 0x3736], al
00ce mov ax, di
00d0 mov byte ptr es:[si + 0x392c], al
00d5 mov al, byte ptr [bp - 2]
00d8 add al, 0x68
00da mov byte ptr es:[si + 0x3d18], al
00df mov bx, word ptr [bp + 6]
00e2 shl bx, 6
00e5 mov byte ptr [bx + di - 0x7718], al
00e9 mov ax, 1
00ec pop si
00ed pop di
00ee leave 
00ef retf 
00f0 xor ax, ax
00f2 pop si
00f3 pop di
00f4 leave 
00f5 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_GetRandDir-2664e9d7f9.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far TryMoveDirB(int x, int y, int dir);` — src/recovered/wf_RaidOutB-794c50ee5a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SimQueenB', 'offset': 15810, 'source': None, 'size': 666}
- {'symbol': '_GetBestDir', 'offset': 16478, 'source': None, 'size': 246}
- {'symbol': '_MakeNewTailB', 'offset': 16970, 'source': None, 'size': 101}
- {'symbol': '_KillTailB', 'offset': 17072, 'source': None, 'size': 45}
