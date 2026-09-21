# Recovery task _GenerateTutorial

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 124 bytes.

```asm
0000 push si
0001 mov es, word ptr [0xc5bc]
0005 mov word ptr es:[0x80b4], 1
000c nop 
000d push cs
000e call 0x6086 ; _RandYard
0011 push 0x20
0013 nop 
0014 push cs
0015 call 0x6c5a ; _AddBlackAnts
0018 add sp, 2
001b push 0x20
001d nop 
001e push cs
001f call 0x6cfe ; _AddRedAnts
0022 add sp, 2
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FullCount
002a mov es, word ptr [0xc5bc]
002e mov word ptr es:[0x80b4], 2
0035 push word ptr [0xce80] ; _MePlane
0039 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 60, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMapPlane
003e add sp, 2
0041 xor si, si
0043 mov al, byte ptr [si + 0x25f0]
0047 cwde 
0048 mov bx, ax
004a shl bx, 4
004d mov al, byte ptr [si + 0x260e]
0051 cwde 
0052 add bx, ax
0054 mov es, word ptr [0xc61a]
0058 mov al, byte ptr [si + 0x262c]
005c shl al, 5
005f mov byte ptr es:[bx + 0xa4], al
0064 mov al, byte ptr [si + 0x264a]
0068 shl al, 5
006b mov es, word ptr [0xc61c]
006f mov byte ptr es:[bx + 0x164], al
0074 inc si
0075 cmp si, 0x1e
0078 jl 0x62a5
007a pop si
007b retf 
```

## Known declaration examples

- `extern void far AddBlackAnts(int count);` — src/recovered/wf_AddSomeAnts-f71da72a1c.c
- `extern void far AddRedAnts(int count);` — src/recovered/wf_AddSomeAnts-f71da72a1c.c
- `extern void far FullCount(void);` — src/recovered/wf_AddSomeAnts-f71da72a1c.c
- `extern void far RandYard(void);` — src/recovered/wf_DoPreLoadInits-ed37124107.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RandWorld', 'offset': 23216, 'source': None, 'size': 1493}
- {'symbol': '_RandYard', 'offset': 24710, 'source': None, 'size': 476}
- {'symbol': '_DigOutBNest', 'offset': 25310, 'source': None, 'size': 218}
- {'symbol': '_DigOutRNest', 'offset': 25528, 'source': None, 'size': 218}
