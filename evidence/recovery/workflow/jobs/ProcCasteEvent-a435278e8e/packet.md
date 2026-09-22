# Recovery task _ProcCasteEvent

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 881 bytes.

```asm
0000 enter 0x18, 0
0004 push di
0005 push si
0006 push 0x1300
0009 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 12, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
000e add sp, 2
0011 les bx, ptr [bp + 6]
0014 mov ax, word ptr es:[bx + 0xc]
0018 sub ax, 0x1303
001b cmp ax, 0xe
001e jbe 0xbd2b
0020 jmp 0xc070
0023 shl ax, 1
0025 xchg bx, ax
0026 jmp word ptr cs:[bx - 0x42cc]
002b nop 
002c dw offset 0xbd52
002e dw offset 0xbd60
0030 dw offset 0xc050
0032 dw offset 0xbd84
0034 dw offset 0xbd84
0036 dw offset 0xbd84
0038 dw offset 0xc070
003a dw offset 0xc070
003c dw offset 0xc070
003e dw offset 0xc070
0040 dw offset 0xbdec
0042 dw offset 0xc070
0044 dw offset 0xc026
0046 dw offset 0xc026
0048 dw offset 0xc026
004a push 0x130e
004d nop 
004e push cs
004f call 0x5aac ; _DoWinHelp
0052 add sp, 2
0055 jmp 0xc070
0058 mov es, word ptr [0xc13c]
005c cmp word ptr es:[0x8630], 0
0062 je 0xbd6f
0064 jmp 0xc070
0067 mov word ptr es:[0x8630], 1
006e push 4
0070 push 0x1300
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeGroupInvisible
0078 jmp 0xc06d
007b nop 
007c push 0x1305
007f push 3
0081 push 0x1300
0084 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 135, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetGroupSelectedObj
0089 add sp, 6
008c mov <resolved loader operand; see bindings> ; [{'operand_offset': 141, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
008f mov bx, word ptr [0x159e] ; _casteSet
0093 mov cx, bx
0095 shl bx, 1
0097 add bx, cx
0099 shl bx, 1
009b mov es, word ptr [0xc13e]
009f push ds
00a0 lea di, [bx - 0x79c6]
00a4 mov si, 0x9b64
00a7 mov ds, ax
00a9 movsw word ptr es:[di], word ptr [si]
00aa movsw word ptr es:[di], word ptr [si]
00ab movsw word ptr es:[di], word ptr [si]
00ac pop ds
00ad les bx, ptr [bp + 6]
00b0 mov cx, word ptr es:[bx + 0xc]
00b4 sub cx, 0x1306
00b8 mov word ptr [0x159e], cx ; _casteSet
00bc mov dx, 0x9b64
00bf mov bx, cx
00c1 shl cx, 1
00c3 add cx, bx
00c5 shl cx, 1
00c7 add cx, 0x863a
00cb mov <resolved loader operand; see bindings> ; [{'operand_offset': 204, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00ce push ds
00cf mov di, dx
00d1 mov si, cx
00d3 mov es, ax
00d5 mov ds, bx
00d7 movsw word ptr es:[di], word ptr [si]
00d8 movsw word ptr es:[di], word ptr [si]
00d9 movsw word ptr es:[di], word ptr [si]
00da pop ds
00db nop 
00dc push cs
00dd call 0xb7a4 ; _UpdateCasteWindow
00e0 jmp 0xc050
00e3 nop 
00e4 lea ax, [bp - 0x18]
00e7 push ss
00e8 push ax
00e9 push 0x130d
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
00f1 add sp, 6
00f4 mov di, word ptr [bp - 0x16]
00f7 mov ax, word ptr [bp - 0x12]
00fa mov word ptr [bp - 2], ax
00fd mov cx, word ptr [bp - 0x14]
0100 mov word ptr [bp - 0xc], cx
0103 mov dx, word ptr [bp - 0x18]
0106 mov word ptr [bp - 0xa], dx
0109 mov ax, cx
010b add ax, dx
010d cdq 
010e sub ax, dx
0110 sar ax, 1
0112 mov word ptr [bp - 4], ax
0115 les bx, ptr [bp + 6]
0118 mov ax, word ptr es:[bx + 8]
011c mov word ptr [bp - 6], ax
011f mov si, word ptr es:[bx + 0xa]
0123 mov ax, word ptr [bp - 0x12]
0126 cmp si, ax
0128 jl 0xbe35
012a jmp 0xbeb6
012d cmp si, di
012f jl 0xbeb6
0131 mov ax, word ptr [bp - 2]
0134 sub ax, di
0136 cdq 
0137 push dx
0138 push ax
0139 mov ax, word ptr [bp - 0xa]
013c sub ax, word ptr [bp - 4]
013f mov cx, si
0141 sub cx, word ptr [bp - 2]
0144 imul cx
0146 push dx
0147 push ax
0148 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 331, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
014d mov cx, ax
014f mov ax, word ptr [bp - 0xa]
0152 mov bx, dx
0154 cdq 
0155 add cx, ax
0157 adc bx, dx
0159 mov ax, word ptr [bp - 6]
015c cdq 
015d cmp bx, dx
015f jl 0xbe76
0161 jg 0xbe6f
0163 cmp cx, ax
0165 jbe 0xbe76
0167 xor ax, ax
0169 jmp 0xbeae
016b nop 
016c nop 
016d nop 
016e mov ax, di
0170 sub ax, word ptr [bp - 2]
0173 cdq 
0174 push dx
0175 push ax
0176 mov ax, word ptr [bp - 4]
0179 sub ax, word ptr [bp - 0xc]
017c mov cx, si
017e sub cx, di
0180 imul cx
0182 push dx
0183 push ax
0184 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 391, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0189 mov cx, ax
018b mov ax, word ptr [bp - 4]
018e mov bx, dx
0190 cdq 
0191 add cx, ax
0193 adc bx, dx
0195 mov ax, word ptr [bp - 6]
0198 cdq 
0199 cmp bx, dx
019b jg 0xbeab
019d jl 0xbe6f
019f cmp cx, ax
01a1 jb 0xbe6f
01a3 mov ax, 1
01a6 mov word ptr [bp - 8], ax
01a9 mov dx, ax
01ab jmp 0xbeb8
01ad nop 
01ae xor dx, dx
01b0 or dx, dx
01b2 jne 0xbebf
01b4 jmp 0xc070
01b7 mov es, word ptr [0xc13c]
01bb cmp word ptr es:[0x8630], 0
01c1 je 0xbeef
01c3 mov word ptr es:[0x8630], 0
01ca push 0x1305
01cd push 3
01cf push 0x1300
01d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 469, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetGroupSelectedObj
01d7 add sp, 6
01da push 4
01dc push 0x1300
01df lcall <resolved loader operand; see bindings> ; [{'operand_offset': 482, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeGroupVisible
01e4 add sp, 4
01e7 mov word ptr [bp - 0x10], 0xffff
01ec push 0x1300
01ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 498, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
01f4 add sp, 2
01f7 mov ax, word ptr [bp + 6]
01fa mov dx, word ptr [bp + 8]
01fd add ax, 8
0200 mov cx, 4
0203 mov di, ax
0205 lea si, [bp - 0x10]
0208 mov es, dx
020a shr cx, 1
020c sbb ax, ax
020e cmp cx, cx
0210 repe cmpsw word ptr [si], word ptr es:[di]
0212 jne 0xbf20
0214 sub cx, ax
0216 repe cmpsb byte ptr [si], byte ptr es:[di]
0218 je 0xbf64
021a mov bx, word ptr [bp + 6]
021d mov ax, word ptr es:[bx + 8]
0221 mov dx, word ptr es:[bx + 0xa]
0225 mov word ptr [bp - 0x10], ax
0228 mov word ptr [bp - 0xe], dx
022b lea ax, [bp - 0x18]
022e push ss
022f push ax
0230 lea ax, [bx + 8]
0233 push es
0234 push ax
0235 mov si, ax
0237 mov di, es
0239 nop 
023a push cs
023b call 0xc438 ; _BoundPointToTri
023e add sp, 8
0241 push di
0242 push si
0243 push <resolved loader operand; see bindings> ; [{'operand_offset': 580, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0246 push 0xa090
0249 push <resolved loader operand; see bindings> ; [{'operand_offset': 586, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
024c push 0x9b64
024f nop 
0250 push cs
0251 call 0xca7a ; _GetTriLatDist
0254 add sp, 0xc
0257 nop 
0258 push cs
0259 call 0xb7a4 ; _UpdateCasteWindow
025c mov ax, word ptr [bp + 6]
025f mov dx, word ptr [bp + 8]
0262 add ax, 8
0265 push dx
0266 push ax
0267 mov si, ax
0269 mov di, dx
026b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 622, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GetMousePos
0270 add sp, 4
0273 push word ptr [0xbccc]
0277 push di
0278 push si
0279 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 634, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 29}}]
027e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 641, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _StillDown
0283 or ax, ax
0285 je 0xbf92
0287 jmp 0xbeff
028a mov <resolved loader operand; see bindings> ; [{'operand_offset': 651, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
028d mov bx, word ptr [0x159e] ; _casteSet
0291 mov cx, bx
0293 shl bx, 1
0295 add bx, cx
0297 shl bx, 1
0299 mov es, word ptr [0xc13e]
029d push ds
029e lea di, [bx - 0x79c6]
02a2 mov si, 0x9b64
02a5 mov ds, ax
02a7 movsw word ptr es:[di], word ptr [si]
02a8 movsw word ptr es:[di], word ptr [si]
02a9 movsw word ptr es:[di], word ptr [si]
02aa pop ds
02ab push 0
02ad push -1
02af mov es, ax
02b1 mov ax, 0x64
02b4 mul word ptr es:[0x9b66]
02b9 add ax, 0x3fff
02bc adc dx, 0
02bf push dx
02c0 push ax
02c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 708, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
02c6 mov es, word ptr [0xc140]
02ca mov word ptr es:[0x8622], ax
02ce push 0
02d0 push -1
02d2 mov ax, 0x64
02d5 mov es, word ptr [0xc128]
02d9 mul word ptr es:[0x9b68]
02de add ax, 0x3fff
02e1 adc dx, 0
02e4 push dx
02e5 push ax
02e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 745, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
02eb mov es, word ptr [0xc140]
02ef mov word ptr es:[0x8624], ax
02f3 push 0
02f5 push -1
02f7 mov ax, 0x32
02fa mov es, word ptr [0xc128]
02fe mul word ptr es:[0x9b64]
0303 add ax, 0x3fff
0306 adc dx, 0
0309 push dx
030a push ax
030b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 782, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
0310 mov es, word ptr [0xc140]
0314 mov word ptr es:[0x8626], ax
0318 mov word ptr es:[0x8628], ax
031c jmp 0xc070
031e xor byte ptr [0x15b4], 1
0323 push word ptr [0xbccc]
0327 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 810, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
032c add sp, 2
032f push word ptr [0x15b4]
0333 push 0
0335 push 0x1300
0338 nop 
0339 push cs
033a call 0xc7c4 ; _DrawControlLevels
033d add sp, 6
0340 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 835, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0345 jmp 0xc070
0347 nop 
0348 mov es, word ptr [0xc13c]
034c cmp word ptr es:[0x8630], 0
0352 je 0xc070
0354 mov word ptr es:[0x8630], 0
035b push 4
035d push 0x1300
0360 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 867, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeGroupVisible
0365 add sp, 4
0368 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 875, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Off
036d pop si
036e pop di
036f leave 
0370 retf 
```

## Known declaration examples

- `extern void far DoWinHelp(int mode);` — src/recovered/wf_ProcEditEvent-1e056fd3ba.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern void far GetMousePos(struct CursorPoint far *point);` — src/recovered/win_IsCursorInObj.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far StillDown(void);` — src/recovered/myButton.c
- `extern int far StillDown(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far UpdateCasteWindow(void);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far clip_Off(void);` — src/recovered/wf_ProcEditEvent-1e056fd3ba.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_ProcEditEvent-1e056fd3ba.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_win_DrawPictureWindow-9fe716872a.c
- `extern void far win_MakeGroupInvisible(int window, int group);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far win_MakeGroupInvisible(int window, int group);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_OpenCasteWindow', 'offset': 48108, 'source': 'src/recovered/wf_OpenCasteWindow-3d435baaee.c', 'size': 141}
- {'symbol': '_OpenModeWindow', 'offset': 48250, 'source': 'src/recovered/wf_OpenModeWindow-b97cc714f9.c', 'size': 141}
- {'symbol': '_ProcModeEvent', 'offset': 49274, 'source': None, 'size': 769}
- {'symbol': '_IsPointInIsoTri', 'offset': 50044, 'source': None, 'size': 188}
