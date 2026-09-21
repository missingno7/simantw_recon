# Recovery task _AddRock5

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 191 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov bx, word ptr [bp + 0xa]
0009 mov ax, bx
000b shl bx, 2
000e add bx, ax
0010 mov word ptr [bp - 8], bx
0013 xor si, si
0015 mov ax, word ptr [bp + 6]
0018 shl ax, 6
001b mov word ptr [bp - 4], ax
001e mov ax, bx
0020 shl bx, 2
0023 add bx, ax
0025 mov word ptr [bp - 0xa], bx
0028 mov <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
002b mov es, ax
002d xor cx, cx
002f mov bx, word ptr [bp - 0xa]
0032 add bx, si
0034 add bx, 0x870a
0038 mov word ptr [bp - 6], si
003b mov si, cx
003d mov cx, word ptr [bp - 4]
0040 cmp byte ptr es:[bx], 0
0044 je 0x4540
0046 mov di, word ptr [bp + 8]
0049 add di, cx
004b add di, si
004d cmp byte ptr [di + 0x28e8], 0x10
0052 ja 0x45a7
0054 add bx, 5
0057 inc si
0058 cmp si, 5
005b jl 0x452c
005d add cx, 0x40
0060 mov si, word ptr [bp - 6]
0063 mov word ptr [bp - 4], cx
0066 inc si
0067 cmp si, 5
006a jl 0x4519
006c xor cx, cx
006e mov ax, word ptr [bp + 6]
0071 shl ax, 6
0074 mov word ptr [bp - 4], ax
0077 mov ax, word ptr [bp - 8]
007a mov dx, ax
007c shl ax, 2
007f add ax, dx
0081 mov word ptr [bp - 0xa], ax
0084 xor bx, bx
0086 mov di, word ptr [bp - 0xa]
0089 add di, cx
008b add di, 0x870a
008f mov word ptr [bp - 6], cx
0092 mov cl, byte ptr es:[di]
0095 sub ch, ch
0097 or cx, cx
0099 je 0x4591
009b mov si, word ptr [bp + 8]
009e add si, word ptr [bp - 4]
00a1 mov byte ptr [bx + si + 0x28e8], cl
00a5 add di, 5
00a8 inc bx
00a9 cmp bx, 5
00ac jl 0x457e
00ae add word ptr [bp - 4], 0x40
00b2 mov cx, word ptr [bp - 6]
00b5 inc cx
00b6 cmp cx, 5
00b9 jl 0x4570
00bb pop si
00bc pop di
00bd leave 
00be retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeYardPatch', 'offset': 16802, 'source': None, 'size': 401}
- {'symbol': '_AddRocks', 'offset': 17204, 'source': None, 'size': 440}
- {'symbol': '_AddRock3', 'offset': 17836, 'source': None, 'size': 188}
- {'symbol': '_InitSpider', 'offset': 18024, 'source': None, 'size': 156}
