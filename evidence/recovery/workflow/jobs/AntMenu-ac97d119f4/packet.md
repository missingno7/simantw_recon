# Recovery task _AntMenu

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 232 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 push ds
0007 push 0x1bb4
000a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
000f add sp, 4
0012 mov bx, 0x9fe8
0015 mov es, word ptr [0xc23a]
0019 mov word ptr [bp - 8], bx
001c mov word ptr [bp - 6], es
001f cmp word ptr es:[bx], 0
0023 jne 0x6d8e
0025 cmp word ptr [0xcc84], 0x40 ; _MeType
002a jne 0x6d7c
002c mov es, word ptr [0xc24c]
0030 cmp word ptr es:[0x8a6c], 0
0036 jne 0x6d7c
0038 mov si, word ptr [bp + 6]
003b mov es, word ptr [bp + 8]
003e push word ptr es:[si + 0xa]
0042 push word ptr es:[si + 8]
0046 push -1
0048 push 0x800
004b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DoProxMenu
0050 add sp, 8
0053 mov di, ax
0055 jmp 0x6daf
0057 nop 
0058 les bx, ptr [bp + 6]
005b push word ptr es:[bx + 0xa]
005f push word ptr es:[bx + 8]
0063 push -1
0065 push 0x700
0068 jmp 0x6d6f
006a mov si, word ptr [bp + 6]
006d les bx, ptr [bp - 8]
0070 cmp word ptr es:[bx], 1
0074 jne 0x6dac
0076 mov es, word ptr [bp + 8]
0079 push word ptr es:[si + 0xa]
007d push word ptr es:[si + 8]
0081 push -1
0083 push 0x2000
0086 jmp 0x6d6f
0088 mov di, 0xffff
008b or di, di
008d jl 0x6e06
008f mov si, di
0091 les bx, ptr [bp - 8]
0094 cmp word ptr es:[bx], 1
0098 jne 0x6dc8
009a mov al, byte ptr [si + 0x1bb0]
009e cwde 
009f mov si, ax
00a1 jmp 0x6dfd
00a3 nop 
00a4 cmp word ptr [0xcc84], 0x40 ; _MeType
00a9 jne 0x6de2
00ab mov es, word ptr [0xc24c]
00af cmp word ptr es:[0x8a6c], 0
00b5 jne 0x6de2
00b7 mov al, byte ptr [si + 0x1ba6]
00bb jmp 0x6dc2
00bd nop 
00be mov al, byte ptr [si + 0x1baa]
00c2 cwde 
00c3 mov si, ax
00c5 cmp si, 2
00c8 jne 0x6dfd
00ca push 0x10
00cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 205, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
00d1 test ah, 0x80
00d4 je 0x6dfd
00d6 mov si, 3
00d9 push si
00da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 221, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YellowCommand
00df add sp, 2
00e2 mov ax, di
00e4 pop si
00e5 pop di
00e6 leave 
00e7 retf 
```

## Known declaration examples

- `extern int near MeType;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c
- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern int far win_DoProxMenu(int menu, int layer, int x, int y);` — src/recovered/wf_EditScentMenu-abd185cb06.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawExamineWindow', 'offset': 27072, 'source': None, 'size': 395}
- {'symbol': '_MagnifyMenu', 'offset': 27468, 'source': None, 'size': 471}
- {'symbol': '_SetExpTool', 'offset': 28172, 'source': 'src/recovered/SetExpTool.c', 'size': 16}
- {'symbol': '_DoWarnSetB', 'offset': 28188, 'source': None, 'size': 86}
