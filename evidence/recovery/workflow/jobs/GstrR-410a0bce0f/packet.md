# Recovery task _GstrR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 332 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 mov <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0008 mov ds, ax
000a cmp word ptr [0x8078], 0
000f jne 0x3e7
0011 mov ax, word ptr ss:[0xaca6]
0015 add ax, word ptr ss:[0xaca8]
001a cmp ax, 0x14
001d jle 0x3e7
001f mov word ptr [0x8078], 0xc8
0025 mov bx, 0x78dc
0028 mov <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
002b mov es, ax
002d mov word ptr [bp - 4], bx
0030 mov word ptr [bp - 2], es
0033 cmp word ptr es:[bx], 0
0037 je 0x406
0039 dec word ptr es:[bx]
003c xor ax, ax
003e push ss
003f pop ds
0040 pop di
0041 leave 
0042 retf 
0043 nop 
0044 mov cx, word ptr ss:[0xac88]
0049 cmp cx, 0xa
004c jge 0x476
004e mov bx, word ptr ss:[0xac82]
0053 mov ax, word ptr ss:[0xac84]
0057 sar ax, 1
0059 cmp ax, bx
005b jle 0x476
005d or bx, bx
005f jle 0x476
0061 mov <resolved loader operand; see bindings> ; [{'operand_offset': 98, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0064 mov es, ax
0066 cmp word ptr es:[0x78e8], 0
006c jle 0x476
006e push ss
006f pop ds
0070 push 0x64
0072 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 117, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0077 add sp, 2
007a add ax, 0x1e
007d les bx, ptr [bp - 4]
0080 mov word ptr es:[bx], ax
0083 push 0x3f
0085 push 0x2b0a
0088 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 139, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
008d add sp, 4
0090 push 0
0092 push 0
0094 push 0x78
0096 mov es, word ptr [0xc4ce]
009a les bx, ptr es:[0x7c94]
009f push word ptr es:[bx + 0x16]
00a3 push word ptr es:[bx + 0x14]
00a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _EditMessage
00ac add sp, 0xa
00af xor ax, ax
00b1 pop di
00b2 leave 
00b3 retf 
00b4 cmp cx, 0x1e
00b7 jge 0x482
00b9 mov ax, 5
00bc jmp 0x400
00bf nop 
00c0 cmp cx, 0x32
00c3 jge 0x48e
00c5 mov ax, 4
00c8 jmp 0x400
00cb nop 
00cc mov di, word ptr ss:[0xac84]
00d1 mov <resolved loader operand; see bindings> ; [{'operand_offset': 210, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00d4 mov es, ax
00d6 cmp word ptr es:[0x7a56], di
00db jge 0x4a6
00dd mov ax, 3
00e0 jmp 0x400
00e3 nop 
00e4 mov ax, di
00e6 shl ax, 1
00e8 cmp word ptr es:[0x7a56], ax
00ed jge 0x4b8
00ef mov ax, 2
00f2 jmp 0x400
00f5 nop 
00f6 cmp di, 0x64
00f9 jle 0x4e2
00fb mov bx, word ptr ss:[0xac82]
0100 or bx, bx
0102 jle 0x4e2
0104 mov <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0107 mov es, ax
0109 cmp word ptr es:[0x78e8], 0
010f jle 0x4e2
0111 mov ax, di
0113 mov cx, 3
0116 cdq 
0117 idiv cx
0119 cmp ax, bx
011b jle 0x4e2
011d jmp 0x430
0120 push ss
0121 pop ds
0122 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 293, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
0127 or ax, ax
0129 jne 0x508
012b mov dx, word ptr [0xac84] ; _RpopT
012f cmp dx, 0x14
0132 jle 0x508
0134 cmp word ptr [0xac82], dx ; _BpopT
0138 jge 0x508
013a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 317, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand128
013f or ax, ax
0141 jne 0x508
0143 jmp 0x432
0146 mov ax, 1
0149 pop di
014a leave 
014b retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int near BpopT;` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far EditMessage(int first,int second,int width,int fourth,int fifth);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern int near RpopT;` — src/recovered/wf_tu_simant1_5344_DoAntSimR_8_scaffold-5f66a96585.c
- `extern int near RpopT;` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far SRand128(void);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int far SRand32(void);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int far SRand32(void);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_8_scaffold-5f66a96585.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far myBeginSong(unsigned int song, unsigned int priority);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSong(unsigned int song, unsigned int mode);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetCasteProd', 'offset': 622, 'source': None, 'size': 183}
- {'symbol': '_SetModeProd', 'offset': 806, 'source': 'src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c', 'size': 156}
- {'symbol': '_StartAttack', 'offset': 1294, 'source': 'src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c', 'size': 66}
- {'symbol': '_ForceModeA', 'offset': 1360, 'source': None, 'size': 210}
