# Recovery task _snd_Deinstall

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 608 bytes.

```asm
0000 enter 0x16, 0
0004 push si
0005 mov bx, 0x8d08
0008 mov es, word ptr [0xbf78]
000c mov word ptr [bp - 0xc], bx
000f mov word ptr [bp - 0xa], es
0012 cmp word ptr es:[bx], 0
0016 jne 0x7c79
0018 jmp 0x7d4a
001b cmp word ptr es:[0x8d0c], 0
0021 je 0x7c84
0023 jmp 0x7d4a
0026 cmp word ptr es:[0x8d0a], 0
002c jne 0x7c8f
002e jmp 0x7d24
0031 mov bx, 0x8d0e
0034 mov word ptr [bp - 0x10], bx
0037 mov word ptr [bp - 0xe], es
003a cmp word ptr es:[bx], 0
003e je 0x7ce4
0040 mov bx, word ptr [bp - 0xc]
0043 push word ptr es:[bx]
0046 push ds
0047 push 0xc02
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
004f mov word ptr [bp - 4], ax
0052 mov word ptr [bp - 2], dx
0055 push ds
0056 push 0xc11
0059 nop 
005a push cs
005b call 0x62bc ; _WinPrintf
005e add sp, 4
0061 mov ax, word ptr [bp - 2]
0064 or ax, word ptr [bp - 4]
0067 je 0x7cdc
0069 les bx, ptr [bp - 0x10]
006c push word ptr es:[bx]
006f push 0x804
0072 push 0
0074 push 0
0076 lea ax, [bp - 8]
0079 push ss
007a push ax
007b lcall [bp - 4]
007e les bx, ptr [bp - 0x10]
0081 mov word ptr es:[bx], 0
0086 mov bx, 0x8d14
0089 mov es, word ptr [0xbf78]
008d mov word ptr [bp - 0x14], bx
0090 mov word ptr [bp - 0x12], es
0093 cmp word ptr es:[bx], 0
0097 je 0x7d40
0099 les bx, ptr [bp - 0xc]
009c push word ptr es:[bx]
009f push ds
00a0 push 0xc25
00a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 164, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
00a8 mov word ptr [bp - 4], ax
00ab mov word ptr [bp - 2], dx
00ae or dx, ax
00b0 je 0x7d19
00b2 les bx, ptr [bp - 0x14]
00b5 push word ptr es:[bx]
00b8 lcall [bp - 4]
00bb les bx, ptr [bp - 0x14]
00be mov word ptr es:[bx], 0
00c3 jmp 0x7d40
00c5 nop 
00c6 les bx, ptr [bp - 0xc]
00c9 push word ptr es:[bx]
00cc push ds
00cd push 0xc32
00d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
00d5 mov word ptr [bp - 4], ax
00d8 mov word ptr [bp - 2], dx
00db or dx, ax
00dd je 0x7d40
00df lcall [bp - 4]
00e2 les bx, ptr [bp - 0xc]
00e5 push word ptr es:[bx]
00e8 jmp 0x7eb6
00eb nop 
00ec les bx, ptr [bp - 0xc]
00ef cmp word ptr es:[bx], 0
00f3 jne 0x7d56
00f5 jmp 0x7e48
00f8 mov es, word ptr [0xbf78]
00fc cmp word ptr es:[0x8d0c], 0
0102 je 0x7d65
0104 jmp 0x7e48
0107 cmp word ptr es:[0x8d0a], 0
010d je 0x7dbc
010f mov es, word ptr [bp - 0xa]
0112 push word ptr es:[bx]
0115 push ds
0116 push 0xcb6
0119 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 282, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
011e mov word ptr [bp - 4], ax
0121 mov word ptr [bp - 2], dx
0124 push ds
0125 push 0xcc5
0128 nop 
0129 push cs
012a call 0x62bc ; _WinPrintf
012d add sp, 4
0130 mov ax, word ptr [bp - 2]
0133 or ax, word ptr [bp - 4]
0136 je 0x7dae
0138 mov es, word ptr [0xbf78]
013c push word ptr es:[0x8d0e]
0141 push 0x804
0144 push 0
0146 push 0
0148 lea ax, [bp - 8]
014b push ss
014c push ax
014d lcall [bp - 4]
0150 mov es, word ptr [0xbf78]
0154 mov word ptr es:[0x8d0e], 0
015b jmp 0x7e4d
015e mov es, word ptr [bp - 0xa]
0161 push word ptr es:[bx]
0164 push ds
0165 push 0xcd9
0168 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 361, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
016d mov word ptr [bp - 4], ax
0170 mov word ptr [bp - 2], dx
0173 or dx, ax
0175 je 0x7deb
0177 lcall [bp - 4]
017a mov si, ax
017c or si, si
017e je 0x7deb
0180 push si
0181 push ds
0182 push 0xce6
0185 nop 
0186 push cs
0187 call 0x62bc ; _WinPrintf
018a add sp, 6
018d les bx, ptr [bp - 0xc]
0190 push word ptr es:[bx]
0193 push ds
0194 push 0xc4f
0197 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 408, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
019c mov word ptr [bp - 4], ax
019f mov word ptr [bp - 2], dx
01a2 or dx, ax
01a4 je 0x7e07
01a6 lcall [bp - 4]
01a9 mov es, word ptr [0xbf78]
01ad push word ptr es:[0x8d20]
01b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 435, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
01b7 mov es, word ptr [0xbf78]
01bb push word ptr es:[0x8d1c]
01c0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 449, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 112}}]
01c5 mov es, word ptr [0xbf78]
01c9 push word ptr es:[0x8d1c]
01ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 463, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
01d3 mov es, word ptr [0xbf78]
01d7 mov word ptr es:[0x8d1c], 0
01de sub ax, ax
01e0 mov word ptr es:[0x8d20], ax
01e4 mov word ptr es:[0x8d1e], ax
01e8 jmp 0x7e4d
01ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 491, 'type': 3, 'target': {'kind': 'import', 'module': 'SOUND', 'ordinal': 2}}]
01ef les bx, ptr [bp - 0xc]
01f2 cmp word ptr es:[bx], 0
01f6 je 0x7ea6
01f8 mov es, word ptr [0xbf78]
01fc cmp word ptr es:[0x8d0c], 0
0202 je 0x7ea6
0204 mov bx, 0x8d14
0207 mov word ptr [bp - 0x14], bx
020a mov word ptr [bp - 0x12], es
020d cmp word ptr es:[bx], 0
0211 je 0x7e9b
0213 les bx, ptr [bp - 0xc]
0216 push word ptr es:[bx]
0219 push ds
021a push 0xc42
021d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 542, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0222 mov word ptr [bp - 4], ax
0225 mov word ptr [bp - 2], dx
0228 or dx, ax
022a je 0x7e93
022c les bx, ptr [bp - 0x14]
022f push word ptr es:[bx]
0232 lcall [bp - 4]
0235 les bx, ptr [bp - 0x14]
0238 mov word ptr es:[bx], 0
023d les bx, ptr [bp - 0xc]
0240 push word ptr es:[bx]
0243 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 580, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 96}}]
0248 mov es, word ptr [0xbf78]
024c mov ax, word ptr es:[0x8d28]
0250 mov word ptr [bp - 0x16], ax
0253 or ax, ax
0255 je 0x7ebb
0257 push ax
0258 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 601, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 96}}]
025d pop si
025e leave 
025f retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsDLLAvail', 'offset': 30734, 'source': None, 'size': 300}
- {'symbol': '_snd_Install', 'offset': 31034, 'source': None, 'size': 804}
- {'symbol': '_snd_IsSongDone', 'offset': 32446, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c', 'size': 44}
- {'symbol': '_musSoundBlasterClose', 'offset': 32490, 'source': None, 'size': 100}
