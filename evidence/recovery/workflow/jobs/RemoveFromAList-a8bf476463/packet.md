# Recovery task _RemoveFromAList

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 255 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov es, word ptr [0xc424]
000d mov bl, byte ptr es:[si + 0x278e]
0012 sub bh, bh
0014 mov di, word ptr es:[si + 0x23a4]
0019 and di, 0xff
001d shl di, 6
0020 mov byte ptr [bx + di + 0x68e8], bh
0024 mov bx, 0x80f0
0027 mov es, word ptr [0xc426]
002b mov word ptr [bp - 8], bx
002e mov word ptr [bp - 6], es
0031 cmp word ptr es:[bx], 0
0035 jle 0x2b7c
0037 dec word ptr es:[bx]
003a les bx, ptr [bp - 8]
003d mov ax, word ptr es:[bx]
0040 sub ax, si
0042 cdq 
0043 mov word ptr [bp - 4], ax
0046 mov word ptr [bp - 2], dx
0049 push dx
004a push ax
004b mov ax, si
004d add si, 0x23a4
0051 mov <resolved loader operand; see bindings> ; [{'operand_offset': 82, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0054 push cx
0055 push si
0056 mov dx, ax
0058 inc ax
0059 mov bx, ax
005b add ax, 0x23a4
005e push cx
005f push ax
0060 mov si, dx
0062 mov di, bx
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 103, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _BlockMove
0069 add sp, 0xc
006c push word ptr [bp - 2]
006f push word ptr [bp - 4]
0072 mov ax, si
0074 add si, 0x278e
0078 mov <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
007b push cx
007c push si
007d mov dx, di
007f add di, 0x278e
0083 push cx
0084 push di
0085 mov si, ax
0087 mov di, dx
0089 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 140, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _BlockMove
008e add sp, 0xc
0091 push word ptr [bp - 2]
0094 push word ptr [bp - 4]
0097 mov ax, si
0099 add si, 0x2b78
009d push <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00a0 push si
00a1 mov cx, di
00a3 add di, 0x2b78
00a7 push <resolved loader operand; see bindings> ; [{'operand_offset': 168, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00aa push di
00ab mov si, ax
00ad mov di, cx
00af lcall <resolved loader operand; see bindings> ; [{'operand_offset': 178, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _BlockMove
00b4 add sp, 0xc
00b7 push word ptr [bp - 2]
00ba push word ptr [bp - 4]
00bd mov ax, si
00bf add si, 0x2f62
00c3 push <resolved loader operand; see bindings> ; [{'operand_offset': 196, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00c6 push si
00c7 mov cx, di
00c9 add di, 0x2f62
00cd push <resolved loader operand; see bindings> ; [{'operand_offset': 206, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00d0 push di
00d1 mov si, ax
00d3 mov di, cx
00d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 216, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _BlockMove
00da add sp, 0xc
00dd push word ptr [bp - 2]
00e0 push word ptr [bp - 4]
00e3 add si, 0x334c
00e7 push <resolved loader operand; see bindings> ; [{'operand_offset': 232, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00ea push si
00eb add di, 0x334c
00ef push <resolved loader operand; see bindings> ; [{'operand_offset': 240, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00f2 push di
00f3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 246, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _BlockMove
00f8 add sp, 0xc
00fb pop si
00fc pop di
00fd leave 
00fe retf 
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

- {'symbol': '_CompactListB', 'offset': 10874, 'source': 'src/recovered/wf_CompactListB-6f09945019.c', 'size': 99}
- {'symbol': '_CompactListR', 'offset': 10974, 'source': 'src/recovered/wf_CompactListR-17480d0ee2.c', 'size': 99}
- {'symbol': '_FindInAList', 'offset': 11330, 'source': None, 'size': 68}
- {'symbol': '_FindInBList', 'offset': 11398, 'source': 'src/recovered/wf_FindInBList-d950932078.c', 'size': 72}
