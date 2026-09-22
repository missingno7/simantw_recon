# Recovery task _AddIndex

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 351 bytes.

```asm
0000 enter 0x18, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 imul bx, si, 0x7c
000c mov word ptr [bp - 0x18], bx
000f add bx, 0x7458
0013 mov es, word ptr [0xc68c]
0017 mov word ptr [bp - 0x16], bx
001a mov word ptr [bp - 0x14], es
001d mov ax, word ptr es:[bx]
0020 mov dx, word ptr es:[bx + 2]
0024 mov word ptr [bp - 8], ax
0027 mov word ptr [bp - 6], dx
002a push word ptr [bp + 0xa]
002d push word ptr [bp + 8]
0030 push si
0031 nop 
0032 push cs
0033 call 0x9d24 ; _FindIndex
0036 add sp, 6
0039 or dx, ax
003b je 0x9f66
003d push ds
003e push 0xb73e
0041 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 68, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0046 add sp, 4
0049 xor ax, ax
004b pop si
004c pop di
004d leave 
004e retf 
004f nop 
0050 mov ax, word ptr [bp + 8]
0053 mov word ptr [bp - 0xe], ax
0056 mov al, byte ptr [bp + 0xa]
0059 mov byte ptr [bp - 0xc], al
005c mov al, byte ptr [bp + 0xc]
005f mov byte ptr [bp - 0xb], al
0062 mov ax, word ptr [bp + 0xe]
0065 mov dx, word ptr [bp + 0x10]
0068 mov word ptr [bp - 0x12], ax
006b mov word ptr [bp - 0x10], dx
006e push ds
006f push 0xb75b
0072 mov es, word ptr [0xc68c]
0076 mov bx, word ptr [bp - 0x18]
0079 inc word ptr es:[bx + 0x745c]
007e mov ax, word ptr es:[bx + 0x745c]
0083 mov word ptr [bp - 0xa], ax
0086 shl ax, 3
0089 push ax
008a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 141, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
008f add sp, 6
0092 mov word ptr [bp - 4], ax
0095 mov word ptr [bp - 2], dx
0098 or dx, ax
009a jne 0x9fbe
009c push ds
009d push 0xb762
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
00a5 add sp, 4
00a8 mov es, word ptr [0xc68c]
00ac mov bx, word ptr [bp - 0x18]
00af cmp word ptr es:[bx + 0x745c], 1
00b5 jne 0x9ff0
00b7 mov ax, word ptr [bp - 6]
00ba or ax, word ptr [bp - 8]
00bd je 0x9fe3
00bf push word ptr [bp - 6]
00c2 push word ptr [bp - 8]
00c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 200, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
00ca add sp, 4
00cd lea si, [bp - 0x12]
00d0 les di, ptr [bp - 4]
00d3 movsw word ptr es:[di], word ptr [si]
00d4 movsw word ptr es:[di], word ptr [si]
00d5 movsw word ptr es:[di], word ptr [si]
00d6 movsw word ptr es:[di], word ptr [si]
00d7 jmp 0xa05e
00d9 nop 
00da les bx, ptr [bp - 0x16]
00dd mov ax, word ptr es:[bx]
00e0 mov dx, word ptr es:[bx + 2]
00e4 mov word ptr [bp - 8], ax
00e7 mov word ptr [bp - 6], dx
00ea mov es, word ptr [0xc68e]
00ee mov cx, word ptr es:[0x9e92]
00f3 mov bx, cx
00f5 shl cx, 3
00f8 push ds
00f9 mov si, ax
00fb mov ds, dx
00fd les di, ptr [bp - 4]
0100 shr cx, 1
0102 rep movsw word ptr es:[di], word ptr [si]
0104 adc cx, cx
0106 rep movsb byte ptr es:[di], byte ptr [si]
0108 pop ds
0109 mov ax, bx
010b shl bx, 3
010e mov cx, bx
0110 add bx, word ptr [bp - 4]
0113 mov di, bx
0115 lea si, [bp - 0x12]
0118 movsw word ptr es:[di], word ptr [si]
0119 movsw word ptr es:[di], word ptr [si]
011a movsw word ptr es:[di], word ptr [si]
011b movsw word ptr es:[di], word ptr [si]
011c add cx, word ptr [bp - 8]
011f mov dx, word ptr [bp - 6]
0122 mov si, cx
0124 mov cx, word ptr [bp - 0xa]
0127 sub cx, ax
0129 dec cx
012a shl cx, 3
012d push ds
012e lea di, [bx + 8]
0131 mov ds, dx
0133 shr cx, 1
0135 rep movsw word ptr es:[di], word ptr [si]
0137 adc cx, cx
0139 rep movsb byte ptr es:[di], byte ptr [si]
013b pop ds
013c push dx
013d push word ptr [bp - 8]
0140 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 323, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
0145 add sp, 4
0148 mov ax, word ptr [bp - 4]
014b mov dx, word ptr [bp - 2]
014e les bx, ptr [bp - 0x16]
0151 mov word ptr es:[bx], ax
0154 mov word ptr es:[bx + 2], dx
0158 mov ax, 1
015b pop si
015c pop di
015d leave 
015e retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FindIndex', 'offset': 40228, 'source': None, 'size': 237}
- {'symbol': '_DeleteCurrentIndex', 'offset': 40466, 'source': None, 'size': 259}
- {'symbol': '_DeleteIndex', 'offset': 41078, 'source': None, 'size': 245}
- {'symbol': '_PackWriteByte', 'offset': 41473, 'source': None, 'size': 64}
