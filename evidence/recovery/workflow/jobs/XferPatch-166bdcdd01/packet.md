# Recovery task _XferPatch

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 385 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0009 mov ds, ax
000b mov si, word ptr [0x78a0]
000f mov di, word ptr [0x789e]
0013 mov <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0016 mov es, ax
0018 cmp di, word ptr es:[0x7a60]
001d jne 0xabb6
001f cmp word ptr es:[0x7a62], si
0024 je 0xabdc
0026 mov <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0029 mov es, ax
002b cmp word ptr es:[0x80b4], 2
0031 je 0xabe2
0033 push ss
0034 pop ds
0035 push 0x7e
0037 push 0
0039 push 1
003b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0040 add sp, 6
0043 push 1
0045 push 0x2710
0048 jmp 0xad03
004b nop 
004c push ss
004d pop ds
004e pop si
004f pop di
0050 leave 
0051 retf 
0052 push ss
0053 pop ds
0054 cmp word ptr [0xac90], 1 ; _ColonyTotalBlack
0059 jg 0xac08
005b cmp word ptr [0xac82], 1 ; _BpopT
0060 jg 0xac08
0062 push 0x7e
0064 push 0
0066 push 1
0068 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 107, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
006d add sp, 6
0070 push 1
0072 push 0x2712
0075 jmp 0xad03
0078 mov es, word ptr [0xc106]
007c mov bx, di
007e shl bx, 4
0081 add bx, si
0083 mov word ptr [bp - 2], bx
0086 cmp byte ptr es:[bx + 0xa4], 1
008c jae 0xac48
008e cmp word ptr [0xcc84], 0x40 ; _MeType
0093 jne 0xac31
0095 mov es, word ptr [0xc108]
0099 cmp word ptr es:[0x8a6c], 0
009f je 0xac48
00a1 push 0x7e
00a3 push 0
00a5 push 1
00a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00ac add sp, 6
00af push 1
00b1 push 0x2714
00b4 jmp 0xad03
00b7 nop 
00b8 push 0x7e
00ba push 0x2afa
00bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 192, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
00c2 add sp, 4
00c5 mov es, word ptr [0xc0f2]
00c9 mov word ptr es:[0x7a60], di
00ce mov word ptr es:[0x7a62], si
00d3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 214, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMap
00d8 mov es, word ptr [0xc10a]
00dc mov word ptr es:[0x9c70], 1
00e3 xor ax, ax
00e5 mov word ptr [0xac8c], ax ; _QueenStorageB
00e8 mov word ptr [0xac8e], ax ; _QueenStorageR
00eb mov es, word ptr [0xc10c]
00ef mov word ptr es:[0x807a], ax
00f3 mov es, word ptr [0xc10e]
00f7 mov word ptr es:[0x9c26], ax
00fb nop 
00fc push cs
00fd call 0x96c4 ; _InvalQueenStorageDisp
0100 mov es, word ptr [0xc108]
0104 mov word ptr es:[0x8a6c], 1
010b push si
010c push di
010d mov es, word ptr [0xc110]
0111 mov bx, word ptr [bp - 2]
0114 mov al, byte ptr es:[bx + 0x164]
0119 sub ah, ah
011b push ax
011c mov es, word ptr [0xc106]
0120 mov al, byte ptr es:[bx + 0xa4]
0125 push ax
0126 mov es, word ptr [0xc0de]
012a mov bx, si
012c shl bx, 1
012e add bx, si
0130 shl bx, 2
0133 add bx, di
0135 shl bx, 1
0137 push word ptr es:[bx + 0x224]
013c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 319, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _RandWorld
0141 add sp, 0xa
0144 mov es, word ptr [0xc110]
0148 mov bx, word ptr [bp - 2]
014b cmp byte ptr es:[bx + 0x164], 0
0151 jne 0xace9
0153 mov word ptr [0xac88], 0 ; _HealthR
0159 nop 
015a push cs
015b call 0x10aa8
015e mov ax, word ptr [bp - 2]
0161 cmp ax, 0x24
0164 jle 0xacfe
0166 push 0
0168 push 0x2716
016b jmp 0xad03
016d nop 
016e push 0
0170 push 0x2717
0173 push 0
0175 nop 
0176 push cs
0177 call 0x615a ; _PictStrnDialog
017a add sp, 6
017d pop si
017e pop di
017f leave 
0180 retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int near BpopT;` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far DrawMap(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMap(void);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int near HealthR;` — src/recovered/wf_tu_simant1_5344_DoAntSimR_8_scaffold-5f66a96585.c
- `extern int near HealthR;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near MeType;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_tu_simant_6A38_SetAlarmDropState_2_scaffold-bb12a76f6c.c
- `extern int near MeType;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near QueenStorageB;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageB;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern int near QueenStorageR;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageR;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern void far RandWorld(int seed, int blackSize, int redSize, int mapWidth, int mapKind);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far myBeginSong(unsigned int song, unsigned int priority);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSong(unsigned int song, unsigned int mode);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_SetAlarmDropState_2_scaffold-bb12a76f6c.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GotoBQueen', 'offset': 43702, 'source': None, 'size': 205}
- {'symbol': '_GotoRQueen', 'offset': 43908, 'source': 'src/recovered/GotoRQueen.c', 'size': 12}
- {'symbol': '_PlaceQueenInYard', 'offset': 44306, 'source': None, 'size': 937}
- {'symbol': '_MysteryButton', 'offset': 45244, 'source': None, 'size': 616}
