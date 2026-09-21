# Recovery task _CarpetFloorR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 182 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov bx, 0x28e8
0009 mov ax, 0x303
000c mov cx, 0x20
000f mov di, bx
0011 push ds
0012 pop es
0013 rep stosw word ptr es:[di], ax
0015 add bx, 0x40
0018 cmp bx, 0x4328
001c jbe 0x35eb
001e xor di, di
0020 xor si, si
0022 mov word ptr [bp - 2], di
0025 push 0xc8
0028 nop 
0029 push cs
002a call 0x158a ; _SRand1
002d add sp, 2
0030 or ax, ax
0032 jne 0x362a
0034 push 2
0036 nop 
0037 push cs
0038 call 0x158a ; _SRand1
003b add sp, 2
003e add al, 0x3e
0040 mov bx, di
0042 add bx, si
0044 mov byte ptr [bx + 0x28e8], al
0048 inc si
0049 cmp si, 0x3f
004c jle 0x3607
004e add di, 0x40
0051 cmp di, 0x1a40
0055 jle 0x3602
0057 mov bx, 0x4368
005a mov ax, 0x7c7c
005d mov cx, 0x20
0060 mov di, bx
0062 push ds
0063 pop es
0064 rep stosw word ptr es:[di], ax
0066 add bx, 0x40
0069 cmp bx, 0x4368
006d jbe 0x363c
006f mov bx, 0x42e8
0072 mov ax, 0x7b7b
0075 mov cx, 0x20
0078 mov di, bx
007a rep stosw word ptr es:[di], ax
007c add bx, 0x40
007f cmp bx, 0x4328
0083 jbe 0x3654
0085 mov bx, 0x4368
0088 mov ax, 0x6464
008b mov cx, 0x20
008e mov di, bx
0090 rep stosw word ptr es:[di], ax
0092 add bx, 0x40
0095 cmp bx, 0x48a8
0099 jbe 0x366a
009b push 0x23
009d push 0x71
009f nop 
00a0 push cs
00a1 call 0x3d44 ; _MakeOutletH
00a4 add sp, 4
00a7 mov es, word ptr [0xc434]
00ab mov word ptr es:[0x9c66], 3
00b2 pop si
00b3 pop di
00b4 leave 
00b5 retf 
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

- {'symbol': '_CarpetFloorL', 'offset': 13506, 'source': None, 'size': 181}
- {'symbol': '_MakeLint2', 'offset': 13688, 'source': None, 'size': 105}
- {'symbol': '_MakeKitchenWall', 'offset': 13976, 'source': None, 'size': 196}
- {'symbol': '_MakeSink', 'offset': 14172, 'source': None, 'size': 487}
