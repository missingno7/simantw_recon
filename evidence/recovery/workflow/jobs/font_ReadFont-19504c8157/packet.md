# Recovery task _font_ReadFont

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 509 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 push ds
0007 push 0xb8e4
000a push 0x2a
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
0011 add sp, 6
0014 mov si, ax
0016 mov word ptr [bp - 0xe], dx
0019 or dx, ax
001b jne 0xaa70
001d xor ax, ax
001f cdq 
0020 pop si
0021 pop di
0022 leave 
0023 retf 
0024 push ds
0025 push 0xb8ef
0028 push word ptr [bp + 8]
002b push word ptr [bp + 6]
002e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _fopen
0033 add sp, 8
0036 mov word ptr [bp - 0xa], ax
0039 mov word ptr [bp - 8], dx
003c or dx, ax
003e jne 0xaa9a
0040 push word ptr [bp - 0xe]
0043 push si
0044 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
0049 add sp, 4
004c jmp 0xaa69
004e mov ax, word ptr [bp - 0xe]
0051 mov word ptr [bp - 4], si
0054 mov word ptr [bp - 2], ax
0057 push word ptr [bp - 8]
005a push word ptr [bp - 0xa]
005d push 2
005f push 0xd
0061 push ax
0062 push si
0063 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 102, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _fread
0068 add sp, 0xc
006b mov word ptr [bp - 6], 0xd
0070 mov word ptr [bp - 0x10], si
0073 mov bx, si
0075 mov cx, word ptr [bp - 6]
0078 mov ds, word ptr [bp - 2]
007b mov ax, word ptr [bx]
007d mov dx, ax
007f mov ah, al
0081 sub al, al
0083 mov dl, dh
0085 sub dh, dh
0087 add dx, ax
0089 mov word ptr [bx], dx
008b add bx, 2
008e dec cx
008f jne 0xaac7
0091 push ss
0092 pop ds
0093 mov si, word ptr [bp - 0x10]
0096 mov ax, word ptr [0xb8e2] ; _buffer_max_height
0099 mov es, word ptr [bp - 0xe]
009c cmp word ptr es:[si + 0xe], ax
00a0 jg 0xaa8c
00a2 mov di, word ptr es:[si + 4]
00a6 sub di, word ptr es:[si + 2]
00aa add di, 3
00ad push ds
00ae push 0xb8f2
00b1 mov ax, word ptr es:[si + 0xe]
00b5 imul word ptr es:[si + 0x18]
00b9 shl ax, 1
00bb push ax
00bc mov word ptr [bp - 0x12], ax
00bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 194, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
00c4 add sp, 6
00c7 mov es, word ptr [bp - 0xe]
00ca mov word ptr es:[si + 0x1a], ax
00ce mov word ptr es:[si + 0x1c], dx
00d2 push ds
00d3 push 0xb8fc
00d6 mov ax, di
00d8 shl ax, 1
00da push ax
00db mov word ptr [bp - 0x14], ax
00de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 225, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
00e3 add sp, 6
00e6 mov es, word ptr [bp - 0xe]
00e9 mov word ptr es:[si + 0x1e], ax
00ed mov word ptr es:[si + 0x20], dx
00f1 push ds
00f2 push 0xb905
00f5 push word ptr [bp - 0x14]
00f8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 251, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
00fd add sp, 6
0100 mov es, word ptr [bp - 0xe]
0103 mov word ptr es:[si + 0x22], ax
0107 mov word ptr es:[si + 0x24], dx
010b push word ptr [bp - 8]
010e push word ptr [bp - 0xa]
0111 push 1
0113 push word ptr [bp - 0x12]
0116 push word ptr es:[si + 0x1c]
011a push word ptr es:[si + 0x1a]
011e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 289, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _fread
0123 add sp, 0xc
0126 push word ptr [bp - 8]
0129 push word ptr [bp - 0xa]
012c push 2
012e push di
012f mov es, word ptr [bp - 0xe]
0132 mov ax, word ptr es:[si + 0x1e]
0136 mov dx, word ptr es:[si + 0x20]
013a mov word ptr [bp - 4], ax
013d mov word ptr [bp - 2], dx
0140 push dx
0141 push ax
0142 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 325, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _fread
0147 add sp, 0xc
014a or di, di
014c jle 0xabc3
014e mov cx, di
0150 mov bx, word ptr [bp - 4]
0153 mov word ptr [bp - 6], di
0156 mov ds, word ptr [bp - 2]
0159 mov ax, word ptr [bx]
015b mov dx, ax
015d mov ah, al
015f sub al, al
0161 mov dl, dh
0163 sub dh, dh
0165 add dx, ax
0167 mov word ptr [bx], dx
0169 add bx, 2
016c dec cx
016d jne 0xaba5
016f mov di, word ptr [bp - 6]
0172 mov si, word ptr [bp - 0x10]
0175 push ss
0176 pop ds
0177 push word ptr [bp - 8]
017a push word ptr [bp - 0xa]
017d push 2
017f push di
0180 mov es, word ptr [bp - 0xe]
0183 mov ax, word ptr es:[si + 0x22]
0187 mov dx, word ptr es:[si + 0x24]
018b mov word ptr [bp - 4], ax
018e mov word ptr [bp - 2], dx
0191 push dx
0192 push ax
0193 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 406, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _fread
0198 add sp, 0xc
019b or di, di
019d jle 0xac11
019f mov cx, di
01a1 mov bx, word ptr [bp - 4]
01a4 mov word ptr [bp - 6], di
01a7 mov ds, word ptr [bp - 2]
01aa mov ax, word ptr [bx]
01ac mov dx, ax
01ae mov ah, al
01b0 sub al, al
01b2 mov dl, dh
01b4 sub dh, dh
01b6 add dx, ax
01b8 mov word ptr [bx], dx
01ba add bx, 2
01bd dec cx
01be jne 0xabf6
01c0 mov si, word ptr [bp - 0x10]
01c3 push ss
01c4 pop ds
01c5 push word ptr [bp - 8]
01c8 push word ptr [bp - 0xa]
01cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 462, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _fclose
01d0 add sp, 4
01d3 mov es, word ptr [bp - 0xe]
01d6 mov ah, byte ptr es:[si + 1]
01da and ax, 0x2000
01dd cmp ax, 1
01e0 sbb ax, ax
01e2 neg ax
01e4 mov word ptr es:[si + 0x26], ax
01e8 mov ax, word ptr es:[si + 4]
01ec sub ax, word ptr es:[si + 2]
01f0 inc ax
01f1 mov word ptr es:[si + 0x28], ax
01f5 mov ax, si
01f7 mov dx, es
01f9 pop si
01fa pop di
01fb leave 
01fc retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InsertNode', 'offset': 43124, 'source': None, 'size': 282}
- {'symbol': '_DeleteNode', 'offset': 43406, 'source': None, 'size': 189}
- {'symbol': '_font_DumpFont', 'offset': 44106, 'source': None, 'size': 123}
- {'symbol': '__font_StringWidth', 'offset': 44230, 'source': None, 'size': 150}
