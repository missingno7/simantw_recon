# Recovery task _ProcEditEvent

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 232 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov si, word ptr [bp + 6]
0007 push 0
0009 nop 
000a push cs
000b call 0xffff8e44
000e add sp, 2
0011 mov es, word ptr [bp + 8]
0014 mov ax, word ptr es:[si + 0xc]
0018 sub ax, 4
001b cmp ax, 0x11
001e jbe 0xb9d
0020 jmp 0xc5a
0023 shl ax, 1
0025 xchg bx, ax
0026 jmp word ptr cs:[bx + 0xba6]
002b nop 
002c dw offset 0xbca
002e dw offset 0xc5a
0030 dw offset 0xbda
0032 dw offset 0xbe6
0034 dw offset 0xbee
0036 dw offset 0xbf8
0038 dw offset 0xbfc
003a dw offset 0xc00
003c dw offset 0xc08
003e dw offset 0xc10
0040 dw offset 0xc18
0042 dw offset 0xc20
0044 dw offset 0xc36
0046 dw offset 0xc3e
0048 dw offset 0xc4c
004a dw offset 0xc5a
004c dw offset 0xc5a
004e dw offset 0xbca
0050 mov ax, es
0052 push ax
0053 push si
0054 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _processEdit
0059 add sp, 4
005c jmp 0xc5a
005f nop 
0060 push 2
0062 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoWinHelp
0067 add sp, 2
006a jmp 0xc5a
006c nop 
006d push cs
006e call 0x67c6 ; _EditToolsMenu
0071 jmp 0xc5a
0073 nop 
0074 push 1
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMapPlane
007b jmp 0xbe1
007d nop 
007e push 2
0080 jmp 0xbf0
0082 push 3
0084 jmp 0xbf0
0086 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 137, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _GotoMyAnt
008b jmp 0xc5a
008d nop 
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _GotoSpider
0093 jmp 0xc5a
0095 nop 
0096 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 153, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _GotoBQueen
009b jmp 0xc5a
009d nop 
009e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 161, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _GotoRQueen
00a3 jmp 0xc5a
00a5 nop 
00a6 mov es, word ptr [0xbf8e]
00aa cmp word ptr es:[0x9c28], 1
00b0 sbb ax, ax
00b2 neg ax
00b4 push ax
00b5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 184, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetPause
00ba jmp 0xbe1
00bc nop 
00bd push cs
00be call 0x675e ; _EditScentMenu
00c1 jmp 0xc5a
00c3 nop 
00c4 push 0x11
00c6 mov ax, es
00c8 push ax
00c9 push si
00ca nop 
00cb push cs
00cc call 0x6e72 ; _DoHealthSetY
00cf jmp 0xc57
00d1 nop 
00d2 push 0x12
00d4 mov ax, es
00d6 push ax
00d7 push si
00d8 nop 
00d9 push cs
00da call 0x6e1c ; _DoWarnSetB
00dd add sp, 6
00e0 nop 
00e1 push cs
00e2 call 0xffff8e46
00e5 pop si
00e6 leave 
00e7 retf 
```

## Known declaration examples

- `extern void far SetMapPlane(int plane);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_LoadTiles', 'offset': 472, 'source': None, 'size': 2218}
- {'symbol': '_ClearEditDeltaTables', 'offset': 2690, 'source': None, 'size': 247}
- {'symbol': '_win_EditChanged', 'offset': 3170, 'source': None, 'size': 458}
- {'symbol': '_OpenEditWindow', 'offset': 3628, 'source': 'src/recovered/OpenEditWindow.c', 'size': 11}
