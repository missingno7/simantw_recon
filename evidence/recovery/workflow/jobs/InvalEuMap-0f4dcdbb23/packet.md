# Recovery task _InvalEuMap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 168 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 cmp word ptr [bp + 6], 0
000a jge 0x60
000c mov word ptr [bp + 6], 0
0011 jmp 0x6b
0013 nop 
0014 cmp word ptr [bp + 0xa], 0x7f
0018 jle 0x6b
001a mov word ptr [bp + 0xa], 0x7f
001f cmp word ptr [bp + 8], 0
0023 jge 0x76
0025 xor dx, dx
0027 jmp 0x84
0029 nop 
002a cmp word ptr [bp + 0xc], 0x3f
002e jle 0x81
0030 mov word ptr [bp + 0xc], 0x3f
0035 mov dx, word ptr [bp + 8]
0038 mov si, dx
003a cmp si, word ptr [bp + 0xc]
003d jg 0xf0
003f mov ax, word ptr [0xcc80] ; _editWidth
0042 imul si
0044 add ax, word ptr [bp + 6]
0047 mov word ptr [bp - 0xa], ax
004a mov bx, word ptr [bp - 0xa]
004d mov ax, word ptr [bp + 6]
0050 mov word ptr [bp - 2], ax
0053 cmp word ptr [bp + 0xa], ax
0056 jl 0xec
0058 mov ax, bx
005a shl ax, 1
005c add ax, word ptr [0x1442]
0060 mov dx, word ptr [0x1444]
0064 mov es, dx
0066 mov cx, word ptr [bp - 2]
0069 mov bx, ax
006b mov di, si
006d or cx, cx
006f jl 0xd2
0071 cmp word ptr [0xcc80], cx ; _editWidth
0075 jle 0xd2
0077 or di, di
0079 jl 0xd2
007b cmp word ptr [0xcd7a], di ; _editHeight
007f jle 0xd2
0081 mov word ptr es:[bx], 0xffff
0086 add bx, 2
0089 inc cx
008a cmp cx, word ptr [bp + 0xa]
008d jle 0xb9
008f mov ax, word ptr [0xcc80] ; _editWidth
0092 add word ptr [bp - 0xa], ax
0095 inc di
0096 cmp di, word ptr [bp + 0xc]
0099 jg 0xf0
009b mov si, di
009d jmp 0x96
009f nop 
00a0 mov di, si
00a2 jmp 0xdb
00a4 pop si
00a5 pop di
00a6 leave 
00a7 retf 
```

## Known declaration examples

- `extern int near editHeight;` — src/recovered/BalloonIsVisible.c
- `extern int near editHeight;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editWidth;` — src/recovered/BalloonIsVisible.c
- `extern int near editWidth;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ZapEuMapAt', 'offset': 0, 'source': None, 'size': 76}
- {'symbol': '_OverlayTileSet', 'offset': 244, 'source': None, 'size': 227}
- {'symbol': '_LoadTiles', 'offset': 472, 'source': None, 'size': 2218}
