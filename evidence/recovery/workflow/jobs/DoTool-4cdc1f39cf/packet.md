# Recovery task _DoTool

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 358 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc26c]
000a mov ax, word ptr es:[0x79e2]
000e cmp ax, 6
0011 jbe 0x7294
0013 jmp 0x73e0
0016 shl ax, 1
0018 xchg bx, ax
0019 jmp word ptr cs:[bx + 0x729c]
001e dw offset 0x72aa
0020 dw offset 0x72d8
0022 dw offset 0x7308
0024 dw offset 0x7324
0026 dw offset 0x7332
0028 dw offset 0x73c4
002a dw offset 0x73d2
002c mov di, word ptr [bp + 8]
002f mov si, word ptr [bp + 6]
0032 push di
0033 push si
0034 push word ptr [0xcc76] ; _MapPlane
0038 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetLife
003d add sp, 6
0040 or ax, ax
0042 jne 0x72c5
0044 jmp 0x73e0
0047 push word ptr [0xcc76] ; _MapPlane
004b push di
004c push si
004d nop 
004e push cs
004f call 0x6b4c ; _MagnifyMenu
0052 add sp, 6
0055 pop si
0056 pop di
0057 leave 
0058 retf 
0059 nop 
005a mov dx, word ptr [0xcc76] ; _MapPlane
005e cmp dx, 1
0061 je 0x72e8
0063 or dx, dx
0065 je 0x72e8
0067 jmp 0x73e0
006a push word ptr [bp + 8]
006d push word ptr [bp + 6]
0070 mov es, word ptr [0xc25e]
0074 push word ptr es:[0x7d48]
0079 push word ptr es:[0x7d46]
007e nop 
007f push cs
0080 call 0x7450 ; _DropWall
0083 add sp, 8
0086 pop si
0087 pop di
0088 leave 
0089 retf 
008a push word ptr [bp + 8]
008d push word ptr [bp + 6]
0090 mov es, word ptr [0xc25e]
0094 push word ptr es:[0x7d48]
0099 push word ptr es:[0x7d46]
009e nop 
009f push cs
00a0 call 0x756e ; _ExpDig
00a3 jmp 0x7301
00a5 nop 
00a6 push word ptr [bp + 8]
00a9 push word ptr [bp + 6]
00ac nop 
00ad push cs
00ae call 0x79fc ; _ExpAddAnt
00b1 jmp 0x73dd
00b4 mov es, word ptr [0xc270]
00b8 cmp byte ptr es:[0x8604], 0
00be jne 0x7362
00c0 push word ptr [bp + 8]
00c3 push word ptr [bp + 6]
00c6 nop 
00c7 push cs
00c8 call 0x7f3a ; _IncFoodHere
00cb add sp, 4
00ce or ax, ax
00d0 jne 0x7353
00d2 jmp 0x73e0
00d5 push 0x7e
00d7 push 0
00d9 push 0x1d
00db lcall <resolved loader operand; see bindings> ; [{'operand_offset': 222, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00e0 jmp 0x72d0
00e3 nop 
00e4 push 0x7e
00e6 push 0
00e8 push 0x20
00ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 237, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00ef add sp, 6
00f2 mov si, 0x14
00f5 mov di, word ptr [bp + 6]
00f8 push 9
00fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 253, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00ff add sp, 2
0102 add ax, di
0104 sub ax, 4
0107 mov word ptr [bp - 2], ax
010a push 9
010c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 271, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0111 add sp, 2
0114 add ax, word ptr [bp + 8]
0117 sub ax, 4
011a mov word ptr [bp - 4], ax
011d push ax
011e push word ptr [bp - 2]
0121 push word ptr [0xcc76] ; _MapPlane
0125 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 296, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidLocation
012a add sp, 6
012d or ax, ax
012f je 0x73bd
0131 push word ptr [bp - 4]
0134 push word ptr [bp - 2]
0137 nop 
0138 push cs
0139 call 0x7f3a ; _IncFoodHere
013c add sp, 4
013f dec si
0140 jne 0x7376
0142 pop si
0143 pop di
0144 leave 
0145 retf 
0146 push word ptr [bp + 8]
0149 push word ptr [bp + 6]
014c nop 
014d push cs
014e call 0x7b9e ; _ExpIncSmell
0151 jmp 0x73dd
0153 nop 
0154 push word ptr [bp + 8]
0157 push word ptr [bp + 6]
015a nop 
015b push cs
015c call 0x7d5c ; _ExpKillAnts
015f add sp, 4
0162 pop si
0163 pop di
0164 leave 
0165 retf 
```

## Known declaration examples

- `extern int far IncFoodHere(int x, int y);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern int far IsValidLocation(int plane, int x, int y);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoExpMenu', 'offset': 28386, 'source': None, 'size': 320}
- {'symbol': '_processExp', 'offset': 28706, 'source': None, 'size': 604}
- {'symbol': '_ReDrawMapEdit', 'offset': 29668, 'source': 'src/recovered/wf_ReDrawMapEdit-0c32a1284f.c', 'size': 107}
- {'symbol': '_DropWall', 'offset': 29776, 'source': None, 'size': 285}
