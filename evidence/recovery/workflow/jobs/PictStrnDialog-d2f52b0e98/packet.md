# Recovery task _PictStrnDialog

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 155 bytes.

```asm
0000 enter 6, 0
0004 cmp word ptr [bp + 0xa], 0
0008 jne 0x6173
000a mov es, word ptr [0xbefa]
000e cmp word ptr es:[0x85f8], 0
0014 jne 0x6173
0016 jmp 0x61f3
0019 nop 
001a push cs
001b call 0 ; _StopSimulation
001e mov word ptr [bp - 2], 0
0023 push word ptr [bp + 8]
0026 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _LoadStringAnt
002b add sp, 2
002e mov word ptr [bp - 6], ax
0031 mov word ptr [bp - 4], dx
0034 or dx, ax
0036 je 0x61b4
0038 les bx, ptr [bp - 6]
003b mov ax, word ptr es:[bx + 2]
003f or ax, word ptr es:[bx]
0042 jne 0x61a2
0044 push ss
0045 pop ds
0046 jmp 0x61b4
0048 mov ds, word ptr [bp - 4]
004b inc word ptr [bp - 2]
004e add bx, 4
0051 mov ax, word ptr [bx + 2]
0054 or ax, word ptr [bx]
0056 jne 0x61a5
0058 jmp 0x619e
005a push word ptr [bp + 0xa]
005d push word ptr [bp + 6]
0060 push word ptr [bp - 2]
0063 push word ptr [bp - 4]
0066 push word ptr [bp - 6]
0069 nop 
006a push cs
006b call 0x62bc ; _PictureDialog
006e add sp, 0xa
0071 mov ax, word ptr [bp - 4]
0074 or ax, word ptr [bp - 6]
0077 je 0x61ee
0079 push word ptr [bp - 4]
007c push word ptr [bp - 6]
007f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _free
0084 add sp, 4
0087 push 4
0089 push word ptr [bp + 8]
008c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 143, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
0091 add sp, 4
0094 nop 
0095 push cs
0096 call 0x34 ; _RestartSimulation
0099 leave 
009a retf 
```

## Known declaration examples

- `extern void free(void far *block);` — src/recovered/mem_free_wrapper.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawCastePopUp', 'offset': 23966, 'source': None, 'size': 814}
- {'symbol': '_SetDefaultWindPrompt', 'offset': 24780, 'source': None, 'size': 141}
- {'symbol': '_win_DrawPictureWindow', 'offset': 25078, 'source': None, 'size': 198}
- {'symbol': '_PictureDialog', 'offset': 25276, 'source': None, 'size': 535}
