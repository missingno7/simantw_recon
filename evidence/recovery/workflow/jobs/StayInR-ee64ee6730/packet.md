# Recovery task _StayInR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 249 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 6]
000c mov bx, si
000e shl bx, 6
0011 add bx, di
0013 mov word ptr [bp - 4], bx
0016 cmp byte ptr [bx + 0x58e8], 0x10
001b jb 0x5c82
001d cmp byte ptr [bx + 0x58e8], 0x13
0022 ja 0x5c82
0024 cmp byte ptr [bx + 0x58e8], 0x10
0029 jne 0x5c50
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0030 mov bx, word ptr [bp - 4]
0033 mov byte ptr [bx + 0x58e8], al
0037 jmp 0x5c54
0039 nop 
003a dec byte ptr [bx + 0x58e8]
003e mov es, word ptr [0xc394]
0042 cmp word ptr es:[0x72de], 0
0048 jle 0x5c65
004a dec word ptr es:[0x72de]
004f mov es, word ptr [0xc384]
0053 mov bx, word ptr es:[0x9b6a]
0058 mov es, word ptr [0xc386]
005c mov byte ptr es:[bx + 0x44f0], 3
0062 or byte ptr es:[bx + 0x46e6], 8
0068 jmp 0x5cff
006a nop 
006b nop 
006c push 3
006e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 113, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0073 add sp, 2
0076 add al, byte ptr [bp + 0xa]
0079 sub al, 2
007b and ax, 7
007e mov word ptr [bp - 2], ax
0081 mov es, word ptr [0xc384]
0085 mov bx, word ptr es:[0x9b6a]
008a mov es, word ptr [0xc386]
008e mov al, byte ptr es:[bx + 0x46e6]
0093 and al, 0xf8
0095 or al, byte ptr [bp - 2]
0098 mov byte ptr es:[bx + 0x46e6], al
009d push word ptr [bp - 2]
00a0 push di
00a1 push si
00a2 nop 
00a3 push cs
00a4 call 0x6850 ; _TryMoveDirR
00a7 add sp, 6
00aa or ax, ax
00ac jne 0x5d0b
00ae mov al, byte ptr [bp + 0xa]
00b1 and ax, 7
00b4 push ax
00b5 push di
00b6 push si
00b7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 186, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetEnterDirR
00bc add sp, 6
00bf or ax, ax
00c1 jge 0x5ce3
00c3 push 8
00c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 200, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00ca add sp, 2
00cd push ax
00ce push di
00cf push si
00d0 nop 
00d1 push cs
00d2 call 0x6850 ; _TryMoveDirR
00d5 add sp, 6
00d8 or ax, ax
00da jne 0x5d0b
00dc mov es, word ptr [0xc384]
00e0 mov bx, word ptr es:[0x9b6a]
00e5 mov es, word ptr [0xc386]
00e9 mov al, byte ptr es:[bx + 0x46e6]
00ee mov bx, word ptr [bp - 4]
00f1 mov byte ptr [bx - 0x6718], al
00f5 pop si
00f6 pop di
00f7 leave 
00f8 retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_GetRandDir-2664e9d7f9.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far TryMoveDirR(int x, int y, int dir);` — src/recovered/wf_RaidOutR-a39ba19d03.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoNestAntR', 'offset': 21412, 'source': None, 'size': None}
- {'symbol': '_RaidInR', 'offset': 23338, 'source': None, 'size': 235}
- {'symbol': '_RaidOutR', 'offset': 23824, 'source': 'src/recovered/wf_RaidOutR-a39ba19d03.c', 'size': 110}
- {'symbol': '_DoRestR', 'offset': 23934, 'source': None, 'size': 298}
