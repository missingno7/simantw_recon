# Recovery task _GoInNest

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 240 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 cmp word ptr [bp + 4], 0x40
0009 jge 0x25ec
000b mov es, word ptr [0xc332]
000f cmp word ptr es:[0x99d4], 0x1f4
0016 jl 0x2597
0018 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _CompactListB
001d mov es, word ptr [0xc332]
0021 cmp word ptr es:[0x99d4], 0x1f4
0028 jl 0x25a7
002a jmp 0x2666
002d mov di, word ptr [bp + 8]
0030 mov si, word ptr [bp + 6]
0033 mov es, word ptr [0xc318]
0037 mov al, byte ptr es:[di + 0x334c]
003c sub ah, ah
003e push ax
003f mov al, byte ptr es:[di + 0x2b78]
0044 push ax
0045 mov al, byte ptr es:[di + 0x2f62]
004a and ax, 0xf8
004d add ax, 4
0050 push ax
0051 push 1
0053 push si
0054 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToBList
0059 add sp, 0xa
005c mov es, word ptr [0xc334]
0060 cmp byte ptr es:[si - 0x7d2e], 0
0066 je 0x2651
0068 push 1
006a push si
006b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 110, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileB
0070 jmp 0x264e
0072 mov es, word ptr [0xc336]
0076 cmp word ptr es:[0x72cc], 0x1f4
007d jl 0x25fe
007f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _CompactListR
0084 mov es, word ptr [0xc336]
0088 cmp word ptr es:[0x72cc], 0x1f4
008f jge 0x2666
0091 mov di, word ptr [bp + 8]
0094 mov si, word ptr [bp + 6]
0097 mov es, word ptr [0xc318]
009b mov al, byte ptr es:[di + 0x334c]
00a0 sub ah, ah
00a2 push ax
00a3 mov al, byte ptr es:[di + 0x2b78]
00a8 push ax
00a9 mov al, byte ptr es:[di + 0x2f62]
00ae and ax, 0xf8
00b1 add ax, 4
00b4 push ax
00b5 push 1
00b7 push si
00b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToRList
00bd add sp, 0xa
00c0 mov es, word ptr [0xc338]
00c4 cmp byte ptr es:[si - 0x7cee], 0
00ca je 0x2651
00cc push 1
00ce push si
00cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 210, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
00d4 add sp, 4
00d7 xor al, al
00d9 mov es, word ptr [0xc318]
00dd mov byte ptr es:[di + 0x2f62], al
00e2 mov bx, word ptr [bp + 4]
00e5 shl bx, 6
00e8 mov byte ptr [bx + si + 0x68e8], al
00ec pop si
00ed pop di
00ee leave 
00ef ret 
```

## Known declaration examples

- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far DigTileB(int x, int y);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far DigTileR(int x, int y);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoForageAnt', 'offset': 7746, 'source': None, 'size': 1126}
- {'symbol': '_DoRecruitAnt', 'offset': 8872, 'source': None, 'size': 722}
- {'symbol': '_StartFightA', 'offset': 9834, 'source': 'src/recovered/wf_StartFightA-b2f3e31b2f.c', 'size': 137}
- {'symbol': '_GetWinner', 'offset': 9972, 'source': None, 'size': 241}
