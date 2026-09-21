# Recovery task __win_SetProxItem

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 197 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov si, word ptr [bp + 6]
0008 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 11, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Push
000d mov bx, si
000f sar bx, 8
0012 shl bx, 1
0014 push word ptr [bx - 0x435a]
0018 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
001d add sp, 2
0020 cmp word ptr [0xbe10], -1 ; _lastProxObj
0025 je 0xdd79
0027 test byte ptr [0xbe10], 0xff ; _lastProxObj
002c je 0xdd79
002e mov di, word ptr [0xbe10] ; _lastProxObj
0032 push di
0033 nop 
0034 push cs
0035 call 0xe3a8 ; _win_LockWin
0038 add sp, 2
003b mov ax, di
003d and di, 0xff
0041 mov bx, ax
0043 sar bx, 8
0046 shl bx, 2
0049 les bx, ptr [bx - 0x3166]
004d add bx, 0x2c
0050 shl di, 2
0053 push word ptr es:[bx + di + 2]
0057 push word ptr es:[bx + di]
005a mov di, ax
005c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 95, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInv
0061 add sp, 4
0064 push di
0065 nop 
0066 push cs
0067 call 0xe3a4 ; _win_UnlockWin
006a add sp, 2
006d cmp si, -1
0070 je 0xddbf
0072 mov ax, si
0074 sub ah, ah
0076 or ax, ax
0078 je 0xddbf
007a push si
007b nop 
007c push cs
007d call 0xe3a8 ; _win_LockWin
0080 add sp, 2
0083 mov di, si
0085 and di, 0xff
0089 mov bx, si
008b sar bx, 8
008e shl bx, 2
0091 les bx, ptr [bx - 0x3166]
0095 add bx, 0x2c
0098 shl di, 2
009b push word ptr es:[bx + di + 2]
009f push word ptr es:[bx + di]
00a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 165, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInv
00a7 add sp, 4
00aa push si
00ab nop 
00ac push cs
00ad call 0xe3a4 ; _win_UnlockWin
00b0 add sp, 2
00b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 182, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
00b8 mov word ptr [0xbe10], si ; _lastProxObj
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Pop
00c1 pop si
00c2 pop di
00c3 leave 
00c4 retf 
```

## Known declaration examples

- `extern void far GRectInv(struct WinRect far *rect);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DoDebugWin-501185d015.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DoDebugWin-501185d015.c
- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern unsigned int near lastProxObj;` — src/recovered/win_GetProxEvent.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_ObjInv', 'offset': 56512, 'source': 'src/recovered/wf_win_ObjInv-18e2e84ce2.c', 'size': 71}
- {'symbol': '_win_GetProxEvent', 'offset': 56584, 'source': 'src/recovered/win_GetProxEvent.c', 'size': 4}
- {'symbol': 'INDIRECTDLGPROC', 'offset': 56786, 'source': None, 'size': 143}
- {'symbol': '_win_DoProxMenu', 'offset': 56930, 'source': None, 'size': 993}
