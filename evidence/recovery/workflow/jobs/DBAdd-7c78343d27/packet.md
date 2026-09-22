# Recovery task _DBAdd

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 327 bytes.

```asm
0000 enter 0x1c, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0x12]
0009 mov si, word ptr [bp + 0xc]
000c push si
000d push ds
000e push 0xb39a
0011 lea ax, [si + 2]
0014 push ax
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
001a add sp, 6
001d mov word ptr [bp - 0xa], ax
0020 mov word ptr [bp - 8], dx
0023 add ax, 2
0026 push dx
0027 push ax
0028 push word ptr [bp + 0xa]
002b push word ptr [bp + 8]
002e nop 
002f push cs
0030 call 0xa3bd ; _PackMemoryToMemory
0033 add sp, 0xa
0036 mov word ptr [bp - 6], ax
0039 mov word ptr [bp - 4], dx
003c and di, 0xfffe
003f test di, 8
0043 jne 0x85fe
0045 sub ax, ax
0047 cmp dx, ax
0049 jg 0x85fe
004b jl 0x85dc
004d cmp word ptr [bp - 6], si
0050 jae 0x85fe
0052 mov ax, word ptr [bp - 0xa]
0055 mov dx, word ptr [bp - 8]
0058 mov word ptr [bp - 0x10], ax
005b mov word ptr [bp - 0xe], dx
005e mov es, dx
0060 mov bx, ax
0062 mov word ptr es:[bx], si
0065 mov ax, word ptr [bp - 6]
0068 add ax, 2
006b mov word ptr [bp - 0xc], ax
006e or di, 1
0071 jmp 0x860d
0073 nop 
0074 mov ax, word ptr [bp + 8]
0077 mov dx, word ptr [bp + 0xa]
007a mov word ptr [bp - 0x10], ax
007d mov word ptr [bp - 0xe], dx
0080 mov word ptr [bp - 0xc], si
0083 mov si, word ptr [bp + 6]
0086 mov es, word ptr [0xc688]
008a imul bx, si, 0x7c
008d mov ax, word ptr es:[bx + 0x7480]
0092 mov word ptr [bp - 2], ax
0095 inc word ptr es:[bx + 0x7474]
009a mov word ptr [bp - 0x1a], 0x5678
009f mov word ptr [bp - 0x18], 0x1234
00a4 mov ax, word ptr [bp - 0xc]
00a7 mov word ptr [bp - 0x14], ax
00aa mov word ptr [bp - 0x12], 0
00af mov cx, word ptr es:[bx + 0x7476]
00b4 mov dx, word ptr es:[bx + 0x7478]
00b9 mov word ptr [bp - 6], cx
00bc mov word ptr [bp - 4], dx
00bf push word ptr [bp - 2]
00c2 add cx, 0xe
00c5 adc dx, 0
00c8 push dx
00c9 push cx
00ca xor cx, cx
00cc mov word ptr [bp - 0x16], cx
00cf push cx
00d0 mov word ptr [bp - 0x1c], bx
00d3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 212, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 84}}]
00d8 push word ptr [bp - 2]
00db lea ax, [bp - 0x1a]
00de push ss
00df push ax
00e0 push 0xa
00e2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 227, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 86}}]
00e7 push word ptr [bp - 2]
00ea push word ptr [bp - 0xe]
00ed push word ptr [bp - 0x10]
00f0 push word ptr [bp - 0xc]
00f3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 86}}]
00f8 mov ax, word ptr [bp - 0xc]
00fb add ax, 0xa
00fe sub dx, dx
0100 mov es, word ptr [0xc688]
0104 mov bx, word ptr [bp - 0x1c]
0107 add word ptr es:[bx + 0x7476], ax
010c adc word ptr es:[bx + 0x7478], dx
0111 push word ptr [bp - 4]
0114 push word ptr [bp - 6]
0117 push di
0118 push word ptr [bp + 0x10]
011b push word ptr [bp + 0xe]
011e push si
011f nop 
0120 push cs
0121 call 0x9f16 ; _AddIndex
0124 add sp, 0xc
0127 mov es, word ptr [0xc688]
012b mov bx, word ptr [bp - 0x1c]
012e mov word ptr es:[bx + 0x7482], 1
0135 push word ptr [bp - 8]
0138 push word ptr [bp - 0xa]
013b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 318, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
0140 add sp, 4
0143 pop si
0144 pop di
0145 leave 
0146 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_db_ReplaceObject', 'offset': 34016, 'source': 'src/recovered/wf_db_ReplaceObject-8f64bec599.c', 'size': 98}
- {'symbol': '_db_SaveObject', 'offset': 34114, 'source': 'src/recovered/db_SaveObject.c', 'size': 72}
- {'symbol': '_DBRecall', 'offset': 34514, 'source': None, 'size': 438}
- {'symbol': '_DBDelete', 'offset': 34952, 'source': None, 'size': 153}
