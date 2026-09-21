# Recovery task _Mini_MakeTable

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 114 bytes.

```asm
0000 enter 2, 0
0004 mov al, byte ptr [0xcc7e] ; _displayType
0007 cwde 
0008 sub ax, 9
000b je 0xe314
000d dec ax
000e je 0xe358
0010 leave 
0011 retf 
0012 mov es, word ptr [0xc228]
0016 mov ax, word ptr es:[0x78ba]
001a mov word ptr [bp - 2], ax
001d cmp ax, 0x40
0020 jne 0xe33e
0022 push word ptr [bp + 0xe]
0025 push ax
0026 push word ptr [bp + 0xc]
0029 push word ptr [bp + 0xa]
002c push word ptr [bp + 8]
002f push word ptr [bp + 6]
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _WindowsMono_MakeTable2x2b
0037 add sp, 0xc
003a leave 
003b retf 
003c push word ptr [bp + 0xe]
003f push word ptr [bp - 2]
0042 push word ptr [bp + 0xc]
0045 push word ptr [bp + 0xa]
0048 push word ptr [bp + 8]
004b push word ptr [bp + 6]
004e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _WindowsMono_MakeTable2x2a
0053 jmp 0xe339
0055 nop 
0056 mov es, word ptr [0xc228]
005a push word ptr es:[0x78ba]
005f push word ptr [bp + 0xc]
0062 push word ptr [bp + 0xa]
0065 push word ptr [bp + 8]
0068 push word ptr [bp + 6]
006b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 110, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _Windows_MakeTable1x1
0070 leave 
0071 retf 
```

## Known declaration examples

- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GPutPic-08fc158e1c.c
- `extern unsigned char near displayType;` — src/recovered/wf_GPutPicS-f46da1bb8a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RibbonToolsMenu', 'offset': 56950, 'source': None, 'size': 649}
- {'symbol': '_MapAreaEvent', 'offset': 57600, 'source': None, 'size': 514}
- {'symbol': '_OpenMiniMapWin', 'offset': 58228, 'source': None, 'size': 1254}
- {'symbol': '_DrawMiniMapCursor', 'offset': 59482, 'source': None, 'size': 155}
