# Recovery task _QueenMoveR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 246 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov es, word ptr [0xc3a6]
000d push word ptr es:[0x9fd2]
0012 mov es, word ptr [0xc3a8]
0016 push word ptr es:[0x9fba]
001b push di
001c push word ptr [bp + 6]
001f push 3
0021 nop 
0022 push cs
0023 call 0x405e ; _GetBestDir
0026 add sp, 0xa
0029 mov si, ax
002b or si, si
002d jge 0x6642
002f inc si
0030 jne 0x663b
0032 jmp 0x66f6
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
003a mov si, ax
003c cmp di, 3
003f jge 0x6657
0041 cmp si, 5
0044 jle 0x664f
0046 jmp 0x66f6
0049 cmp si, 3
004c jge 0x6657
004e jmp 0x66f6
0051 mov word ptr [bp - 2], si
0054 push si
0055 push di
0056 push word ptr [bp + 6]
0059 nop 
005a push cs
005b call 0x6850 ; _TryMoveDirR
005e add sp, 6
0061 or ax, ax
0063 jne 0x666e
0065 jmp 0x66f6
0068 mov es, word ptr [0xc396]
006c mov bl, byte ptr [bp + 0xa]
006f xor bl, 0xfc
0072 and bx, 7
0075 mov al, byte ptr es:[bx + 8]
007a cwde 
007b mov cx, bx
007d mov bx, ax
007f add bx, di
0081 mov es, word ptr [0xc398]
0085 mov si, cx
0087 mov al, byte ptr es:[si]
008c cwde 
008d mov si, ax
008f add si, word ptr [bp + 6]
0092 mov word ptr [bp - 4], si
0095 shl si, 6
0098 mov byte ptr [bx + si - 0x6718], 0
009d mov al, byte ptr [bp + 0xa]
00a0 and ax, 7
00a3 add ax, 0xe8
00a6 push ax
00a7 push bx
00a8 push word ptr [bp - 4]
00ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 174, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
00b0 add sp, 6
00b3 mov si, ax
00b5 or si, si
00b7 jl 0x66ef
00b9 mov <resolved loader operand; see bindings> ; [{'operand_offset': 186, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00bc mov es, ax
00be cmp byte ptr es:[si + 0x46e6], 0
00c4 je 0x66ef
00c6 mov al, byte ptr [bp + 6]
00c9 mov byte ptr es:[si + 0x4104], al
00ce mov ax, di
00d0 mov byte ptr es:[si + 0x42fa], al
00d5 mov al, byte ptr [bp - 2]
00d8 sub al, 0x18
00da mov byte ptr es:[si + 0x46e6], al
00df mov bx, word ptr [bp + 6]
00e2 shl bx, 6
00e5 mov byte ptr [bx + di - 0x6718], al
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
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_GetRandDir-2664e9d7f9.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far TryMoveDirR(int x, int y, int dir);` — src/recovered/wf_RaidOutR-a39ba19d03.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SimEggR', 'offset': 25254, 'source': None, 'size': 223}
- {'symbol': '_SimQueenR', 'offset': 25478, 'source': None, 'size': 639}
- {'symbol': '_MakeNewTailR', 'offset': 26364, 'source': None, 'size': 101}
- {'symbol': '_KillTailR', 'offset': 26466, 'source': None, 'size': 45}
