# Recovery task _DBDelete

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 153 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 push word ptr [bp + 0xa]
000c push word ptr [bp + 8]
000f push si
0010 nop 
0011 push cs
0012 call 0x9d24 ; _FindIndex
0015 add sp, 6
0018 mov word ptr [bp - 6], ax
001b mov word ptr [bp - 4], dx
001e or dx, ax
0020 jne 0x88b0
0022 xor ax, ax
0024 pop si
0025 pop di
0026 leave 
0027 retf 
0028 mov es, word ptr [0xc688]
002c imul bx, si, 0x7c
002f mov di, word ptr es:[bx + 0x7480]
0034 push di
0035 mov ax, bx
0037 les bx, ptr [bp - 6]
003a mov cx, word ptr es:[bx]
003d mov dx, word ptr es:[bx + 2]
0041 add cx, 0xe
0044 adc dx, 0
0047 push dx
0048 push cx
0049 push 0
004b mov word ptr [bp - 0x12], ax
004e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 79, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 84}}]
0053 push di
0054 lea ax, [bp - 0x10]
0057 push ss
0058 push ax
0059 push 0xa
005b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 92, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 82}}]
0060 mov ax, word ptr [bp - 0xa]
0063 add ax, 0xa
0066 mov word ptr [bp - 2], ax
0069 push si
006a nop 
006b push cs
006c call 0x9e12 ; _DeleteCurrentIndex
006f add sp, 2
0072 mov es, word ptr [0xc688]
0076 mov bx, word ptr [bp - 0x12]
0079 dec word ptr es:[bx + 0x7474]
007e mov ax, word ptr [bp - 2]
0081 sub dx, dx
0083 add word ptr es:[bx + 0x747a], ax
0088 adc word ptr es:[bx + 0x747c], dx
008d mov ax, 1
0090 mov word ptr es:[bx + 0x7482], ax
0095 pop si
0096 pop di
0097 leave 
0098 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DBAdd', 'offset': 34186, 'source': None, 'size': 327}
- {'symbol': '_DBRecall', 'offset': 34514, 'source': None, 'size': 438}
- {'symbol': '_DBPack', 'offset': 35106, 'source': None, 'size': 547}
- {'symbol': '_DBReplace', 'offset': 35654, 'source': None, 'size': 169}
