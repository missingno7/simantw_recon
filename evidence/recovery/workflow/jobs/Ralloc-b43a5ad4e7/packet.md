# Recovery task _Ralloc

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 160 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov ax, word ptr [bp + 6]
0009 mov dx, word ptr [bp + 8]
000c add ax, 0x11
000f adc dx, 0
0012 push dx
0013 push ax
0014 mov si, ax
0016 mov di, dx
0018 nop 
0019 push cs
001a call 0x56a8 ; _RallocFindMem
001d add sp, 4
0020 push 2
0022 push di
0023 push si
0024 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 15}}]
0029 mov word ptr [bp - 2], ax
002c or ax, ax
002e jne 0x582a
0030 xor ax, ax
0032 cdq 
0033 pop si
0034 pop di
0035 leave 
0036 retf 
0037 nop 
0038 push ax
0039 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 58, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 18}}]
003e mov si, ax
0040 mov word ptr [bp - 4], dx
0043 or dx, ax
0045 jne 0x5844
0047 push word ptr [bp - 2]
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
004f jmp 0x5822
0051 nop 
0052 mov cx, word ptr [bp - 4]
0055 lea ax, [si + 0x10]
0058 mov es, cx
005a mov word ptr es:[si], ax
005d mov word ptr es:[si + 2], cx
0061 mov ax, word ptr [bp - 2]
0064 mov word ptr es:[si + 4], ax
0068 mov di, cx
006a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 107, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 13}}]
006f mov es, di
0071 mov word ptr es:[si + 0xa], ax
0075 mov word ptr es:[si + 0xc], dx
0079 mov ax, word ptr [bp + 0xa]
007c mov word ptr es:[si + 0xe], ax
0080 mov ax, word ptr [bp + 6]
0083 mov dx, word ptr [bp + 8]
0086 mov word ptr es:[si + 6], ax
008a mov word ptr es:[si + 8], dx
008e add word ptr [0x85c], 1
0093 adc word ptr [0x85e], 0
0098 mov ax, si
009a mov dx, di
009c pop si
009d pop di
009e leave 
009f retf 
```

## Known declaration examples

- `extern void far RallocFindMem(int low, int high);` — src/recovered/wf_RallocFree-a82b13cb86.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RallocInfo', 'offset': 22158, 'source': 'src/recovered/RallocInfo.c', 'size': 25}
- {'symbol': '_RallocFindMem', 'offset': 22184, 'source': None, 'size': 329}
- {'symbol': '_RallocRealloc', 'offset': 22674, 'source': None, 'size': 163}
- {'symbol': '_RallocFree', 'offset': 22838, 'source': 'src/recovered/wf_RallocFree-a82b13cb86.c', 'size': 53}
