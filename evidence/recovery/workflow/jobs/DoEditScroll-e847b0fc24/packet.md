# Recovery task _DoEditScroll

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 1047 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 8]
0009 mov word ptr [bp - 2], 0
000e cmp si, 0x114
0012 jne 0x5c8a
0014 push word ptr [bp + 6]
0017 push 0
0019 jmp 0x5c8f
001b nop 
001c push word ptr [bp + 6]
001f push 1
0021 lea ax, [bp - 4]
0024 push ss
0025 push ax
0026 lea ax, [bp - 6]
0029 push ss
002a push ax
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 65}}]
0030 mov ax, word ptr [bp + 0xa]
0033 cmp ax, 7
0036 ja 0x5cbe
0038 shl ax, 1
003a xchg bx, ax
003b jmp word ptr cs:[bx + 0x5cae]
0040 dw offset 0x5cc4
0042 dw offset 0x5dd4
0044 dw offset 0x5eca
0046 dw offset 0x5f04
0048 dw offset 0x5f5c
004a dw offset 0x5f5c
004c dw offset 0x5fd8
004e dw offset 0x5ffe
0050 mov si, word ptr [bp - 2]
0053 jmp 0x6031
0056 cmp si, 0x114
005a je 0x5ccd
005c jmp 0x5d50
005f mov ax, word ptr [bp - 4]
0062 mov es, word ptr [0xbf92]
0066 cmp word ptr es:[0x7d2e], ax
006b jle 0x5cbe
006d push word ptr [bp + 6]
0070 push 0
0072 dec word ptr es:[0x7d2e]
0077 push word ptr es:[0x7d2e]
007c push 1
007e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 62}}]
0083 push 0
0085 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 136, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
008a add sp, 2
008d or ax, ax
008f je 0x5d42
0091 push 0
0093 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 150, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinExposed
0098 add sp, 2
009b or ax, ax
009d je 0x5d42
009f mov es, word ptr [0xbf8a]
00a3 mov word ptr es:[0x8df6], 1
00aa push word ptr [0xcc80] ; _editWidth
00ae push word ptr [0xcd7a] ; _editHeight
00b2 push word ptr [0x1444]
00b6 push word ptr [0x1442]
00ba push word ptr [0x1440]
00be push word ptr [0x143e]
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _EditScrollLeftAsm
00c7 add sp, 0xc
00ca mov si, 1
00cd mov word ptr [0x1456], si ; _scrollBarFlag
00d1 jmp 0x6031
00d4 push 0x6c
00d6 nop 
00d7 push cs
00d8 call 0x5b2c ; _DoEditScrollLine
00db add sp, 2
00de jmp 0x5cbe
00e1 nop 
00e2 mov si, word ptr [bp - 2]
00e5 mov ax, word ptr [bp - 4]
00e8 mov es, word ptr [0xbf92]
00ec cmp word ptr es:[0x7d30], ax
00f1 jg 0x5d64
00f3 jmp 0x6031
00f6 push word ptr [bp + 6]
00f9 push 1
00fb dec word ptr es:[0x7d30]
0100 push word ptr es:[0x7d30]
0105 push 1
0107 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 264, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 62}}]
010c mov si, 1
010f push 0
0111 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 276, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
0116 add sp, 2
0119 or ax, ax
011b je 0x5dc6
011d push 0
011f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 290, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinExposed
0124 add sp, 2
0127 or ax, ax
0129 je 0x5dc6
012b mov es, word ptr [0xbf8a]
012f mov word ptr es:[0x8df6], si
0134 push word ptr [0xcc80] ; _editWidth
0138 push word ptr [0xcd7a] ; _editHeight
013c push word ptr [0x1444]
0140 push word ptr [0x1442]
0144 push word ptr [0x1440]
0148 push word ptr [0x143e]
014c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 335, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _EditScrollUpAsm
0151 add sp, 0xc
0154 jmp 0x5d3b
0157 nop 
0158 push 0x75
015a nop 
015b push cs
015c call 0x5b2c ; _DoEditScrollLine
015f add sp, 2
0162 jmp 0x6031
0165 nop 
0166 mov di, word ptr [bp + 6]
0169 cmp si, 0x114
016d jne 0x5e54
016f mov si, word ptr [bp - 2]
0172 mov ax, word ptr [bp - 6]
0175 mov es, word ptr [0xbf92]
0179 cmp word ptr es:[0x7d2e], ax
017e jl 0x5df1
0180 jmp 0x6031
0183 push di
0184 push 0
0186 inc word ptr es:[0x7d2e]
018b push word ptr es:[0x7d2e]
0190 push 1
0192 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 403, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 62}}]
0197 mov si, 1
019a push 0
019c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 415, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
01a1 add sp, 2
01a4 or ax, ax
01a6 je 0x5e4e
01a8 push 0
01aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 429, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinExposed
01af add sp, 2
01b2 or ax, ax
01b4 je 0x5e4e
01b6 mov es, word ptr [0xbf8a]
01ba mov word ptr es:[0x8df6], si
01bf push word ptr [0xcc80] ; _editWidth
01c3 push word ptr [0xcd7a] ; _editHeight
01c7 push word ptr [0x1444]
01cb push word ptr [0x1442]
01cf push word ptr [0x1440]
01d3 push word ptr [0x143e]
01d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 474, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _EditScrollRightAsm
01dc jmp 0x5dbf
01df nop 
01e0 push 0x72
01e2 jmp 0x5dc8
01e5 nop 
01e6 mov si, word ptr [bp - 2]
01e9 mov ax, word ptr [bp - 6]
01ec mov es, word ptr [0xbf92]
01f0 cmp word ptr es:[0x7d30], ax
01f5 jl 0x5e68
01f7 jmp 0x6031
01fa push di
01fb push 1
01fd inc word ptr es:[0x7d30]
0202 push word ptr es:[0x7d30]
0207 push 1
0209 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 522, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 62}}]
020e mov si, 1
0211 push 0
0213 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 534, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
0218 add sp, 2
021b or ax, ax
021d je 0x5ec4
021f push 0
0221 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 548, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinExposed
0226 add sp, 2
0229 or ax, ax
022b je 0x5ec4
022d mov es, word ptr [0xbf8a]
0231 mov word ptr es:[0x8df6], si
0236 push word ptr [0xcc80] ; _editWidth
023a push word ptr [0xcd7a] ; _editHeight
023e push word ptr [0x1444]
0242 push word ptr [0x1442]
0246 push word ptr [0x1440]
024a push word ptr [0x143e]
024e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 593, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _EditScrollDownAsm
0253 jmp 0x5dbf
0256 push 0x64
0258 jmp 0x5dc8
025b nop 
025c cmp si, 0x114
0260 jne 0x5eea
0262 mov <resolved loader operand; see bindings> ; [{'operand_offset': 611, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0265 mov es, ax
0267 mov ax, word ptr [bp - 4]
026a mov cx, word ptr [0xcc80] ; _editWidth
026e sub word ptr es:[0x7d2e], cx
0273 cmp word ptr es:[0x7d2e], ax
0278 jge 0x5f26
027a jmp 0x5f22
027c mov <resolved loader operand; see bindings> ; [{'operand_offset': 637, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
027f mov es, ax
0281 mov ax, word ptr [bp - 4]
0284 mov cx, word ptr [0xcd7a] ; _editHeight
0288 sub word ptr es:[0x7d30], cx
028d cmp word ptr es:[0x7d30], ax
0292 jge 0x5f54
0294 jmp 0x5f50
0296 cmp si, 0x114
029a jne 0x5f38
029c mov <resolved loader operand; see bindings> ; [{'operand_offset': 669, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
029f mov es, ax
02a1 mov ax, word ptr [bp - 6]
02a4 mov cx, word ptr [0xcc80] ; _editWidth
02a8 add word ptr es:[0x7d2e], cx
02ad cmp word ptr es:[0x7d2e], ax
02b2 jle 0x5f26
02b4 mov word ptr es:[0x7d2e], ax
02b8 push word ptr [bp + 6]
02bb push 0
02bd mov es, word ptr [0xbf92]
02c1 push word ptr es:[0x7d2e]
02c6 jmp 0x6027
02c9 nop 
02ca mov <resolved loader operand; see bindings> ; [{'operand_offset': 715, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
02cd mov es, ax
02cf mov ax, word ptr [bp - 6]
02d2 mov cx, word ptr [0xcd7a] ; _editHeight
02d6 add word ptr es:[0x7d30], cx
02db cmp word ptr es:[0x7d30], ax
02e0 jle 0x5f54
02e2 mov word ptr es:[0x7d30], ax
02e6 push word ptr [bp + 6]
02e9 push 1
02eb jmp 0x601e
02ee mov bx, word ptr [bp + 0xa]
02f1 mov <resolved loader operand; see bindings> ; [{'operand_offset': 754, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
02f4 mov es, ax
02f6 cmp word ptr es:[0x85f2], 0
02fc jne 0x5f71
02fe cmp bx, 4
0301 jne 0x5f8c
0303 cmp si, 0x114
0307 jne 0x5fa8
0309 mov <resolved loader operand; see bindings> ; [{'operand_offset': 778, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
030c mov es, ax
030e mov ax, word ptr [bp + 0xc]
0311 cmp word ptr es:[0x7d2e], ax
0316 je 0x5f94
0318 mov si, 1
031b jmp 0x5f96
031d nop 
031e mov si, word ptr [bp - 2]
0321 push ss
0322 pop ds
0323 jmp 0x6031
0326 xor si, si
0328 mov word ptr es:[0x7d2e], ax
032c cmp bx, 4
032f jne 0x5f8f
0331 push ss
0332 pop ds
0333 push word ptr [bp + 6]
0336 push 0
0338 jmp 0x5fce
033a push ss
033b pop ds
033c mov <resolved loader operand; see bindings> ; [{'operand_offset': 829, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
033f mov es, ax
0341 mov ax, word ptr [bp + 0xc]
0344 cmp word ptr es:[0x7d30], ax
0349 je 0x5fbe
034b mov si, 1
034e jmp 0x5fc0
0350 xor si, si
0352 mov word ptr es:[0x7d30], ax
0356 cmp bx, 4
0359 jne 0x6031
035b push word ptr [bp + 6]
035e push 1
0360 push ax
0361 push 1
0363 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 868, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 62}}]
0368 jmp 0x6031
036a mov di, word ptr [bp + 6]
036d mov ax, word ptr [bp - 4]
0370 mov es, word ptr [0xbf92]
0374 mov word ptr es:[0x7d30], ax
0378 mov word ptr es:[0x7d2e], ax
037c push di
037d push 1
037f push ax
0380 push 1
0382 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 899, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 62}}]
0387 push di
0388 push 0
038a push word ptr [bp - 4]
038d jmp 0x6027
038f nop 
0390 mov di, word ptr [bp + 6]
0393 mov ax, word ptr [bp - 6]
0396 mov es, word ptr [0xbf92]
039a mov word ptr es:[0x7d30], ax
039e mov word ptr es:[0x7d2e], ax
03a2 push di
03a3 push 1
03a5 push ax
03a6 push 1
03a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 937, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 62}}]
03ad push di
03ae push 0
03b0 mov es, word ptr [0xbf92]
03b4 push word ptr es:[0x7d30]
03b9 push 1
03bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 956, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 62}}]
03c0 mov si, 1
03c3 or si, si
03c5 je 0x6064
03c7 nop 
03c8 push cs
03c9 call 0x11e0 ; _UpdateEdit
03cc push 0x100
03cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 978, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
03d4 add sp, 2
03d7 or ax, ax
03d9 je 0x6064
03db push word ptr [0xbca8]
03df lcall <resolved loader operand; see bindings> ; [{'operand_offset': 994, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
03e4 add sp, 2
03e7 nop 
03e8 push cs
03e9 call 0xc70c ; _EraseMapCursor
03ec nop 
03ed push cs
03ee call 0xc652 ; _DrawMapCursor
03f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1012, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
03f6 mov word ptr [0x1456], 0 ; _scrollBarFlag
03fc mov es, word ptr [0xc07e]
0400 cmp word ptr es:[0x85ee], 0x32
0406 jne 0x6081
0408 mov es, word ptr [0xc080]
040c mov word ptr es:[0x9fb0], 1
0413 pop si
0414 pop di
0415 leave 
0416 retf 
```

## Known declaration examples

- `extern void far DrawMapCursor(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far UpdateEdit(void);` — src/recovered/DoEditUpdateDraw.c
- `extern void far UpdateEdit(void);` — src/recovered/ForceUpdateEdit.c
- `extern void far UpdateEdit(void);` — src/recovered/UpdateEditWindow.c
- `extern int near editHeight;` — src/recovered/BalloonIsVisible.c
- `extern int near editHeight;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editHeight;` — src/recovered/wf_EggBalloons-c5deff5dd7.c
- `extern int near editWidth;` — src/recovered/BalloonIsVisible.c
- `extern int near editWidth;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editWidth;` — src/recovered/wf_EggBalloons-c5deff5dd7.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int near scrollBarFlag;` — src/recovered/InvalidUpdateEdit.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawBalloons', 'offset': 22442, 'source': None, 'size': 897}
- {'symbol': '_DoEditScrollLine', 'offset': 23340, 'source': None, 'size': 322}
- {'symbol': '_ResetEditScrollRange', 'offset': 24710, 'source': None, 'size': 230}
- {'symbol': '_EditScentMenu', 'offset': 26462, 'source': 'src/recovered/wf_EditScentMenu-abd185cb06.c', 'size': 103}
