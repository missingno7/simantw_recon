# Recovery task _GPutPic

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 104 bytes.

```asm
0000 enter 4, 0
0004 push si
0005 mov ax, word ptr [bp + 6]
0008 mov word ptr [bp - 4], ax
000b mov ax, word ptr [bp + 8]
000e mov word ptr [bp - 2], ax
0011 test byte ptr [0xcc7e], 1 ; _displayType
0016 jne 0x3cda
0018 mov si, word ptr [bp + 0xa]
001b push word ptr [bp + 0xe]
001e mov cx, word ptr [bp + 0xc]
0021 lea ax, [si + 4]
0024 push cx
0025 push ax
0026 mov es, cx
0028 push word ptr es:[si + 2]
002c push word ptr es:[si]
002f push word ptr [bp - 2]
0032 push word ptr [bp - 4]
0035 nop 
0036 push cs
0037 call 0x332a ; _DoBitmap
003a add sp, 0xe
003d pop si
003e leave 
003f retf 
0040 mov si, word ptr [bp + 0xa]
0043 push word ptr [bp + 0xe]
0046 mov cx, word ptr [bp + 0xc]
0049 lea ax, [si + 4]
004c push cx
004d push ax
004e mov es, cx
0050 push word ptr es:[si + 2]
0054 push word ptr es:[si]
0057 push word ptr [bp - 2]
005a push word ptr [bp - 4]
005d nop 
005e push cs
005f call 0x364c ; _DoMonoBitmap
0062 add sp, 0xe
0065 pop si
0066 leave 
0067 retf 
```

## Known declaration examples

- `extern void far DoBitmap(int x, int y, int arg3, int arg4, int arg5, int arg6, int arg7);` — src/recovered/wf_GPutPicS-f46da1bb8a.c
- `extern void far DoMonoBitmap(int x, int y, int width, int height, void far *data, int mask);` — src/recovered/GPutImg.c
- `extern void far DoMonoBitmap(int x, int y, int arg3, int arg4, int arg5, int arg6, int arg7);` — src/recovered/wf_GPutPicS-f46da1bb8a.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GPutPicS-f46da1bb8a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GSetAttrib-bba4337448.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoFastBitmap', 'offset': 14770, 'source': None, 'size': 405}
- {'symbol': '_DoFastMonoBitmap', 'offset': 15176, 'source': None, 'size': 337}
- {'symbol': '_GPutImg', 'offset': 15618, 'source': 'src/recovered/GPutImg.c', 'size': 57}
- {'symbol': '_GPutPicS', 'offset': 15676, 'source': 'src/recovered/wf_GPutPicS-f46da1bb8a.c', 'size': 78}
