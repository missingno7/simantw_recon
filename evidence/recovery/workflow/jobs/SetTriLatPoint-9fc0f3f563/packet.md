# Recovery task _SetTriLatPoint

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 221 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xe]
0009 mov si, word ptr [bp + 6]
000c push 0
000e push -1
0010 mov es, word ptr [0xc122]
0014 mov ax, word ptr es:[0x80d0]
0018 sub ax, 2
001b push 0
001d push ax
001e mov es, word ptr [bp + 8]
0021 mov cx, word ptr es:[si]
0024 mov bx, cx
0026 sub ax, ax
0028 mov word ptr [bp - 8], cx
002b mov word ptr [bp - 6], ax
002e mov ax, 0xffff
0031 xor dx, dx
0033 sub ax, cx
0035 sbb dx, word ptr [bp - 6]
0038 push dx
0039 push ax
003a mov word ptr [bp - 0xa], bx
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0042 push dx
0043 push ax
0044 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
0049 les bx, ptr [bp + 0xa]
004c add ax, word ptr es:[bx + 2]
0050 mov es, word ptr [bp + 0x10]
0053 mov word ptr es:[di + 2], ax
0057 push 0
0059 push -1
005b mov es, word ptr [0xc120]
005f push 0
0061 push word ptr es:[0x7f00]
0066 push word ptr [bp - 6]
0069 push word ptr [bp - 8]
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0071 push dx
0072 push ax
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
0078 mov word ptr [bp - 4], ax
007b shl ax, 1
007d mov es, word ptr [0xc11c]
0081 sub ax, word ptr es:[0x9cec]
0086 neg ax
0088 mov word ptr [bp - 2], ax
008b cmp word ptr [bp - 0xa], -1
008f je 0xcc70
0091 cmp ax, 3
0094 jl 0xcc70
0096 mov ax, 0xffff
0099 mov es, word ptr [bp + 8]
009c sub ax, word ptr es:[si]
009f push 0
00a1 push ax
00a2 mov ax, word ptr [bp - 2]
00a5 sub ax, 3
00a8 cdq 
00a9 push dx
00aa push ax
00ab push 0
00ad push word ptr es:[si + 4]
00b1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 180, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
00b6 push dx
00b7 push ax
00b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00bd les bx, ptr [bp + 0xa]
00c0 add ax, word ptr es:[bx + 4]
00c4 add ax, word ptr [bp - 4]
00c7 jmp 0xcc76
00c9 nop 
00ca les bx, ptr [bp + 0xa]
00cd mov ax, word ptr es:[bx]
00d0 add ax, 2
00d3 mov es, word ptr [bp + 0x10]
00d6 mov word ptr es:[di], ax
00d9 pop si
00da pop di
00db leave 
00dc retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_cvtLevels2IdealCaste', 'offset': 51678, 'source': 'src/recovered/wf_cvtLevels2IdealCaste-f8fed91c5a.c', 'size': 156}
- {'symbol': '_GetTriLatDist', 'offset': 51834, 'source': None, 'size': 299}
- {'symbol': '_initControls', 'offset': 52356, 'source': None, 'size': 291}
- {'symbol': '_DrawSimPayoff', 'offset': 52648, 'source': None, 'size': 401}
