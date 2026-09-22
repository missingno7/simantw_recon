# Recovery task _YellowCommand

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 625 bytes.

```asm
0000 enter 0xe, 0
0004 mov es, word ptr [0xbf0c]
0008 mov ax, word ptr es:[0x9fe8]
000c mov word ptr [bp - 6], ax
000f cmp ax, 1
0012 jle 0x87d1
0014 jmp 0x8a29
0017 mov es, word ptr [0xbf58]
001b cmp word ptr es:[0x9dda], 0
0021 je 0x87e0
0023 jmp 0x8a29
0026 mov ax, word ptr [bp + 6]
0029 cmp ax, 0xc
002c jbe 0x87eb
002e jmp 0x8a29
0031 shl ax, 1
0033 xchg bx, ax
0034 jmp word ptr cs:[bx - 0x780c]
0039 nop 
003a dw offset 0x880e
003c dw offset 0x884e
003e dw offset 0x8868
0040 dw offset 0x887a
0042 dw offset 0x888c
0044 dw offset 0x88a2
0046 dw offset 0x88b4
0048 dw offset 0x88bc
004a dw offset 0x894e
004c dw offset 0x8978
004e dw offset 0x89cc
0050 dw offset 0x89d4
0052 dw offset 0x89f4
0054 push word ptr [0xcd78] ; _rootWnd
0058 push <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
005b push 0x76ac
005e push 1
0060 cmp word ptr [bp - 6], 0
0064 jne 0x8838
0066 cmp word ptr [0xcc84], 0x40 ; _MeType
006b jne 0x8830
006d mov ax, 0x100
0070 mov dx, 3
0073 jmp 0x883e
0075 nop 
0076 mov ax, 0x100
0079 mov dx, 1
007c jmp 0x883e
007e mov ax, 0x100
0081 mov dx, 2
0084 mov word ptr [bp - 4], ax
0087 mov word ptr [bp - 2], dx
008a push dx
008b push ax
008c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 141, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 171}}]
0091 jmp 0x8a29
0094 push 0x7e
0096 push 0x2b05
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 156, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
009e add sp, 4
00a1 push 5
00a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 166, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _Recruit
00a8 add sp, 2
00ab leave 
00ac retf 
00ad nop 
00ae push 0x7e
00b0 push 0x2b06
00b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 182, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
00b8 add sp, 4
00bb push 0xa
00bd jmp 0x885d
00bf nop 
00c0 push 0x7e
00c2 push 0x2b07
00c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 200, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
00ca add sp, 4
00cd push 0x3e8
00d0 jmp 0x885d
00d2 push 0x7e
00d4 push 0x2b08
00d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
00dc add sp, 4
00df push 0
00e1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 228, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UnRecruit
00e6 jmp 0x8862
00e8 push 0x7e
00ea push 0x2b09
00ed lcall <resolved loader operand; see bindings> ; [{'operand_offset': 240, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
00f2 add sp, 4
00f5 push 1
00f7 jmp 0x889b
00f9 nop 
00fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 253, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _StartLifeTransfer
00ff leave 
0100 retf 
0101 nop 
0102 mov bx, 0x75fa
0105 mov es, word ptr [0xbf50]
0109 mov word ptr [bp - 0xa], bx
010c mov word ptr [bp - 8], es
010f cmp word ptr es:[bx], 1
0113 sbb cx, cx
0115 neg cx
0117 or cx, cx
0119 je 0x8906
011b cmp word ptr [0xce80], 1 ; _MePlane
0120 jne 0x88fe
0122 cmp word ptr [bp - 6], 0
0126 jne 0x88fe
0128 mov word ptr [0xac58], 0 ; _ELayerMode
012e push cx
012f push 0x10
0131 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 308, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
0136 add sp, 4
0139 les bx, ptr [bp - 0xa]
013c mov word ptr es:[bx], 1
0141 jmp 0x891f
0143 nop 
0144 push 0x7e
0146 push 0
0148 push 1
014a jmp 0x8925
014c les bx, ptr [bp - 0xa]
014f mov word ptr es:[bx], 0
0154 push cx
0155 push 0x10
0157 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 346, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
015c add sp, 4
015f mov word ptr [0xac58], 0xffff ; _ELayerMode
0165 push 0x7e
0167 push 0
0169 push 0xf
016b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 366, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0170 add sp, 6
0173 mov es, word ptr [0xbf52]
0177 push word ptr es:[0x9b6c]
017c mov es, word ptr [0xbf54]
0180 push word ptr es:[0x7292]
0185 push 0
0187 push 0
0189 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 396, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _InvalEuMap
018e add sp, 8
0191 leave 
0192 retf 
0193 nop 
0194 cmp word ptr [0xce80], 1 ; _MePlane
0199 jne 0x896f
019b push word ptr [0xce7e] ; _MeLocY
019f push word ptr [0xcd88] ; _MeLocX
01a3 push word ptr [0xce80] ; _MePlane
01a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 426, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _TryMyDropOrLift
01ac add sp, 6
01af inc ax
01b0 je 0x896f
01b2 jmp 0x8a29
01b5 push 0x7e
01b7 push 0
01b9 push 1
01bb jmp 0x8a24
01be cmp word ptr [0xce80], 2 ; _MePlane
01c3 jne 0x896f
01c5 cmp word ptr [0xce7e], 3 ; _MeLocY
01ca jl 0x896f
01cc push 6
01ce nop 
01cf push cs
01d0 call 0x96b0 ; _SetSimCursor
01d3 add sp, 2
01d6 push 1
01d8 push 0x10
01da mov es, word ptr [0xbf72]
01de mov bx, word ptr [0xcf50] ; _MeDir
01e2 xor bl, 4
01e5 mov al, byte ptr es:[bx + 8]
01ea cwde 
01eb shl ax, 1
01ed add ax, word ptr [0xce7e] ; _MeLocY
01f1 push ax
01f2 mov es, word ptr [0xbf70]
01f6 mov al, byte ptr es:[bx]
01fb cwde 
01fc shl ax, 1
01fe add ax, word ptr [0xcd88] ; _MeLocX
0202 push ax
0203 push word ptr [0xce80] ; _MePlane
0207 nop 
0208 push cs
0209 call 0x739e ; _YellowBirth
020c add sp, 0xa
020f leave 
0210 retf 
0211 nop 
0212 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 533, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _TargetAnt
0217 leave 
0218 retf 
0219 nop 
021a mov bx, 0x7d60
021d mov es, word ptr [0xbf36]
0221 mov word ptr [bp - 0xe], bx
0224 mov word ptr [bp - 0xc], es
0227 cmp word ptr es:[bx], 7
022b je 0x8a07
022d mov word ptr es:[bx], 7
0232 push 0x7e
0234 push 0x2b77
0237 jmp 0x8a11
0239 nop 
023a mov bx, 0x7d60
023d mov es, word ptr [0xbf36]
0241 mov word ptr [bp - 0xe], bx
0244 mov word ptr [bp - 0xc], es
0247 cmp word ptr es:[bx], 8
024b jne 0x8a16
024d mov word ptr es:[bx], 0
0252 push 0x7e
0254 push 0x56ee
0257 push 2
0259 jmp 0x8a24
025b nop 
025c les bx, ptr [bp - 0xe]
025f mov word ptr es:[bx], 8
0264 push 0x7e
0266 push 0
0268 push 0x29
026a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 621, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
026f leave 
0270 retf 
```

## Known declaration examples

- `extern int near ELayerMode;` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int near ELayerMode;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far InvalEuMap(int a, int b, int columns, int rows);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near MeDir;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeDir;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocX;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocY;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern int near rootWnd;` — src/recovered/DoWinHelp.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_ClearBookmarks-ffba50efd3.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_DoUserButtonUpdate-cf874c4e35.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetAlarmDropState', 'offset': 33996, 'source': None, 'size': 149}
- {'symbol': '_YellowCommandKey', 'offset': 34146, 'source': None, 'size': 600}
- {'symbol': '_YellowHelp', 'offset': 35372, 'source': 'src/recovered/wf_YellowHelp-e88c6bf26d.c', 'size': 62}
- {'symbol': '_OpenHistoryWindow', 'offset': 35434, 'source': 'src/recovered/OpenHistoryWindow.c', 'size': 12}
