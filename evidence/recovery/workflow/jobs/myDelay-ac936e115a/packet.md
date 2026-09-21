# Recovery task _myDelay

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 116 bytes.

```asm
0000 enter 6, 0
0004 push si
0005 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 8, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
000a mov word ptr [bp - 4], ax
000d mov word ptr [bp - 2], dx
0010 mov ax, word ptr [bp + 6]
0013 mov cx, 3
0016 sub dx, dx
0018 div cx
001a mov word ptr [bp - 6], ax
001d push word ptr [bp - 6]
0020 lea ax, [bp - 4]
0023 push ss
0024 push ax
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WaitedEnough
002a add sp, 6
002d or ax, ax
002f jne 0x9691
0031 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
0036 or ax, ax
0038 jne 0x9691
003a mov bx, word ptr [0x150a]
003e shl bx, 1
0040 push word ptr [bx - 0x350c]
0044 mov ax, word ptr [0x150a]
0047 shl ax, 2
004a add ax, 0xcad4
004d push ds
004e push ax
004f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 82, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WaitedEnough
0054 add sp, 6
0057 or ax, ax
0059 je 0x9680
005b mov si, 1
005e jmp 0x968d
0060 push 0x20
0062 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 99, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0067 mov si, ax
0069 and si, 0x8000
006d or si, si
006f je 0x963d
0071 pop si
0072 leave 
0073 retf 
```

## Known declaration examples

- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern int far WaitedEnough(long far *stamp, int waitValue);` — src/recovered/wf_DialogAbort-1a41498b6d.c
- `extern int far WaitedEnough(long far *stamp, int waitValue);` — src/recovered/wf_DialogAbortOrCont-ea87855190.c
- `extern int far WaitedEnough(long far *stamp, int waitValue);` — src/recovered/wf_DialogWait-50782e4ed5.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetMapTitle', 'offset': 38204, 'source': None, 'size': 161}
- {'symbol': '_ClearMapScentButtons', 'offset': 38366, 'source': None, 'size': 65}
- {'symbol': '_MacTickCount', 'offset': 38548, 'source': 'src/recovered/MacTickCount.c', 'size': 18}
- {'symbol': '_myButton', 'offset': 38566, 'source': 'src/recovered/myButton.c', 'size': 6}
