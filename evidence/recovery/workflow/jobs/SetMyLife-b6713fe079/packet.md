# Recovery task _SetMyLife

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 196 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 cmp word ptr [bp + 6], 1
000a jg 0x6560
000c mov di, word ptr [bp + 8]
000f or di, di
0011 jl 0x6578
0013 cmp di, 0x7f
0016 jg 0x6578
0018 cmp word ptr [bp + 0xa], 0
001c jl 0x6578
001e cmp word ptr [bp + 0xa], 0x3f
0022 jg 0x6578
0024 mov dx, 1
0027 jmp 0x657a
0029 nop 
002a mov di, word ptr [bp + 8]
002d or di, di
002f jl 0x6578
0031 cmp di, 0x3f
0034 jg 0x6578
0036 cmp word ptr [bp + 0xa], 0
003a jl 0x6578
003c cmp word ptr [bp + 0xa], 0x3f
0040 jle 0x655a
0042 xor dx, dx
0044 dec dx
0045 jne 0x65f6
0047 mov si, word ptr [bp + 0x10]
004a push si
004b push word ptr [bp + 0xa]
004e push di
004f push word ptr [bp + 6]
0052 nop 
0053 push cs
0054 call 0x5d18 ; _SetLife
0057 add sp, 8
005a cmp word ptr [bp + 0xc], 0x60
005e jne 0x65d6
0060 cmp si, 0xff
0064 jne 0x65a4
0066 mov word ptr [bp - 2], 0xfe
006b jmp 0x65a7
006d nop 
006e mov word ptr [bp - 2], si
0071 push word ptr [bp - 2]
0074 mov es, word ptr [0xc478]
0078 mov bx, word ptr [bp + 0xe]
007b xor bl, 4
007e mov al, byte ptr es:[bx + 8]
0083 cwde 
0084 add ax, word ptr [bp + 0xa]
0087 push ax
0088 mov es, word ptr [0xc47a]
008c mov al, byte ptr es:[bx]
0091 cwde 
0092 add ax, di
0094 push ax
0095 push word ptr [bp + 6]
0098 nop 
0099 push cs
009a call 0x5d18 ; _SetLife
009d add sp, 8
00a0 or si, si
00a2 je 0x65f6
00a4 mov word ptr [0xcd88], di ; _MeLocX
00a8 mov ax, word ptr [bp + 0xa]
00ab mov word ptr [0xce7e], ax ; _MeLocY
00ae mov ax, word ptr [bp + 0xe]
00b1 mov word ptr [0xcf50], ax ; _MeDir
00b4 mov ax, word ptr [bp + 0xc]
00b7 mov word ptr [0xcc84], ax ; _MeType
00ba mov ax, word ptr [bp + 6]
00bd mov word ptr [0xce80], ax ; _MePlane
00c0 pop si
00c1 pop di
00c2 leave 
00c3 retf 
```

## Known declaration examples

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

- {'symbol': '_ClearMyLife', 'offset': 25374, 'source': None, 'size': 465}
- {'symbol': '_SetQueenTail', 'offset': 25840, 'source': None, 'size': 70}
- {'symbol': '_MoveMyLife', 'offset': 26106, 'source': None, 'size': 217}
- {'symbol': '_DoMapUpdateDraw', 'offset': 26324, 'source': 'src/recovered/DoMapUpdateDraw.c', 'size': 1}
