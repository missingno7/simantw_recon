# Recovery task _DoLoadInitializations

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 481 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc17c]
000a cmp word ptr es:[0x9b6e], 1
0010 je 0x9dde
0012 mov es, word ptr [0xc17e]
0016 mov word ptr es:[0x85ea], 0x3e8
001d jmp 0x9de9
001f nop 
0020 mov es, word ptr [0xc17e]
0024 mov word ptr es:[0x85ea], 0x3e9
002b push word ptr es:[0x85ea]
0030 push 0
0032 nop 
0033 push cs
0034 call 0x100f4
0037 add sp, 4
003a mov si, 0x68e8
003d xor ax, ax
003f mov cx, 0x20
0042 mov di, si
0044 push ds
0045 pop es
0046 rep stosw word ptr es:[di], ax
0048 add si, 0x40
004b cmp si, 0x88e8
004f jb 0x9dfb
0051 mov bx, 0x88e8
0054 mov cx, 0x20
0057 mov di, bx
0059 rep stosw word ptr es:[di], ax
005b add bx, 0x40
005e cmp bx, 0x98e8
0062 jb 0x9e12
0064 mov bx, 0x98e8
0067 mov cx, 0x20
006a mov di, bx
006c rep stosw word ptr es:[di], ax
006e add bx, 0x40
0071 cmp bx, 0xa8e8
0075 jb 0x9e25
0077 mov es, word ptr [0xc180]
007b mov si, word ptr es:[0x80f0]
0080 or si, si
0082 jl 0x9e66
0084 mov <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0087 mov ds, ax
0089 mov bl, byte ptr [si + 0x23a4]
008d sub bh, bh
008f shl bx, 6
0092 mov al, byte ptr [si + 0x278e]
0096 sub ah, ah
0098 add bx, ax
009a mov al, byte ptr [si + 0x2f62]
009e mov byte ptr ss:[bx + 0x68e8], al
00a3 dec si
00a4 jns 0x9e47
00a6 push ss
00a7 pop ds
00a8 mov es, word ptr [0xc182]
00ac mov si, word ptr es:[0x99d4]
00b1 or si, si
00b3 jl 0x9e97
00b5 mov <resolved loader operand; see bindings> ; [{'operand_offset': 182, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00b8 mov ds, ax
00ba mov bl, byte ptr [si + 0x3736]
00be sub bh, bh
00c0 shl bx, 6
00c3 mov al, byte ptr [si + 0x392c]
00c7 sub ah, ah
00c9 add bx, ax
00cb mov al, byte ptr [si + 0x3d18]
00cf mov byte ptr ss:[bx - 0x7718], al
00d4 dec si
00d5 jns 0x9e78
00d7 push ss
00d8 pop ds
00d9 mov es, word ptr [0xc184]
00dd mov si, word ptr es:[0x72cc]
00e2 or si, si
00e4 jl 0x9ec8
00e6 mov <resolved loader operand; see bindings> ; [{'operand_offset': 231, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00e9 mov ds, ax
00eb mov bl, byte ptr [si + 0x4104]
00ef sub bh, bh
00f1 shl bx, 6
00f4 mov al, byte ptr [si + 0x42fa]
00f8 sub ah, ah
00fa add bx, ax
00fc mov al, byte ptr [si + 0x46e6]
0100 mov byte ptr ss:[bx - 0x6718], al
0105 dec si
0106 jns 0x9ea9
0108 push ss
0109 pop ds
010a mov es, word ptr [0xc186]
010e cmp word ptr es:[0x9fe8], 0
0114 jne 0x9ef3
0116 push 0xff
0119 push word ptr [0xcf50] ; _MeDir
011d push word ptr [0xcc84] ; _MeType
0121 push word ptr [0xce7e] ; _MeLocY
0125 push word ptr [0xcd88] ; _MeLocX
0129 push word ptr [0xce80] ; _MePlane
012d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 304, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
0132 add sp, 0xc
0135 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 312, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FullCount
013a mov ax, word ptr [0xcd88] ; _MeLocX
013d mov word ptr [bp - 4], ax
0140 mov ax, word ptr [0xce7e] ; _MeLocY
0143 mov word ptr [bp - 2], ax
0146 mov ax, word ptr [0xce80] ; _MePlane
0149 or ax, ax
014b je 0x9f16
014d dec ax
014e je 0x9f2c
0150 dec ax
0151 je 0x9f42
0153 dec ax
0154 je 0x9f58
0156 jmp 0x9f6b
0158 mov ax, word ptr [bp - 4]
015b mov dx, word ptr [bp - 2]
015e mov es, word ptr [0xc188]
0162 mov word ptr es:[0x789e], ax
0166 mov word ptr es:[0x78a0], dx
016b jmp 0x9f6b
016d nop 
016e mov ax, word ptr [bp - 4]
0171 mov dx, word ptr [bp - 2]
0174 mov es, word ptr [0xc18a]
0178 mov word ptr es:[0x9f2c], ax
017c mov word ptr es:[0x9f2e], dx
0181 jmp 0x9f6b
0183 nop 
0184 mov ax, word ptr [bp - 4]
0187 mov dx, word ptr [bp - 2]
018a mov es, word ptr [0xc18c]
018e mov word ptr es:[0x9fb2], ax
0192 mov word ptr es:[0x9fb4], dx
0197 jmp 0x9f6b
0199 nop 
019a mov ax, word ptr [bp - 4]
019d mov dx, word ptr [bp - 2]
01a0 mov es, word ptr [0xc18e]
01a4 mov word ptr es:[0x72f6], ax
01a8 mov word ptr es:[0x72f8], dx
01ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 432, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetDefaultWindows
01b2 mov ax, word ptr [0xcc76] ; _MapPlane
01b5 cmp word ptr [0xce80], ax ; _MePlane
01b9 jne 0x9f89
01bb push word ptr [0xce7e] ; _MeLocY
01bf push word ptr [0xcd88] ; _MeLocX
01c3 nop 
01c4 push cs
01c5 call 0x11620
01c8 add sp, 4
01cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 462, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _UpdateLayQueenModeDisplay
01d0 push 1
01d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 469, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetDefaultWindPrompt
01d7 add sp, 2
01da mov ax, 1
01dd pop si
01de pop di
01df leave 
01e0 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern void far FullCount(void);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern void far FullCount(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far FullCount(void);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near MeDir;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeDir;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
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
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SpecialTutorialInit', 'offset': 40170, 'source': 'src/recovered/wf_SpecialTutorialInit-e0cff25916.c', 'size': 153}
- {'symbol': '_DoPreLoadInits', 'offset': 40324, 'source': 'src/recovered/wf_DoPreLoadInits-ed37124107.c', 'size': 58}
- {'symbol': '_LoadGame', 'offset': 40864, 'source': None, 'size': 669}
- {'symbol': '_SaveGame', 'offset': 41534, 'source': None, 'size': 626}
