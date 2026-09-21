# Recovery task _OpenIndex

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 194 bytes.

```asm
0000 enter 0x70, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 0xa]
0009 push word ptr [bp + 8]
000c push word ptr [bp + 6]
000f push ds
0010 push 0xb65c
0013 lea ax, [bp - 0x6a]
0016 push ss
0017 push ax
0018 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
001d add sp, 0xc
0020 lea ax, [bp - 0x6a]
0023 push ss
0024 push ax
0025 push 2
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 85}}]
002c mov es, word ptr [0xc68c]
0030 imul bx, si, 0x7c
0033 mov word ptr [bp - 0x6c], bx
0036 mov word ptr es:[bx + 0x747e], ax
003b mov di, ax
003d or di, di
003f jg 0x9ad3
0041 push ds
0042 push 0xb663
0045 nop 
0046 push cs
0047 call 0x8f0c ; _DosPunt
004a add sp, 4
004d push di
004e mov ax, word ptr [bp - 0x6c]
0051 add ax, 0x745c
0054 mov <resolved loader operand; see bindings> ; [{'operand_offset': 85, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0057 push cx
0058 push ax
0059 push 0x14
005b mov si, ax
005d mov word ptr [bp - 0x70], si
0060 mov word ptr [bp - 0x6e], cx
0063 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 82}}]
0068 lea ax, [bp - 0x6a]
006b push ss
006c push ax
006d les bx, ptr [bp - 0x70]
0070 mov ax, word ptr es:[bx]
0073 shl ax, 3
0076 mov word ptr [bp - 6], ax
0079 push ax
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
007f add sp, 6
0082 mov es, word ptr [0xc68c]
0086 mov bx, word ptr [bp - 0x6c]
0089 mov word ptr es:[bx + 0x7458], ax
008e mov word ptr es:[bx + 0x745a], dx
0093 mov word ptr [bp - 4], ax
0096 mov word ptr [bp - 2], dx
0099 or dx, ax
009b jne 0x9b2f
009d push ds
009e push 0xb676
00a1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 164, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
00a6 add sp, 4
00a9 push di
00aa push word ptr [bp - 2]
00ad push word ptr [bp - 4]
00b0 push word ptr [bp - 6]
00b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 180, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 82}}]
00b8 push di
00b9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 186, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 81}}]
00be pop si
00bf pop di
00c0 leave 
00c1 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
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

- {'symbol': '_ch_GetPrime', 'offset': 39366, 'source': None, 'size': 159}
- {'symbol': '_ch_SetCacheHooks', 'offset': 39526, 'source': 'src/recovered/ch_SetCacheHooks.c', 'size': 31}
- {'symbol': '_CreateIndex', 'offset': 39752, 'source': None, 'size': 251}
- {'symbol': '_CloseIndex', 'offset': 40004, 'source': None, 'size': 222}
