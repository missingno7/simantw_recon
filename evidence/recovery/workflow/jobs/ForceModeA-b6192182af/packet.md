# Recovery task _ForceModeA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 210 bytes.

```asm
0000 enter 2, 0
0004 push si
0005 mov ax, word ptr [bp + 8]
0008 dec ax
0009 cmp ax, 8
000c ja 0x578
000e shl ax, 1
0010 xchg bx, ax
0011 jmp word ptr cs:[bx + 0x566]
0016 dw offset 0x588
0018 dw offset 0x580
001a dw offset 0x5a6
001c dw offset 0x578
001e dw offset 0x5d8
0020 dw offset 0x580
0022 dw offset 0x5a6
0024 dw offset 0x578
0026 dw offset 0x5d8
0028 mov <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
002b mov es, ax
002d jmp 0x5f9
002f nop 
0030 mov <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0033 mov es, ax
0035 jmp 0x5e8
0037 nop 
0038 mov si, word ptr [bp + 6]
003b mov <resolved loader operand; see bindings> ; [{'operand_offset': 60, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
003e mov es, ax
0040 add byte ptr es:[si + 0x2f62], 8
0046 mov al, byte ptr [bp + 0xa]
0049 mov byte ptr es:[si + 0x2b78], al
004e mov byte ptr es:[si + 0x334c], 0
0054 jmp 0x5f9
0056 mov si, word ptr [bp + 6]
0059 mov <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
005c mov es, ax
005e sub byte ptr es:[si + 0x2f62], 8
0064 mov bl, byte ptr es:[si + 0x23a4]
0069 sub bh, bh
006b shl bx, 6
006e mov al, byte ptr es:[si + 0x278e]
0073 sub ah, ah
0075 add bx, ax
0077 add bx, 0x28e8
007b mov word ptr [bp - 2], bx
007e cmp byte ptr [bx], 0x48
0081 jae 0x5e8
0083 mov byte ptr [bx], 0x48
0086 jmp 0x5e8
0088 mov si, word ptr [bp + 6]
008b mov <resolved loader operand; see bindings> ; [{'operand_offset': 140, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
008e mov es, ax
0090 sub byte ptr es:[si + 0x2f62], 0x18
0096 jmp 0x596
0098 mov al, byte ptr [bp + 0xa]
009b mov bx, word ptr [bp + 6]
009e mov byte ptr es:[bx + 0x2b78], al
00a3 mov byte ptr es:[bx + 0x334c], 0
00a9 cmp word ptr [bp + 0xa], 6
00ad jne 0x61f
00af cmp word ptr [0xce80], 1 ; _MePlane
00b4 jne 0x61f
00b6 mov al, byte ptr [0xce7e] ; _MeLocY
00b9 and al, 0xfc
00bb shl al, 2
00be mov cx, word ptr [0xcd88] ; _MeLocX
00c2 sar cx, 3
00c5 or al, cl
00c7 mov bx, word ptr [bp + 6]
00ca mov byte ptr es:[bx + 0x334c], al
00cf pop si
00d0 leave 
00d1 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GstrR', 'offset': 962, 'source': None, 'size': 332}
- {'symbol': '_StartAttack', 'offset': 1294, 'source': None, 'size': 66}
- {'symbol': '_ForceModeB', 'offset': 1570, 'source': None, 'size': 176}
- {'symbol': '_Recruit', 'offset': 1746, 'source': 'src/recovered/wf_tu_simtwo_0000_Recruit_3-04bd7dd52e.c', 'size': 184}
