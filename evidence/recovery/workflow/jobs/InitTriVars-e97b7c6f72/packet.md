# Recovery task _InitTriVars

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 152 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 8]
0009 lea ax, [bp - 8]
000c push ss
000d push ax
000e push word ptr [bp + 6]
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0016 add sp, 6
0019 mov ax, word ptr [bp - 4]
001c sub ax, word ptr [bp - 8]
001f mov es, word ptr [0xc11c]
0023 mov word ptr es:[0x9cec], ax
0027 shr ax, 1
0029 mov es, word ptr [0xc11e]
002d mov word ptr es:[0x99d6], ax
0031 mov es, word ptr [0xc120]
0035 mov word ptr es:[0x7f00], ax
0039 mov cx, word ptr [bp - 2]
003c sub cx, word ptr [bp - 6]
003f mov es, word ptr [0xc122]
0043 mov word ptr es:[0x80d0], cx
0048 push 0
004a push cx
004b mov cx, ax
004d sub dx, dx
004f mov dl, ah
0051 mov ah, al
0053 sub al, al
0055 push dx
0056 push ax
0057 mov di, cx
0059 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 92, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
005e mov es, word ptr [0xc124]
0062 mov word ptr es:[0x9fc0], ax
0066 mov word ptr es:[0x9fc2], dx
006b add di, word ptr [bp - 8]
006e mov es, word ptr [bp + 0xa]
0071 mov word ptr es:[si], di
0074 mov ax, word ptr [bp - 6]
0077 mov word ptr es:[si + 2], ax
007b mov ax, word ptr [bp - 2]
007e mov word ptr es:[si + 0xa], ax
0082 mov word ptr es:[si + 6], ax
0086 mov ax, word ptr [bp - 8]
0089 mov word ptr es:[si + 4], ax
008d mov ax, word ptr [bp - 4]
0090 mov word ptr es:[si + 8], ax
0094 pop si
0095 pop di
0096 leave 
0097 retf 
```

## Known declaration examples

- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct CursorRect far *rect);` — src/recovered/win_IsCursorInObj.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/win_MapChanged.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PlaceQueenInYard', 'offset': 44306, 'source': None, 'size': 937}
- {'symbol': '_MysteryButton', 'offset': 45244, 'source': None, 'size': None}
- {'symbol': '_win_CasteControlChanged', 'offset': 46012, 'source': None, 'size': 500}
- {'symbol': '_win_ModeControlChanged', 'offset': 46512, 'source': None, 'size': 500}
