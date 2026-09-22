# Recovery task _GetTriLatDist

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 299 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov cx, word ptr [bp + 0xa]
0009 mov bx, word ptr [bp + 0xe]
000c mov es, word ptr [bp + 0x10]
000f mov ax, word ptr es:[bx]
0012 mov si, cx
0014 mov es, word ptr [bp + 0xc]
0017 sub ax, word ptr es:[si + 4]
001b mov word ptr [bp - 4], ax
001e mov ax, es
0020 mov es, word ptr [bp + 0x10]
0023 mov di, word ptr es:[bx + 2]
0027 mov es, ax
0029 sub di, word ptr es:[si + 2]
002d mov es, word ptr [0xc122]
0031 mov ax, word ptr es:[0x80d0]
0035 mov word ptr [bp - 8], ax
0038 sub ax, 2
003b cmp di, ax
003d jbe 0xcac6
003f mov si, word ptr [bp + 6]
0042 mov es, word ptr [bp + 8]
0045 mov word ptr es:[si], 0
004a jmp 0xcaec
004c mov si, word ptr [bp + 6]
004f mov ax, word ptr [bp - 8]
0052 sub ax, 2
0055 push 0
0057 push ax
0058 mov ax, word ptr [bp - 8]
005b sub ax, di
005d sub ax, 2
0060 mov cx, 0xffff
0063 mul cx
0065 push dx
0066 push ax
0067 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 106, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
006c mov es, word ptr [bp + 8]
006f mov word ptr es:[si], ax
0072 push 0
0074 push -1
0076 mov ax, word ptr es:[si]
0079 mov es, word ptr [0xc120]
007d mul word ptr es:[0x7f00]
0082 push dx
0083 push ax
0084 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 135, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
0089 mov word ptr [bp - 2], ax
008c shl ax, 1
008e mov es, word ptr [0xc11c]
0092 mov di, word ptr es:[0x9cec]
0097 sub di, ax
0099 cmp di, 2
009c jg 0xcb2a
009e xor ax, ax
00a0 mov es, word ptr [bp + 8]
00a3 mov word ptr es:[si + 2], ax
00a7 mov word ptr es:[si + 4], ax
00ab pop si
00ac pop di
00ad leave 
00ae retf 
00af nop 
00b0 mov dx, word ptr [bp - 2]
00b3 mov ax, word ptr [bp - 4]
00b6 sub ax, dx
00b8 mov word ptr [bp - 0xa], ax
00bb lea cx, [di - 2]
00be cmp ax, cx
00c0 jl 0xcb48
00c2 mov ax, 0xffff
00c5 mov es, word ptr [bp + 8]
00c8 sub ax, word ptr es:[si]
00cb jmp 0xcb8f
00cd nop 
00ce mov word ptr [bp - 6], di
00d1 mov di, word ptr [bp - 4]
00d4 cmp ax, 2
00d7 jg 0xcb5e
00d9 mov es, word ptr [bp + 8]
00dc mov word ptr es:[si + 4], 0
00e2 jmp 0xcb93
00e4 mov ax, word ptr [bp - 6]
00e7 sub ax, 2
00ea cdq 
00eb push dx
00ec push ax
00ed mov ax, word ptr [bp - 0xa]
00f0 cdq 
00f1 push dx
00f2 push ax
00f3 mov ax, 0xffff
00f6 xor dx, dx
00f8 mov es, word ptr [bp + 8]
00fb mov cx, word ptr es:[si]
00fe sub bx, bx
0100 sub ax, cx
0102 sbb dx, bx
0104 push dx
0105 push ax
0106 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 265, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
010b push dx
010c push ax
010d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 272, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0112 mov es, word ptr [bp + 8]
0115 mov word ptr es:[si + 4], ax
0119 mov ax, 0xffff
011c sub ax, word ptr es:[si + 4]
0120 sub ax, word ptr es:[si]
0123 mov word ptr es:[si + 2], ax
0127 pop si
0128 pop di
0129 leave 
012a retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawControlLevels', 'offset': 51140, 'source': None, 'size': 538}
- {'symbol': '_cvtLevels2IdealCaste', 'offset': 51678, 'source': 'src/recovered/wf_cvtLevels2IdealCaste-f8fed91c5a.c', 'size': 156}
- {'symbol': '_SetTriLatPoint', 'offset': 52134, 'source': None, 'size': 221}
- {'symbol': '_initControls', 'offset': 52356, 'source': None, 'size': 291}
