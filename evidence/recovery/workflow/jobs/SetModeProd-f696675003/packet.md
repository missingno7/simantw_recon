# Recovery task _SetModeProd

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 156 bytes.

```asm
0000 enter 0x1a, 0
0004 push di
0005 push si
0006 xor di, di
0008 mov bx, 0x9e70
000b mov <resolved loader operand; see bindings> ; [{'operand_offset': 12, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
000e mov es, ax
0010 add di, word ptr es:[bx]
0013 add bx, 2
0016 cmp bx, 0x9e76
001a jb 0x336
001c xor si, si
001e mov word ptr [bp - 2], di
0021 mov <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0024 mov es, ax
0026 push 0
0028 push -1
002a mov ax, di
002c cdq 
002d push dx
002e push ax
002f push 0
0031 push word ptr es:[si - 0x638c]
0036 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 57, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
003b push dx
003c push ax
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
0042 mov word ptr [bp + si - 0x1a], ax
0045 add si, 2
0048 cmp si, 6
004b jl 0x34c
004d xor bx, bx
004f mov <resolved loader operand; see bindings> ; [{'operand_offset': 80, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0052 mov es, ax
0054 mov si, bx
0056 mov ax, word ptr [bp + si - 0x1a]
0059 sub ax, word ptr es:[bx - 0x6190]
005e mov word ptr [bp + si - 0xe], ax
0061 add bx, 2
0064 cmp bx, 6
0067 jl 0x37a
0069 xor dx, dx
006b mov cx, dx
006d mov di, dx
006f lea bx, [bp - 0xe]
0072 cmp word ptr [bx], cx
0074 jle 0x3a0
0076 mov cx, word ptr [bx]
0078 mov di, dx
007a inc dx
007b add bx, 2
007e lea ax, [bp - 8]
0081 cmp bx, ax
0083 jb 0x398
0085 mov es, word ptr [0xc4ca]
0089 shl di, 1
008b mov ax, word ptr es:[di - 0x764a]
0090 mov es, word ptr [0xc4cc]
0094 mov word ptr es:[0x8a58], ax
0098 pop si
0099 pop di
009a leave 
009b retf 
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

- {'symbol': '_GstrB', 'offset': 460, 'source': None, 'size': 162}
- {'symbol': '_SetCasteProd', 'offset': 622, 'source': None, 'size': 183}
- {'symbol': '_GstrR', 'offset': 962, 'source': None, 'size': 332}
- {'symbol': '_StartAttack', 'offset': 1294, 'source': None, 'size': 66}
