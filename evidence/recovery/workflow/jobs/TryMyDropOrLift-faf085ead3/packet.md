# Recovery task _TryMyDropOrLift

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 619 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov cx, word ptr [0xcc84] ; _MeType
000a mov al, cl
000c and al, 8
000e jne 0x98f1
0010 jmp 0x9974
0013 mov ax, word ptr [0xcd88] ; _MeLocX
0016 mov word ptr [bp - 4], ax
0019 mov ax, word ptr [0xce7e] ; _MeLocY
001c mov word ptr [bp - 6], ax
001f mov ax, cx
0021 cmp ax, 0x48
0024 je 0x994c
0026 ja 0x9916
0028 sub al, 8
002a je 0x9920
002c sub al, 0x10
002e je 0x9936
0030 sub al, 0x10
0032 je 0x994c
0034 sub al, 0x10
0036 je 0x9936
0038 xor si, si
003a mov word ptr [bp - 2], si
003d mov di, si
003f jmp 0x9965
0041 nop 
0042 push word ptr [bp + 0xa]
0045 push word ptr [bp + 8]
0048 push word ptr [bp - 6]
004b push word ptr [bp - 4]
004e push word ptr [bp + 6]
0051 nop 
0052 push cs
0053 call 0x8188 ; _DropMyEgg
0056 jmp 0x9960
0058 push word ptr [bp + 0xa]
005b push word ptr [bp + 8]
005e push word ptr [bp - 6]
0061 push word ptr [bp - 4]
0064 push word ptr [bp + 6]
0067 nop 
0068 push cs
0069 call 0x7576 ; _DropMyFood
006c jmp 0x9960
006e push word ptr [bp + 0xa]
0071 push word ptr [bp + 8]
0074 push word ptr [bp - 6]
0077 push word ptr [bp - 4]
007a push word ptr [bp + 6]
007d nop 
007e push cs
007f call 0x7c52 ; _DropMyRock
0082 add sp, 0xa
0085 mov di, ax
0087 cmp di, 1
008a sbb si, si
008c and si, 0xfffe
008f inc si
0090 mov ax, si
0092 pop si
0093 pop di
0094 leave 
0095 retf 
0096 mov al, cl
0098 and al, 8
009a je 0x997e
009c xor dx, dx
009e jmp 0x99c2
00a0 cmp cx, 0x10
00a3 jne 0x9986
00a5 jmp 0x9a2e
00a8 cmp word ptr [0xac8a], 0xa ; _MeHealth
00ad jge 0x9990
00af jmp 0x9a2e
00b2 xor si, si
00b4 or si, si
00b6 jne 0x99c0
00b8 push word ptr [bp + 0xa]
00bb push word ptr [bp + 8]
00be push word ptr [bp + 6]
00c1 nop 
00c2 push cs
00c3 call 0x85ee ; _PickupMyRock
00c6 add sp, 6
00c9 mov si, ax
00cb or si, si
00cd jne 0x99c0
00cf push word ptr [bp + 0xa]
00d2 push word ptr [bp + 8]
00d5 push word ptr [bp + 6]
00d8 nop 
00d9 push cs
00da call 0x8f4c ; _PickupMyFood
00dd add sp, 6
00e0 mov si, ax
00e2 mov dx, si
00e4 or dx, dx
00e6 je 0x99c9
00e8 jmp 0x9ade
00eb mov es, word ptr [0xc4ba]
00ef cmp word ptr es:[0x85e2], dx
00f4 jne 0x99ec
00f6 cmp word ptr [0xcc84], 0x40 ; _MeType
00fb je 0x99de
00fd jmp 0x9ad6
0100 mov es, word ptr [0xc4bc]
0104 cmp word ptr es:[0x8a6c], dx
0109 je 0x99ec
010b jmp 0x9ad6
010e cmp word ptr [0xce80], 1 ; _MePlane
0113 je 0x99f6
0115 jmp 0x9ad6
0118 mov ax, word ptr [0xcd88] ; _MeLocX
011b cmp word ptr [bp + 8], ax
011e je 0x9a01
0120 jmp 0x9ad6
0123 mov ax, word ptr [0xce7e] ; _MeLocY
0126 cmp word ptr [bp + 0xa], ax
0129 je 0x9a0c
012b jmp 0x9ad6
012e push word ptr [bp + 0xa]
0131 push word ptr [bp + 8]
0134 nop 
0135 push cs
0136 call 0x116ae
0139 add sp, 4
013c or ax, ax
013e jne 0x9a21
0140 jmp 0x9acc
0143 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 326, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _EnterNest
0148 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 331, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _GotoMyAnt
014d jmp 0x9b40
0150 mov es, word ptr [0xc48c]
0154 mov word ptr es:[0x8a6a], 0xfd
015b push word ptr [bp + 0xa]
015e push word ptr [bp + 8]
0161 push word ptr [bp + 6]
0164 lea ax, [bp - 2]
0167 push ss
0168 push ax
0169 nop 
016a push cs
016b call 0x88a2 ; _FindEggAt
016e add sp, 0xa
0171 mov si, ax
0173 or si, si
0175 jge 0x9a58
0177 jmp 0x9990
017a push 0
017c push 0
017e push 0
0180 push 0
0182 push 0
0184 push word ptr [bp - 2]
0187 push word ptr [bp + 6]
018a nop 
018b push cs
018c call 0x584a ; _SetAntIndex
018f add sp, 0xe
0192 mov ax, word ptr [0xcd88] ; _MeLocX
0195 cmp word ptr [bp + 8], ax
0198 jne 0x9a80
019a mov ax, word ptr [0xce7e] ; _MeLocY
019d cmp word ptr [bp + 0xa], ax
01a0 je 0x9a93
01a2 push 0
01a4 push word ptr [bp + 0xa]
01a7 push word ptr [bp + 8]
01aa push word ptr [bp + 6]
01ad nop 
01ae push cs
01af call 0x5d18 ; _SetLife
01b2 add sp, 8
01b5 cmp word ptr [0xac8a], 0xa ; _MeHealth
01ba jl 0x9aba
01bc push 0x7e
01be push 0
01c0 push 0x1c
01c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 453, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
01c7 add sp, 6
01ca mov es, word ptr [0xc48c]
01ce mov word ptr es:[0x8a6a], si
01d3 mov word ptr [0xcc84], 8 ; _MeType
01d9 jmp 0x9ac5
01db nop 
01dc mov es, word ptr [0xc4b2]
01e0 mov word ptr es:[0x8a6e], 3
01e7 mov si, 1
01ea jmp 0x9992
01ed nop 
01ee mov si, 0xffff
01f1 mov ax, si
01f3 pop si
01f4 pop di
01f5 leave 
01f6 retf 
01f7 nop 
01f8 xor si, si
01fa mov ax, si
01fc pop si
01fd pop di
01fe leave 
01ff retf 
0200 push word ptr [bp + 0xa]
0203 push word ptr [bp + 8]
0206 push word ptr [0xce7e] ; _MeLocY
020a push word ptr [0xcd88] ; _MeLocX
020e nop 
020f push cs
0210 call 0x110cc
0213 add sp, 8
0216 mov word ptr [bp - 2], ax
0219 or ax, ax
021b jle 0x9b15
021d dec ax
021e push ax
021f push word ptr [0xcc84] ; _MeType
0223 push word ptr [0xce7e] ; _MeLocY
0227 push word ptr [0xcd88] ; _MeLocX
022b push word ptr [0xce80] ; _MePlane
022f nop 
0230 push cs
0231 call 0x65fa ; _MoveMyLife
0234 add sp, 0xa
0237 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 570, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DoEditUpdateDraw
023c mov bx, 0x8a6e
023f mov es, word ptr [0xc4b2]
0243 mov word ptr [bp - 0xa], bx
0246 mov word ptr [bp - 8], es
0249 cmp word ptr es:[bx], 0
024d jl 0x9b40
024f push word ptr es:[bx]
0252 nop 
0253 push cs
0254 call 0x8cda ; _EatMyFood
0257 add sp, 2
025a les bx, ptr [bp - 0xa]
025d mov word ptr es:[bx], 0xffff
0262 mov si, 1
0265 mov ax, si
0267 pop si
0268 pop di
0269 leave 
026a retf 
```

## Known declaration examples

- `extern void far DoEditUpdateDraw(void);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far DoEditUpdateDraw(void);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int far DropMyEgg(int, int, int, int, int);` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int far DropMyFood(int, int, int, int, int);` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int far DropMyRock(int, int, int, int, int);` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern void far EatMyFood(int amount);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far FindEggAt(int far *index, int plane, int x, int y);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far GotoMyAnt(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MeHealth;` — src/recovered/wf_SetMyHealth-5d15d1e8e5.c
- `extern int near MeHealth;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near MeHealth;` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeType;` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int near MeType;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far MoveMyLife(int plane, int x, int y, int type, int direction);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far PickupMyFood(int plane, int x, int y);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int far PickupMyRock(int plane, int x, int y);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far SetAntIndex(int plane, int index, int a, int b, int c, int d, int e);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_SetQueenTail-103d1d54cd.c
- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsSamePlane', 'offset': 38826, 'source': None, 'size': 32}
- {'symbol': '_IsLiftable', 'offset': 38858, 'source': 'src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c', 'size': 275}
- {'symbol': '_IsItAHole', 'offset': 39754, 'source': 'src/recovered/wf_IsItAHole-fd9d6ad240.c', 'size': 184}
- {'symbol': '_IsValidA', 'offset': 39938, 'source': 'src/recovered/IsValidA.c', 'size': 36}
