# Recovery task INDIRECTDLGPROC

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 143 bytes.

```asm
0000 mov ax, ss
0002 push bp
0003 mov bp, sp
0005 push si
0006 push ds
0007 mov ds, ax
0009 mov ax, word ptr [bp + 0xc]
000c sub ax, 0xf
000f je 0xddf0
0011 sub ax, 0x101
0014 je 0xde12
0016 sub ax, 0xf1
0019 je 0xde3a
001b jmp 0xde58
001d nop 
001e push 0
0020 push 0
0022 push word ptr [bp + 8]
0025 push word ptr [bp + 6]
0028 push word ptr [bp + 0xa]
002b push word ptr [bp + 0xc]
002e push word ptr [bp + 0xe]
0031 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _PaintStuff
0036 add sp, 0xe
0039 pop ds
003a pop si
003b leave 
003c retf 0xa
003f nop 
0040 mov si, word ptr [bp + 0xe]
0043 mov bx, word ptr [bp + 6]
0046 mov word ptr [0xcc5c], bx
004a sar bx, 8
004d shl bx, 1
004f mov word ptr [bx - 0x435a], si
0053 push si
0054 push ds
0055 push 0xbe12
0058 push word ptr [bp + 6]
005b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 92, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 26}}]
0060 push si
0061 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 98, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 18}}]
0066 jmp 0xde58
0068 mov bx, word ptr [0xcc5c]
006c sar bx, 8
006f shl bx, 1
0071 mov word ptr [bx - 0x435a], 0
0077 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 120, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 19}}]
007c push word ptr [bp + 0xe]
007f push 0
0081 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 88}}]
0086 xor ax, ax
0088 cdq 
0089 pop ds
008a pop si
008b leave 
008c retf 0xa
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_GetProxEvent', 'offset': 56584, 'source': 'src/recovered/win_GetProxEvent.c', 'size': 4}
- {'symbol': '__win_SetProxItem', 'offset': 56588, 'source': None, 'size': 197}
- {'symbol': '_win_DoProxMenu', 'offset': 56930, 'source': None, 'size': 993}
- {'symbol': '_win_InvalidateObject', 'offset': 57924, 'source': 'src/recovered/wf_win_InvalidateObject-69cbeedc5b.c', 'size': 113}
