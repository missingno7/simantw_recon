# Recovery task _EditMessage

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 351 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 cmp word ptr [bp + 0xe], 0
0009 jne 0x930c
000b mov es, word ptr [0xc0c4]
000f cmp word ptr es:[0x85fa], 0
0015 je 0x92e6
0017 mov es, word ptr [0xc0c6]
001b mov ax, word ptr es:[0x1448]
001f or ax, word ptr es:[0x1446]
0024 je 0x930c
0026 mov ax, word ptr [bp + 8]
0029 or ax, word ptr [bp + 6]
002c je 0x92f1
002e jmp 0x941b
0031 mov es, word ptr [0xc0c8]
0035 cmp word ptr es:[0x144a], -1
003b je 0x9300
003d jmp 0x941b
0040 cmp word ptr es:[0x144c], 0x7fff
0047 je 0x930c
0049 jmp 0x941b
004c cmp word ptr [bp + 0xc], 0
0050 jl 0x934c
0052 push 0
0054 push 2
0056 mov ax, word ptr [bp + 0xa]
0059 mov dx, word ptr [bp + 0xc]
005c mov cx, ax
005e mov bx, dx
0060 shl ax, 1
0062 rcl dx, 1
0064 add ax, cx
0066 adc dx, bx
0068 push dx
0069 push ax
006a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
006f mov si, ax
0071 mov di, dx
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0078 add si, ax
007a adc di, dx
007c mov es, word ptr [0xc0c8]
0080 mov word ptr es:[0x144a], si
0085 mov word ptr es:[0x144c], di
008a jmp 0x935e
008c mov es, word ptr [0xc0c8]
0090 mov word ptr es:[0x144a], 0xffff
0097 mov word ptr es:[0x144c], 0x7fff
009e mov ax, word ptr [bp + 6]
00a1 mov dx, word ptr [bp + 8]
00a4 mov es, word ptr [0xc0c6]
00a8 cmp word ptr es:[0x1446], ax
00ad jne 0x9376
00af cmp word ptr es:[0x1448], dx
00b4 je 0x937f
00b6 mov word ptr es:[0x1446], ax
00ba mov word ptr es:[0x1448], dx
00bf cmp word ptr [bp + 0xc], 0
00c3 jl 0x93c0
00c5 push 0
00c7 push 2
00c9 mov ax, word ptr [bp + 0xa]
00cc mov dx, word ptr [bp + 0xc]
00cf mov cx, ax
00d1 mov bx, dx
00d3 shl ax, 1
00d5 rcl dx, 1
00d7 add ax, cx
00d9 adc dx, bx
00db push dx
00dc push ax
00dd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 224, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00e2 mov si, ax
00e4 mov di, dx
00e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 233, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
00eb add si, ax
00ed adc di, dx
00ef mov es, word ptr [0xc0ca]
00f3 mov word ptr es:[0x19a2], si
00f8 mov word ptr es:[0x19a4], di
00fd jmp 0x93d2
00ff nop 
0100 mov es, word ptr [0xc0ca]
0104 mov word ptr es:[0x19a2], 0xffff
010b mov word ptr es:[0x19a4], 0x7fff
0112 mov ax, word ptr [bp + 6]
0115 mov dx, word ptr [bp + 8]
0118 mov es, word ptr [0xc0cc]
011c cmp word ptr es:[0x199e], ax
0121 jne 0x93ea
0123 cmp word ptr es:[0x19a0], dx
0128 je 0x93f3
012a mov word ptr es:[0x199e], ax
012e mov word ptr es:[0x19a0], dx
0133 push 0x2200
0136 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 313, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
013b add sp, 2
013e or ax, ax
0140 je 0x9407
0142 nop 
0143 push cs
0144 call 0x10b26
0147 push 0x1900
014a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 333, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
014f add sp, 2
0152 or ax, ax
0154 je 0x941b
0156 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 345, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawAnimYardMessage
015b pop si
015c pop di
015d leave 
015e retf 
```

## Known declaration examples

- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_drawHistGraph', 'offset': 36472, 'source': None, 'size': 777}
- {'symbol': '_HistUpdate', 'offset': 37250, 'source': None, 'size': 317}
- {'symbol': '_win_YardClosed', 'offset': 37920, 'source': 'src/recovered/wf_win_YardClosed-13af30aa32.c', 'size': 131}
- {'symbol': '_UpdateLayQueenModeDisplay', 'offset': 38052, 'source': None, 'size': 108}
