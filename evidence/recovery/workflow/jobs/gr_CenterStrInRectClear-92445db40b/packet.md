# Recovery task _gr_CenterStrInRectClear

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 217 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 mov ax, word ptr [bp + 6]
0009 mov dx, word ptr [bp + 8]
000c push ds
000d lea di, [bp - 0xc]
0010 mov si, ax
0012 push ss
0013 pop es
0014 mov ds, dx
0016 movsw word ptr es:[di], word ptr [si]
0017 movsw word ptr es:[di], word ptr [si]
0018 movsw word ptr es:[di], word ptr [si]
0019 movsw word ptr es:[di], word ptr [si]
001a pop ds
001b push word ptr [bp + 0xc]
001e push word ptr [bp + 0xa]
0021 nop 
0022 push cs
0023 call 0x60ce ; _font_StringWidth
0026 add sp, 4
0029 mov word ptr [bp - 2], ax
002c mov ax, word ptr [bp - 8]
002f sub ax, word ptr [bp - 2]
0032 add ax, word ptr [bp - 0xc]
0035 cdq 
0036 sub ax, dx
0038 sar ax, 1
003a mov word ptr [bp - 4], ax
003d cmp ax, word ptr [bp - 0xc]
0040 jge 0x485e
0042 mov ax, word ptr [bp - 0xc]
0045 mov word ptr [bp - 4], ax
0048 mov word ptr [bp - 0xc], ax
004b add ax, word ptr [bp - 2]
004e mov word ptr [bp - 8], ax
0051 nop 
0052 push cs
0053 call 0x60ae ; _font_FontHeight
0056 sub ax, word ptr [bp - 6]
0059 neg ax
005b sub ax, word ptr [bp - 0xa]
005e cdq 
005f sub ax, dx
0061 sar ax, 1
0063 add word ptr [bp - 0xa], ax
0066 nop 
0067 push cs
0068 call 0x60ae ; _font_FontHeight
006b add ax, word ptr [bp - 0xa]
006e mov word ptr [bp - 6], ax
0071 push word ptr [bp + 0xc]
0074 push word ptr [bp + 0xa]
0077 push word ptr [bp - 0xa]
007a push word ptr [bp - 0xc]
007d nop 
007e push cs
007f call 0x6216 ; _font_PrintStr
0082 add sp, 8
0085 mov ax, word ptr [bp - 0xc]
0088 les bx, ptr [bp + 6]
008b cmp word ptr es:[bx], ax
008e jge 0x48c2
0090 push word ptr [0xce8a] ; __backColor
0094 mov ax, word ptr [bp - 6]
0097 dec ax
0098 push ax
0099 mov ax, word ptr [bp - 0xc]
009c dec ax
009d push ax
009e push word ptr [bp - 0xa]
00a1 push word ptr es:[bx]
00a4 nop 
00a5 push cs
00a6 call 0x19e6 ; _GBoxFill
00a9 add sp, 0xa
00ac mov ax, word ptr [bp - 8]
00af les bx, ptr [bp + 6]
00b2 cmp word ptr es:[bx + 4], ax
00b6 jle 0x48eb
00b8 push word ptr [0xce8a] ; __backColor
00bc mov ax, word ptr [bp - 6]
00bf dec ax
00c0 push ax
00c1 mov ax, word ptr es:[bx + 4]
00c5 dec ax
00c6 push ax
00c7 push word ptr [bp - 0xa]
00ca push word ptr [bp - 8]
00cd nop 
00ce push cs
00cf call 0x19e6 ; _GBoxFill
00d2 add sp, 0xa
00d5 pop si
00d6 pop di
00d7 leave 
00d8 retf 
```

## Known declaration examples

- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near _backColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near _backColor;` — src/recovered/wf_GRectFillOutline-24e4a6aa35.c
- `extern int near _backColor;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern int far _font_FontHeight(unsigned int lo, unsigned int hi);` — src/recovered/font_FontHeight.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far font_FontHeight(void);` — src/recovered/win_StringSize.c
- `extern void far font_PrintStr(int x, int y, char far *string);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_StringWidth(char far *string);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_StringWidth(int first, int second);` — src/recovered/win_StringSize.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_StillDown', 'offset': 18198, 'source': 'src/recovered/wf_StillDown-a90f7d48e5.c', 'size': 161}
- {'symbol': '_WaitedEnough', 'offset': 18360, 'source': 'src/recovered/wf_WaitedEnough-b76919c4b5.c', 'size': 94}
- {'symbol': '_gr_CenterStrInRect', 'offset': 18672, 'source': 'src/recovered/wf_gr_CenterStrInRect-59694d56d6.c', 'size': 137}
- {'symbol': '_PointInRect', 'offset': 18810, 'source': None, 'size': 106}
