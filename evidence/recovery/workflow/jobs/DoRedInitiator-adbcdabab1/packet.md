# Recovery task _DoRedInitiator

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 619 bytes.

```asm
0000 enter 0x18, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov es, word ptr [0xc632]
000d mov al, byte ptr es:[si + 0x278e]
0012 sub ah, ah
0014 mov di, ax
0016 mov bx, si
0018 add bx, 0x2f62
001c mov word ptr [bp - 0x10], bx
001f mov word ptr [bp - 0xe], es
0022 mov cl, byte ptr es:[bx]
0025 sub ch, ch
0027 mov word ptr [bp - 0xc], cx
002a and cx, 0xf8
002e mov word ptr [bp - 0xa], cx
0031 mov cl, byte ptr es:[si + 0x23a4]
0036 sub ch, ch
0038 mov word ptr [bp - 6], cx
003b mov es, word ptr [0xc634]
003f mov word ptr es:[0x80a6], cx
0044 mov es, word ptr [0xc636]
0048 mov word ptr es:[0x80ac], ax
004c mov es, word ptr [0xc638]
0050 mov word ptr es:[0x7606], 1
0057 mov bx, 0x9d74
005a mov es, word ptr [0xc63a]
005e mov word ptr [bp - 0x14], bx
0061 mov word ptr [bp - 0x12], es
0064 mov ax, word ptr es:[bx]
0067 or ax, ax
0069 je 0x974a
006b dec ax
006c dec ax
006d jne 0x9746
006f jmp 0x9814
0072 jmp 0x983b
0075 nop 
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UnRecruitRed
007b cmp word ptr [0xce80], 1 ; _MePlane
0080 jne 0x979a
0082 push 0x20
0084 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 135, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0089 add sp, 2
008c add ax, 0x40
008f cmp ax, word ptr [0xcd88] ; _MeLocX
0093 jge 0x979a
0095 push 0xa
0097 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 154, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
009c add sp, 2
009f mov es, word ptr [0xc63c]
00a3 cmp ax, word ptr es:[0x9e7a]
00a8 jge 0x979a
00aa les bx, ptr [bp - 0x14]
00ad mov word ptr es:[bx], 2
00b2 mov es, word ptr [0xc63c]
00b6 push word ptr es:[0x9e7a]
00bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 190, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _RecruitRed
00c0 add sp, 2
00c3 jmp 0x983b
00c6 mov es, word ptr [0xc63e]
00ca mov ax, word ptr es:[0x836c]
00ce mov bx, 0x9c22
00d1 mov es, word ptr [0xc640]
00d5 mov word ptr [bp - 0x18], bx
00d8 mov word ptr [bp - 0x16], es
00db mov word ptr es:[bx], ax
00de mov es, word ptr [0xc63e]
00e2 mov ax, word ptr es:[0x836a]
00e6 mov es, word ptr [0xc642]
00ea mov word ptr es:[0x9bee], ax
00ee cmp ax, 0x1e
00f1 jle 0x97d0
00f3 sub word ptr es:[0x9bee], 5
00f9 jmp 0x97ea
00fb nop 
00fc les bx, ptr [bp - 0x18]
00ff cmp word ptr es:[bx], 0x14
0103 jge 0x97e0
0105 add word ptr es:[bx], 5
0109 jmp 0x97ea
010b nop 
010c cmp word ptr es:[bx], 0x28
0110 jle 0x97ea
0112 sub word ptr es:[bx], 5
0116 mov ax, word ptr [0xaca2]
0119 add ax, word ptr [0xaca4]
011d mov word ptr [bp - 2], ax
0120 cmp ax, 0x14
0123 jge 0x97fe
0125 sar ax, 2
0128 jmp 0x9801
012a sar ax, 3
012d push ax
012e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 305, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _RecruitRed
0133 add sp, 2
0136 les bx, ptr [bp - 0x14]
0139 mov word ptr es:[bx], 1
013e jmp 0x983b
0140 cmp word ptr [0xce80], 1 ; _MePlane
0145 jne 0x983b
0147 mov es, word ptr [0xc644]
014b mov ax, word ptr es:[0x9fe4]
014f mov es, word ptr [0xc642]
0153 mov word ptr es:[0x9bee], ax
0157 mov es, word ptr [0xc646]
015b mov ax, word ptr es:[0x9fea]
015f mov es, word ptr [0xc640]
0163 mov word ptr es:[0x9c22], ax
0167 mov es, word ptr [0xc640]
016b push word ptr es:[0x9c22]
0170 mov es, word ptr [0xc642]
0174 push word ptr es:[0x9bee]
0179 mov es, word ptr [0xc636]
017d push word ptr es:[0x80ac]
0182 mov es, word ptr [0xc634]
0186 push word ptr es:[0x80a6]
018b push 1
018d nop 
018e push cs
018f call 0x9a18 ; _GetRedBestDirs
0192 add sp, 0xa
0195 mov word ptr [bp - 4], ax
0198 or ax, ax
019a jge 0x988a
019c push 0xa
019e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 417, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
01a3 add sp, 2
01a6 or ax, ax
01a8 jne 0x9884
01aa les bx, ptr [bp - 0x14]
01ad mov word ptr es:[bx], ax
01b0 les bx, ptr [bp - 0x10]
01b3 jmp 0x992e
01b6 mov es, word ptr [0xc648]
01ba mov bx, ax
01bc mov al, byte ptr es:[bx + 8]
01c1 cwde 
01c2 mov cx, ax
01c4 add cx, di
01c6 mov es, word ptr [0xc64a]
01ca mov al, byte ptr es:[bx]
01cf cwde 
01d0 mov bx, ax
01d2 add bx, word ptr [bp - 6]
01d5 mov word ptr [bp - 2], bx
01d8 shl bx, 6
01db add bx, cx
01dd mov al, byte ptr [bx + 0x68e8]
01e1 sub ah, ah
01e3 mov word ptr [bp - 8], ax
01e6 or ax, ax
01e8 jne 0x98f6
01ea mov al, byte ptr [bp - 0xa]
01ed or al, byte ptr [bp - 4]
01f0 mov bx, word ptr [bp - 2]
01f3 shl bx, 6
01f6 add bx, cx
01f8 mov byte ptr [bx + 0x68e8], al
01fc les bx, ptr [bp - 0x10]
01ff mov byte ptr es:[bx], al
0202 mov bx, word ptr [bp - 6]
0205 shl bx, 6
0208 mov byte ptr [bx + di + 0x68e8], ah
020c mov al, byte ptr [bp - 2]
020f mov es, word ptr [0xc632]
0213 mov byte ptr es:[si + 0x23a4], al
0218 mov byte ptr es:[si + 0x278e], cl
021d pop si
021e pop di
021f leave 
0220 retf 
0221 nop 
0222 push ax
0223 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 550, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0228 add sp, 2
022b dec ax
022c jne 0x9912
022e push si
022f push 1
0231 nop 
0232 push cs
0233 call 0x823e ; _YellowFight
0236 add sp, 4
0239 pop si
023a pop di
023b leave 
023c retf 
023d nop 
023e cmp word ptr [bp - 8], 0x7f
0242 jle 0x993b
0244 mov al, byte ptr [bp - 0xc]
0247 and ax, 7
024a push ax
024b call 0x2a22 ; _RandTurn
024e add sp, 2
0251 or al, byte ptr [bp - 0xa]
0254 les bx, ptr [bp - 0x10]
0257 mov byte ptr es:[bx], al
025a mov al, byte ptr es:[bx]
025d mov bx, word ptr [bp - 6]
0260 shl bx, 6
0263 mov byte ptr [bx + di + 0x68e8], al
0267 pop si
0268 pop di
0269 leave 
026a retf 
```

## Known declaration examples

- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_AddRocks-01eddceee1.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetSmellT', 'offset': 38418, 'source': None, 'size': 106}
- {'symbol': '_MakeRedInitiator', 'offset': 38524, 'source': None, 'size': 88}
- {'symbol': '_GetNewRedTask', 'offset': 39232, 'source': None, 'size': 215}
- {'symbol': '_GetRedBestDirs', 'offset': 39448, 'source': None, 'size': 220}
