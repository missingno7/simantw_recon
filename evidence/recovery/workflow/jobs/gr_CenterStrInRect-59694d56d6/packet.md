# Recovery task _gr_CenterStrInRect

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 137 bytes.

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
0040 jge 0x4938
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
0085 pop si
0086 pop di
0087 leave 
0088 retf 
```

## Known declaration examples

- `extern int far _font_FontHeight(unsigned int lo, unsigned int hi);` — src/recovered/font_FontHeight.c
- `extern int far font_FontHeight(void);` — src/recovered/win_StringSize.c
- `extern int far font_StringWidth(int first, int second);` — src/recovered/win_StringSize.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_WaitedEnough', 'offset': 18360, 'source': 'src/recovered/wf_WaitedEnough-b76919c4b5.c', 'size': 94}
- {'symbol': '_gr_CenterStrInRectClear', 'offset': 18454, 'source': None, 'size': 217}
- {'symbol': '_PointInRect', 'offset': 18810, 'source': None, 'size': 106}
- {'symbol': '_WaitHundredths', 'offset': 18916, 'source': None, 'size': 55}
