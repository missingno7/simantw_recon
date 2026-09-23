# Recovery task _ProcessPost

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 672 bytes.

```asm
0000 enter 0x48, 0
0004 push si
0005 lea ax, [bp - 0x48]
0008 mov word ptr [bp - 8], ax
000b mov word ptr [bp - 6], ss
000e xor si, si
0010 mov word ptr [bp - 4], si
0013 push 0x40
0015 push ax
0016 push ss
0017 mov es, word ptr [0xbe96]
001b mov bx, word ptr es:[0x7c42]
0020 shl bx, 1
0022 mov es, word ptr [0xbe94]
0026 push word ptr es:[bx - 0x5f64]
002b mov es, word ptr [0xbe92]
002f push word ptr es:[bx - 0x7f82]
0034 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 55, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _movedata
0039 add sp, 0xa
003c mov es, word ptr [0xbe96]
0040 inc word ptr es:[0x7c42]
0045 cmp word ptr es:[0x7c42], 0xa
004b jne 0x1e11
004d mov word ptr es:[0x7c42], si
0052 mov al, byte ptr [bp - 0x48]
0055 cwde 
0056 sub ax, 0xff91
0059 je 0x1e28
005b sub ax, 5
005e jne 0x1e22
0060 jmp 0x200e
0063 mov ax, si
0065 pop si
0066 leave 
0067 retf 
0068 nop 
0069 mov al, byte ptr [bp - 0x17]
006c cwde 
006d or ax, ax
006f je 0x1e52
0071 lea ax, [bp - 0x48]
0074 push ss
0075 push ax
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbFinalStatus
007b add sp, 4
007e mov al, byte ptr [bp - 0x46]
0081 push ax
0082 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbHangUp
0087 add sp, 2
008a mov si, 1
008d mov ax, si
008f pop si
0090 leave 
0091 retf 
0092 nop 
0093 mov al, byte ptr [bp - 0x46]
0096 push ax
0097 push 2
0099 push ds
009a push 0xcc76
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 160, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
00a2 add sp, 8
00a5 mov ax, word ptr [0xcc76] ; _MapPlane
00a8 or ax, ax
00aa jge 0x1e6e
00ac jmp 0x1fb3
00af jno 0x1e73
00b1 jmp 0x1fb3
00b4 dec ax
00b5 jle 0x1e86
00b7 dec ax
00b8 jne 0x1e7c
00ba jmp 0x1f2e
00bd dec ax
00be jne 0x1e82
00c0 jmp 0x1f6c
00c3 jmp 0x1fb3
00c6 nop 
00c7 mov word ptr [bp - 2], 0x1000
00cc lea ax, [bp - 2]
00cf push ss
00d0 push ax
00d1 push ds
00d2 push 0x28e8
00d5 mov cl, byte ptr [bp - 0x46]
00d8 push cx
00d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 220, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
00de add sp, 0xa
00e1 mov al, byte ptr [bp - 0x46]
00e4 push ax
00e5 push 2
00e7 lea ax, [bp - 4]
00ea push ss
00eb push ax
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
00f1 add sp, 8
00f4 mov word ptr [bp - 2], 0x1000
00f9 lea ax, [bp - 2]
00fc push ss
00fd push ax
00fe mov cx, 0x28e8
0101 mov dx, ds
0103 add ch, 0x10
0106 adc dx, si
0108 push dx
0109 push cx
010a mov cl, byte ptr [bp - 0x46]
010d push cx
010e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
0113 add sp, 0xa
0116 mov al, byte ptr [bp - 0x46]
0119 push ax
011a push 2
011c lea ax, [bp - 4]
011f push ss
0120 push ax
0121 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 292, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
0126 add sp, 8
0129 mov word ptr [bp - 2], 0x1000
012e lea ax, [bp - 2]
0131 push ss
0132 push ax
0133 push ds
0134 push 0x68e8
0137 mov cl, byte ptr [bp - 0x46]
013a push cx
013b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 318, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
0140 add sp, 0xa
0143 mov al, byte ptr [bp - 0x46]
0146 push ax
0147 push 2
0149 lea ax, [bp - 4]
014c push ss
014d push ax
014e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 337, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
0153 add sp, 8
0156 mov word ptr [bp - 2], 0x1000
015b lea ax, [bp - 2]
015e push ss
015f push ax
0160 mov ax, 0x68e8
0163 mov dx, ds
0165 add ah, 0x10
0168 adc dx, si
016a push dx
016b push ax
016c jmp 0x1fa7
016e nop 
016f mov word ptr [bp - 2], 0x1000
0174 lea ax, [bp - 2]
0177 push ss
0178 push ax
0179 push ds
017a push 0x48e8
017d mov cl, byte ptr [bp - 0x46]
0180 push cx
0181 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 388, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
0186 add sp, 0xa
0189 mov al, byte ptr [bp - 0x46]
018c push ax
018d push 2
018f lea ax, [bp - 4]
0192 push ss
0193 push ax
0194 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 407, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
0199 add sp, 8
019c mov word ptr [bp - 2], 0x1000
01a1 lea ax, [bp - 2]
01a4 push ss
01a5 push ax
01a6 push ds
01a7 push 0x88e8
01aa jmp 0x1fa7
01ac nop 
01ad mov word ptr [bp - 2], 0x1000
01b2 lea ax, [bp - 2]
01b5 push ss
01b6 push ax
01b7 push ds
01b8 push 0x58e8
01bb mov cl, byte ptr [bp - 0x46]
01be push cx
01bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 450, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
01c4 add sp, 0xa
01c7 mov al, byte ptr [bp - 0x46]
01ca push ax
01cb push 2
01cd lea ax, [bp - 4]
01d0 push ss
01d1 push ax
01d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 469, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
01d7 add sp, 8
01da mov word ptr [bp - 2], 0x1000
01df lea ax, [bp - 2]
01e2 push ss
01e3 push ax
01e4 push ds
01e5 push 0x98e8
01e8 mov al, byte ptr [bp - 0x46]
01eb push ax
01ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 495, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
01f1 add sp, 0xa
01f4 mov al, byte ptr [bp - 0x46]
01f7 push ax
01f8 push 2
01fa lea ax, [bp - 4]
01fd push ss
01fe push ax
01ff lcall <resolved loader operand; see bindings> ; [{'operand_offset': 514, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
0204 add sp, 8
0207 mov ax, 0xacac
020a sub ax, 0xac5a
020d mov word ptr [bp - 2], ax
0210 lea ax, [bp - 2]
0213 push ss
0214 push ax
0215 push ds
0216 push 0xac5a
0219 mov al, byte ptr [bp - 0x46]
021c push ax
021d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 544, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
0222 add sp, 0xa
0225 mov al, byte ptr [bp - 0x46]
0228 push ax
0229 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 556, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbHangUp
022e add sp, 2
0231 push <resolved loader operand; see bindings> ; [{'operand_offset': 562, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _StopSimulation
0234 push 0x1d72
0237 push si
0238 push 0x3c
023a push ds
023b push 0x2c6
023e push ds
023f push 0x2ce
0242 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 581, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbPostListen
0247 add sp, 0x10
024a mov ax, si
024c pop si
024d leave 
024e retf 
024f mov al, byte ptr [bp - 0x17]
0252 cwde 
0253 cmp ax, 0xa
0256 je 0x2054
0258 ja 0x2021
025a or al, al
025c je 0x2032
025e sub al, 5
0260 je 0x2032
0262 lea ax, [bp - 0x48]
0265 push ss
0266 push ax
0267 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 618, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbFinalStatus
026c add sp, 4
026f jmp 0x1e49
0272 nop 
0273 push <resolved loader operand; see bindings> ; [{'operand_offset': 628, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _StopSimulation
0276 push 0x1d72
0279 push 0x2000
027c push word ptr [0x3e]
0280 push word ptr [0x3c] ; _theNetBiosBuffer
0284 mov al, byte ptr [bp + 6]
0287 push ax
0288 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 651, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbPostReceiveAny
028d add sp, 0xc
0290 mov ax, si
0292 pop si
0293 leave 
0294 retf 
0295 mov word ptr [0x2c4], 1
029b mov ax, si
029d pop si
029e leave 
029f retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far StopSimulation(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoDebugWin', 'offset': 7358, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c', 'size': 179}
- {'symbol': '_NetBIOSPost', 'offset': 7538, 'source': None, 'size': None}
- {'symbol': '_NetworkSend', 'offset': 8288, 'source': None, 'size': 451}
- {'symbol': '_UpdateWindows', 'offset': 8740, 'source': None, 'size': 540}
