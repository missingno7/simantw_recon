# Recovery task _font_PrintStr

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 165 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 les bx, ptr [bp + 0xa]
0008 cmp byte ptr es:[bx], 0
000c jne 0x623e
000e mov <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0011 mov es, ax
0013 mov ax, word ptr [bp + 6]
0016 mov word ptr es:[0x7692], ax
001a mov ax, word ptr [bp + 8]
001d mov word ptr es:[0x7694], ax
0021 push ss
0022 pop ds
0023 pop si
0024 pop di
0025 leave 
0026 retf 
0027 nop 
0028 mov ax, word ptr ss:[0x1688]
002c or ax, word ptr ss:[0x1686]
0031 jne 0x6260
0033 push ss
0034 pop ds
0035 push es
0036 push bx
0037 push word ptr [bp + 8]
003a push word ptr [bp + 6]
003d nop 
003e push cs
003f call 0x1792 ; _GPutStr
0042 add sp, 8
0045 pop si
0046 pop di
0047 leave 
0048 retf 
0049 nop 
004a push ss
004b pop ds
004c mov si, word ptr [bp + 6]
004f mov di, word ptr [bp + 8]
0052 push word ptr [0x1688]
0056 push word ptr [0x1686] ; _curFontPtr
005a push 0
005c push es
005d push bx
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _font_MakeImage
0063 add sp, 0xa
0066 push 1
0068 mov es, word ptr [0xc16c]
006c push word ptr es:[0x7d1e]
0071 push word ptr es:[0x7d1c]
0076 push word ptr es:[0x7d22]
007b push word ptr es:[0x7d20]
0080 push di
0081 push si
0082 nop 
0083 push cs
0084 call 0x3d8a ; _GPutImgS
0087 add sp, 0xe
008a mov es, word ptr [0xc16c]
008e add si, word ptr es:[0x7d1c]
0093 mov es, word ptr [0xc16e]
0097 mov word ptr es:[0x7692], si
009c mov word ptr es:[0x7694], di
00a1 pop si
00a2 pop di
00a3 leave 
00a4 retf 
```

## Known declaration examples

- `extern struct FarAddress near curFontPtr;` — src/recovered/font_CharWidth.c
- `extern struct FarAddress near curFontPtr;` — src/recovered/font_FontHeight.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_font_SetFont', 'offset': 24860, 'source': None, 'size': 80}
- {'symbol': '_font_InitFonts', 'offset': 24940, 'source': None, 'size': 169}
- {'symbol': '_WinPrintf', 'offset': 25276, 'source': 'src/recovered/wf_WinPrintf-d81cd63317.c', 'size': 101}
- {'symbol': '_DebugWinPrintf', 'offset': 25378, 'source': None, 'size': 101}
