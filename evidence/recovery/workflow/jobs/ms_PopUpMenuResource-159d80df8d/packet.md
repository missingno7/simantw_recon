# Recovery task _ms_PopUpMenuResource

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 320 bytes.

```asm
0000 enter 0x1a, 0
0004 push di
0005 push si
0006 lea ax, [bp - 0xe]
0009 push ss
000a push ax
000b push word ptr [bp + 0xa]
000e nop 
000f push cs
0010 call 0x4cce ; _ms_LoadPopUpResource
0013 add sp, 6
0016 mov word ptr [bp - 0xc], ax
0019 mov word ptr [bp - 0xa], dx
001c cmp word ptr [bp - 0xe], 0
0020 jg 0x5171
0022 jmp 0x5286
0025 les di, ptr [bp + 0xc]
0028 mov al, byte ptr es:[di]
002b cwde 
002c cmp ax, word ptr [bp - 0xe]
002f jle 0x5181
0031 mov byte ptr es:[di], 0xff
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 415}}]
003a mov word ptr [bp - 8], ax
003d mov word ptr [bp - 2], 0
0042 cmp word ptr [bp - 0xe], 0
0046 jle 0x51f0
0048 mov ax, word ptr [bp - 0xc]
004b mov dx, word ptr [bp - 0xa]
004e mov cx, ax
0050 mov word ptr [bp - 4], dx
0053 mov si, word ptr [bp - 2]
0056 mov word ptr [bp - 6], cx
0059 mov di, ax
005b mov es, word ptr [bp - 4]
005e les bx, ptr es:[di]
0061 inc bx
0062 mov word ptr [bp - 0x16], bx
0065 mov word ptr [bp - 0x14], es
0068 cmp byte ptr es:[bx], 0x2d
006c jne 0x51ce
006e push word ptr [bp - 8]
0071 push 0x800
0074 lea ax, [si + 1]
0077 or ah, 0xf9
007a push ax
007b push 0
007d push 0
007f jmp 0x51de
0081 nop 
0082 push word ptr [bp - 8]
0085 push 0
0087 lea ax, [si + 1]
008a or ah, 0xf9
008d push ax
008e push word ptr [bp - 0x14]
0091 push bx
0092 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 147, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 411}}]
0097 add di, 4
009a lea ax, [si + 1]
009d mov si, ax
009f cmp si, word ptr [bp - 0xe]
00a2 jl 0x51a7
00a4 push word ptr [bp - 0xa]
00a7 push word ptr [bp - 0xc]
00aa nop 
00ab push cs
00ac call 0x54ca ; _mem_free
00af add sp, 4
00b2 mov ax, word ptr [bp + 6]
00b5 mov word ptr [bp - 0x12], ax
00b8 mov ax, word ptr [bp + 8]
00bb mov word ptr [bp - 0x10], ax
00be push word ptr [0xcd78] ; _rootWnd
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _MyGetTopWindow
00c7 add sp, 2
00ca push ax
00cb lea ax, [bp - 0x12]
00ce push ss
00cf push ax
00d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 28}}]
00d5 mov bx, 0x80ee
00d8 mov es, word ptr [0xc6c2]
00dc mov word ptr [bp - 0x1a], bx
00df mov word ptr [bp - 0x18], es
00e2 mov word ptr es:[bx], 0
00e7 push word ptr [bp - 8]
00ea push 0
00ec push word ptr [bp - 0x12]
00ef push word ptr [bp - 0x10]
00f2 push 0
00f4 push word ptr [0xcd78] ; _rootWnd
00f8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 251, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _MyGetTopWindow
00fd add sp, 2
0100 push ax
0101 push 0
0103 push 0
0105 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 262, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 416}}]
010a or ax, ax
010c je 0x527e
010e push word ptr [bp - 8]
0111 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 274, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 152}}]
0116 les bx, ptr [bp - 0x1a]
0119 cmp word ptr es:[bx], 0
011d je 0x5286
011f mov al, byte ptr es:[bx]
0122 les si, ptr [bp + 0xc]
0125 mov byte ptr es:[si], al
0128 mov es, word ptr [bp - 0x18]
012b mov ax, word ptr es:[bx]
012e pop si
012f pop di
0130 leave 
0131 retf 
0132 push word ptr [bp - 8]
0135 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 310, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 152}}]
013a xor ax, ax
013c pop si
013d pop di
013e leave 
013f retf 
```

## Known declaration examples

- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ms_LoadPopUpResource', 'offset': 19662, 'source': None, 'size': 359}
- {'symbol': '_InitMenu', 'offset': 20022, 'source': None, 'size': 790}
- {'symbol': '_TrapFill', 'offset': 21132, 'source': None, 'size': 495}
- {'symbol': '_mem_Flush', 'offset': 21628, 'source': 'src/recovered/mem_Flush.c', 'size': 10}
