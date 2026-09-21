# Recovery task _BoundPointToTri

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 176 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 les bx, ptr [bp + 0xa]
0009 mov di, word ptr es:[bx + 2]
000d mov si, word ptr es:[bx + 6]
0011 dec si
0012 mov ax, word ptr es:[bx + 4]
0016 mov word ptr [bp - 0x10], ax
0019 mov cx, word ptr es:[bx]
001c mov word ptr [bp - 4], cx
001f add ax, cx
0021 cdq 
0022 sub ax, dx
0024 sar ax, 1
0026 mov word ptr [bp - 0xe], ax
0029 les bx, ptr [bp + 6]
002c mov ax, word ptr es:[bx]
002f mov word ptr [bp - 2], ax
0032 mov ax, word ptr es:[bx + 2]
0036 mov word ptr [bp - 0xc], ax
0039 cmp si, ax
003b jge 0xc47a
003d mov word ptr [bp - 0xc], si
0040 jmp 0xc482
0042 cmp word ptr [bp - 0xc], di
0045 jge 0xc482
0047 mov word ptr [bp - 0xc], di
004a mov ax, si
004c sub ax, di
004e cdq 
004f push dx
0050 push ax
0051 mov ax, word ptr [bp - 4]
0054 sub ax, word ptr [bp - 0xe]
0057 mov cx, word ptr [bp - 0xc]
005a sub cx, si
005c imul cx
005e push dx
005f push ax
0060 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 99, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0065 add ax, word ptr [bp - 4]
0068 cmp ax, word ptr [bp - 2]
006b jle 0xc4aa
006d mov si, ax
006f jmp 0xc4d7
0071 nop 
0072 mov word ptr [bp - 8], si
0075 mov si, word ptr [bp - 2]
0078 mov ax, di
007a sub ax, word ptr [bp - 8]
007d cdq 
007e push dx
007f push ax
0080 mov ax, word ptr [bp - 0xe]
0083 sub ax, word ptr [bp - 0x10]
0086 mov cx, word ptr [bp - 0xc]
0089 sub cx, di
008b imul cx
008d push dx
008e push ax
008f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0094 mov di, ax
0096 add di, word ptr [bp - 0xe]
0099 cmp di, si
009b jge 0xc4d7
009d mov si, di
009f les bx, ptr [bp + 6]
00a2 mov word ptr es:[bx], si
00a5 mov ax, word ptr [bp - 0xc]
00a8 mov word ptr es:[bx + 2], ax
00ac pop si
00ad pop di
00ae leave 
00af retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ProcModeEvent', 'offset': 49274, 'source': None, 'size': None}
- {'symbol': '_IsPointInIsoTri', 'offset': 50044, 'source': None, 'size': 188}
- {'symbol': '_win_DrawModeWindow', 'offset': 50408, 'source': None, 'size': 216}
- {'symbol': '_win_ModeControlClosed', 'offset': 50624, 'source': None, 'size': 149}
