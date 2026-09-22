# Recovery task _GetDefendDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 365 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c or di, di
000e jne 0x1062
0010 or si, si
0012 jne 0x104a
0014 push 3
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
001b add sp, 2
001e add ax, 3
0021 jmp 0x10a8
0023 nop 
0024 cmp si, 0x3f
0027 jne 0x1054
0029 push 3
002b jmp 0x1056
002d nop 
002e push 5
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0035 add sp, 2
0038 inc ax
0039 jmp 0x10a8
003b nop 
003c or si, si
003e jne 0x107e
0040 cmp di, 0x7f
0043 jne 0x107a
0045 push 3
0047 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 74, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
004c add sp, 2
004f add ax, 5
0052 jmp 0x10a8
0054 push 5
0056 jmp 0x103c
0058 cmp di, 0x7f
005b jne 0x109c
005d cmp si, 0x3f
0060 jne 0x1098
0062 push 3
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 103, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0069 add sp, 2
006c add ax, 7
006f jmp 0x10a8
0071 nop 
0072 push 5
0074 jmp 0x106d
0076 cmp si, 0x3f
0079 jne 0x10a6
007b push 5
007d jmp 0x108a
007f nop 
0080 xor ax, ax
0082 mov word ptr [bp - 2], ax
0085 or ax, ax
0087 je 0x10bc
0089 mov al, byte ptr [bp - 2]
008c dec al
008e and ax, 7
0091 pop si
0092 pop di
0093 leave 
0094 retf 
0095 nop 
0096 mov ax, word ptr [0xce80] ; _MePlane
0099 dec ax
009a je 0x10ee
009c dec ax
009d jne 0x10c8
009f jmp 0x116e
00a2 dec ax
00a3 jne 0x10ce
00a5 jmp 0x1186
00a8 mov si, word ptr [bp - 2]
00ab or si, si
00ad jne 0x10d8
00af jmp 0x118c
00b2 mov es, word ptr [0xc4e6]
00b6 mov bx, word ptr [bp + 0xa]
00b9 shl bx, 3
00bc add bx, si
00be mov al, byte ptr es:[bx + 0x23]
00c3 cwde 
00c4 pop si
00c5 pop di
00c6 leave 
00c7 retf 
00c8 mov es, word ptr [0xc4be]
00cc cmp word ptr es:[0x72ec], 1
00d2 jne 0x111a
00d4 mov ax, word ptr [0xac7e] ; _SpidY
00d7 sar ax, 4
00da push ax
00db mov ax, word ptr [0xac7c] ; _SpidX
00de sar ax, 4
00e1 push ax
00e2 push word ptr [bp + 8]
00e5 push word ptr [bp + 6]
00e8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 235, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
00ed add sp, 8
00f0 mov si, ax
00f2 jmp 0x10d1
00f4 mov es, word ptr [0xc4c2]
00f8 push word ptr es:[0x9fea]
00fd mov es, word ptr [0xc4c0]
0101 push word ptr es:[0x9fe4]
0106 push word ptr [bp + 8]
0109 push word ptr [bp + 6]
010c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 271, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
0111 add sp, 8
0114 mov si, ax
0116 mov es, word ptr [0xc4ec]
011a mov ax, word ptr es:[0x9e7a]
011e sar ax, 1
0120 cmp ax, si
0122 jge 0x115e
0124 mov es, word ptr [0xc4c2]
0128 push word ptr es:[0x9fea]
012d mov es, word ptr [0xc4c0]
0131 push word ptr es:[0x9fe4]
0136 jmp 0x1108
0138 push 8
013a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 317, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
013f add sp, 2
0142 mov si, ax
0144 inc si
0145 jmp 0x10d1
0148 push 0
014a push word ptr [bp + 0xa]
014d push word ptr [bp + 8]
0150 push word ptr [bp + 6]
0153 nop 
0154 push cs
0155 call 0xc30 ; _GetNestDir
0158 add sp, 8
015b pop si
015c pop di
015d leave 
015e retf 
015f nop 
0160 push 0x80
0163 jmp 0x1170
0165 nop 
0166 mov ax, word ptr [bp + 0xa]
0169 pop si
016a pop di
016b leave 
016c retf 
```

## Known declaration examples

- `extern unsigned long far GetDis(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetAlarmDir', 'offset': 3668, 'source': None, 'size': 286}
- {'symbol': '_GetRandDir', 'offset': 3954, 'source': 'src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c', 'size': 179}
- {'symbol': '_GetRedDefendDir', 'offset': 4500, 'source': None, 'size': 343}
- {'symbol': '_Bounce', 'offset': 4844, 'source': 'src/recovered/wf_Bounce-0d87abbf42.c', 'size': 140}
