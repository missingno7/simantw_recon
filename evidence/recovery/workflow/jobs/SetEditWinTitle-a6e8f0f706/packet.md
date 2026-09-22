# Recovery task _SetEditWinTitle

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 232 bytes.

```asm
0000 enter 0x50, 0
0004 push di
0005 push si
0006 mov cx, word ptr [bp + 6]
0009 mov ax, word ptr [bp + 8]
000c or ax, cx
000e je 0x1b1e
0010 mov ax, word ptr [bp + 8]
0013 push ax
0014 push cx
0015 jmp 0x1bb4
0018 lea di, [bp - 0x50]
001b mov si, 0x14f0
001e mov ax, ss
0020 mov es, ax
0022 movsw word ptr es:[di], word ptr [si]
0023 movsw word ptr es:[di], word ptr [si]
0024 movsw word ptr es:[di], word ptr [si]
0025 movsb byte ptr es:[di], byte ptr [si]
0026 mov es, word ptr [0xbf9e]
002a les bx, ptr es:[0x7294]
002f mov si, word ptr es:[bx + 0x3c]
0033 mov cx, word ptr es:[bx + 0x3e]
0037 mov di, si
0039 lea si, [bp - 0x50]
003c mov es, cx
003e push ds
003f mov cx, 0xffff
0042 xor ax, ax
0044 repne scasb al, byte ptr es:[di]
0046 not cx
0048 sub di, cx
004a mov bx, cx
004c xchg si, di
004e push ds
004f push es
0050 pop ds
0051 pop es
0052 mov cx, 0xffff
0055 repne scasb al, byte ptr es:[di]
0057 dec di
0058 mov cx, bx
005a shr cx, 1
005c rep movsw word ptr es:[di], word ptr [si]
005e adc cx, cx
0060 rep movsb byte ptr es:[di], byte ptr [si]
0062 pop ds
0063 mov es, word ptr [0xbfa0]
0067 mov bx, word ptr es:[0x80b4]
006c shl bx, 2
006f mov es, word ptr [0xbfa2]
0073 les si, ptr es:[0x7a4a]
0078 mov di, word ptr es:[bx + si]
007b mov cx, word ptr es:[bx + si + 2]
007f mov bx, cx
0081 lea si, [bp - 0x50]
0084 mov es, cx
0086 push ds
0087 mov cx, 0xffff
008a repne scasb al, byte ptr es:[di]
008c not cx
008e sub di, cx
0090 mov bx, cx
0092 xchg si, di
0094 push ds
0095 push es
0096 pop ds
0097 pop es
0098 mov cx, 0xffff
009b repne scasb al, byte ptr es:[di]
009d dec di
009e mov cx, bx
00a0 shr cx, 1
00a2 rep movsw word ptr es:[di], word ptr [si]
00a4 adc cx, cx
00a6 rep movsb byte ptr es:[di], byte ptr [si]
00a8 pop ds
00a9 lea ax, [bp - 0x50]
00ac push ss
00ad push ax
00ae push 1
00b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 179, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
00b5 add sp, 6
00b8 push 0
00ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00bf add sp, 2
00c2 or ax, ax
00c4 je 0x1bea
00c6 nop 
00c7 push cs
00c8 call 0x8e50 ; _clip_Push
00cb push 0
00cd nop 
00ce push cs
00cf call 0x8e44 ; _clip_SetWin
00d2 add sp, 2
00d5 push 1
00d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawTitle
00dc add sp, 2
00df nop 
00e0 push cs
00e1 call 0x8e4e ; _clip_Pop
00e4 pop si
00e5 pop di
00e6 leave 
00e7 retf 
```

## Known declaration examples

- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far win_DrawTitle(int object);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far win_SetObjFormatStr(int object, char far *text);` — src/recovered/wf_SetMapTitle-b3c9718398.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CenterEdit', 'offset': 5664, 'source': None, 'size': 180}
- {'symbol': '_DrawEditGraphs', 'offset': 6538, 'source': None, 'size': 379}
- {'symbol': '_InvalidUpdateEdit', 'offset': 7150, 'source': 'src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c', 'size': 41}
- {'symbol': '_PreDrawSpider', 'offset': 7192, 'source': None, 'size': 337}
