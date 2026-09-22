# Recovery task _YellowCommandKey

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 600 bytes.

```asm
0000 enter 2, 0
0004 mov word ptr [bp - 2], 1
0009 mov ax, word ptr [bp + 6]
000c cmp ax, 0x78
000f jne 0x8576
0011 jmp 0x87ae
0014 ja 0x85ee
0016 cmp al, 0x4a
0018 jne 0x857f
001a jmp 0x878e
001d jg 0x85b8
001f cmp al, 0x31
0021 jne 0x8588
0023 jmp 0x871e
0026 jg 0x85a0
0028 sub al, 8
002a je 0x85f8
002c sub al, 0x1c
002e jne 0x8595
0030 jmp 0x8706
0033 sub al, 0xc
0035 jne 0x859c
0037 jmp 0x8718
003a jmp 0x85ee
003c nop 
003d nop 
003e sub al, 0x32
0040 jne 0x85a7
0042 jmp 0x874a
0045 dec al
0047 jne 0x85ae
0049 jmp 0x8786
004c dec al
004e jne 0x85b5
0050 jmp 0x878a
0053 jmp 0x85ee
0055 nop 
0056 sub al, 0x58
0058 cmp ax, 0x12
005b ja 0x85ee
005d shl ax, 1
005f xchg bx, ax
0060 jmp word ptr cs:[bx - 0x7a38]
0065 nop 
0066 dw offset 0x87ae
0068 dw offset 0x85ee
006a dw offset 0x85ee
006c dw offset 0x85ee
006e dw offset 0x85ee
0070 dw offset 0x85ee
0072 dw offset 0x85ee
0074 dw offset 0x85ee
0076 dw offset 0x8718
0078 dw offset 0x871e
007a dw offset 0x874a
007c dw offset 0x8786
007e dw offset 0x878a
0080 dw offset 0x85ee
0082 dw offset 0x85ee
0084 dw offset 0x85ee
0086 dw offset 0x85ee
0088 dw offset 0x85ee
008a dw offset 0x878e
008c mov word ptr [bp - 2], 0
0091 mov ax, word ptr [bp - 2]
0094 leave 
0095 retf 
0096 push 0x10
0098 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 153, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
009d test ah, 0x80
00a0 je 0x860e
00a2 nop 
00a3 push cs
00a4 call 0xa764 ; _GotoMyAnt
00a7 mov ax, word ptr [bp - 2]
00aa leave 
00ab retf 
00ac mov <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00af mov es, ax
00b1 cmp word ptr es:[0x9fe8], 0
00b7 je 0x861e
00b9 jmp 0x86aa
00bc mov <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00bf mov es, ax
00c1 cmp word ptr es:[0x7d24], 0
00c7 jne 0x862e
00c9 jmp 0x86d3
00cc mov ax, word ptr ss:[0xce80]
00d0 mov <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00d3 mov es, cx
00d5 mov word ptr es:[0x9be0], ax
00d9 mov ax, word ptr ss:[0xcd88]
00dd mov <resolved loader operand; see bindings> ; [{'operand_offset': 222, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00e0 mov es, cx
00e2 mov word ptr es:[0xa0d6], ax
00e6 mov <resolved loader operand; see bindings> ; [{'operand_offset': 231, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00e9 mov es, cx
00eb mov word ptr es:[0x80c6], ax
00ef mov ax, word ptr ss:[0xce7e]
00f3 mov <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00f6 mov es, cx
00f8 mov word ptr es:[0xa0da], ax
00fc mov <resolved loader operand; see bindings> ; [{'operand_offset': 253, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00ff mov es, cx
0101 mov word ptr es:[0x80d2], ax
0105 xor ax, ax
0107 mov <resolved loader operand; see bindings> ; [{'operand_offset': 264, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
010a mov es, cx
010c mov word ptr es:[0x9bc4], ax
0110 mov <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0113 mov es, cx
0115 mov word ptr es:[0x7d24], ax
0119 mov <resolved loader operand; see bindings> ; [{'operand_offset': 282, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
011c mov es, cx
011e mov word ptr es:[0x9fe2], ax
0122 mov <resolved loader operand; see bindings> ; [{'operand_offset': 291, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0125 mov es, cx
0127 mov word ptr es:[0x80aa], ax
012b mov <resolved loader operand; see bindings> ; [{'operand_offset': 300, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
012e mov es, cx
0130 mov word ptr es:[0x9c7e], ax
0134 mov <resolved loader operand; see bindings> ; [{'operand_offset': 309, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0137 mov es, ax
0139 mov word ptr es:[0x72e4], 0xfffe
0140 push ss
0141 pop ds
0142 mov ax, word ptr [bp - 2]
0145 leave 
0146 retf 
0147 nop 
0148 cmp word ptr es:[0x9fe8], 1
014e jne 0x86a2
0150 mov bx, word ptr ss:[0xcd88]
0155 mov <resolved loader operand; see bindings> ; [{'operand_offset': 342, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0158 mov es, ax
015a cmp word ptr es:[0x78b8], bx
015f jne 0x86e0
0161 mov <resolved loader operand; see bindings> ; [{'operand_offset': 354, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0164 mov es, ax
0166 mov ax, word ptr es:[0x78ea]
016a cmp word ptr ss:[0xce7e], ax
016f jne 0x86e0
0171 push ss
0172 pop ds
0173 nop 
0174 push cs
0175 call 0xa6e0 ; _CenterAnt
0178 mov ax, word ptr [bp - 2]
017b leave 
017c retf 
017d nop 
017e push ss
017f pop ds
0180 mov es, word ptr [0xbf32]
0184 mov word ptr es:[0x78b8], bx
0189 mov ax, word ptr [0xce7e] ; _MeLocY
018c mov es, word ptr [0xbf34]
0190 mov word ptr es:[0x78ea], ax
0194 mov es, word ptr [0xbf30]
0198 mov word ptr es:[0x729e], 0
019f mov ax, word ptr [bp - 2]
01a2 leave 
01a3 retf 
01a4 push 0x7e
01a6 push 0
01a8 push 0xf
01aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 429, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
01af add sp, 6
01b2 jmp 0x8604
01b5 nop 
01b6 push 7
01b8 jmp 0x87b0
01bb nop 
01bc mov es, word ptr [0xbf0c]
01c0 cmp word ptr es:[0x9fe8], 0
01c6 jne 0x8746
01c8 cmp word ptr [0xcc84], 0x40 ; _MeType
01cd jne 0x8742
01cf mov es, word ptr [0xbf44]
01d3 cmp word ptr es:[0x8a6c], 0
01d9 jne 0x8742
01db push 8
01dd jmp 0x87b0
01df nop 
01e0 push 1
01e2 jmp 0x87b0
01e4 push 0xa
01e6 jmp 0x87b0
01e8 mov es, word ptr [0xbf0c]
01ec cmp word ptr es:[0x9fe8], 0
01f2 jne 0x8782
01f4 cmp word ptr [0xcc84], 0x40 ; _MeType
01f9 jne 0x876e
01fb mov es, word ptr [0xbf44]
01ff cmp word ptr es:[0x8a6c], 0
0205 jne 0x876e
0207 push 9
0209 jmp 0x87b0
020b nop 
020c push 0x11
020e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 527, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0213 test ah, 0x80
0216 je 0x877e
0218 push 3
021a jmp 0x87b0
021c push 2
021e jmp 0x87b0
0220 push 0xb
0222 jmp 0x87b0
0224 push 4
0226 jmp 0x87b0
0228 push 5
022a jmp 0x87b0
022c push 9
022e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 559, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0233 test ah, 0x80
0236 jne 0x879d
0238 jmp 0x85ee
023b mov es, word ptr [0xbf0c]
023f cmp word ptr es:[0x9fe8], 1
0245 jne 0x87b5
0247 push 0xc
0249 jmp 0x87b0
024b nop 
024c push 6
024e nop 
024f push cs
0250 call 0x87ba ; _YellowCommand
0253 mov ax, word ptr [bp - 2]
0256 leave 
0257 retf 
```

## Known declaration examples

- `extern void far GotoMyAnt(void);` — src/recovered/wf_ProcEditEvent-1e056fd3ba.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocY;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeType;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c
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

- {'symbol': '_DoTroph', 'offset': 33902, 'source': None, 'size': 93}
- {'symbol': '_SetAlarmDropState', 'offset': 33996, 'source': None, 'size': 149}
- {'symbol': '_YellowCommand', 'offset': 34746, 'source': None, 'size': 625}
- {'symbol': '_YellowHelp', 'offset': 35372, 'source': 'src/recovered/wf_YellowHelp-e88c6bf26d.c', 'size': 62}
