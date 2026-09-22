# Recovery task _SFoundAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 319 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 mov di, word ptr [0xac7e] ; _SpidY
000a sar di, 4
000d mov si, word ptr [0xac7c] ; _SpidX
0011 sar si, 4
0014 mov word ptr [bp - 0xc], si
0017 mov cx, di
0019 mov es, word ptr [0xc44a]
001d cmp word ptr es:[0x7d60], 7
0023 je 0x541e
0025 jmp 0x54a8
0028 mov es, word ptr [0xc46c]
002c mov si, word ptr es:[0x80f0]
0031 dec si
0032 js 0x545f
0034 mov word ptr [bp - 0xa], di
0037 mov es, word ptr [0xc456]
003b cmp byte ptr es:[si + 0x2f62], 0
0041 je 0x545c
0043 mov al, byte ptr es:[si + 0x278e]
0048 sub ah, ah
004a push ax
004b mov al, byte ptr es:[si + 0x23a4]
0050 push ax
0051 push di
0052 push word ptr [bp - 0xc]
0055 nop 
0056 push cs
0057 call 0x1122 ; _GetDis
005a add sp, 8
005d or dx, dx
005f jne 0x545c
0061 cmp ax, 0x320
0064 jbe 0x54a2
0066 dec si
0067 jns 0x542d
0069 mov es, word ptr [0xc454]
006d cmp word ptr es:[0x9fe8], 0
0073 je 0x546e
0075 jmp 0x552e
0078 cmp word ptr [0xce80], 1 ; _MePlane
007d je 0x5478
007f jmp 0x552e
0082 push word ptr [0xce7e] ; _MeLocY
0086 push word ptr [0xcd88] ; _MeLocX
008a push di
008b push word ptr [bp - 0xc]
008e nop 
008f push cs
0090 call 0x1122 ; _GetDis
0093 add sp, 8
0096 or dx, dx
0098 je 0x5493
009a jmp 0x552e
009d cmp ax, 0x320
00a0 jbe 0x549b
00a2 jmp 0x552e
00a5 mov ax, 0xffff
00a8 pop si
00a9 pop di
00aa leave 
00ab retf 
00ac mov ax, si
00ae pop si
00af pop di
00b0 leave 
00b1 retf 
00b2 mov word ptr [bp - 0xa], di
00b5 mov word ptr [bp - 4], 0
00ba mov es, word ptr [0xc46e]
00be mov bx, word ptr [0xac80] ; _SpidDir
00c2 mov al, byte ptr es:[bx + 8]
00c7 cwde 
00c8 add di, ax
00ca push di
00cb mov es, word ptr [0xc470]
00cf mov al, byte ptr es:[bx]
00d4 cwde 
00d5 add si, ax
00d7 push si
00d8 nop 
00d9 push cs
00da call 0x9c02 ; _IsValidA
00dd add sp, 4
00e0 or ax, ax
00e2 je 0x552e
00e4 push di
00e5 push si
00e6 push word ptr [bp - 0xa]
00e9 push word ptr [bp - 0xc]
00ec nop 
00ed push cs
00ee call 0x1122 ; _GetDis
00f1 add sp, 8
00f4 or dx, dx
00f6 jne 0x552e
00f8 cmp ax, 0x190
00fb ja 0x552e
00fd mov bx, si
00ff shl bx, 6
0102 mov al, byte ptr [bx + di + 0x68e8]
0106 sub ah, ah
0108 mov word ptr [bp - 2], ax
010b or ax, ax
010d je 0x5525
010f push ax
0110 nop 
0111 push cs
0112 call 0x5720 ; _IsYellowAnt
0115 add sp, 2
0118 or ax, ax
011a jne 0x549b
011c push word ptr [bp - 2]
011f push di
0120 push si
0121 push 1
0123 nop 
0124 push cs
0125 call 0x59fc ; _FindAntIndex
0128 add sp, 8
012b or ax, ax
012d jge 0x5531
012f inc word ptr [bp - 4]
0132 cmp word ptr [bp - 4], 0x14
0136 jl 0x54b0
0138 mov ax, 0xfffe
013b pop si
013c pop di
013d leave 
013e retf 
```

## Known declaration examples

- `extern int far FindAntIndex(int list, int life, int column, int attribute);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern unsigned long far GetDis(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_tu_simant1_0000_DoSmells_10_scaffold-13ce956607.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_tu_simtwo_4CDC_StorePillarMap_4_scaffold-c16d27de40.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_9_scaffold-03367c8694.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
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

- {'symbol': '_ScanForAnts', 'offset': 21346, 'source': None, 'size': 113}
- {'symbol': '_KillSpider', 'offset': 21460, 'source': 'src/recovered/wf_tu_simone_4668_KillSpider_1_scaffold-37d274226a.c', 'size': 34}
- {'symbol': '_SpiderScan', 'offset': 21814, 'source': None, 'size': 387}
- {'symbol': '_SGetDis', 'offset': 22202, 'source': 'src/recovered/SGetDis.c', 'size': 31}
