# Recovery task _win_AutoSize

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 225 bytes.

```asm
0000 enter 4, 0
0004 push si
0005 les si, ptr [bp + 6]
0008 mov al, byte ptr es:[si + 0x21]
000c cwde 
000d sub ax, 5
0010 cmp ax, 0xd
0013 ja 0xe440
0015 shl ax, 1
0017 xchg bx, ax
0018 jmp word ptr cs:[bx - 0x1bdc]
001d nop 
001e dw offset 0xe458
0020 dw offset 0xe464
0022 dw offset 0xe440
0024 dw offset 0xe440
0026 dw offset 0xe476
0028 dw offset 0xe440
002a dw offset 0xe440
002c dw offset 0xe458
002e dw offset 0xe464
0030 dw offset 0xe440
0032 dw offset 0xe440
0034 dw offset 0xe4a2
0036 dw offset 0xe4ac
0038 dw offset 0xe4a2
003a mov ax, word ptr es:[si + 4]
003e sub ax, word ptr es:[si]
0041 mov word ptr [0xcc5e], ax
0044 mov ax, word ptr es:[si + 6]
0048 sub ax, word ptr es:[si + 2]
004c mov word ptr [0xcc60], ax
004f jmp 0xe4dd
0052 mov ax, si
0054 mov dx, es
0056 add ax, 0x28
0059 push dx
005a push ax
005b jmp 0xe4b3
005d nop 
005e push word ptr es:[si + 0x28]
0062 push ds
0063 push 0xcc5e
0066 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
006b add sp, 6
006e jmp 0xe4dd
0070 mov ax, si
0072 mov dx, es
0074 add ax, 0x28
0077 push dx
0078 push ax
0079 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 124, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_StringWidth
007e add sp, 4
0081 mov word ptr [bp - 4], ax
0084 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 135, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_FontHeight
0089 mov word ptr [bp - 2], ax
008c mov ax, word ptr [bp - 4]
008f mov dx, word ptr [bp - 2]
0092 mov word ptr [0xcc5e], ax
0095 mov word ptr [0xcc60], dx
0099 jmp 0xe4dd
009b nop 
009c mov ax, si
009e mov dx, es
00a0 add ax, 0x2c
00a3 jmp 0xe47d
00a5 nop 
00a6 mov cx, es
00a8 add si, 0x2c
00ab push cx
00ac push si
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_StringWidth
00b2 add sp, 4
00b5 mov word ptr [bp - 4], ax
00b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_FontHeight
00bd mov word ptr [bp - 2], ax
00c0 mov ax, word ptr [bp - 4]
00c3 mov dx, word ptr [bp - 2]
00c6 mov word ptr [0xcc5e], ax
00c9 mov word ptr [0xcc60], dx
00cd add word ptr [0xcc5e], 8
00d2 add word ptr [0xcc60], 8
00d7 mov ax, word ptr [0xcc5e]
00da mov dx, word ptr [0xcc60]
00de pop si
00df leave 
00e0 retf 
```

## Known declaration examples

- `extern int far _font_FontHeight(unsigned int lo, unsigned int hi);` — src/recovered/font_FontHeight.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_win_DrawPictureWindow-9fe716872a.c
- `extern int far font_FontHeight(void);` — src/recovered/win_StringSize.c
- `extern int far font_StringWidth(char far *string);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_StringWidth(int first, int second);` — src/recovered/win_StringSize.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_win_DrawPictureWindow-9fe716872a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_SortRect', 'offset': 58286, 'source': 'src/recovered/win_SortRect.c', 'size': 50}
- {'symbol': '_win_StringSize', 'offset': 58336, 'source': 'src/recovered/win_StringSize.c', 'size': 37}
- {'symbol': '_win_GetVal', 'offset': 58600, 'source': None, 'size': 138}
- {'symbol': '_win_GetArg', 'offset': 58738, 'source': None, 'size': 60}
