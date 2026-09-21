# Recovery task _ExpDig

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 997 bytes.

```asm
0000 enter 0x22, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc270]
000a mov al, byte ptr es:[0x8602]
000e cwde 
000f mov di, ax
0011 push 0x11
0013 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0018 test ah, 0x80
001b je 0x758e
001d xor di, 1
0020 mov word ptr [bp - 8], di
0023 mov si, word ptr [bp + 6]
0026 mov cx, word ptr [bp + 8]
0029 mov ax, 0x72c8
002c mov <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
002f mov word ptr [bp - 0xc], ax
0032 mov word ptr [bp - 0xa], dx
0035 mov ax, 0x8104
0038 mov <resolved loader operand; see bindings> ; [{'operand_offset': 57, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
003b mov word ptr [bp - 0x10], ax
003e mov word ptr [bp - 0xe], dx
0041 mov ax, 0x811a
0044 mov <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0047 mov word ptr [bp - 0x14], ax
004a mov word ptr [bp - 0x12], dx
004d mov ax, 0x7a56
0050 mov <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0053 mov word ptr [bp - 0x18], ax
0056 mov word ptr [bp - 0x16], dx
0059 mov ax, 0x9ddc
005c mov <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
005f mov word ptr [bp - 0x1c], ax
0062 mov word ptr [bp - 0x1a], dx
0065 mov ax, 0x9de2
0068 mov <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
006b mov word ptr [bp - 0x20], ax
006e mov word ptr [bp - 0x1e], dx
0071 mov di, cx
0073 cmp word ptr [bp - 8], 0
0077 je 0x75ea
0079 jmp 0x76b4
007c mov ax, word ptr [0xcc76] ; _MapPlane
007f or ax, ax
0081 jge 0x75f4
0083 jmp 0x791e
0086 jno 0x75f9
0088 jmp 0x791e
008b dec ax
008c jle 0x7606
008e dec ax
008f je 0x7646
0091 dec ax
0092 je 0x7678
0094 jmp 0x791e
0097 nop 
0098 push di
0099 push si
009a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 157, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigMyNewHole
009f add sp, 4
00a2 or ax, ax
00a4 je 0x7617
00a6 jmp 0x76aa
00a9 push 0x7e
00ab push ax
00ac push 1
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00b3 add sp, 6
00b6 push 1
00b8 push 0
00ba push 0x78
00bc mov es, word ptr [0xc276]
00c0 les bx, ptr es:[0x737a]
00c5 push word ptr es:[bx + 0x5a]
00c9 push word ptr es:[bx + 0x58]
00cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 208, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _EditMessage
00d2 add sp, 0xa
00d5 jmp 0x791e
00d8 push di
00d9 push si
00da push 2
00dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 223, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItDigable
00e1 add sp, 6
00e4 or ax, ax
00e6 jne 0x7659
00e8 jmp 0x791e
00eb or di, di
00ed jne 0x7660
00ef jmp 0x791e
00f2 push di
00f3 push si
00f4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 247, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
00f9 add sp, 4
00fc mov ax, di
00fe dec ax
00ff jne 0x76aa
0101 push si
0102 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MakeNewHoleB
0107 jmp 0x76a7
0109 nop 
010a push di
010b push si
010c push 3
010e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItDigable
0113 add sp, 6
0116 or ax, ax
0118 jne 0x768b
011a jmp 0x791e
011d or di, di
011f jne 0x7692
0121 jmp 0x791e
0124 push di
0125 push si
0126 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 297, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
012b add sp, 4
012e mov ax, di
0130 dec ax
0131 jne 0x76aa
0133 push si
0134 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MakeNewHoleR
0139 add sp, 2
013c push 0x7e
013e push 0
0140 push 0x13
0142 jmp 0x7916
0145 nop 
0146 mov ax, word ptr [0xcc76] ; _MapPlane
0149 or ax, ax
014b jge 0x76be
014d jmp 0x791e
0150 jno 0x76c3
0152 jmp 0x791e
0155 dec ax
0156 jle 0x76d2
0158 dec ax
0159 je 0x76fc
015b dec ax
015c jne 0x76cf
015e jmp 0x7808
0161 jmp 0x791e
0164 push 0x7e
0166 push 0
0168 push 1
016a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 365, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
016f add sp, 6
0172 push 1
0174 push 0
0176 push 0xb4
0179 mov es, word ptr [0xc276]
017d les bx, ptr es:[0x737a]
0182 push word ptr es:[bx + 0x56]
0186 push word ptr es:[bx + 0x54]
018a jmp 0x763b
018d nop 
018e push di
018f push si
0190 push 2
0192 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 405, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItDigable
0197 add sp, 6
019a or ax, ax
019c je 0x770f
019e jmp 0x791e
01a1 or di, di
01a3 jne 0x7716
01a5 jmp 0x791e
01a8 mov bx, si
01aa shl bx, 6
01ad add bx, di
01af mov word ptr [bp - 0x22], bx
01b2 cmp byte ptr [bx - 0x7718], 0
01b7 je 0x7770
01b9 mov es, word ptr [0xc278]
01bd mov cx, word ptr es:[0x99d4]
01c2 or cx, cx
01c4 je 0x7768
01c6 mov word ptr [bp - 6], si
01c9 mov si, cx
01cb mov cx, word ptr [bp - 6]
01ce mov <resolved loader operand; see bindings> ; [{'operand_offset': 463, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01d1 mov ds, ax
01d3 dec si
01d4 cmp byte ptr [si + 0x3d18], 0
01d9 je 0x775f
01db mov al, byte ptr [si + 0x3736]
01df sub ah, ah
01e1 cmp ax, cx
01e3 jne 0x775f
01e5 mov al, byte ptr [si + 0x392c]
01e9 cmp ax, di
01eb jne 0x775f
01ed mov byte ptr [si + 0x3d18], ah
01f1 or si, si
01f3 jne 0x7741
01f5 mov si, word ptr [bp - 6]
01f8 push ss
01f9 pop ds
01fa mov bx, word ptr [bp - 0x22]
01fd mov byte ptr [bx - 0x7718], 0
0202 mov byte ptr [bx + 0x48e8], 0x2e
0207 mov byte ptr [bx - 0x7718], 0
020c les bx, ptr [bp - 0xc]
020f cmp word ptr es:[bx], 1
0213 jle 0x77c3
0215 mov ax, si
0217 cdq 
0218 les bx, ptr [bp - 0x10]
021b sub word ptr es:[bx], ax
021e sbb word ptr es:[bx + 2], dx
0222 cmp word ptr es:[bx + 2], 0
0227 jge 0x77a0
0229 sub ax, ax
022b mov word ptr es:[bx + 2], ax
022f mov word ptr es:[bx], ax
0232 mov ax, di
0234 cdq 
0235 les bx, ptr [bp - 0x14]
0238 sub word ptr es:[bx], ax
023b sbb word ptr es:[bx + 2], dx
023f cmp word ptr es:[bx + 2], 0
0244 jge 0x77bd
0246 sub ax, ax
0248 mov word ptr es:[bx + 2], ax
024c mov word ptr es:[bx], ax
024f les bx, ptr [bp - 0xc]
0252 dec word ptr es:[bx]
0255 lea ax, [di - 1]
0258 push ax
0259 push si
025a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 605, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SmoothEdgesB
025f add sp, 4
0262 push di
0263 lea ax, [si + 1]
0266 push ax
0267 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 618, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SmoothEdgesB
026c add sp, 4
026f lea ax, [di + 1]
0272 push ax
0273 push si
0274 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 631, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SmoothEdgesB
0279 add sp, 4
027c push di
027d lea ax, [si - 1]
0280 push ax
0281 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 644, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SmoothEdgesB
0286 add sp, 4
0289 mov es, word ptr [0xc27a]
028d mov bx, word ptr [bp - 0x22]
0290 mov byte ptr es:[bx + 0x3a4], 0
0296 jmp 0x7910
0299 nop 
029a push di
029b push si
029c push 3
029e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 673, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItDigable
02a3 add sp, 6
02a6 or ax, ax
02a8 je 0x781b
02aa jmp 0x791e
02ad or di, di
02af jne 0x7822
02b1 jmp 0x791e
02b4 mov bx, si
02b6 shl bx, 6
02b9 add bx, di
02bb mov word ptr [bp - 0x22], bx
02be cmp byte ptr [bx - 0x6718], 0
02c3 je 0x787c
02c5 mov es, word ptr [0xc27c]
02c9 mov cx, word ptr es:[0x72cc]
02ce or cx, cx
02d0 je 0x7874
02d2 mov word ptr [bp - 6], si
02d5 mov si, cx
02d7 mov cx, word ptr [bp - 6]
02da mov <resolved loader operand; see bindings> ; [{'operand_offset': 731, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
02dd mov ds, ax
02df dec si
02e0 cmp byte ptr [si + 0x46e6], 0
02e5 je 0x786b
02e7 mov al, byte ptr [si + 0x4104]
02eb sub ah, ah
02ed cmp ax, cx
02ef jne 0x786b
02f1 mov al, byte ptr [si + 0x42fa]
02f5 cmp ax, di
02f7 jne 0x786b
02f9 mov byte ptr [si + 0x46e6], ah
02fd or si, si
02ff jne 0x784d
0301 mov si, word ptr [bp - 6]
0304 push ss
0305 pop ds
0306 mov bx, word ptr [bp - 0x22]
0309 mov byte ptr [bx - 0x6718], 0
030e mov byte ptr [bx + 0x58e8], 0x2e
0313 mov byte ptr [bx - 0x6718], 0
0318 les bx, ptr [bp - 0x18]
031b cmp word ptr es:[bx], 1
031f jle 0x78cf
0321 mov ax, si
0323 cdq 
0324 les bx, ptr [bp - 0x1c]
0327 sub word ptr es:[bx], ax
032a sbb word ptr es:[bx + 2], dx
032e cmp word ptr es:[bx + 2], 0
0333 jge 0x78ac
0335 sub ax, ax
0337 mov word ptr es:[bx + 2], ax
033b mov word ptr es:[bx], ax
033e mov ax, di
0340 cdq 
0341 les bx, ptr [bp - 0x20]
0344 sub word ptr es:[bx], ax
0347 sbb word ptr es:[bx + 2], dx
034b cmp word ptr es:[bx + 2], 0
0350 jge 0x78c9
0352 sub ax, ax
0354 mov word ptr es:[bx + 2], ax
0358 mov word ptr es:[bx], ax
035b les bx, ptr [bp - 0x18]
035e dec word ptr es:[bx]
0361 lea ax, [di - 1]
0364 push ax
0365 push si
0366 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 873, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SmoothEdgesR
036b add sp, 4
036e push di
036f lea ax, [si + 1]
0372 push ax
0373 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 886, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SmoothEdgesR
0378 add sp, 4
037b lea ax, [di + 1]
037e push ax
037f push si
0380 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 899, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SmoothEdgesR
0385 add sp, 4
0388 push di
0389 lea ax, [si - 1]
038c push ax
038d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 912, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SmoothEdgesR
0392 add sp, 4
0395 mov es, word ptr [0xc27a]
0399 mov bx, word ptr [bp - 0x22]
039c mov byte ptr es:[bx + 0x13a4], 0
03a2 push 0x7e
03a4 push 0
03a6 push 0x12
03a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 939, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
03ad add sp, 6
03b0 push word ptr [bp + 0xc]
03b3 push word ptr [bp + 0xa]
03b6 push di
03b7 push si
03b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 955, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
03bd add sp, 8
03c0 mov bx, ax
03c2 mov es, word ptr [0xc272]
03c6 mov al, byte ptr es:[bx + 0x10]
03cb cwde 
03cc add si, ax
03ce mov es, word ptr [0xc274]
03d2 mov al, byte ptr es:[bx + 0x1a]
03d7 cwde 
03d8 add di, ax
03da or bx, bx
03dc je 0x794f
03de jmp 0x75e1
03e1 pop si
03e2 pop di
03e3 leave 
03e4 retf 
```

## Known declaration examples

- `extern void far DigTileB(int x, int y);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far DigTileR(int x, int y);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern void far SmoothEdgesB(int x, int y);` — src/recovered/wf_FillDirtB-b73109489f.c
- `extern void far SmoothEdgesR(int x, int y);` — src/recovered/wf_FillDirtR-d16ac84868.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ReDrawMapEdit', 'offset': 29668, 'source': 'src/recovered/wf_ReDrawMapEdit-0c32a1284f.c', 'size': 107}
- {'symbol': '_DropWall', 'offset': 29776, 'source': None, 'size': 285}
- {'symbol': '_ClearLifeB', 'offset': 31060, 'source': 'src/recovered/wf_ClearLifeB-f9a6e1c57a.c', 'size': 83}
- {'symbol': '_ClearLifeR', 'offset': 31144, 'source': 'src/recovered/wf_ClearLifeR-d74962e731.c', 'size': 83}
