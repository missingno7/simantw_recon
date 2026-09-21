# Recovery task _DropWall

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 285 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov di, word ptr [bp + 8]
000c push di
000d push si
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0013 add sp, 4
0016 or ax, ax
0018 jne 0x746d
001a jmp 0x7569
001d push 0x11
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 32, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0024 test ah, 0x80
0027 je 0x74b0
0029 mov bx, si
002b shl bx, 6
002e add bx, di
0030 mov word ptr [bp - 4], bx
0033 cmp byte ptr [bx + 0x28e8], 0x50
0038 jbe 0x74a2
003a cmp byte ptr [bx + 0x28e8], 0x68
003f jae 0x74a2
0041 push 0x10
0043 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 70, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0048 add sp, 2
004b mov bx, word ptr [bp - 4]
004e mov byte ptr [bx + 0x28e8], al
0052 push di
0053 push si
0054 nop 
0055 push cs
0056 call 0x805a ; _ConnectAll
0059 add sp, 4
005c jmp 0x7532
005f nop 
0060 mov es, word ptr [0xc270]
0064 cmp byte ptr es:[0x8601], 0
006a jne 0x74ec
006c mov bx, si
006e shl bx, 6
0071 add bx, di
0073 mov word ptr [bp - 4], bx
0076 cmp byte ptr [bx + 0x28e8], 0x50
007b jae 0x74d9
007d cmp byte ptr [bx + 0x68e8], 0
0082 jne 0x74d9
0084 mov byte ptr [bx + 0x28e8], 0x60
0089 push di
008a push si
008b nop 
008c push cs
008d call 0x805a ; _ConnectAll
0090 add sp, 4
0093 push 0x7e
0095 push 0
0097 push 0x28
0099 jmp 0x752a
009b nop 
009c mov bx, si
009e shl bx, 6
00a1 add bx, di
00a3 mov word ptr [bp - 4], bx
00a6 cmp byte ptr [bx + 0x28e8], 0x50
00ab jae 0x7517
00ad cmp byte ptr [bx + 0x68e8], 0
00b2 jne 0x7517
00b4 push 3
00b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 185, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00bb add sp, 2
00be add al, 0x51
00c0 mov bx, word ptr [bp - 4]
00c3 mov byte ptr [bx + 0x28e8], al
00c7 push 0x7e
00c9 push 0x2710
00cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 207, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00d1 add sp, 2
00d4 add ax, 0x7d0
00d7 push ax
00d8 push 0xa
00da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 221, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00df add sp, 6
00e2 push word ptr [bp + 0xc]
00e5 push word ptr [bp + 0xa]
00e8 push di
00e9 push si
00ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 237, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
00ef add sp, 8
00f2 mov bx, ax
00f4 mov es, word ptr [0xc272]
00f8 mov al, byte ptr es:[bx + 0x10]
00fd or al, al
00ff je 0x7556
0101 cwde 
0102 add si, ax
0104 jmp 0x7562
0106 mov es, word ptr [0xc274]
010a mov al, byte ptr es:[bx + 0x1a]
010f cwde 
0110 add di, ax
0112 or bx, bx
0114 je 0x7569
0116 jmp 0x745c
0119 pop si
011a pop di
011b leave 
011c retf 
```

## Known declaration examples

- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_IsPillDead-8cef0d554b.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoTool', 'offset': 29310, 'source': None, 'size': None}
- {'symbol': '_ReDrawMapEdit', 'offset': 29668, 'source': 'src/recovered/wf_ReDrawMapEdit-0c32a1284f.c', 'size': 107}
- {'symbol': '_ExpDig', 'offset': 30062, 'source': None, 'size': 997}
- {'symbol': '_ClearLifeB', 'offset': 31060, 'source': 'src/recovered/wf_ClearLifeB-f9a6e1c57a.c', 'size': 83}
