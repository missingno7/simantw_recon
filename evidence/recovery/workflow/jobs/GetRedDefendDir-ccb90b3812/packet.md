# Recovery task _GetRedDefendDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 343 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c or di, di
000e jne 0x11d0
0010 or si, si
0012 jne 0x11b8
0014 push 3
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
001b add sp, 2
001e add ax, 3
0021 jmp 0x1216
0023 nop 
0024 cmp si, 0x3f
0027 jne 0x11c2
0029 push 3
002b jmp 0x11c4
002d nop 
002e push 5
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0035 add sp, 2
0038 inc ax
0039 jmp 0x1216
003b nop 
003c or si, si
003e jne 0x11ec
0040 cmp di, 0x7f
0043 jne 0x11e8
0045 push 3
0047 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 74, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
004c add sp, 2
004f add ax, 5
0052 jmp 0x1216
0054 push 5
0056 jmp 0x11aa
0058 cmp di, 0x7f
005b jne 0x120a
005d cmp si, 0x3f
0060 jne 0x1206
0062 push 3
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 103, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0069 add sp, 2
006c add ax, 7
006f jmp 0x1216
0071 nop 
0072 push 5
0074 jmp 0x11db
0076 cmp si, 0x3f
0079 jne 0x1214
007b push 5
007d jmp 0x11f8
007f nop 
0080 xor ax, ax
0082 mov word ptr [bp - 2], ax
0085 or ax, ax
0087 je 0x122a
0089 mov al, byte ptr [bp - 2]
008c dec al
008e and ax, 7
0091 pop si
0092 pop di
0093 leave 
0094 retf 
0095 nop 
0096 mov es, word ptr [0xc4ee]
009a mov ax, word ptr es:[0x7606]
009e dec ax
009f je 0x1262
00a1 dec ax
00a2 jne 0x123b
00a4 jmp 0x12c6
00a7 dec ax
00a8 jne 0x1241
00aa jmp 0x12de
00ad mov si, word ptr [bp - 2]
00b0 or si, si
00b2 jne 0x124b
00b4 jmp 0x12e4
00b7 mov es, word ptr [0xc4e6]
00bb mov bx, word ptr [bp + 0xa]
00be shl bx, 3
00c1 add bx, si
00c3 mov al, byte ptr es:[bx + 0x23]
00c8 cwde 
00c9 pop si
00ca pop di
00cb leave 
00cc retf 
00cd nop 
00ce mov es, word ptr [0xc4f0]
00d2 push word ptr es:[0x80ac]
00d7 mov es, word ptr [0xc4f2]
00db push word ptr es:[0x80a6]
00e0 push word ptr [bp + 8]
00e3 push word ptr [bp + 6]
00e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 233, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
00eb add sp, 8
00ee mov si, ax
00f0 mov es, word ptr [0xc4f4]
00f4 mov ax, word ptr es:[0xa08e]
00f8 sar ax, 1
00fa cmp ax, si
00fc jge 0x12b6
00fe mov es, word ptr [0xc4f0]
0102 push word ptr es:[0x80ac]
0107 mov es, word ptr [0xc4f2]
010b push word ptr es:[0x80a6]
0110 push word ptr [bp + 8]
0113 push word ptr [bp + 6]
0116 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 281, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
011b add sp, 8
011e mov si, ax
0120 jmp 0x1244
0122 push 8
0124 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 295, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0129 add sp, 2
012c mov si, ax
012e inc si
012f jmp 0x1244
0132 push 0
0134 push word ptr [bp + 0xa]
0137 push word ptr [bp + 8]
013a push word ptr [bp + 6]
013d nop 
013e push cs
013f call 0xc30 ; _GetNestDir
0142 add sp, 8
0145 pop si
0146 pop di
0147 leave 
0148 retf 
0149 nop 
014a push 0x80
014d jmp 0x12c8
014f nop 
0150 mov ax, word ptr [bp + 0xa]
0153 pop si
0154 pop di
0155 leave 
0156 retf 
```

## Known declaration examples

- `extern unsigned long far GetDis(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetRandDir', 'offset': 3954, 'source': 'src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c', 'size': 179}
- {'symbol': '_GetDefendDir', 'offset': 4134, 'source': None, 'size': 365}
- {'symbol': '_Bounce', 'offset': 4844, 'source': 'src/recovered/wf_Bounce-0d87abbf42.c', 'size': 140}
- {'symbol': '_InitSimYard', 'offset': 4984, 'source': 'src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c', 'size': 304}
