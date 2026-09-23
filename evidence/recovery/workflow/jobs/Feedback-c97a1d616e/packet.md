# Recovery task _Feedback

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 453 bytes.

```asm
0000 enter 0xc, 0
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0007 mov es, ax
0009 cmp word ptr es:[0x80b4], 0
000f jne 0x7942
0011 mov <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0014 mov es, ax
0016 inc word ptr es:[0x85ec]
001b cmp word ptr es:[0x85ec], 0x400
0022 jle 0x78f5
0024 mov word ptr es:[0x85ec], 0
002b test byte ptr es:[0x85ec], 7
0031 jne 0x7942
0033 mov bx, 0x7d62
0036 mov <resolved loader operand; see bindings> ; [{'operand_offset': 55, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0039 mov es, ax
003b mov word ptr [bp - 4], bx
003e mov word ptr [bp - 2], es
0041 inc word ptr es:[bx]
0044 mov bx, 0x85f0
0047 mov <resolved loader operand; see bindings> ; [{'operand_offset': 72, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
004a mov es, ax
004c mov word ptr [bp - 8], bx
004f mov word ptr [bp - 6], es
0052 cmp word ptr es:[bx], 0
0056 jne 0x7946
0058 push ss
0059 pop ds
005a mov es, word ptr [0xc65c]
005e push word ptr es:[0x85ee]
0063 nop 
0064 push cs
0065 call 0x7b4e ; _GiveLesson
0068 add sp, 2
006b les bx, ptr [bp - 8]
006e mov word ptr es:[bx], 1
0073 les bx, ptr [bp - 4]
0076 jmp 0x798d
0078 push ss
0079 pop ds
007a jmp 0x7992
007c push ss
007d pop ds
007e mov es, word ptr [0xc65c]
0082 push word ptr es:[0x85ee]
0087 nop 
0088 push cs
0089 call 0x7f02 ; _LessonDone
008c add sp, 2
008f or ax, ax
0091 je 0x7968
0093 mov es, word ptr [0xc65c]
0097 inc word ptr es:[0x85ee]
009c jmp 0x798a
009e les bx, ptr [bp - 4]
00a1 cmp word ptr es:[bx], 0xf
00a5 jle 0x7992
00a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00ac mov es, word ptr [0xc65e]
00b0 cmp dx, word ptr es:[0x9b12]
00b5 jl 0x7992
00b7 jg 0x798a
00b9 cmp ax, word ptr es:[0x9b10]
00be jbe 0x7992
00c0 les bx, ptr [bp - 8]
00c3 mov word ptr es:[bx], 0
00c8 mov es, word ptr [0xc660]
00cc cmp word ptr es:[0x85fa], 0
00d2 jne 0x79a1
00d4 jmp 0x7a8d
00d7 mov es, word ptr [0xc662]
00db mov ax, word ptr es:[0x9fe8]
00df mov word ptr [bp - 0xa], ax
00e2 or ax, ax
00e4 jne 0x7a04
00e6 mov bx, word ptr [0xac8a] ; _MeHealth
00ea mov es, word ptr [0xc664]
00ee cmp word ptr es:[0x9bec], bx
00f3 jg 0x79c4
00f5 cmp bx, 0xa
00f8 jge 0x7a04
00fa cmp bx, 0xa
00fd jge 0x79ea
00ff push 1
0101 push 0
0103 push 0x78
0105 mov es, word ptr [0xc666]
0109 les bx, ptr es:[0x7c94]
010e push word ptr es:[bx + 2]
0112 push word ptr es:[bx]
0115 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 280, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _EditMessage
011a add sp, 0xa
011d leave 
011e retf 
011f nop 
0120 push 0
0122 push 0
0124 push 0x78
0126 mov es, word ptr [0xc666]
012a les bx, ptr es:[0x7c94]
012f push word ptr es:[bx + 6]
0133 push word ptr es:[bx + 4]
0137 jmp 0x79df
0139 nop 
013a mov ax, word ptr [0xac86] ; _HealthB
013d mov es, word ptr [0xc668]
0141 cmp word ptr es:[0x769c], ax
0146 jle 0x7a2c
0148 push 0
014a push 0
014c push 0x78
014e mov es, word ptr [0xc666]
0152 les bx, ptr es:[0x7c94]
0157 push word ptr es:[bx + 0xa]
015b push word ptr es:[bx + 8]
015f jmp 0x79df
0161 nop 
0162 mov es, word ptr [0xc66a]
0166 mov ax, word ptr es:[0x72c8]
016a mov word ptr [bp - 0xc], ax
016d cmp ax, word ptr [0xac82] ; _BpopT
0171 jge 0x7a86
0173 cmp word ptr [bp - 0xa], 0
0177 jne 0x7a6c
0179 mov es, word ptr [0xc66c]
017d cmp word ptr es:[0x8a6c], 0
0183 jne 0x7a6c
0185 or ax, ax
0187 jne 0x7a6c
0189 push ax
018a push ax
018b push 0x78
018d mov es, word ptr [0xc666]
0191 les bx, ptr es:[0x7c94]
0196 push word ptr es:[bx + 0xe]
019a push word ptr es:[bx + 0xc]
019e jmp 0x79df
01a1 nop 
01a2 push 0
01a4 push 0
01a6 push 0x78
01a8 mov es, word ptr [0xc666]
01ac les bx, ptr es:[0x7c94]
01b1 push word ptr es:[bx + 0x12]
01b5 push word ptr es:[bx + 0x10]
01b9 jmp 0x79df
01bc push 0
01be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 449, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetDefaultWindPrompt
01c3 leave 
01c4 retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near BpopT;` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern int near BpopT;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far EditMessage(int first,int second,int width,int fourth,int fifth);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern int near HealthB;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near HealthB;` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern int near HealthB;` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near MeHealth;` — src/recovered/wf_SetMyHealth-5d15d1e8e5.c
- `extern int near MeHealth;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near MeHealth;` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_OverlayOutsideTiles', 'offset': 30898, 'source': 'src/recovered/OverlayOutsideTiles.c', 'size': 12}
- {'symbol': '_OverlayInsideTiles', 'offset': 30910, 'source': 'src/recovered/OverlayInsideTiles.c', 'size': 12}
- {'symbol': '_RunTutor', 'offset': 31376, 'source': None, 'size': 190}
- {'symbol': '_GiveLesson', 'offset': 31566, 'source': None, 'size': 948}
