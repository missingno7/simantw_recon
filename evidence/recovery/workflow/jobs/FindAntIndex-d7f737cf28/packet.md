# Recovery task _FindAntIndex

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 213 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 mov dx, word ptr [bp + 6]
0009 cmp dx, 1
000c jg 0x5a38
000e mov <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0011 mov es, ax
0013 mov cx, word ptr es:[0x80f0]
0018 mov ax, 0x23a4
001b mov <resolved loader operand; see bindings> ; [{'operand_offset': 28, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
001e mov word ptr [bp - 0xa], ax
0021 mov ds, dx
0023 mov ax, 0x278e
0026 mov si, ax
0028 mov word ptr [bp - 0xc], dx
002b mov word ptr [bp - 6], 0x2f62
0030 mov word ptr [bp - 4], dx
0033 mov bx, word ptr [bp - 0xa]
0036 mov word ptr [bp - 8], ds
0039 jmp 0x5a89
003b nop 
003c cmp dx, 2
003f jne 0x5a64
0041 mov <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0044 mov es, ax
0046 mov cx, word ptr es:[0x99d4]
004b mov ax, 0x3736
004e mov <resolved loader operand; see bindings> ; [{'operand_offset': 79, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0051 mov bx, ax
0053 mov ds, dx
0055 mov ax, 0x392c
0058 mov si, ax
005a mov word ptr [bp - 0xc], dx
005d mov word ptr [bp - 6], 0x3d18
0062 mov word ptr [bp - 4], dx
0065 jmp 0x5a32
0067 nop 
0068 mov <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
006b mov es, ax
006d mov cx, word ptr es:[0x72cc]
0072 mov ax, 0x4104
0075 mov <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0078 mov bx, ax
007a mov word ptr [bp - 8], dx
007d mov ax, 0x42fa
0080 mov si, ax
0082 mov word ptr [bp - 0xc], dx
0085 mov word ptr [bp - 6], 0x46e6
008a mov word ptr [bp - 4], dx
008d mov dx, cx
008f dec dx
0090 jns 0x5a92
0092 mov si, dx
0094 jmp 0x5ac9
0096 mov word ptr [bp - 0xe], si
0099 mov si, dx
009b mov cx, word ptr [bp - 0xe]
009e mov ds, word ptr [bp - 8]
00a1 mov di, bx
00a3 add di, si
00a5 mov al, byte ptr [di]
00a7 sub ah, ah
00a9 cmp ax, word ptr [bp + 8]
00ac jne 0x5ac6
00ae mov es, word ptr [bp - 0xc]
00b1 mov di, cx
00b3 add di, si
00b5 mov al, byte ptr es:[di]
00b8 cmp ax, word ptr [bp + 0xa]
00bb jne 0x5ac6
00bd les di, ptr [bp - 6]
00c0 add di, si
00c2 mov al, byte ptr es:[di]
00c5 cmp ax, word ptr [bp + 0xc]
00c8 je 0x5ac9
00ca dec si
00cb jns 0x5a9d
00cd push ss
00ce pop ds
00cf mov ax, si
00d1 pop si
00d2 pop di
00d3 leave 
00d4 retf 
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

- {'symbol': '_SetAntIndex', 'offset': 22602, 'source': None, 'size': 216}
- {'symbol': '_FindLifeIndex', 'offset': 22818, 'source': None, 'size': 217}
- {'symbol': '_IsClear3x3', 'offset': 23250, 'source': None, 'size': 90}
- {'symbol': '_IsClearTile', 'offset': 23340, 'source': None, 'size': 332}
