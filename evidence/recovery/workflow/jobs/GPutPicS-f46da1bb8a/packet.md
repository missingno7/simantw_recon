# Recovery task _GPutPicS

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 78 bytes.

```asm
0000 enter 4, 0
0004 mov ax, word ptr [bp + 6]
0007 mov word ptr [bp - 4], ax
000a mov ax, word ptr [bp + 8]
000d mov word ptr [bp - 2], ax
0010 test byte ptr [0xcc7e], 1 ; _displayType
0015 jne 0x3d6e
0017 push word ptr [bp + 0x12]
001a push word ptr [bp + 0xc]
001d push word ptr [bp + 0xa]
0020 push word ptr [bp + 0x10]
0023 push word ptr [bp + 0xe]
0026 push ax
0027 push word ptr [bp - 4]
002a nop 
002b push cs
002c call 0x332a ; _DoBitmap
002f leave 
0030 retf 
0031 nop 
0032 push word ptr [bp + 0x12]
0035 push word ptr [bp + 0xc]
0038 push word ptr [bp + 0xa]
003b push word ptr [bp + 0x10]
003e push word ptr [bp + 0xe]
0041 push word ptr [bp - 2]
0044 push word ptr [bp - 4]
0047 nop 
0048 push cs
0049 call 0x364c ; _DoMonoBitmap
004c leave 
004d retf 
```

## Known declaration examples

- `extern void far DoMonoBitmap(int x, int y, int width, int height, void far *data, int mask);` — src/recovered/GPutImg.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GSetAttrib-bba4337448.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GPutPic', 'offset': 15514, 'source': None, 'size': 104}
- {'symbol': '_GPutImg', 'offset': 15618, 'source': 'src/recovered/GPutImg.c', 'size': 57}
- {'symbol': '_GPutImgS', 'offset': 15754, 'source': None, 'size': 39}
- {'symbol': '_GPicSize', 'offset': 15794, 'source': 'src/recovered/GPicSize.c', 'size': 36}
