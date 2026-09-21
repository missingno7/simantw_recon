# Recovery task _PickupMyEgg

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 181 bytes.

```asm
0000 enter 2, 0
0004 push si
0005 cmp word ptr [0xcc84], 0x10 ; _MeType
000a je 0x8eac
000c cmp word ptr [0xac8a], 0xa ; _MeHealth
0011 jl 0x8eac
0013 jmp 0x8f46
0016 mov es, word ptr [0xc48c]
001a mov word ptr es:[0x8a6a], 0xfd
0021 push word ptr [bp + 0xa]
0024 push word ptr [bp + 8]
0027 push word ptr [bp + 6]
002a lea ax, [bp - 2]
002d push ss
002e push ax
002f nop 
0030 push cs
0031 call 0x88a2 ; _FindEggAt
0034 add sp, 0xa
0037 mov si, ax
0039 or si, si
003b jl 0x8f46
003d push 0
003f push 0
0041 push 0
0043 push 0
0045 push 0
0047 push word ptr [bp - 2]
004a push word ptr [bp + 6]
004d nop 
004e push cs
004f call 0x584a ; _SetAntIndex
0052 add sp, 0xe
0055 mov ax, word ptr [0xcd88] ; _MeLocX
0058 cmp word ptr [bp + 8], ax
005b jne 0x8efb
005d mov ax, word ptr [0xce7e] ; _MeLocY
0060 cmp word ptr [bp + 0xa], ax
0063 je 0x8f0e
0065 push 0
0067 push word ptr [bp + 0xa]
006a push word ptr [bp + 8]
006d push word ptr [bp + 6]
0070 nop 
0071 push cs
0072 call 0x5d18 ; _SetLife
0075 add sp, 8
0078 cmp word ptr [0xac8a], 0xa ; _MeHealth
007d jl 0x8f34
007f push 0x7e
0081 push 0
0083 push 0x1c
0085 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 136, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
008a add sp, 6
008d mov es, word ptr [0xc48c]
0091 mov word ptr es:[0x8a6a], si
0096 mov word ptr [0xcc84], 8 ; _MeType
009c jmp 0x8f3f
009e mov es, word ptr [0xc4b2]
00a2 mov word ptr es:[0x8a6e], 3
00a9 mov ax, 1
00ac pop si
00ad leave 
00ae retf 
00af nop 
00b0 xor ax, ax
00b2 pop si
00b3 leave 
00b4 retf 
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
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetMyHealth', 'offset': 35952, 'source': None, 'size': 105}
- {'symbol': '_EatMyFood', 'offset': 36058, 'source': None, 'size': 443}
- {'symbol': '_PickupMyFood', 'offset': 36684, 'source': None, 'size': 672}
- {'symbol': '_DropMyObject', 'offset': 37356, 'source': None, 'size': 100}
