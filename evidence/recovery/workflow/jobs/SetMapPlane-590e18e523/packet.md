# Recovery task _SetMapPlane

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 277 bytes.

```asm
0000 enter 4, 0
0004 cmp word ptr [bp + 6], 0
0008 je 0xa5f4
000a mov es, word ptr [0xc0ec]
000e push word ptr es:[0x9b6c]
0013 mov es, word ptr [0xc0ee]
0017 push word ptr es:[0x7292]
001c push 0
001e push 0
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _InvalEuMap
0025 add sp, 8
0028 jmp 0xa5fa
002a mov ax, word ptr [0xcc76] ; _MapPlane
002d mov word ptr [0xcc78], ax ; _OldMapPlane
0030 mov ax, word ptr [bp + 6]
0033 mov word ptr [0xcc76], ax ; _MapPlane
0036 dec ax
0037 jne 0xa608
0039 mov ax, 0x80
003c jmp 0xa60b
003e mov ax, 0x40
0041 mov es, word ptr [0xc0ee]
0045 sub ax, word ptr es:[0x7292]
004a mov es, word ptr [0xc0f0]
004e mov word ptr es:[0x769a], ax
0052 mov es, word ptr [0xc0f8]
0056 mov bx, word ptr [0xcc76] ; _MapPlane
005a shl bx, 1
005c mov ax, word ptr es:[bx - 0x79f8]
0061 mov es, word ptr [0xc0e2]
0065 mov word ptr es:[0x9fe0], ax
0069 mov ax, word ptr [0xcc76] ; _MapPlane
006c or ax, ax
006e je 0xa646
0070 dec ax
0071 je 0xa656
0073 dec ax
0074 je 0xa666
0076 dec ax
0077 je 0xa676
0079 jmp 0xa689
007b nop 
007c mov es, word ptr [0xc0f4]
0080 mov ax, word ptr es:[0x789e]
0084 mov dx, word ptr es:[0x78a0]
0089 jmp 0xa683
008b nop 
008c mov es, word ptr [0xc0fa]
0090 mov ax, word ptr es:[0x9f2c]
0094 mov dx, word ptr es:[0x9f2e]
0099 jmp 0xa683
009b nop 
009c mov es, word ptr [0xc0fc]
00a0 mov ax, word ptr es:[0x9fb2]
00a4 mov dx, word ptr es:[0x9fb4]
00a9 jmp 0xa683
00ab nop 
00ac mov es, word ptr [0xc0fe]
00b0 mov ax, word ptr es:[0x72f6]
00b4 mov dx, word ptr es:[0x72f8]
00b9 mov word ptr [bp - 4], ax
00bc mov word ptr [bp - 2], dx
00bf push word ptr [bp - 2]
00c2 push word ptr [bp - 4]
00c5 push word ptr [bp + 6]
00c8 nop 
00c9 push cs
00ca call 0xa386 ; _SetMapPlaneLocation
00cd add sp, 6
00d0 cmp word ptr [0xcc76], 0 ; _MapPlane
00d5 je 0xa6cc
00d7 push word ptr [bp - 2]
00da push word ptr [bp - 4]
00dd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 224, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _CenterEdit
00e2 add sp, 4
00e5 or ax, ax
00e7 je 0xa6b8
00e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 236, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
00ee push 0x100
00f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00f6 add sp, 2
00f9 or ax, ax
00fb je 0xa6cc
00fd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 256, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMap
0102 push word ptr [0xcc76] ; _MapPlane
0106 nop 
0107 push cs
0108 call 0x9e82 ; _SetMapModeAnt
010b add sp, 2
010e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
0113 leave 
0114 retf 
```

## Known declaration examples

- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMap(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMap(void);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern void far SetMapPlaneLocation(int plane, int x, int y);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far UpdateEdit(void);` — src/recovered/DoEditUpdateDraw.c
- `extern void far UpdateEdit(void);` — src/recovered/ForceUpdateEdit.c
- `extern void far UpdateEdit(void);` — src/recovered/UpdateEditWindow.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetMapPlaneLocation', 'offset': 41862, 'source': None, 'size': 419}
- {'symbol': '_GotoMapPoint', 'offset': 42282, 'source': 'src/recovered/wf_GotoMapPoint-52cd2a4427.c', 'size': 160}
- {'symbol': '_CenterAnt', 'offset': 42720, 'source': 'src/recovered/wf_CenterAnt-5b585d8f15.c', 'size': 132}
- {'symbol': '_GotoMyAnt', 'offset': 42852, 'source': None, 'size': 224}
