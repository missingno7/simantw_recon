# Recovery task _SpiderScan

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 387 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc448]
000a cmp word ptr es:[0x729e], 5
0010 jne 0x5550
0012 mov ax, 0xffff
0015 pop si
0016 pop di
0017 leave 
0018 retf 
0019 nop 
001a mov bx, word ptr [0xac80] ; _SpidDir
001e mov al, bl
0020 sub al, 2
0022 and ax, 7
0025 shl ax, 5
0028 mov word ptr [bp - 0xa], ax
002b mov cx, word ptr [0xac7c] ; _SpidX
002f sar cx, 4
0032 mov word ptr [bp - 0x10], cx
0035 mov cx, word ptr [0xac7e] ; _SpidY
0039 sar cx, 4
003c mov word ptr [bp - 0xe], cx
003f mov word ptr [bp - 0x12], 0xffff
0044 xor cx, cx
0046 mov word ptr [bp - 2], cx
0049 mov word ptr [bp - 0xc], cx
004c add ax, 0x20
004f mov word ptr [bp - 0x14], ax
0052 mov ax, word ptr [bp - 0xa]
0055 sub ax, 0x20
0058 mov word ptr [bp - 8], ax
005b cmp ax, word ptr [bp - 0x14]
005e jl 0x5599
0060 jmp 0x5642
0063 push 0xc
0065 nop 
0066 push cs
0067 call 0x158a ; _SRand1
006a add sp, 2
006d inc ax
006e mov word ptr [bp - 2], ax
0071 push 0
0073 push 0x7fff
0076 cdq 
0077 push dx
0078 push ax
0079 push word ptr [bp - 8]
007c mov si, ax
007e mov di, dx
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _fracCOS
0085 add sp, 2
0088 cdq 
0089 push dx
008a push ax
008b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 142, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0090 push dx
0091 push ax
0092 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 149, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0097 mov cx, si
0099 mov si, ax
009b add si, word ptr [bp - 0x10]
009e mov ax, di
00a0 push 0
00a2 push 0x7fff
00a5 push ax
00a6 push cx
00a7 push word ptr [bp - 8]
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _fracSIN
00af add sp, 2
00b2 cdq 
00b3 push dx
00b4 push ax
00b5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 184, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
00ba push dx
00bb push ax
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00c1 mov di, ax
00c3 add di, word ptr [bp - 0xe]
00c6 or si, si
00c8 jl 0x5634
00ca cmp si, 0x7f
00cd jg 0x5634
00cf or di, di
00d1 jl 0x5634
00d3 cmp di, 0x3f
00d6 jg 0x5634
00d8 mov bx, si
00da shl bx, 6
00dd mov al, byte ptr [bx + di + 0x68e8]
00e1 sub ah, ah
00e3 mov word ptr [bp - 2], ax
00e6 or ax, ax
00e8 je 0x5634
00ea push ax
00eb push di
00ec push si
00ed push 1
00ef nop 
00f0 push cs
00f1 call 0x59fc ; _FindAntIndex
00f4 add sp, 8
00f7 mov word ptr [bp - 0x12], ax
00fa or ax, ax
00fc jge 0x5650
00fe inc word ptr [bp - 8]
0101 mov ax, word ptr [bp - 8]
0104 cmp word ptr [bp - 0x14], ax
0107 jle 0x5642
0109 jmp 0x5599
010c inc word ptr [bp - 0xc]
010f cmp word ptr [bp - 0xc], 2
0113 jge 0x564e
0115 jmp 0x5588
0118 jmp 0x56b2
011a mov word ptr [bp - 4], si
011d mov ax, di
011f shl ax, 4
0122 add ax, 7
0125 push ax
0126 mov ax, si
0128 shl ax, 4
012b add ax, 7
012e push ax
012f push word ptr [0xac7e] ; _SpidY
0133 push word ptr [0xac7c] ; _SpidX
0137 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 314, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoLaserFire
013c add sp, 8
013f mov si, word ptr [bp - 0x12]
0142 nop 
0143 push cs
0144 call 0x15ce ; _SRand4
0147 or ax, ax
0149 je 0x56ab
014b mov bx, di
014d mov di, word ptr [bp - 4]
0150 shl di, 6
0153 xor al, al
0155 mov byte ptr [bx + di + 0x68e8], al
0159 mov es, word ptr [0xc456]
015d mov byte ptr es:[si + 0x2f62], al
0162 mov al, byte ptr [bp - 2]
0165 and ax, 0x80
0168 push ax
0169 push bx
016a push word ptr [bp - 4]
016d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 368, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _DeadAntHere
0172 add sp, 6
0175 mov ax, si
0177 pop si
0178 pop di
0179 leave 
017a retf 
017b nop 
017c mov ax, word ptr [bp - 0x12]
017f pop si
0180 pop di
0181 leave 
0182 retf 
```

## Known declaration examples

- `extern int far FindAntIndex(int list, int life, int column, int attribute);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near SpidX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near SpidX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern int near SpidY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near SpidY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_KillSpider', 'offset': 21460, 'source': 'src/recovered/wf_tu_simone_4668_KillSpider_1_scaffold-37d274226a.c', 'size': 34}
- {'symbol': '_SFoundAnt', 'offset': 21494, 'source': None, 'size': 319}
- {'symbol': '_SGetDis', 'offset': 22202, 'source': 'src/recovered/SGetDis.c', 'size': 31}
- {'symbol': '_IsValidLocation', 'offset': 22234, 'source': 'src/recovered/IsValidLocation.c', 'size': 70}
