# Recovery task _SetFancyCursor

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 175 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov si, word ptr [bp + 6]
0007 cmp word ptr [0xbca6], si ; _win_hwnd
000b jne 0x289b
000d push 0
000f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
0014 add sp, 2
0017 or ax, ax
0019 jne 0x28bf
001b cmp si, word ptr [0xbca8]
001f je 0x28a4
0021 jmp 0x292a
0024 push 0x100
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 42, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
002c add sp, 2
002f or ax, ax
0031 je 0x292a
0033 push 0x10
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
003a test ah, 0x80
003d je 0x292a
003f cmp word ptr [bp + 8], 1
0043 jne 0x292a
0045 mov es, word ptr [0xbe8c]
0049 cmp word ptr es:[0x80b4], 3
004f jne 0x292a
0051 mov es, word ptr [0xbeae]
0055 mov ax, word ptr es:[0x79e2]
0059 cmp ax, 6
005c ja 0x2923
005e shl ax, 1
0060 xchg bx, ax
0061 jmp word ptr cs:[bx + 0x28e8]
0066 nop 
0067 nop 
0068 dw offset 0x28f6
006a dw offset 0x28fc
006c dw offset 0x2902
006e dw offset 0x2908
0070 dw offset 0x290e
0072 dw offset 0x2914
0074 dw offset 0x291a
0076 push word ptr [0xcd82] ; _magCursor
007a jmp 0x291e
007c push word ptr [0xcd80] ; _rockCursor
0080 jmp 0x291e
0082 push word ptr [0xce84] ; _digCursor
0086 jmp 0x291e
0088 push word ptr [0xce94] ; _antCursor
008c jmp 0x291e
008e push word ptr [0xcc82] ; _foodCursor
0092 jmp 0x291e
0094 push word ptr [0xcd7c] ; _dropCursor
0098 jmp 0x291e
009a push word ptr [0xce8c] ; _sprayCursor
009e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 159, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 69}}]
00a3 mov ax, 1
00a6 pop si
00a7 leave 
00a8 retf 
00a9 nop 
00aa xor ax, ax
00ac pop si
00ad leave 
00ae retf 
```

## Known declaration examples

- `extern unsigned int near antCursor;` — src/recovered/wf_LoadFancyCursor-9a23f6f0e0.c
- `extern unsigned int near digCursor;` — src/recovered/wf_LoadFancyCursor-9a23f6f0e0.c
- `extern unsigned int near dropCursor;` — src/recovered/wf_LoadFancyCursor-9a23f6f0e0.c
- `extern unsigned int near foodCursor;` — src/recovered/wf_LoadFancyCursor-9a23f6f0e0.c
- `extern unsigned int near magCursor;` — src/recovered/wf_LoadFancyCursor-9a23f6f0e0.c
- `extern unsigned int near rockCursor;` — src/recovered/wf_LoadFancyCursor-9a23f6f0e0.c
- `extern unsigned int near sprayCursor;` — src/recovered/wf_LoadFancyCursor-9a23f6f0e0.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd[];` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near win_hwnd[];` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': 'MYTIMERFUNC', 'offset': 9280, 'source': None, 'size': 973}
- {'symbol': '_LoadFancyCursor', 'offset': 10254, 'source': 'src/recovered/wf_LoadFancyCursor-9a23f6f0e0.c', 'size': 113}
- {'symbol': 'MAINWNDPROC', 'offset': 10544, 'source': None, 'size': 4953}
- {'symbol': '_InitInstance', 'offset': 15498, 'source': None, 'size': 325}
