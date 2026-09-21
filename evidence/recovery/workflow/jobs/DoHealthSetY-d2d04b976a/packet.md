# Recovery task _DoHealthSetY

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 86 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xa]
0009 mov si, word ptr [bp + 6]
000c lea ax, [bp - 8]
000f push ss
0010 push ax
0011 push di
0012 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 21, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0017 add sp, 6
001a cmp di, 0x11
001d jne 0x6ea6
001f mov ax, word ptr [bp - 2]
0022 mov cx, ax
0024 sub cx, word ptr [bp - 6]
0027 mov es, word ptr [bp + 8]
002a sub ax, word ptr es:[si + 0xa]
002e imul ax, ax, 0x64
0031 jmp 0x6eb9
0033 nop 
0034 mov es, word ptr [bp + 8]
0037 mov ax, word ptr es:[si + 8]
003b sub ax, word ptr [bp - 8]
003e imul ax, ax, 0x64
0041 mov cx, word ptr [bp - 4]
0044 sub cx, word ptr [bp - 8]
0047 cdq 
0048 idiv cx
004a mov es, word ptr [0xc254]
004e mov word ptr es:[0x9bec], ax
0052 pop si
0053 pop di
0054 leave 
0055 retf 
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

- {'symbol': '_SetExpTool', 'offset': 28172, 'source': 'src/recovered/SetExpTool.c', 'size': 16}
- {'symbol': '_DoWarnSetB', 'offset': 28188, 'source': None, 'size': 86}
- {'symbol': '_DoTab', 'offset': 28360, 'source': 'src/recovered/DoTab.c', 'size': 26}
- {'symbol': '_DoExpMenu', 'offset': 28386, 'source': None, 'size': 320}
