# Recovery task _RallocRealloc

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 163 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 les bx, ptr [bp + 6]
0009 mov si, word ptr es:[bx + 4]
000d push si
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
0013 mov ax, word ptr [bp + 0xa]
0016 mov dx, word ptr [bp + 0xc]
0019 add ax, 0x11
001c adc dx, 0
001f push dx
0020 push ax
0021 mov di, ax
0023 mov word ptr [bp - 8], dx
0026 nop 
0027 push cs
0028 call 0x56a8 ; _RallocFindMem
002b add sp, 4
002e push si
002f push word ptr [bp - 8]
0032 push di
0033 push 2
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 16}}]
003a mov si, ax
003c or si, si
003e jne 0x58da
0040 xor ax, ax
0042 cdq 
0043 pop si
0044 pop di
0045 leave 
0046 retf 
0047 nop 
0048 push si
0049 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 74, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 18}}]
004e mov di, ax
0050 mov word ptr [bp - 4], dx
0053 or dx, ax
0055 jne 0x58f2
0057 push si
0058 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
005d jmp 0x58d2
005f nop 
0060 mov cx, word ptr [bp - 4]
0063 lea ax, [di + 0x10]
0066 mov es, cx
0068 mov word ptr es:[di], ax
006b mov word ptr es:[di + 2], cx
006f mov ax, si
0071 mov word ptr es:[di + 4], ax
0075 mov si, cx
0077 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 120, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 13}}]
007c mov es, si
007e mov word ptr es:[di + 0xa], ax
0082 mov word ptr es:[di + 0xc], dx
0086 mov ax, word ptr [bp + 0xe]
0089 mov word ptr es:[di + 0xe], ax
008d mov ax, word ptr [bp + 0xa]
0090 mov dx, word ptr [bp + 0xc]
0093 mov word ptr es:[di + 6], ax
0097 mov word ptr es:[di + 8], dx
009b mov ax, di
009d mov dx, si
009f pop si
00a0 pop di
00a1 leave 
00a2 retf 
```

## Known declaration examples

- `extern void far RallocFindMem(long bytes);` — src/recovered/wf_Ralloc-b43a5ad4e7.c
- `extern void far RallocFindMem(int low, int high);` — src/recovered/wf_RallocFree-a82b13cb86.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RallocFindMem', 'offset': 22184, 'source': None, 'size': 329}
- {'symbol': '_Ralloc', 'offset': 22514, 'source': 'src/recovered/wf_Ralloc-b43a5ad4e7.c', 'size': 160}
- {'symbol': '_RallocFree', 'offset': 22838, 'source': 'src/recovered/wf_RallocFree-a82b13cb86.c', 'size': 53}
- {'symbol': '_RallocAge', 'offset': 22892, 'source': 'src/recovered/RallocAge.c', 'size': 18}
