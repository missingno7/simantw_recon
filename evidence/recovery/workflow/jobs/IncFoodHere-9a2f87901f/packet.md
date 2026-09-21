# Recovery task _IncFoodHere

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 287 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov dx, word ptr [0xcc76] ; _MapPlane
000a cmp dx, 1
000d je 0x7f52
000f or dx, dx
0011 je 0x7f52
0013 mov si, 0x10
0016 jmp 0x7f55
0018 mov si, 0x48
001b push word ptr [bp + 8]
001e push word ptr [bp + 6]
0021 push dx
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0027 add sp, 6
002a mov di, ax
002c push 0x11
002e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 47, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0033 test ah, 0x80
0036 je 0x7fea
0038 cmp si, di
003a jle 0x7f7e
003c xor ax, ax
003e pop si
003f pop di
0040 leave 
0041 retf 
0042 nop 
0043 nop 
0044 lea ax, [si + 3]
0047 cmp ax, di
0049 jl 0x7f76
004b push 8
004d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 80, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0052 add sp, 2
0055 mov word ptr [bp - 2], ax
0058 cmp word ptr [0xcc76], 1 ; _MapPlane
005d je 0x7fa6
005f cmp word ptr ss:[0xcc76], 0
0065 je 0x7fa6
0067 push ss
0068 pop ds
0069 jmp 0x803d
006c mov <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
006f mov es, ax
0071 cmp word ptr es:[0x9e84], 0
0077 jle 0x7fba
0079 dec word ptr es:[0x9e84]
007e jmp 0x7fa1
0080 cmp word ptr ss:[0xcc76], 2
0086 jne 0x7fd6
0088 mov <resolved loader operand; see bindings> ; [{'operand_offset': 137, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
008b mov es, ax
008d cmp word ptr es:[0x9ea4], 0
0093 jle 0x7fa1
0095 dec word ptr es:[0x9ea4]
009a jmp 0x7fa1
009c mov <resolved loader operand; see bindings> ; [{'operand_offset': 157, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
009f mov es, ax
00a1 cmp word ptr es:[0x72de], 0
00a7 jle 0x7fa1
00a9 dec word ptr es:[0x72de]
00ae jmp 0x7fa1
00b0 lea ax, [si + 2]
00b3 cmp ax, di
00b5 jl 0x7f76
00b7 cmp si, di
00b9 jle 0x8002
00bb mov word ptr [bp - 2], di
00be cmp di, 0x18
00c1 jge 0x8008
00c3 mov word ptr [bp - 2], si
00c6 jmp 0x8008
00c8 mov word ptr [bp - 2], di
00cb inc word ptr [bp - 2]
00ce cmp word ptr [0xcc76], 1 ; _MapPlane
00d3 je 0x8034
00d5 cmp word ptr [0xcc76], 0 ; _MapPlane
00da je 0x8034
00dc cmp word ptr [0xcc76], 2 ; _MapPlane
00e1 jne 0x8028
00e3 mov es, word ptr [0xc27e]
00e7 inc word ptr es:[0x9ea4]
00ec jmp 0x803d
00ee mov es, word ptr [0xc280]
00f2 inc word ptr es:[0x72de]
00f7 jmp 0x803d
00f9 nop 
00fa mov es, word ptr [0xc282]
00fe inc word ptr es:[0x9e84]
0103 push word ptr [bp - 2]
0106 push word ptr [bp + 8]
0109 push word ptr [bp + 6]
010c push word ptr [0xcc76] ; _MapPlane
0110 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 275, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMap
0115 add sp, 8
0118 mov ax, 1
011b pop si
011c pop di
011d leave 
011e retf 
```

## Known declaration examples

- `extern int far GetMap(int plane, int x, int y);` — src/recovered/wf_WallNeighbors-7ac5fa173f.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far SetMap(int plane, int x, int y, int value);` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ExpIncSmell', 'offset': 31646, 'source': None, 'size': 445}
- {'symbol': '_ExpKillAnts', 'offset': 32092, 'source': None, 'size': 478}
- {'symbol': '_ConnectAll', 'offset': 32858, 'source': None, 'size': 1267}
- {'symbol': '_ConnectWall', 'offset': 34126, 'source': None, 'size': 241}
