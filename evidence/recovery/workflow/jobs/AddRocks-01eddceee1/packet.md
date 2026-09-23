# Recovery task _AddRocks

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 440 bytes.

```asm
0000 push di
0001 push si
0002 push 3
0004 nop 
0005 push cs
0006 call 0x158a ; _SRand1
0009 add sp, 2
000c mov di, ax
000e add di, 2
0011 or di, di
0013 jg 0x434c
0015 jmp 0x4414
0018 mov si, di
001a push 0
001c push 0x3a
001e nop 
001f push cs
0020 call 0x158a ; _SRand1
0023 add sp, 2
0026 push ax
0027 push 0x7a
0029 nop 
002a push cs
002b call 0x158a ; _SRand1
002e add sp, 2
0031 push ax
0032 nop 
0033 push cs
0034 call 0x44ec ; _AddRock5
0037 add sp, 6
003a push 1
003c push 0x3a
003e nop 
003f push cs
0040 call 0x158a ; _SRand1
0043 add sp, 2
0046 push ax
0047 push 0x7a
0049 nop 
004a push cs
004b call 0x158a ; _SRand1
004e add sp, 2
0051 push ax
0052 nop 
0053 push cs
0054 call 0x44ec ; _AddRock5
0057 add sp, 6
005a push 2
005c push 0x3a
005e nop 
005f push cs
0060 call 0x158a ; _SRand1
0063 add sp, 2
0066 push ax
0067 push 0x7a
0069 nop 
006a push cs
006b call 0x158a ; _SRand1
006e add sp, 2
0071 push ax
0072 nop 
0073 push cs
0074 call 0x44ec ; _AddRock5
0077 add sp, 6
007a push 3
007c push 0x3a
007e nop 
007f push cs
0080 call 0x158a ; _SRand1
0083 add sp, 2
0086 push ax
0087 push 0x7a
0089 nop 
008a push cs
008b call 0x158a ; _SRand1
008e add sp, 2
0091 push ax
0092 nop 
0093 push cs
0094 call 0x44ec ; _AddRock5
0097 add sp, 6
009a push 4
009c push 0x3a
009e nop 
009f push cs
00a0 call 0x158a ; _SRand1
00a3 add sp, 2
00a6 push ax
00a7 push 0x7a
00a9 nop 
00aa push cs
00ab call 0x158a ; _SRand1
00ae add sp, 2
00b1 push ax
00b2 nop 
00b3 push cs
00b4 call 0x44ec ; _AddRock5
00b7 add sp, 6
00ba push 5
00bc push 0x3a
00be nop 
00bf push cs
00c0 call 0x158a ; _SRand1
00c3 add sp, 2
00c6 push ax
00c7 push 0x7a
00c9 nop 
00ca push cs
00cb call 0x158a ; _SRand1
00ce add sp, 2
00d1 push ax
00d2 nop 
00d3 push cs
00d4 call 0x44ec ; _AddRock5
00d7 add sp, 6
00da dec si
00db je 0x4414
00dd jmp 0x434e
00e0 mov ax, di
00e2 shl ax, 1
00e4 or ax, ax
00e6 jg 0x441f
00e8 jmp 0x44e9
00eb mov si, di
00ed shl si, 1
00ef push 0
00f1 push 0x3c
00f3 nop 
00f4 push cs
00f5 call 0x158a ; _SRand1
00f8 add sp, 2
00fb push ax
00fc push 0x7c
00fe nop 
00ff push cs
0100 call 0x158a ; _SRand1
0103 add sp, 2
0106 push ax
0107 nop 
0108 push cs
0109 call 0x45ac ; _AddRock3
010c add sp, 6
010f push 1
0111 push 0x3c
0113 nop 
0114 push cs
0115 call 0x158a ; _SRand1
0118 add sp, 2
011b push ax
011c push 0x7c
011e nop 
011f push cs
0120 call 0x158a ; _SRand1
0123 add sp, 2
0126 push ax
0127 nop 
0128 push cs
0129 call 0x45ac ; _AddRock3
012c add sp, 6
012f push 2
0131 push 0x3c
0133 nop 
0134 push cs
0135 call 0x158a ; _SRand1
0138 add sp, 2
013b push ax
013c push 0x7c
013e nop 
013f push cs
0140 call 0x158a ; _SRand1
0143 add sp, 2
0146 push ax
0147 nop 
0148 push cs
0149 call 0x45ac ; _AddRock3
014c add sp, 6
014f push 3
0151 push 0x3c
0153 nop 
0154 push cs
0155 call 0x158a ; _SRand1
0158 add sp, 2
015b push ax
015c push 0x7c
015e nop 
015f push cs
0160 call 0x158a ; _SRand1
0163 add sp, 2
0166 push ax
0167 nop 
0168 push cs
0169 call 0x45ac ; _AddRock3
016c add sp, 6
016f push 4
0171 push 0x3c
0173 nop 
0174 push cs
0175 call 0x158a ; _SRand1
0178 add sp, 2
017b push ax
017c push 0x7c
017e nop 
017f push cs
0180 call 0x158a ; _SRand1
0183 add sp, 2
0186 push ax
0187 nop 
0188 push cs
0189 call 0x45ac ; _AddRock3
018c add sp, 6
018f push 5
0191 push 0x3c
0193 nop 
0194 push cs
0195 call 0x158a ; _SRand1
0198 add sp, 2
019b push ax
019c push 0x7c
019e nop 
019f push cs
01a0 call 0x158a ; _SRand1
01a3 add sp, 2
01a6 push ax
01a7 nop 
01a8 push cs
01a9 call 0x45ac ; _AddRock3
01ac add sp, 6
01af dec si
01b0 je 0x44e9
01b2 jmp 0x4423
01b5 pop si
01b6 pop di
01b7 retf 
```

## Known declaration examples

- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FillMapLegs', 'offset': 16298, 'source': None, 'size': 503}
- {'symbol': '_MakeYardPatch', 'offset': 16802, 'source': None, 'size': 401}
- {'symbol': '_AddRock5', 'offset': 17644, 'source': None, 'size': 191}
- {'symbol': '_AddRock3', 'offset': 17836, 'source': None, 'size': 188}
