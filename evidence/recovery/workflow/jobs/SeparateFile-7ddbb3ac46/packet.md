# Recovery task _SeparateFile

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 184 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0x10]
0009 push word ptr [bp + 0x12]
000c push di
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 14, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 90}}]
0012 mov bx, ax
0014 mov ax, word ptr [bp + 0x12]
0017 mov es, ax
0019 add bx, di
001b mov si, bx
001d cmp byte ptr es:[bx], 0x3a
0021 je 0x906a
0023 cmp byte ptr es:[si], 0x5c
0027 je 0x906a
0029 mov ax, si
002b cmp ax, di
002d jbe 0x906a
002f push word ptr [bp + 0x12]
0032 push di
0033 push es
0034 push si
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 473}}]
003a mov es, dx
003c mov bx, ax
003e mov si, ax
0040 cmp byte ptr es:[bx], 0x3a
0044 jne 0x9047
0046 cmp byte ptr es:[si], 0x3a
004a je 0x9090
004c cmp byte ptr es:[si], 0x5c
0050 je 0x9090
0052 push word ptr [bp + 0xe]
0055 push word ptr [bp + 0xc]
0058 push word ptr [bp + 0x12]
005b push di
005c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
0061 les bx, ptr [bp + 8]
0064 mov byte ptr es:[bx], 0
0068 pop si
0069 pop di
006a leave 
006b retf 
006c push word ptr [bp + 0xe]
006f push word ptr [bp + 0xc]
0072 mov cx, es
0074 mov word ptr [bp - 0xa], si
0077 inc si
0078 push cx
0079 push si
007a mov word ptr [bp - 0xe], si
007d mov word ptr [bp - 0xc], cx
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
0085 les bx, ptr [bp - 0xe]
0088 mov al, byte ptr es:[bx]
008b mov byte ptr [bp - 1], al
008e push word ptr [bp + 0xa]
0091 push word ptr [bp + 8]
0094 mov ax, word ptr [bp + 0x12]
0097 push ax
0098 push di
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 154, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
009e mov al, byte ptr [bp - 1]
00a1 les bx, ptr [bp - 0xe]
00a4 mov byte ptr es:[bx], al
00a7 mov si, word ptr [bp - 0xa]
00aa sub si, di
00ac les bx, ptr [bp + 8]
00af mov byte ptr es:[bx + si + 1], 0
00b4 pop si
00b5 pop di
00b6 leave 
00b7 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_clip_ToObj', 'offset': 36436, 'source': 'src/recovered/clip_ToObj.c', 'size': 1}
- {'symbol': '_UpdateListBox', 'offset': 36438, 'source': None, 'size': 461}
- {'symbol': '_ChangeDirectory', 'offset': 37084, 'source': None, 'size': 364}
- {'symbol': 'OPENDLG', 'offset': 37448, 'source': None, 'size': 667}
