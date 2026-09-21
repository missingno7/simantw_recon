# Recovery task _DBReplace

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 169 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 push word ptr [bp + 0x10]
0009 push word ptr [bp + 0xe]
000c push word ptr [bp + 6]
000f nop 
0010 push cs
0011 call 0x9d24 ; _FindIndex
0014 add sp, 6
0017 mov word ptr [bp - 4], ax
001a mov word ptr [bp - 2], dx
001d or dx, ax
001f je 0x8bce
0021 mov es, word ptr [0xc688]
0025 imul bx, word ptr [bp + 6], 0x7c
0029 mov si, word ptr es:[bx + 0x7480]
002e push si
002f les di, ptr [bp - 4]
0032 mov ax, word ptr es:[di]
0035 mov dx, word ptr es:[di + 2]
0039 add ax, 0xe
003c adc dx, 0
003f push dx
0040 push ax
0041 push 0
0043 mov di, bx
0045 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 70, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 84}}]
004a push si
004b lea ax, [bp - 0xe]
004e push ss
004f push ax
0050 push 0xa
0052 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 82}}]
0057 mov ax, di
0059 mov di, word ptr [bp - 8]
005c add di, 0xa
005f push word ptr [bp + 6]
0062 mov si, ax
0064 nop 
0065 push cs
0066 call 0x9e12 ; _DeleteCurrentIndex
0069 add sp, 2
006c mov es, word ptr [0xc688]
0070 dec word ptr es:[si + 0x7474]
0075 sub cx, cx
0077 add word ptr es:[si + 0x747a], di
007c adc word ptr es:[si + 0x747c], cx
0081 mov word ptr es:[si + 0x7482], 1
0088 push word ptr [bp + 0x12]
008b push word ptr [bp + 0x10]
008e push word ptr [bp + 0xe]
0091 push word ptr [bp + 0xc]
0094 push word ptr [bp + 0xa]
0097 push word ptr [bp + 8]
009a push word ptr [bp + 6]
009d nop 
009e push cs
009f call 0x858a ; _DBAdd
00a2 add sp, 0xe
00a5 pop si
00a6 pop di
00a7 leave 
00a8 retf 
```

## Known declaration examples

- `extern void far DBAdd(int handle, int arg4, int arg5, int arg6, int object, int type, int arg3);` — src/recovered/db_SaveObject.c
- `extern void far DBAdd(int handle, int arg4, int arg5, int arg6, int object, int type, int arg3);` — src/recovered/wf_db_ReplaceObject-8f64bec599.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DBDelete', 'offset': 34952, 'source': None, 'size': 153}
- {'symbol': '_DBPack', 'offset': 35106, 'source': None, 'size': 547}
- {'symbol': '_OpenDB', 'offset': 35824, 'source': None, 'size': 517}
- {'symbol': '_FlushDB', 'offset': 36342, 'source': 'src/recovered/FlushDB.c', 'size': 1}
