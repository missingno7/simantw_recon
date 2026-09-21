# Recovery task _EditScentMenu

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 103 bytes.

```asm
0000 enter 8, 0
0004 push si
0005 lea ax, [bp - 8]
0008 push ss
0009 push ax
000a push 0x10
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0011 add sp, 6
0014 push word ptr [bp - 6]
0017 mov ax, word ptr [bp - 4]
001a add ax, 2
001d push ax
001e mov ax, word ptr [0xac58] ; _ELayerMode
0021 inc ax
0022 push ax
0023 push 0x600
0026 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DoProxMenu
002b add sp, 8
002e mov si, ax
0030 cmp si, -1
0033 je 0x67c2
0035 lea ax, [si - 1]
0038 mov word ptr [0xac58], ax ; _ELayerMode
003b push 0
003d nop 
003e push cs
003f call 0x8e44 ; _clip_SetWin
0042 add sp, 2
0045 cmp word ptr [0xac58], -1 ; _ELayerMode
004a je 0x67b0
004c mov ax, 1
004f jmp 0x67b2
0051 nop 
0052 xor ax, ax
0054 push ax
0055 push 0x10
0057 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
005c add sp, 4
005f nop 
0060 push cs
0061 call 0xe50 ; _ForceUpdateEdit
0064 pop si
0065 leave 
0066 retf 
```

## Known declaration examples

- `extern void far win_GetObjRect(int object, struct CursorRect far *rect);` — src/recovered/win_IsCursorInObj.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/win_MapChanged.c
- `extern void far win_GetObjRect(int object, struct PrintRect far *rect);` — src/recovered/win_PrintTextInObj.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoEditScroll', 'offset': 23662, 'source': None, 'size': None}
- {'symbol': '_ResetEditScrollRange', 'offset': 24710, 'source': None, 'size': 230}
- {'symbol': '_EditToolsMenu', 'offset': 26566, 'source': None, 'size': 506}
- {'symbol': '_win_DrawExamineWindow', 'offset': 27072, 'source': None, 'size': 395}
