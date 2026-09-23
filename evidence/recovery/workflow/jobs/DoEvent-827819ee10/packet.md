# Recovery task _DoEvent

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 548 bytes.

```asm
0000 enter 2, 0
0004 cmp word ptr [0x10], 0 ; _bHelp
0009 jne 0xbd0
000b jmp 0xd42
000e mov word ptr [0x10], 0 ; _bHelp
0014 mov ah, byte ptr [bp + 0x13]
0017 sub al, al
0019 mov word ptr [bp - 2], ax
001c cmp ax, 0x1300
001f je 0xc62
0021 ja 0xbfc
0023 or ax, ax
0025 je 0xc12
0027 sub ax, 0x100
002a je 0xc2a
002c sub ax, 0x400
002f je 0xc62
0031 sub ax, 0xd00
0034 je 0xc62
0036 leave 
0037 retf 
0038 nop 
0039 nop 
003a sub ax, 0x1500
003d je 0xc3e
003f sub ax, 0x400
0042 je 0xc2a
0044 sub ax, 0x900
0047 je 0xc3e
0049 sub ax, 0x100
004c je 0xc3e
004e leave 
004f retf 
0050 push word ptr [0xcd78] ; _rootWnd
0054 push <resolved loader operand; see bindings> ; [{'operand_offset': 85, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0057 push 0x76ac
005a push 1
005c push 0
005e push 4
0060 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 171}}]
0065 leave 
0066 retf 
0067 nop 
0068 push word ptr [0xcd78] ; _rootWnd
006c push <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
006f push 0x76ac
0072 push 1
0074 push 0
0076 push 0x102
0079 jmp 0xc22
007b nop 
007c mov ax, word ptr [bp + 0x12]
007f cmp ax, 0x2217
0082 ja 0xc8c
0084 cmp ax, 0x2210
0087 jb 0xc4e
0089 jmp 0xcea
008c cmp ax, 0x2209
008f ja 0xc76
0091 cmp ax, 0x2202
0094 jae 0xcbe
0096 sub ax, 0x1503
0099 jb 0xc62
009b sub ax, 0xa
009e jbe 0xcbe
00a0 push word ptr [0xcd78] ; _rootWnd
00a4 push <resolved loader operand; see bindings> ; [{'operand_offset': 165, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00a7 push 0x76ac
00aa push 1
00ac push 0
00ae push word ptr [bp - 2]
00b1 jmp 0xc22
00b3 nop 
00b4 sub ax, 0x220b
00b7 jb 0xc62
00b9 sub ax, 2
00bc jbe 0xcbe
00be sub ax, 1
00c1 jb 0xc62
00c3 sub ax, 1
00c6 jbe 0xcd2
00c8 jmp 0xc62
00ca cmp ax, 0x2308
00cd je 0xcbe
00cf ja 0xca8
00d1 sub ax, 0x2218
00d4 jb 0xc62
00d6 sub ax, 6
00d9 jbe 0xd12
00db sub ax, 0xe4
00de jb 0xc62
00e0 sub ax, 3
00e3 jmp 0xc60
00e5 nop 
00e6 sub ax, 0x230b
00e9 jb 0xc62
00eb sub ax, 7
00ee jbe 0xd26
00f0 sub ax, 1
00f3 jb 0xc62
00f5 sub ax, 6
00f8 jbe 0xd12
00fa jmp 0xc62
00fc push word ptr [0xcd78] ; _rootWnd
0100 push <resolved loader operand; see bindings> ; [{'operand_offset': 257, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0103 push 0x76ac
0106 push 1
0108 push 0
010a push word ptr [bp + 0x12]
010d jmp 0xc22
0110 push word ptr [0xcd78] ; _rootWnd
0114 push <resolved loader operand; see bindings> ; [{'operand_offset': 277, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0117 push 0x76ac
011a push 1
011c mov ax, word ptr [bp + 0x12]
011f sub ax, 3
0122 push 0
0124 push ax
0125 jmp 0xc22
0128 push word ptr [0xcd78] ; _rootWnd
012c push <resolved loader operand; see bindings> ; [{'operand_offset': 301, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
012f push 0x76ac
0132 push 1
0134 mov es, word ptr [0xbe7a]
0138 mov bx, ax
013a shl bx, 1
013c mov bx, word ptr [bx - 0x440e]
0140 shl bx, 2
0143 push word ptr es:[bx - 0x7518]
0148 push word ptr es:[bx - 0x751a]
014d jmp 0xc22
0150 push word ptr [0xcd78] ; _rootWnd
0154 push <resolved loader operand; see bindings> ; [{'operand_offset': 341, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0157 push 0x76ac
015a push 1
015c push 0
015e push 0xfd48
0161 jmp 0xc22
0164 push word ptr [0xcd78] ; _rootWnd
0168 push <resolved loader operand; see bindings> ; [{'operand_offset': 361, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
016b push 0x76ac
016e push 1
0170 mov es, word ptr [0xbe7a]
0174 mov bx, word ptr [bp + 0x12]
0177 shl bx, 1
0179 mov bx, word ptr [bx - 0x45f4]
017d jmp 0xd02
017f nop 
0180 mov ah, byte ptr [bp + 0x13]
0183 sub al, al
0185 cmp ax, 0x1300
0188 je 0xdaa
018a ja 0xd64
018c or ax, ax
018e je 0xd7a
0190 sub ax, 0x100
0193 je 0xd86
0195 sub ax, 0x400
0198 je 0xd92
019a sub ax, 0xd00
019d je 0xd9e
019f leave 
01a0 retf 
01a1 nop 
01a2 sub ax, 0x1500
01a5 je 0xdb6
01a7 sub ax, 0x400
01aa je 0xdc2
01ac sub ax, 0x900
01af je 0xdce
01b1 sub ax, 0x100
01b4 je 0xdda
01b6 leave 
01b7 retf 
01b8 lea ax, [bp + 6]
01bb push ss
01bc push ax
01bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 448, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ProcEditEvent
01c2 jmp 0xde4
01c4 lea ax, [bp + 6]
01c7 push ss
01c8 push ax
01c9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 460, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ProcMapEvent
01ce jmp 0xde4
01d0 lea ax, [bp + 6]
01d3 push ss
01d4 push ax
01d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 472, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _ProcInfoEvent
01da jmp 0xde4
01dc lea ax, [bp + 6]
01df push ss
01e0 push ax
01e1 nop 
01e2 push cs
01e3 call 0xffffc07a
01e6 jmp 0xde4
01e8 lea ax, [bp + 6]
01eb push ss
01ec push ax
01ed nop 
01ee push cs
01ef call 0xffffbd08
01f2 jmp 0xde4
01f4 lea ax, [bp + 6]
01f7 push ss
01f8 push ax
01f9 nop 
01fa push cs
01fb call 0x8a76 ; _ProcHistoryEvent
01fe jmp 0xde4
0200 lea ax, [bp + 6]
0203 push ss
0204 push ax
0205 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 520, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ProcYardEvent
020a jmp 0xde4
020c lea ax, [bp + 6]
020f push ss
0210 push ax
0211 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 532, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ProcMapRibbonEvent
0216 jmp 0xde4
0218 lea ax, [bp + 6]
021b push ss
021c push ax
021d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 544, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ProcYardRibbonEvent
0222 leave 
0223 retf 
```

## Known declaration examples

- `extern int far bHelp;` — src/recovered/wf_tu_antedit_A998_DrawYardCursor_3_scaffold-c71c8e4e09.c
- `extern int far bHelp;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near bHelp;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ClearBookmarks', 'offset': 2728, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c', 'size': 125}
- {'symbol': '_DrawRibbonMessage', 'offset': 2854, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c', 'size': 156}
- {'symbol': '_HelpKeyDown', 'offset': 3558, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c', 'size': 166}
- {'symbol': '_DoKeyDown', 'offset': 3724, 'source': None, 'size': 1385}
