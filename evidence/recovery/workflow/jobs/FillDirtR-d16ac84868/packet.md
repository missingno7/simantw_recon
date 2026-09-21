# Recovery task _FillDirtR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 193 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 6]
0008 mov si, word ptr [bp + 8]
000b mov bx, di
000d shl bx, 6
0010 add bx, si
0012 mov byte ptr ss:[bx + 0x58e8], 0x2e
0018 mov byte ptr ss:[bx - 0x6718], 0
001e mov <resolved loader operand; see bindings> ; [{'operand_offset': 31, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0021 mov es, ax
0023 cmp word ptr es:[0x7a56], 1
0029 jle 0x8852
002b mov <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
002e mov ds, ax
0030 mov ax, di
0032 cdq 
0033 sub word ptr [0x9ddc], ax
0037 sbb word ptr [0x9dde], dx
003b cmp word ptr [0x9dde], 0
0040 jge 0x8824
0042 sub ax, ax
0044 mov word ptr [0x9dde], ax
0047 mov word ptr [0x9ddc], ax
004a mov ax, si
004c cdq 
004d mov <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0050 mov es, cx
0052 sub word ptr es:[0x9de2], ax
0057 sbb word ptr es:[0x9de4], dx
005c cmp word ptr es:[0x9de4], 0
0062 jge 0x8848
0064 sub ax, ax
0066 mov word ptr es:[0x9de4], ax
006a mov word ptr es:[0x9de2], ax
006e mov <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0071 mov es, ax
0073 dec word ptr es:[0x7a56]
0078 push ss
0079 pop ds
007a lea ax, [si - 1]
007d push ax
007e push di
007f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SmoothEdgesR
0084 add sp, 4
0087 push si
0088 lea ax, [di + 1]
008b push ax
008c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 143, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SmoothEdgesR
0091 add sp, 4
0094 lea ax, [si + 1]
0097 push ax
0098 push di
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 156, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SmoothEdgesR
009e add sp, 4
00a1 push si
00a2 lea ax, [di - 1]
00a5 push ax
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SmoothEdgesR
00ab add sp, 4
00ae mov es, word ptr [0xc27a]
00b2 shl di, 6
00b5 add si, di
00b7 mov byte ptr es:[si + 0x13a4], 0
00bd pop si
00be pop di
00bf leave 
00c0 retf 
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

- {'symbol': '_IsItWall', 'offset': 34558, 'source': 'src/recovered/wf_IsItWall-da7d76733f.c', 'size': 26}
- {'symbol': '_FillDirtB', 'offset': 34584, 'source': 'src/recovered/wf_FillDirtB-b73109489f.c', 'size': 193}
- {'symbol': '_SmoothMany', 'offset': 34972, 'source': 'src/recovered/wf_SmoothMany-a26578c922.c', 'size': 87}
- {'symbol': '_SmoothACell', 'offset': 35060, 'source': None, 'size': 944}
