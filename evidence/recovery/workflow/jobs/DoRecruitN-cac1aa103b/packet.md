# Recovery task _DoRecruitN

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 232 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 cmp word ptr [0xce80], 2 ; _MePlane
000b je 0x398a
000d push word ptr [bp + 0xa]
0010 push word ptr [bp + 8]
0013 push word ptr [bp + 6]
0016 nop 
0017 push cs
0018 call 0x4eb0 ; _DoDigOutB
001b jmp 0x3a4d
001e mov di, word ptr [bp + 6]
0021 mov bx, di
0023 shl bx, 6
0026 add bx, word ptr [bp + 8]
0029 add bx, 0x88e8
002d mov word ptr [bp - 6], bx
0030 mov al, byte ptr [bx]
0032 sub ah, ah
0034 mov si, ax
0036 push si
0037 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 58, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
003c add sp, 2
003f dec ax
0040 jne 0x39ce
0042 cmp word ptr [0xce98], 0 ; _MeColor
0047 je 0x39ce
0049 mov es, word ptr [0xc350]
004d push word ptr es:[0x9b6a]
0052 push 2
0054 nop 
0055 push cs
0056 call 0x823e ; _YellowFight
0059 add sp, 4
005c mov si, 1
005f jmp 0x3a24
0061 nop 
0062 cmp si, 0x87
0066 jle 0x3a22
0068 cmp si, 0xe8
006c jge 0x3a22
006e push si
006f push word ptr [bp + 8]
0072 push di
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
0078 add sp, 6
007b mov word ptr [bp - 2], ax
007e or ax, ax
0080 jl 0x3a22
0082 push word ptr [bp + 0xa]
0085 push si
0086 call 0x26f4 ; _GetWinner
0089 add sp, 4
008c mov es, word ptr [0xc352]
0090 mov bx, word ptr [bp - 2]
0093 mov byte ptr es:[bx + 0x3f0e], al
0098 and al, 0x80
009a add al, 0x70
009c mov byte ptr es:[bx + 0x3d18], al
00a1 mov si, word ptr [bp - 6]
00a4 mov byte ptr [si], al
00a6 mov byte ptr es:[bx + 0x3b22], 0xa
00ac mov word ptr [bp - 4], 1
00b1 mov si, word ptr [bp - 4]
00b4 jmp 0x3a24
00b6 xor si, si
00b8 dec si
00b9 je 0x3a50
00bb mov al, byte ptr [bp + 0xa]
00be and ax, 7
00c1 push ax
00c2 push word ptr [bp + 8]
00c5 push di
00c6 nop 
00c7 push cs
00c8 call 0x439e ; _TryMoveDirB
00cb add sp, 6
00ce or ax, ax
00d0 jne 0x3a50
00d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
00d7 push ax
00d8 push word ptr [bp + 8]
00db push di
00dc nop 
00dd push cs
00de call 0x439e ; _TryMoveDirB
00e1 add sp, 6
00e4 pop si
00e5 pop di
00e6 leave 
00e7 retf 
```

## Known declaration examples

- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_StartFightA-b2f3e31b2f.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MeColor;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_GetRandDir-2664e9d7f9.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far TryMoveDirB(int x, int y, int dir);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoDrownB', 'offset': 14244, 'source': None, 'size': 210}
- {'symbol': '_DoRandB', 'offset': 14454, 'source': None, 'size': 246}
- {'symbol': '_DoNestFightB', 'offset': 14932, 'source': None, 'size': 334}
- {'symbol': '_CheckNestFightB', 'offset': 15266, 'source': 'src/recovered/wf_CheckNestFightB-6daf29ea80.c', 'size': 154}
