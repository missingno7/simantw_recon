# Recovery task _CloseIndex

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 222 bytes.

```asm
0000 enter 0x70, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 imul ax, si, 0x7c
000c mov word ptr [bp - 0x66], ax
000f add ax, 0x7408
0012 push <resolved loader operand; see bindings> ; [{'operand_offset': 19, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0015 push ax
0016 push ds
0017 push 0xb6c4
001a lea ax, [bp - 0x64]
001d push ss
001e push ax
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
0024 add sp, 0xc
0027 mov es, word ptr [0xc68c]
002b mov bx, word ptr [bp - 0x66]
002e cmp word ptr es:[bx + 0x7482], 0
0034 je 0x9cf7
0036 lea ax, [bp - 0x64]
0039 push ss
003a push ax
003b push 0
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 83}}]
0042 mov es, word ptr [0xc68c]
0046 mov bx, word ptr [bp - 0x66]
0049 mov word ptr es:[bx + 0x747e], ax
004e mov di, ax
0050 or di, di
0052 jg 0x9ca4
0054 push ds
0055 push 0xb6cb
0058 nop 
0059 push cs
005a call 0x8f0c ; _DosPunt
005d add sp, 4
0060 push di
0061 push 0
0063 push 0
0065 push 0
0067 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 104, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 84}}]
006c push di
006d mov ax, word ptr [bp - 0x66]
0070 add ax, 0x745c
0073 mov <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0076 push cx
0077 push ax
0078 push 0x14
007a mov word ptr [bp - 0x6c], ax
007d mov word ptr [bp - 0x6a], cx
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 86}}]
0085 les bx, ptr [bp - 0x6c]
0088 mov ax, word ptr es:[bx]
008b mov word ptr [bp - 0x68], ax
008e or ax, ax
0090 je 0x9cf1
0092 push di
0093 mov es, word ptr [0xc68c]
0097 mov bx, word ptr [bp - 0x66]
009a push word ptr es:[bx + 0x745a]
009f push word ptr es:[bx + 0x7458]
00a4 shl ax, 3
00a7 push ax
00a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 86}}]
00ad push di
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 175, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 81}}]
00b3 mov es, word ptr [0xc68c]
00b7 mov bx, word ptr [bp - 0x66]
00ba mov ax, word ptr es:[bx + 0x7458]
00bf mov dx, word ptr es:[bx + 0x745a]
00c4 mov word ptr [bp - 0x70], ax
00c7 mov word ptr [bp - 0x6e], dx
00ca or dx, ax
00cc je 0x9d1e
00ce push word ptr [bp - 0x6e]
00d1 push ax
00d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
00d7 add sp, 4
00da pop si
00db pop di
00dc leave 
00dd retf 
```

## Known declaration examples

- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_OpenIndex', 'offset': 39558, 'source': None, 'size': 194}
- {'symbol': '_CreateIndex', 'offset': 39752, 'source': None, 'size': 251}
- {'symbol': '_FindIndex', 'offset': 40228, 'source': None, 'size': 237}
- {'symbol': '_DeleteCurrentIndex', 'offset': 40466, 'source': None, 'size': 259}
