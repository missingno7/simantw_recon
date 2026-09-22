# Recovery task _ForceModeB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 176 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov ax, word ptr [bp + 8]
0007 dec ax
0008 cmp ax, 8
000b ja 0x64a
000d shl ax, 1
000f xchg bx, ax
0010 jmp word ptr cs:[bx + 0x638]
0015 nop 
0016 dw offset 0x65a
0018 dw offset 0x652
001a dw offset 0x678
001c dw offset 0x64a
001e dw offset 0x688
0020 dw offset 0x652
0022 dw offset 0x678
0024 dw offset 0x64a
0026 dw offset 0x688
0028 mov <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
002b mov es, ax
002d jmp 0x6a9
002f nop 
0030 mov <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0033 mov es, ax
0035 jmp 0x698
0037 nop 
0038 mov si, word ptr [bp + 6]
003b mov <resolved loader operand; see bindings> ; [{'operand_offset': 60, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
003e mov es, ax
0040 add byte ptr es:[si + 0x3d18], 8
0046 mov al, byte ptr [bp + 0xa]
0049 mov byte ptr es:[si + 0x3b22], al
004e mov byte ptr es:[si + 0x3f0e], 0
0054 jmp 0x6a9
0056 mov <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0059 mov es, ax
005b mov bx, word ptr [bp + 6]
005e sub byte ptr es:[bx + 0x3d18], 8
0064 jmp 0x698
0066 mov si, word ptr [bp + 6]
0069 mov <resolved loader operand; see bindings> ; [{'operand_offset': 106, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
006c mov es, ax
006e sub byte ptr es:[si + 0x3d18], 0x18
0074 jmp 0x668
0076 mov al, byte ptr [bp + 0xa]
0079 mov bx, word ptr [bp + 6]
007c mov byte ptr es:[bx + 0x3b22], al
0081 mov byte ptr es:[bx + 0x3f0e], 0
0087 cmp word ptr [bp + 0xa], 6
008b jne 0x6cf
008d cmp word ptr [0xce80], 1 ; _MePlane
0092 jne 0x6cf
0094 mov al, byte ptr [0xce7e] ; _MeLocY
0097 and al, 0xfc
0099 shl al, 2
009c mov cx, word ptr [0xcd88] ; _MeLocX
00a0 sar cx, 3
00a3 or al, cl
00a5 mov bx, word ptr [bp + 6]
00a8 mov byte ptr es:[bx + 0x3f0e], al
00ad pop si
00ae leave 
00af retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocX;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocY;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_StartAttack', 'offset': 1294, 'source': None, 'size': 66}
- {'symbol': '_ForceModeA', 'offset': 1360, 'source': None, 'size': 210}
- {'symbol': '_Recruit', 'offset': 1746, 'source': 'src/recovered/wf_tu_simtwo_0000_Recruit_3-04bd7dd52e.c', 'size': 184}
- {'symbol': '_UnRecruit', 'offset': 1930, 'source': 'src/recovered/wf_tu_simtwo_0000_Recruit_3-04bd7dd52e.c', 'size': 220}
