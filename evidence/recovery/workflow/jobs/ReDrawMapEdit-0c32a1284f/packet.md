# Recovery task _ReDrawMapEdit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 107 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push 0
0005 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 8, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
000a mov sp, bp
000c or ax, ax
000e je 0x7422
0010 nop 
0011 push cs
0012 call 0x11e0 ; _UpdateEdit
0015 nop 
0016 push cs
0017 call 0x14ee ; _DrawEdit
001a push 0x100
001d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 32, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0022 mov sp, bp
0024 or ax, ax
0026 je 0x744d
0028 test byte ptr [bp + 6], 3
002c jne 0x744d
002e push 1
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MakeDMap
0035 mov sp, bp
0037 nop 
0038 push cs
0039 call 0xcd3e ; _DrawMap
003c leave 
003d retf 
003e push 1
0040 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MakeDMap
0045 mov sp, bp
0047 nop 
0048 push cs
0049 call 0xcd3e ; _DrawMap
004c push 0
004e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0053 mov sp, bp
0055 or ax, ax
0057 je 0x744d
0059 test byte ptr [bp + 6], 3
005d jne 0x744d
005f nop 
0060 push cs
0061 call 0x11e0 ; _UpdateEdit
0064 nop 
0065 push cs
0066 call 0x14ee ; _DrawEdit
0069 leave 
006a retf 
```

## Known declaration examples

- `extern void far UpdateEdit(void);` — src/recovered/DoEditUpdateDraw.c
- `extern void far UpdateEdit(void);` — src/recovered/ForceUpdateEdit.c
- `extern void far UpdateEdit(void);` — src/recovered/UpdateEditWindow.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawYard-bff77801c5.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_processExp', 'offset': 28706, 'source': None, 'size': 604}
- {'symbol': '_DoTool', 'offset': 29310, 'source': None, 'size': None}
- {'symbol': '_DropWall', 'offset': 29776, 'source': None, 'size': 285}
- {'symbol': '_ExpDig', 'offset': 30062, 'source': None, 'size': 997}
