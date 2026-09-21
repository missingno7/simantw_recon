# Recovery task _CreateIndex

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 251 bytes.

```asm
0000 enter 0x6e, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 0xa]
0009 push word ptr [bp + 8]
000c push word ptr [bp + 6]
000f push ds
0010 push 0xb69f
0013 lea ax, [bp - 0x68]
0016 push ss
0017 push ax
0018 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
001d add sp, 0xc
0020 lea ax, [bp - 0x68]
0023 push ss
0024 push ax
0025 push 0
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 83}}]
002c mov es, word ptr [0xc68c]
0030 imul bx, si, 0x7c
0033 mov word ptr [bp - 0x6a], bx
0036 mov word ptr es:[bx + 0x747e], ax
003b mov word ptr [bp - 2], ax
003e or ax, ax
0040 jg 0x9b9f
0042 push word ptr [0xacf8] ; _errno
0046 lea ax, [bp - 0x68]
0049 push ss
004a push ax
004b push ds
004c push 0xb6a6
004f nop 
0050 push cs
0051 call 0x8f0c ; _DosPunt
0054 add sp, 0xa
0057 xor ax, ax
0059 mov es, word ptr [0xc68c]
005d mov bx, word ptr [bp - 0x6a]
0060 mov word ptr es:[bx + 0x745c], ax
0065 mov word ptr es:[bx + 0x745e], ax
006a sub cx, cx
006c mov word ptr es:[bx + 0x7462], cx
0071 mov word ptr es:[bx + 0x7460], cx
0076 mov word ptr es:[bx + 0x7466], cx
007b mov word ptr es:[bx + 0x7464], cx
0080 mov word ptr es:[bx + 0x746a], cx
0085 mov word ptr es:[bx + 0x7468], cx
008a mov word ptr es:[bx + 0x746c], ax
008f mov word ptr es:[bx + 0x746e], ax
0094 push word ptr [bp - 2]
0097 add bx, 0x745c
009b push es
009c push bx
009d push 0x14
009f mov di, bx
00a1 mov word ptr [bp - 0x6e], di
00a4 mov word ptr [bp - 0x6c], es
00a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 168, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 86}}]
00ac les bx, ptr [bp - 0x6e]
00af mov ax, word ptr es:[bx]
00b2 shl ax, 3
00b5 mov word ptr [bp - 4], ax
00b8 or ax, ax
00ba je 0x9c24
00bc push ds
00bd push 0xb6be
00c0 push ax
00c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 196, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
00c6 add sp, 6
00c9 mov es, word ptr [0xc68c]
00cd mov bx, word ptr [bp - 0x6a]
00d0 mov word ptr es:[bx + 0x7458], ax
00d5 mov word ptr es:[bx + 0x745a], dx
00da jmp 0x9c37
00dc mov es, word ptr [0xc68c]
00e0 mov bx, word ptr [bp - 0x6a]
00e3 sub ax, ax
00e5 mov word ptr es:[bx + 0x745a], ax
00ea mov word ptr es:[bx + 0x7458], ax
00ef push word ptr [bp - 2]
00f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 81}}]
00f7 pop si
00f8 pop di
00f9 leave 
00fa retf 
```

## Known declaration examples

- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ch_SetCacheHooks', 'offset': 39526, 'source': 'src/recovered/ch_SetCacheHooks.c', 'size': 31}
- {'symbol': '_OpenIndex', 'offset': 39558, 'source': None, 'size': 194}
- {'symbol': '_CloseIndex', 'offset': 40004, 'source': None, 'size': 222}
- {'symbol': '_FindIndex', 'offset': 40228, 'source': None, 'size': 237}
