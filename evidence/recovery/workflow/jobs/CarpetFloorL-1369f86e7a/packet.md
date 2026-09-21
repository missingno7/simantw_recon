# Recovery task _CarpetFloorL

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 181 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov bx, 0x28e8
0009 mov ax, 0x6464
000c mov cx, 0x20
000f mov di, bx
0011 push ds
0012 pop es
0013 rep stosw word ptr es:[di], ax
0015 add bx, 0x40
0018 cmp bx, 0x2de8
001c jbe 0x34cb
001e mov bx, 0x2e28
0021 mov ax, 0x7a7a
0024 mov cx, 0x20
0027 mov di, bx
0029 rep stosw word ptr es:[di], ax
002b add bx, 0x40
002e cmp bx, 0x2e28
0032 jbe 0x34e3
0034 mov bx, 0x2e68
0037 mov ax, 0x7b7b
003a mov cx, 0x20
003d mov di, bx
003f rep stosw word ptr es:[di], ax
0041 add bx, 0x40
0044 cmp bx, 0x2ea8
0048 jbe 0x34f9
004a mov bx, 0x2ea8
004d mov ax, 0x303
0050 mov cx, 0x20
0053 mov di, bx
0055 rep stosw word ptr es:[di], ax
0057 add bx, 0x40
005a cmp bx, 0x48a8
005e jbe 0x350f
0060 mov di, 0x5c0
0063 xor si, si
0065 mov word ptr [bp - 2], di
0068 push 0xc8
006b nop 
006c push cs
006d call 0x158a ; _SRand1
0070 add sp, 2
0073 or ax, ax
0075 jne 0x354d
0077 push 2
0079 nop 
007a push cs
007b call 0x158a ; _SRand1
007e add sp, 2
0081 add al, 0x3e
0083 mov bx, di
0085 add bx, si
0087 mov byte ptr [bx + 0x28e8], al
008b inc si
008c cmp si, 0x3f
008f jle 0x352a
0091 add di, 0x40
0094 cmp di, 0x1fc0
0098 jle 0x3525
009a push 0x19
009c push 2
009e nop 
009f push cs
00a0 call 0x3d44 ; _MakeOutletH
00a3 add sp, 4
00a6 mov es, word ptr [0xc434]
00aa mov word ptr es:[0x9c66], 1
00b1 pop si
00b2 pop di
00b3 leave 
00b4 retf 
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

- {'symbol': '_MakeHousePatch', 'offset': 12576, 'source': None, 'size': None}
- {'symbol': '_FloorTiles', 'offset': 13318, 'source': None, 'size': 188}
- {'symbol': '_MakeLint2', 'offset': 13688, 'source': None, 'size': 105}
- {'symbol': '_CarpetFloorR', 'offset': 13794, 'source': None, 'size': 182}
