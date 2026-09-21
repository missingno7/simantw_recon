# Recovery task _IsItYellow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 206 bytes.

```asm
0000 enter 2, 0
0004 push si
0005 mov cx, word ptr [bp + 6]
0008 or cx, cx
000a jne 0x96c8
000c mov dx, 1
000f jmp 0x96ca
0011 nop 
0012 mov dx, cx
0014 cmp word ptr [0xce80], dx ; _MePlane
0018 jne 0x96d6
001a mov bx, 1
001d jmp 0x96d8
001f nop 
0020 xor bx, bx
0022 or bx, bx
0024 jne 0x96e2
0026 xor ax, ax
0028 pop si
0029 leave 
002a retf 
002b nop 
002c mov es, word ptr [0xc48a]
0030 cmp word ptr es:[0x9fe8], 1
0036 jne 0x9726
0038 cmp cx, 1
003b jg 0x96dc
003d push word ptr [0xac7e] ; _SpidY
0041 push word ptr [0xac7c] ; _SpidX
0045 mov ax, word ptr [bp + 0xa]
0048 shl ax, 4
004b add ax, 8
004e push ax
004f mov ax, word ptr [bp + 8]
0052 shl ax, 4
0055 add ax, 8
0058 push ax
0059 nop 
005a push cs
005b call 0x11122
005e add sp, 8
0061 or dx, dx
0063 jne 0x96dc
0065 cmp ax, 0x200
0068 jae 0x96dc
006a mov ax, 1
006d pop si
006e leave 
006f retf 
0070 mov ax, cx
0072 or ax, ax
0074 jl 0x9737
0076 jo 0x9737
0078 dec ax
0079 jle 0x973c
007b dec ax
007c je 0x974c
007e dec ax
007f je 0x975c
0081 mov dx, word ptr [bp - 2]
0084 jmp 0x976b
0086 mov si, word ptr [bp + 8]
0089 shl si, 6
008c mov bx, word ptr [bp + 0xa]
008f mov dl, byte ptr [bx + si + 0x68e8]
0093 jmp 0x9769
0095 nop 
0096 mov si, word ptr [bp + 8]
0099 shl si, 6
009c mov bx, word ptr [bp + 0xa]
009f mov dl, byte ptr [bx + si - 0x7718]
00a3 jmp 0x9769
00a5 nop 
00a6 mov si, word ptr [bp + 8]
00a9 shl si, 6
00ac mov bx, word ptr [bp + 0xa]
00af mov dl, byte ptr [bx + si - 0x6718]
00b3 sub dh, dh
00b5 cmp dx, 0xff
00b9 je 0x977c
00bb cmp dx, 0xfe
00bf je 0x977c
00c1 xor dx, dx
00c3 jmp 0x977f
00c5 nop 
00c6 mov dx, 1
00c9 mov ax, dx
00cb pop si
00cc leave 
00cd retf 
```

## Known declaration examples

- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsNotObstacle', 'offset': 38086, 'source': None, 'size': 255}
- {'symbol': '_IsItDigable', 'offset': 38342, 'source': None, 'size': 240}
- {'symbol': '_IsLessThanHole', 'offset': 38788, 'source': 'src/recovered/IsLessThanHole.c', 'size': 37}
- {'symbol': '_IsSamePlane', 'offset': 38826, 'source': None, 'size': 32}
