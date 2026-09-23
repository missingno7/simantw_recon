# Recovery task _ChangeDirectory

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 364 bytes.

```asm
0000 enter 0x10e, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov di, word ptr [bp + 8]
000c push si
000d push 0x191
0010 push word ptr [bp + 0xa]
0013 push di
0014 push 0x80
0017 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 93}}]
001c mov es, word ptr [bp + 0xa]
001f mov byte ptr es:[di + 0x7f], 0
0024 push 0x2a
0026 push es
0027 push di
0028 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 43, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
002d add sp, 6
0030 or dx, ax
0032 jne 0x914a
0034 push 0x3f
0036 push word ptr [bp + 0xa]
0039 push di
003a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 61, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
003f add sp, 6
0042 or dx, ax
0044 jne 0x914a
0046 cmp word ptr [bp + 0xc], 0xc010
004b jne 0x9144
004d push si
004e push 0x194
0051 push 0x409
0054 push 0
0056 push 0
0058 push 0
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 91, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
005f cmp ax, 0xffff
0062 jne 0x914a
0064 cmp dx, ax
0066 jne 0x914a
0068 xor ax, ax
006a pop si
006b pop di
006c leave 
006d retf 
006e push word ptr [bp + 0xa]
0071 push di
0072 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 115, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 90}}]
0077 mov bx, ax
0079 mov ax, word ptr [bp + 0xa]
007c mov es, ax
007e add bx, di
0080 mov si, bx
0082 mov word ptr [bp - 4], es
0085 cmp byte ptr es:[bx], 0x3a
0089 je 0x918d
008b cmp byte ptr es:[si], 0x5c
008f je 0x918d
0091 mov ax, si
0093 cmp ax, di
0095 jbe 0x918d
0097 push word ptr [bp + 0xa]
009a push di
009b push es
009c push si
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 473}}]
00a2 mov es, dx
00a4 mov bx, ax
00a6 mov si, ax
00a8 mov word ptr [bp - 4], es
00ab cmp byte ptr es:[bx], 0x3a
00af jne 0x9167
00b1 cmp byte ptr es:[si], 0x3a
00b5 je 0x91b0
00b7 cmp byte ptr es:[si], 0x5c
00bb je 0x91b0
00bd push <resolved loader operand; see bindings> ; [{'operand_offset': 190, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00c0 push 0x9f10
00c3 push word ptr [bp + 0xa]
00c6 push di
00c7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 200, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
00cc mov byte ptr [bp - 0x106], 0
00d1 jmp 0x91ff
00d3 nop 
00d4 push <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00d7 push 0x9f10
00da mov cx, es
00dc mov word ptr [bp - 0x10a], si
00e0 mov word ptr [bp - 0x108], cx
00e4 inc si
00e5 push cx
00e6 push si
00e7 mov word ptr [bp - 0x10e], si
00eb mov word ptr [bp - 0x10c], cx
00ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 240, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
00f4 les bx, ptr [bp - 0x10e]
00f8 mov al, byte ptr es:[bx]
00fb mov byte ptr [bp - 1], al
00fe lea ax, [bp - 0x106]
0102 push ss
0103 push ax
0104 mov ax, word ptr [bp + 0xa]
0107 push ax
0108 push di
0109 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 266, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
010e mov al, byte ptr [bp - 1]
0111 les bx, ptr [bp - 0x10e]
0115 mov byte ptr es:[bx], al
0118 mov si, word ptr [bp - 0x10a]
011c sub si, di
011e mov byte ptr [bp + si - 0x105], 0
0123 cmp byte ptr [bp - 0x106], 0
0128 je 0x9233
012a mov bx, 0x94a0
012d mov <resolved loader operand; see bindings> ; [{'operand_offset': 302, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0130 push ds
0131 lea di, [bp - 0x106]
0135 mov si, bx
0137 mov cx, ss
0139 mov es, cx
013b mov ds, ax
013d mov cx, 0xffff
0140 xor ax, ax
0142 repne scasb al, byte ptr es:[di]
0144 not cx
0146 sub di, cx
0148 xchg si, di
014a push ds
014b push es
014c pop ds
014d pop es
014e shr cx, 1
0150 rep movsw word ptr es:[di], word ptr [si]
0152 adc cx, cx
0154 rep movsb byte ptr es:[di], byte ptr [si]
0156 pop ds
0157 push word ptr [bp + 0xc]
015a push word ptr [bp + 6]
015d nop 
015e push cs
015f call 0x8e56 ; _UpdateListBox
0162 add sp, 4
0165 mov ax, 1
0168 pop si
0169 pop di
016a leave 
016b retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UpdateListBox', 'offset': 36438, 'source': None, 'size': 461}
- {'symbol': '_SeparateFile', 'offset': 36900, 'source': 'src/recovered/wf_SeparateFile-7ddbb3ac46.c', 'size': 184}
- {'symbol': 'OPENDLG', 'offset': 37448, 'source': None, 'size': 667}
- {'symbol': 'SAVEASDLG', 'offset': 38116, 'source': None, 'size': 1083}
