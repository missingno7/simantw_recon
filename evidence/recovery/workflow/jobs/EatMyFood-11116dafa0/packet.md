# Recovery task _EatMyFood

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 443 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov si, word ptr [bp + 6]
0008 mov ax, si
000a or ax, ax
000c je 0x8cf4
000e dec ax
000f je 0x8d10
0011 dec ax
0012 je 0x8d42
0014 dec ax
0015 je 0x8d5c
0017 jmp 0x8dc2
001a push 0x7e
001c push 0
001e push 0x2c
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0025 add sp, 6
0028 push 1
002a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetDefaultWindPrompt
002f add sp, 2
0032 jmp 0x8dc2
0035 nop 
0036 push -1
0038 push 0x2396
003b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YellowDialog
0040 add sp, 4
0043 mov es, word ptr [0xc4ae]
0047 sub ax, ax
0049 mov word ptr es:[0x9ea0], ax
004d mov word ptr es:[0x9e9e], ax
0051 push ax
0052 push ax
0053 push 0x78
0055 mov es, word ptr [0xc4b0]
0059 les bx, ptr es:[0x737a]
005e push word ptr es:[bx + 0x2e]
0062 push word ptr es:[bx + 0x2c]
0066 jmp 0x8dba
0068 push 0
006a push 0
006c push 0x78
006e mov es, word ptr [0xc4b0]
0072 les bx, ptr es:[0x737a]
0077 push word ptr es:[bx + 0x32]
007b push word ptr es:[bx + 0x30]
007f jmp 0x8dba
0081 nop 
0082 push 0x7e
0084 push 0
0086 push 0x2c
0088 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 139, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
008d add sp, 6
0090 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 147, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySoundIsDone
0095 or ax, ax
0097 jne 0x8d88
0099 push 0
009b push 5
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 160, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _myDelay
00a2 add sp, 4
00a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 168, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mySoundIsDone
00aa or ax, ax
00ac je 0x8d73
00ae push 0x7e
00b0 push 0
00b2 push 0xa
00b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 183, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
00b9 add sp, 6
00bc mov es, word ptr [0xc4ae]
00c0 sub ax, ax
00c2 mov word ptr es:[0x9ea0], ax
00c6 mov word ptr es:[0x9e9e], ax
00ca push ax
00cb push ax
00cc push 0xb4
00cf mov es, word ptr [0xc4b0]
00d3 les bx, ptr es:[0x737a]
00d8 push word ptr es:[bx + 0x36]
00dc push word ptr es:[bx + 0x34]
00e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 227, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _EditMessage
00e5 add sp, 0xa
00e8 cmp si, 2
00eb je 0x8e2e
00ed mov di, word ptr [0xac8a] ; _MeHealth
00f1 lea ax, [di + 0x64]
00f4 cmp ax, 0x64
00f7 jle 0x8dfa
00f9 dec si
00fa je 0x8dfa
00fc mov bx, word ptr [0xac82] ; _BpopT
0100 lea ax, [bx - 1]
0103 or ax, ax
0105 jle 0x8dfa
0107 mov ax, di
0109 lea cx, [bx - 1]
010c cdq 
010d idiv cx
010f add word ptr [0xac86], ax ; _HealthB
0113 cmp word ptr [0xac86], 0x64 ; _HealthB
0118 jle 0x8dfa
011a mov word ptr [0xac86], 0x64 ; _HealthB
0120 sub ax, ax
0122 add ax, 0x64
0125 mov word ptr [0xac8a], ax ; _MeHealth
0128 mov es, word ptr [0xc49c]
012c mov word ptr es:[0x9cf0], 0
0133 mov es, word ptr [0xc49e]
0137 cmp word ptr es:[0x9bec], ax
013c jge 0x8e86
013e cmp ax, 0xa
0141 jl 0x8e86
0143 mov es, word ptr [0xc4a0]
0147 mov word ptr es:[0x9af2], 0
014e pop si
014f pop di
0150 leave 
0151 retf 
0152 nop 
0153 nop 
0154 mov bx, word ptr [0xac8a] ; _MeHealth
0158 cmp bx, 0xa
015b jle 0x8e91
015d lea cx, [bx - 0xa]
0160 mov es, word ptr [0xc49a]
0164 cmp word ptr es:[0x8a5e], 0
016a jne 0x8e4a
016c mov bx, cx
016e jmp 0x8e4d
0170 mov bx, 0x64
0173 or bx, bx
0175 jle 0x8e5c
0177 mov es, word ptr [0xc49c]
017b mov word ptr es:[0x9cf0], 0
0182 cmp bx, 0x64
0185 jle 0x8e66
0187 mov bx, 0x64
018a jmp 0x8e6c
018c or bx, bx
018e jge 0x8e6c
0190 xor bx, bx
0192 mov es, word ptr [0xc49e]
0196 cmp word ptr es:[0x9bec], bx
019b jge 0x8e82
019d cmp bx, 0xa
01a0 jl 0x8e82
01a2 mov word ptr [0xac8a], bx ; _MeHealth
01a6 jmp 0x8e1d
01a8 mov word ptr [0xac8a], bx ; _MeHealth
01ac mov es, word ptr [0xc4a0]
01b0 mov word ptr es:[0x9af2], 1
01b7 pop si
01b8 pop di
01b9 leave 
01ba retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int near BpopT;` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far EditMessage(int first,int second,int width,int fourth,int fifth);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern int near HealthB;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_10_scaffold-f17e6a990c.c
- `extern int near HealthB;` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern int near HealthB;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near MeHealth;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeHealth;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_SetAlarmDropState_2_scaffold-bb12a76f6c.c
- `extern void far myDelay(unsigned long ticks);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int far mySoundIsDone(void);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FindLifeAt', 'offset': 35478, 'source': None, 'size': 473}
- {'symbol': '_SetMyHealth', 'offset': 35952, 'source': None, 'size': 105}
- {'symbol': '_PickupMyEgg', 'offset': 36502, 'source': 'src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c', 'size': 181}
- {'symbol': '_PickupMyFood', 'offset': 36684, 'source': None, 'size': 672}
