# Recovery task _InvertPatch

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 159 bytes.

```asm
0000 enter 0x18, 0
0004 push di
0005 push si
0006 nop 
0007 push cs
0008 call 0x8e50 ; _clip_Push
000b push 0x1900
000e nop 
000f push cs
0010 call 0x8e44 ; _clip_SetWin
0013 add sp, 2
0016 cmp word ptr [0xce82], 2 ; _YardMode
001b jge 0xbe3a
001d mov bx, word ptr [bp + 8]
0020 imul di, word ptr [bp + 6], 0x1c
0024 mov ax, bx
0026 shl ax, 2
0029 add ax, bx
002b shl ax, 1
002d mov word ptr [bp - 0x18], ax
0030 sub di, ax
0032 dec di
0033 jmp 0xbe4f
0035 nop 
0036 mov bx, word ptr [bp + 8]
0039 imul di, word ptr [bp + 6], 0x1c
003d mov ax, bx
003f shl ax, 2
0042 add ax, bx
0044 shl ax, 1
0046 mov word ptr [bp - 0x18], ax
0049 sub di, ax
004b mov es, word ptr [0xc1c4]
004f add di, word ptr es:[0x8110]
0054 mov cx, ax
0056 add cx, word ptr es:[0x8112]
005b mov word ptr [bp - 2], 0
0060 mov bx, word ptr [bp - 2]
0063 mov word ptr [bp - 6], cx
0066 mov word ptr [bp - 4], di
0069 mov ax, word ptr [bx + 0x1894]
006d add ax, di
006f mov si, bx
0071 mov word ptr [bp + si - 0x16], ax
0074 mov ax, word ptr [bx + 0x1896]
0078 add ax, cx
007a mov word ptr [bp + si - 0x14], ax
007d add bx, 4
0080 cmp bx, 0x10
0083 jl 0xbe6d
0085 push -1
0087 push -1
0089 lea ax, [bp - 0x16]
008c push ss
008d push ax
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TrapFill
0093 add sp, 8
0096 nop 
0097 push cs
0098 call 0x8e4e ; _clip_Pop
009b pop si
009c pop di
009d leave 
009e retf 
```

## Known declaration examples

- `extern int near YardMode;` — src/recovered/wf_DrawYard-bff77801c5.c
- `extern int near YardMode;` — src/recovered/wf_UpdateYard-32751811c5.c
- `extern void far clip_Pop(void);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void far clip_Push(void);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_win_YardClosed-13af30aa32.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawSwarm', 'offset': 47886, 'source': None, 'size': 718}
- {'symbol': '_TooFar', 'offset': 48604, 'source': 'src/recovered/wf_TooFar-89685c4366.c', 'size': 39}
- {'symbol': '_DrawSimColonies', 'offset': 48804, 'source': None, 'size': 247}
- {'symbol': '_DrawColonyBars', 'offset': 49052, 'source': None, 'size': 253}
