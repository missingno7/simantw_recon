# Recovery task _FindLifeIndex

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 217 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 mov dx, word ptr [bp + 6]
0009 cmp dx, 1
000c jg 0x595e
000e mov <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0011 mov es, ax
0013 mov cx, word ptr es:[0x80f0]
0018 mov ax, 0x23a4
001b mov <resolved loader operand; see bindings> ; [{'operand_offset': 28, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
001e mov word ptr [bp - 0xa], ax
0021 mov ds, dx
0023 mov ax, 0x278e
0026 mov bx, ax
0028 mov word ptr [bp - 0xc], dx
002b mov word ptr [bp - 6], 0x2f62
0030 mov word ptr [bp - 4], dx
0033 mov di, word ptr [bp - 0xa]
0036 mov word ptr [bp - 8], ds
0039 jmp 0x59af
003b nop 
003c cmp dx, 2
003f jne 0x598a
0041 mov <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0044 mov es, ax
0046 mov cx, word ptr es:[0x99d4]
004b mov ax, 0x3736
004e mov <resolved loader operand; see bindings> ; [{'operand_offset': 79, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0051 mov di, ax
0053 mov ds, dx
0055 mov ax, 0x392c
0058 mov bx, ax
005a mov word ptr [bp - 0xc], dx
005d mov word ptr [bp - 6], 0x3d18
0062 mov word ptr [bp - 4], dx
0065 jmp 0x5958
0067 nop 
0068 mov <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
006b mov es, ax
006d mov cx, word ptr es:[0x72cc]
0072 mov ax, 0x4104
0075 mov <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0078 mov di, ax
007a mov word ptr [bp - 8], dx
007d mov ax, 0x42fa
0080 mov bx, ax
0082 mov word ptr [bp - 0xc], dx
0085 mov word ptr [bp - 6], 0x46e6
008a mov word ptr [bp - 4], dx
008d mov dx, cx
008f dec dx
0090 js 0x59ba
0092 mov word ptr [bp - 0xe], bx
0095 jmp 0x59be
0097 nop 
0098 mov si, dx
009a jmp 0x59f3
009c mov si, dx
009e mov ds, word ptr [bp - 8]
00a1 les bx, ptr [bp - 6]
00a4 mov cl, byte ptr es:[bx + si]
00a7 and cl, byte ptr [bp + 0x10]
00aa sub ch, ch
00ac mov bx, di
00ae add bx, si
00b0 mov al, byte ptr [bx]
00b2 sub ah, ah
00b4 cmp ax, word ptr [bp + 8]
00b7 jne 0x59f0
00b9 les bx, ptr [bp - 0xe]
00bc mov al, byte ptr es:[bx + si]
00bf cmp ax, word ptr [bp + 0xa]
00c2 jne 0x59f0
00c4 cmp word ptr [bp + 0xc], cx
00c7 jg 0x59f0
00c9 cmp cx, word ptr [bp + 0xe]
00cc jle 0x59f3
00ce dec si
00cf jns 0x59c3
00d1 push ss
00d2 pop ds
00d3 mov ax, si
00d5 pop si
00d6 pop di
00d7 leave 
00d8 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetAntIndex', 'offset': 22332, 'source': None, 'size': 269}
- {'symbol': '_SetAntIndex', 'offset': 22602, 'source': 'src/recovered/wf_SetAntIndex-965b821698.c', 'size': 216}
- {'symbol': '_FindAntIndex', 'offset': 23036, 'source': None, 'size': 213}
- {'symbol': '_IsClear3x3', 'offset': 23250, 'source': None, 'size': 90}
