# Recovery task _AddMsgBalloon

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 276 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xc]
0009 cmp di, 0xa
000c jne 0x4bbe
000e mov ax, word ptr [bp + 6]
0011 cdq 
0012 idiv word ptr ss:[0x143a]
0017 mov bx, ax
0019 mov ax, word ptr [bp + 8]
001c cdq 
001d idiv word ptr ss:[0x143c]
0022 mov cx, ax
0024 jmp 0x4bc4
0026 mov bx, word ptr [bp + 6]
0029 mov cx, word ptr [bp + 8]
002c mov si, 0x9fd0
002f mov <resolved loader operand; see bindings> ; [{'operand_offset': 48, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0032 mov es, ax
0034 mov word ptr [bp - 6], si
0037 mov word ptr [bp - 4], es
003a cmp word ptr es:[si], 6
003e jl 0x4bdb
0040 jmp 0x4ca6
0043 mov ax, word ptr [bp + 0xa]
0046 cmp word ptr ss:[0xcc76], ax
004b jne 0x4c18
004d mov <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0050 mov ds, ax
0052 cmp word ptr [0x7d2e], bx
0056 jg 0x4c18
0058 mov ax, word ptr [0x7d2e]
005b add ax, word ptr ss:[0xcc80]
0060 cmp ax, bx
0062 jle 0x4c18
0064 mov ax, cx
0066 sub ax, 3
0069 cmp word ptr [0x7d30], ax
006d jg 0x4c18
006f mov ax, word ptr [0x7d30]
0072 add ax, word ptr ss:[0xcd7a]
0077 cmp ax, cx
0079 jle 0x4c18
007b mov dx, 1
007e jmp 0x4c1a
0080 xor dx, dx
0082 or dx, dx
0084 jne 0x4c21
0086 jmp 0x4ca6
0089 cmp di, 0xa
008c jne 0x4c30
008e mov <resolved loader operand; see bindings> ; [{'operand_offset': 143, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0091 mov es, ax
0093 mov ax, word ptr [bp + 6]
0096 jmp 0x4c3f
0098 mov <resolved loader operand; see bindings> ; [{'operand_offset': 153, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
009b mov es, ax
009d mov ax, word ptr ss:[0x143a]
00a1 imul word ptr [bp + 6]
00a4 add ax, 8
00a7 lds bx, ptr [bp - 6]
00aa mov bx, word ptr [bx]
00ac shl bx, 2
00af mov word ptr [bp - 8], bx
00b2 mov word ptr es:[bx - 0x7f2a], ax
00b7 cmp di, 0xa
00ba jne 0x4c5a
00bc mov ax, word ptr [bp + 8]
00bf jmp 0x4c64
00c1 nop 
00c2 mov ax, word ptr ss:[0x143c]
00c6 imul word ptr [bp + 8]
00c9 add ax, 8
00cc mov word ptr es:[bx - 0x7f28], ax
00d1 mov ax, word ptr [bp + 0xa]
00d4 les bx, ptr [bp - 6]
00d7 mov si, word ptr es:[bx]
00da shl si, 1
00dc mov <resolved loader operand; see bindings> ; [{'operand_offset': 221, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00df mov es, cx
00e1 mov word ptr es:[si + 0x7d68], ax
00e6 mov <resolved loader operand; see bindings> ; [{'operand_offset': 231, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00e9 mov es, ax
00eb mov word ptr es:[si + 0x78be], di
00f0 mov ax, word ptr [bp + 0xe]
00f3 mov dx, word ptr [bp + 0x10]
00f6 mov <resolved loader operand; see bindings> ; [{'operand_offset': 247, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00f9 mov es, cx
00fb mov bx, word ptr [bp - 8]
00fe mov word ptr es:[bx + 0x7c24], ax
0103 mov word ptr es:[bx + 0x7c26], dx
0108 les bx, ptr [bp - 6]
010b inc word ptr es:[bx]
010e push ss
010f pop ds
0110 pop si
0111 pop di
0112 leave 
0113 retf 
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

- {'symbol': '_QueenBalloons', 'offset': 19012, 'source': 'src/recovered/wf_QueenBalloons-a57aa281b9.c', 'size': 169}
- {'symbol': '_RestBalloons', 'offset': 19182, 'source': 'src/recovered/wf_RestBalloons-17fb4c1bf3.c', 'size': 169}
- {'symbol': '_DrawCurBalloons', 'offset': 19628, 'source': None, 'size': 2693}
- {'symbol': '_EditMsgBalloon', 'offset': 22322, 'source': 'src/recovered/wf_EditMsgBalloon-9036028d9e.c', 'size': 114}
