# Recovery task _PickupMyObject

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 241 bytes.

```asm
0000 enter 2, 0
0004 push si
0005 mov dx, word ptr [0xcc84] ; _MeType
0009 test dl, 8
000c je 0x9264
000e xor ax, ax
0010 pop si
0011 leave 
0012 retf 
0013 nop 
0014 cmp dx, 0x10
0017 je 0x9273
0019 cmp word ptr [0xac8a], 0xa ; _MeHealth
001e jl 0x9273
0020 jmp 0x930c
0023 mov es, word ptr [0xc48c]
0027 mov word ptr es:[0x8a6a], 0xfd
002e push word ptr [bp + 0xa]
0031 push word ptr [bp + 8]
0034 push word ptr [bp + 6]
0037 lea ax, [bp - 2]
003a push ss
003b push ax
003c nop 
003d push cs
003e call 0x88a2 ; _FindEggAt
0041 add sp, 0xa
0044 mov si, ax
0046 or si, si
0048 jl 0x930c
004a push 0
004c push 0
004e push 0
0050 push 0
0052 push 0
0054 push word ptr [bp - 2]
0057 push word ptr [bp + 6]
005a nop 
005b push cs
005c call 0x584a ; _SetAntIndex
005f add sp, 0xe
0062 mov ax, word ptr [0xcd88] ; _MeLocX
0065 cmp word ptr [bp + 8], ax
0068 jne 0x92c2
006a mov ax, word ptr [0xce7e] ; _MeLocY
006d cmp word ptr [bp + 0xa], ax
0070 je 0x92d5
0072 push 0
0074 push word ptr [bp + 0xa]
0077 push word ptr [bp + 8]
007a push word ptr [bp + 6]
007d nop 
007e push cs
007f call 0x5d18 ; _SetLife
0082 add sp, 8
0085 cmp word ptr [0xac8a], 0xa ; _MeHealth
008a jl 0x92fc
008c push 0x7e
008e push 0
0090 push 0x1c
0092 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 149, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0097 add sp, 6
009a mov es, word ptr [0xc48c]
009e mov word ptr es:[0x8a6a], si
00a3 mov word ptr [0xcc84], 8 ; _MeType
00a9 jmp 0x9307
00ab nop 
00ac mov es, word ptr [0xc4b2]
00b0 mov word ptr es:[0x8a6e], 3
00b7 mov si, 1
00ba jmp 0x930e
00bc xor si, si
00be or si, si
00c0 jne 0x933c
00c2 push word ptr [bp + 0xa]
00c5 push word ptr [bp + 8]
00c8 push word ptr [bp + 6]
00cb nop 
00cc push cs
00cd call 0x85ee ; _PickupMyRock
00d0 add sp, 6
00d3 mov si, ax
00d5 or si, si
00d7 jne 0x933c
00d9 push word ptr [bp + 0xa]
00dc push word ptr [bp + 8]
00df push word ptr [bp + 6]
00e2 nop 
00e3 push cs
00e4 call 0x8f4c ; _PickupMyFood
00e7 add sp, 6
00ea mov si, ax
00ec mov ax, si
00ee pop si
00ef leave 
00f0 retf 
```

## Known declaration examples

- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c
- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PickupMyFood', 'offset': 36684, 'source': None, 'size': 672}
- {'symbol': '_DropMyObject', 'offset': 37356, 'source': None, 'size': 100}
- {'symbol': '_TileCanBeMovedOn', 'offset': 37698, 'source': None, 'size': 349}
- {'symbol': '_IsNotBarrier', 'offset': 38048, 'source': 'src/recovered/IsNotBarrier.c', 'size': 37}
