# Recovery task _MoveMyLife

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 217 bytes.

```asm
0000 enter 2, 0
0004 push si
0005 mov si, word ptr [bp + 6]
0008 push word ptr [0xcf50] ; _MeDir
000c push word ptr [0xcc84] ; _MeType
0010 push word ptr [0xce7e] ; _MeLocY
0014 push word ptr [0xcd88] ; _MeLocX
0018 push word ptr [0xce80] ; _MePlane
001c nop 
001d push cs
001e call 0x631e ; _ClearMyLife
0021 add sp, 0xa
0024 or si, si
0026 jne 0x662a
0028 mov word ptr [bp - 2], 1
002d jmp 0x662d
002f nop 
0030 mov word ptr [bp - 2], si
0033 cmp word ptr [bp - 2], 1
0037 jg 0x6650
0039 mov si, word ptr [bp + 8]
003c or si, si
003e jl 0x6668
0040 cmp si, 0x7f
0043 jg 0x6668
0045 cmp word ptr [bp + 0xa], 0
0049 jl 0x6668
004b cmp word ptr [bp + 0xa], 0x3f
004f jg 0x6668
0051 mov dx, 1
0054 jmp 0x666a
0056 mov si, word ptr [bp + 8]
0059 or si, si
005b jl 0x6668
005d cmp si, 0x3f
0060 jg 0x6668
0062 cmp word ptr [bp + 0xa], 0
0066 jl 0x6668
0068 cmp word ptr [bp + 0xa], 0x3f
006c jle 0x664b
006e xor dx, dx
0070 dec dx
0071 jne 0x66d0
0073 push 0xff
0076 push word ptr [bp + 0xa]
0079 push si
007a push word ptr [bp - 2]
007d nop 
007e push cs
007f call 0x5d18 ; _SetLife
0082 add sp, 8
0085 cmp word ptr [bp + 0xc], 0x60
0089 jne 0x66b4
008b push 0xfe
008e mov es, word ptr [0xc478]
0092 mov bx, word ptr [bp + 0xe]
0095 xor bl, 4
0098 mov al, byte ptr es:[bx + 8]
009d cwde 
009e add ax, word ptr [bp + 0xa]
00a1 push ax
00a2 mov es, word ptr [0xc47a]
00a6 mov al, byte ptr es:[bx]
00ab cwde 
00ac add ax, si
00ae push ax
00af push word ptr [bp - 2]
00b2 nop 
00b3 push cs
00b4 call 0x5d18 ; _SetLife
00b7 add sp, 8
00ba mov word ptr [0xcd88], si ; _MeLocX
00be mov ax, word ptr [bp + 0xa]
00c1 mov word ptr [0xce7e], ax ; _MeLocY
00c4 mov ax, word ptr [bp + 0xe]
00c7 mov word ptr [0xcf50], ax ; _MeDir
00ca mov ax, word ptr [bp + 0xc]
00cd mov word ptr [0xcc84], ax ; _MeType
00d0 mov ax, word ptr [bp - 2]
00d3 mov word ptr [0xce80], ax ; _MePlane
00d6 pop si
00d7 leave 
00d8 retf 
```

## Known declaration examples

- `extern void far ClearMyLife(int plane, int x, int y, int type, int dir);` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeDir;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c
- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_AddAntToList-44a11714fc.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetQueenTail', 'offset': 25840, 'source': None, 'size': 70}
- {'symbol': '_SetMyLife', 'offset': 25910, 'source': None, 'size': 196}
- {'symbol': '_DoMapUpdateDraw', 'offset': 26324, 'source': 'src/recovered/DoMapUpdateDraw.c', 'size': 1}
- {'symbol': '_DoEditAndMapUpdateDraw', 'offset': 26326, 'source': 'src/recovered/DoEditAndMapUpdateDraw.c', 'size': 6}
