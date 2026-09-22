# Recovery task _DeleteCurrentIndex

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 259 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0009 mov es, ax
000b imul bx, word ptr [bp + 6], 0x7c
000f mov ax, word ptr es:[bx + 0x7458]
0014 mov dx, word ptr es:[bx + 0x745a]
0019 mov word ptr [bp - 0xa], ax
001c mov word ptr [bp - 8], dx
001f dec word ptr es:[bx + 0x745c]
0024 mov si, word ptr es:[bx + 0x745c]
0029 or si, si
002b jge 0x9e4b
002d push ds
002e push 0xb6de
0031 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0036 add sp, 4
0039 or si, si
003b jne 0x9e5a
003d sub ax, ax
003f mov word ptr [bp - 4], ax
0042 mov word ptr [bp - 6], ax
0045 jmp 0x9eeb
0048 mov word ptr [bp - 2], si
004b mov es, word ptr [0xc68c]
004f imul bx, word ptr [bp + 6], 0x7c
0053 mov ax, word ptr es:[bx + 0x7458]
0058 mov dx, word ptr es:[bx + 0x745a]
005d mov word ptr [bp - 0xa], ax
0060 mov word ptr [bp - 8], dx
0063 push ds
0064 push 0xb713
0067 mov ax, si
0069 shl ax, 3
006c push ax
006d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
0072 add sp, 6
0075 mov word ptr [bp - 6], ax
0078 mov word ptr [bp - 4], dx
007b or dx, ax
007d jne 0x9e9d
007f push ds
0080 push 0xb71a
0083 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 134, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0088 add sp, 4
008b mov ax, word ptr [bp - 0xa]
008e mov dx, word ptr [bp - 8]
0091 mov es, word ptr [0xc68e]
0095 mov cx, word ptr es:[0x9e92]
009a mov bx, cx
009c shl cx, 3
009f push ds
00a0 mov si, ax
00a2 mov ds, dx
00a4 les di, ptr [bp - 6]
00a7 shr cx, 1
00a9 rep movsw word ptr es:[di], word ptr [si]
00ab adc cx, cx
00ad rep movsb byte ptr es:[di], byte ptr [si]
00af pop ds
00b0 mov cx, bx
00b2 shl bx, 3
00b5 mov si, bx
00b7 add bx, ax
00b9 lea ax, [bx + 8]
00bc mov bx, word ptr [bp - 6]
00bf mov di, cx
00c1 mov cx, word ptr [bp - 2]
00c4 sub cx, di
00c6 shl cx, 3
00c9 push ds
00ca lea di, [bx + si]
00cc mov si, ax
00ce mov ds, dx
00d0 shr cx, 1
00d2 rep movsw word ptr es:[di], word ptr [si]
00d4 adc cx, cx
00d6 rep movsb byte ptr es:[di], byte ptr [si]
00d8 pop ds
00d9 mov ax, word ptr [bp - 6]
00dc mov dx, word ptr [bp - 4]
00df mov es, word ptr [0xc68c]
00e3 imul bx, word ptr [bp + 6], 0x7c
00e7 mov word ptr es:[bx + 0x7458], ax
00ec mov word ptr es:[bx + 0x745a], dx
00f1 push word ptr [bp - 8]
00f4 push word ptr [bp - 0xa]
00f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 250, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
00fc add sp, 4
00ff pop si
0100 pop di
0101 leave 
0102 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CloseIndex', 'offset': 40004, 'source': None, 'size': 222}
- {'symbol': '_FindIndex', 'offset': 40228, 'source': None, 'size': 237}
- {'symbol': '_AddIndex', 'offset': 40726, 'source': None, 'size': 351}
- {'symbol': '_DeleteIndex', 'offset': 41078, 'source': None, 'size': 245}
