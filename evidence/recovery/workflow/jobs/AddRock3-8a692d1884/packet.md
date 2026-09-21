# Recovery task _AddRock3

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 188 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov bx, word ptr [bp + 0xa]
0009 mov ax, bx
000b shl bx, 1
000d add bx, ax
000f mov word ptr [bp - 8], bx
0012 xor si, si
0014 mov ax, word ptr [bp + 6]
0017 shl ax, 6
001a mov word ptr [bp - 4], ax
001d mov ax, bx
001f shl bx, 1
0021 add bx, ax
0023 mov word ptr [bp - 0xa], bx
0026 mov <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0029 mov es, ax
002b xor cx, cx
002d mov bx, word ptr [bp - 0xa]
0030 add bx, si
0032 add bx, 0x87a0
0036 mov word ptr [bp - 6], si
0039 mov si, cx
003b mov cx, word ptr [bp - 4]
003e cmp byte ptr es:[bx], 0
0042 je 0x45fe
0044 mov di, word ptr [bp + 8]
0047 add di, cx
0049 add di, si
004b cmp byte ptr [di + 0x28e8], 0x10
0050 ja 0x4664
0052 add bx, 3
0055 inc si
0056 cmp si, 3
0059 jl 0x45ea
005b add cx, 0x40
005e mov si, word ptr [bp - 6]
0061 mov word ptr [bp - 4], cx
0064 inc si
0065 cmp si, 3
0068 jl 0x45d7
006a xor cx, cx
006c mov ax, word ptr [bp + 6]
006f shl ax, 6
0072 mov word ptr [bp - 4], ax
0075 mov ax, word ptr [bp - 8]
0078 mov dx, ax
007a shl ax, 1
007c add ax, dx
007e mov word ptr [bp - 0xa], ax
0081 xor bx, bx
0083 mov di, word ptr [bp - 0xa]
0086 add di, cx
0088 add di, 0x87a0
008c mov word ptr [bp - 6], cx
008f mov cl, byte ptr es:[di]
0092 sub ch, ch
0094 or cx, cx
0096 je 0x464e
0098 mov si, word ptr [bp + 8]
009b add si, word ptr [bp - 4]
009e mov byte ptr [bx + si + 0x28e8], cl
00a2 add di, 3
00a5 inc bx
00a6 cmp bx, 3
00a9 jl 0x463b
00ab add word ptr [bp - 4], 0x40
00af mov cx, word ptr [bp - 6]
00b2 inc cx
00b3 cmp cx, 3
00b6 jl 0x462d
00b8 pop si
00b9 pop di
00ba leave 
00bb retf 
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

- {'symbol': '_AddRocks', 'offset': 17204, 'source': None, 'size': 440}
- {'symbol': '_AddRock5', 'offset': 17644, 'source': None, 'size': 191}
- {'symbol': '_InitSpider', 'offset': 18024, 'source': None, 'size': 156}
- {'symbol': '_MoveSpider', 'offset': 18180, 'source': None, 'size': None}
