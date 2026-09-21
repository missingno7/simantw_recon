# Recovery task _RestBalloons

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 169 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov <resolved loader operand; see bindings> ; [{'operand_offset': 4, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0006 mov es, ax
0008 cmp word ptr es:[0xa07e], 0
000e je 0x4b01
0010 jmp 0x4b93
0013 mov bx, word ptr [bp + 6]
0016 mov cx, word ptr [bp + 0xa]
0019 cmp word ptr ss:[0xcc76], cx
001e jne 0x4b44
0020 mov <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0023 mov ds, ax
0025 cmp word ptr [0x7d2e], bx
0029 jg 0x4b44
002b mov ax, word ptr [0x7d2e]
002e add ax, word ptr ss:[0xcc80]
0033 cmp ax, bx
0035 jle 0x4b44
0037 mov ax, word ptr [bp + 8]
003a sub ax, 3
003d cmp word ptr [0x7d30], ax
0041 jg 0x4b44
0043 mov ax, word ptr [0x7d30]
0046 add ax, word ptr ss:[0xcd7a]
004b cmp ax, word ptr [bp + 8]
004e jle 0x4b44
0050 mov dx, 1
0053 jmp 0x4b46
0055 nop 
0056 xor dx, dx
0058 or dx, dx
005a je 0x4b93
005c mov <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
005f mov ds, ax
0061 cmp word ptr [0x7d40], bx
0065 jne 0x4b78
0067 mov ax, word ptr [bp + 8]
006a cmp word ptr [0x7d42], ax
006e jne 0x4b78
0070 mov <resolved loader operand; see bindings> ; [{'operand_offset': 113, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0073 mov es, ax
0075 cmp word ptr es:[0x72a2], cx
007a jne 0x4b78
007c mov <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
007f mov es, ax
0081 inc word ptr es:[0xa07e]
0086 push ss
0087 pop ds
0088 leave 
0089 retf 
008a mov <resolved loader operand; see bindings> ; [{'operand_offset': 139, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
008d mov es, ax
008f mov word ptr es:[0x72c4], bx
0094 mov ax, word ptr [bp + 8]
0097 mov word ptr es:[0x72c6], ax
009b mov <resolved loader operand; see bindings> ; [{'operand_offset': 156, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
009e mov es, ax
00a0 mov word ptr es:[0x7c46], cx
00a5 push ss
00a6 pop ds
00a7 leave 
00a8 retf 
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

- {'symbol': '_FightBalloons', 'offset': 18842, 'source': 'src/recovered/wf_FightBalloons-dfb233112a.c', 'size': 169}
- {'symbol': '_QueenBalloons', 'offset': 19012, 'source': 'src/recovered/wf_QueenBalloons-a57aa281b9.c', 'size': 169}
- {'symbol': '_AddMsgBalloon', 'offset': 19352, 'source': None, 'size': 276}
- {'symbol': '_DrawCurBalloons', 'offset': 19628, 'source': None, 'size': 2693}
