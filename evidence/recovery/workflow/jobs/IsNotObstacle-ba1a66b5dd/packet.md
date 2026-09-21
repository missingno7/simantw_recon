# Recovery task _IsNotObstacle

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 255 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 2], 0xffff
000b cmp word ptr [bp + 6], 1
000f jg 0x94f4
0011 mov si, word ptr [bp + 8]
0014 or si, si
0016 jl 0x950c
0018 cmp si, 0x7f
001b jg 0x950c
001d cmp word ptr [bp + 0xa], 0
0021 jl 0x950c
0023 cmp word ptr [bp + 0xa], 0x3f
0027 jg 0x950c
0029 mov dx, 1
002c jmp 0x950e
002e mov si, word ptr [bp + 8]
0031 or si, si
0033 jl 0x950c
0035 cmp si, 0x3f
0038 jg 0x950c
003a cmp word ptr [bp + 0xa], 0
003e jl 0x950c
0040 cmp word ptr [bp + 0xa], 0x3f
0044 jle 0x94ef
0046 xor dx, dx
0048 dec dx
0049 je 0x9516
004b mov dx, word ptr [bp - 2]
004e jmp 0x9552
0050 mov ax, word ptr [bp + 6]
0053 or ax, ax
0055 jl 0x9511
0057 jo 0x9511
0059 dec ax
005a jle 0x952a
005c dec ax
005d je 0x9538
005f dec ax
0060 je 0x9546
0062 jmp 0x9511
0064 mov bx, word ptr [bp + 0xa]
0067 mov di, si
0069 shl di, 6
006c mov dl, byte ptr [bx + di + 0x28e8]
0070 jmp 0x9550
0072 mov bx, word ptr [bp + 0xa]
0075 mov di, si
0077 shl di, 6
007a mov dl, byte ptr [bx + di + 0x48e8]
007e jmp 0x9550
0080 shl si, 6
0083 mov bx, word ptr [bp + 0xa]
0086 mov dl, byte ptr [bx + si + 0x58e8]
008a sub dh, dh
008c mov cx, dx
008e or cx, cx
0090 jge 0x9560
0092 xor bx, bx
0094 mov ax, bx
0096 pop si
0097 pop di
0098 leave 
0099 retf 
009a mov dx, word ptr [bp + 6]
009d cmp dx, 1
00a0 jg 0x9590
00a2 mov <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00a5 mov es, ax
00a7 cmp word ptr es:[0x9b6e], 0
00ad jne 0x957a
00af cmp cx, 0x53
00b2 jmp 0x958b
00b4 cmp word ptr es:[0x9b6e], 0
00ba jne 0x9588
00bc cmp cx, 0x50
00bf jmp 0x958b
00c1 nop 
00c2 cmp cx, 0x5f
00c5 jg 0x9558
00c7 jmp 0x95bc
00c9 nop 
00ca cmp cx, 0x18
00cd jle 0x95bc
00cf cmp dx, 1
00d2 jg 0x95ac
00d4 dec dx
00d5 jne 0x95b6
00d7 cmp cx, 0x51
00da jl 0x95b6
00dc cmp cx, 0x53
00df jg 0x95b6
00e1 mov dx, 1
00e4 jmp 0x95b8
00e6 cmp cx, 0x30
00e9 jl 0x95b6
00eb cmp cx, 0x31
00ee jle 0x95a7
00f0 xor dx, dx
00f2 or dx, dx
00f4 je 0x9558
00f6 mov bx, 1
00f9 mov ax, bx
00fb pop si
00fc pop di
00fd leave 
00fe retf 
```

## Known declaration examples

- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_TileCanBeMovedOn', 'offset': 37698, 'source': None, 'size': 349}
- {'symbol': '_IsNotBarrier', 'offset': 38048, 'source': 'src/recovered/IsNotBarrier.c', 'size': 37}
- {'symbol': '_IsItDigable', 'offset': 38342, 'source': None, 'size': 240}
- {'symbol': '_IsItYellow', 'offset': 38582, 'source': None, 'size': 206}
