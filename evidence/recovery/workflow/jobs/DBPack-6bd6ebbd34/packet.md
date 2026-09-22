# Recovery task _DBPack

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 547 bytes.

```asm
0000 enter 0x4a, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov es, word ptr [0xc688]
000d imul bx, si, 0x7c
0010 mov word ptr [bp - 0x48], bx
0013 mov ax, word ptr es:[bx + 0x747a]
0018 mov dx, word ptr es:[bx + 0x747c]
001d mov word ptr [bp - 0x1a], ax
0020 mov word ptr [bp - 0x18], dx
0023 push dx
0024 push ax
0025 push ds
0026 push 0xb413
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
002e add sp, 8
0031 mov ax, 0xb442
0034 mov word ptr [bp - 4], ax
0037 mov word ptr [bp - 2], ds
003a push ds
003b push ax
003c push 0
003e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 63, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 83}}]
0043 mov word ptr [bp - 0x16], ax
0046 or ax, ax
0048 jg 0x897e
004a push ds
004b push 0xb44c
004e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0053 add sp, 4
0056 xor ax, ax
0058 pop si
0059 pop di
005a leave 
005b retf 
005c mov es, word ptr [0xc688]
0060 mov bx, word ptr [bp - 0x48]
0063 mov ax, word ptr es:[bx + 0x7480]
0068 mov word ptr [bp - 0x10], ax
006b mov ax, word ptr es:[bx + 0x745c]
0070 mov word ptr [bp - 0xe], ax
0073 mov word ptr [bp - 0x2e], ax
0076 mov word ptr [bp - 0x32], 0x5678
007b mov word ptr [bp - 0x30], 0x1234
0080 push ds
0081 push 0xb467
0084 push 0xfde8
0087 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 138, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
008c add sp, 6
008f mov word ptr [bp - 0x14], ax
0092 mov word ptr [bp - 0x12], dx
0095 or dx, ax
0097 jne 0x89c7
0099 push ds
009a push 0xb46b
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 160, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
00a2 add sp, 4
00a5 push word ptr [bp - 0x16]
00a8 lea ax, [bp - 0x32]
00ab push ss
00ac push ax
00ad push 0xe
00af lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 86}}]
00b4 mov es, word ptr [0xc688]
00b8 mov bx, word ptr [bp - 0x48]
00bb mov ax, word ptr es:[bx + 0x7458]
00c0 mov dx, word ptr es:[bx + 0x745a]
00c5 mov di, ax
00c7 mov word ptr [bp - 0xa], dx
00ca sub ax, ax
00cc mov word ptr [bp - 2], ax
00cf mov word ptr [bp - 4], ax
00d2 mov word ptr [bp - 0xc], di
00d5 mov si, di
00d7 jmp 0x8aa2
00da push word ptr [bp - 0x10]
00dd mov es, word ptr [bp - 0xa]
00e0 mov ax, word ptr es:[si]
00e3 mov dx, word ptr es:[si + 2]
00e7 add ax, 0xe
00ea adc dx, 0
00ed push dx
00ee push ax
00ef push 0
00f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 242, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 84}}]
00f6 mov word ptr [bp - 8], ax
00f9 mov word ptr [bp - 6], dx
00fc push word ptr [bp - 0x10]
00ff lea ax, [bp - 0x24]
0102 push ss
0103 push ax
0104 push 0xa
0106 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 263, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 82}}]
010b push word ptr [bp - 0x10]
010e push word ptr [bp - 0x12]
0111 push word ptr [bp - 0x14]
0114 mov di, word ptr [bp - 0x1e]
0117 push di
0118 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 281, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 82}}]
011d push word ptr [bp - 2]
0120 push word ptr [bp - 4]
0123 mov ax, word ptr [bp - 8]
0126 mov dx, word ptr [bp - 6]
0129 sub ax, 0xe
012c sbb dx, 0
012f push dx
0130 push ax
0131 lea ax, [di + 0xa]
0134 push ax
0135 push ds
0136 push 0xb487
0139 mov word ptr [bp - 0x4a], ax
013c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 319, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0141 add sp, 0xe
0144 push word ptr [bp - 0x16]
0147 lea ax, [bp - 0x24]
014a push ss
014b push ax
014c push 0xa
014e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 335, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 86}}]
0153 push word ptr [bp - 0x16]
0156 push word ptr [bp - 0x12]
0159 push word ptr [bp - 0x14]
015c push di
015d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 350, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 86}}]
0162 mov ax, word ptr [bp - 4]
0165 mov dx, word ptr [bp - 2]
0168 mov es, word ptr [bp - 0xa]
016b mov word ptr es:[si], ax
016e mov word ptr es:[si + 2], dx
0172 mov ax, word ptr [bp - 0x4a]
0175 sub dx, dx
0177 add word ptr [bp - 4], ax
017a adc word ptr [bp - 2], dx
017d add si, 8
0180 mov ax, word ptr [bp - 0xe]
0183 dec word ptr [bp - 0xe]
0186 or ax, ax
0188 je 0x8aaf
018a jmp 0x89fc
018d mov ax, word ptr [bp - 0x48]
0190 add ax, 0x7408
0193 push <resolved loader operand; see bindings> ; [{'operand_offset': 404, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0196 push ax
0197 push ds
0198 push 0xb4ab
019b lea ax, [bp - 0x46]
019e push ss
019f push ax
01a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 419, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
01a5 add sp, 0xc
01a8 push word ptr [bp - 0x10]
01ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 428, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 81}}]
01b0 push word ptr [bp - 0x16]
01b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 436, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 81}}]
01b8 lea ax, [bp - 0x46]
01bb push ss
01bc push ax
01bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 448, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _unlink,_remove
01c2 add sp, 4
01c5 push word ptr [bp - 0x12]
01c8 push word ptr [bp - 0x14]
01cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 462, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
01d0 add sp, 4
01d3 lea ax, [bp - 0x46]
01d6 push ss
01d7 push ax
01d8 push ds
01d9 push 0xb442
01dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 479, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _rename
01e1 add sp, 8
01e4 lea ax, [bp - 0x46]
01e7 push ss
01e8 push ax
01e9 push 2
01eb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 492, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 85}}]
01f0 mov es, word ptr [0xc688]
01f4 mov bx, word ptr [bp - 0x48]
01f7 mov word ptr es:[bx + 0x7480], ax
01fc mov ax, word ptr [bp - 0x1a]
01ff mov dx, word ptr [bp - 0x18]
0202 sub word ptr es:[bx + 0x7476], ax
0207 sbb word ptr es:[bx + 0x7478], dx
020c sub ax, ax
020e mov word ptr es:[bx + 0x747c], ax
0213 mov word ptr es:[bx + 0x747a], ax
0218 mov word ptr es:[bx + 0x7482], 1
021f pop si
0220 pop di
0221 leave 
0222 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far pascal PeekMessage(void far *message, int window, unsigned int first, unsigned int last, unsigned int remove);` — src/recovered/StopSimulation.c
- `extern int far pascal PeekMessage(void far *message, int window, unsigned int first, unsigned int last, unsigned int remove);` — src/recovered/wf_UpdateAllWindows-97a1ff92dc.c
- `extern int far pascal PeekMessage(struct MSG far *message, int hwnd, unsigned int first, unsigned int last, unsigned int remove);` — src/recovered/wf_win_FlushEvents-3010537d93.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DBRecall', 'offset': 34514, 'source': None, 'size': 438}
- {'symbol': '_DBDelete', 'offset': 34952, 'source': None, 'size': 153}
- {'symbol': '_DBReplace', 'offset': 35654, 'source': None, 'size': 169}
- {'symbol': '_OpenDB', 'offset': 35824, 'source': None, 'size': 517}
