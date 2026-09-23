# Recovery task _SmoothEdgesR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 362 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 or si, si
000b jge 0x26f4
000d jmp 0x284a
0010 cmp si, 0x3f
0013 jle 0x26fc
0015 jmp 0x284a
0018 mov di, word ptr [bp + 8]
001b cmp di, 0x3f
001e jle 0x2707
0020 jmp 0x284a
0023 or di, di
0025 jne 0x2728
0027 mov bx, si
0029 shl bx, 6
002c add bx, di
002e mov word ptr [bp - 6], bx
0031 cmp byte ptr [bx + 0x58e8], 0x30
0036 jb 0x271f
0038 jmp 0x284a
003b mov byte ptr [bx + 0x58e8], 0x18
0040 pop si
0041 pop di
0042 leave 
0043 retf 
0044 mov bx, si
0046 shl bx, 6
0049 add bx, di
004b mov word ptr [bp - 6], bx
004e mov al, byte ptr [bx + 0x58e8]
0052 sub ah, ah
0054 mov word ptr [bp - 2], ax
0057 cmp ax, 0x20
005a jge 0x2743
005c jmp 0x284a
005f cmp ax, 0x2f
0062 jle 0x2750
0064 cmp ax, 0x4f
0067 jge 0x2750
0069 jmp 0x284a
006c cmp ax, 0x4d
006f jle 0x275a
0071 mov ax, 0x2f
0074 jmp 0x275c
0076 xor ax, ax
0078 mov word ptr [bp - 2], ax
007b xor dx, dx
007d cmp di, 2
0080 jl 0x2787
0082 mov word ptr [bp - 4], dx
0085 mov dl, byte ptr [bx + 0x58e7]
0089 cmp dx, 0x20
008c jge 0x2776
008e xor dx, dx
0090 jmp 0x2783
0092 cmp dx, 0x2f
0095 jle 0x2780
0097 cmp dx, 0x4f
009a jl 0x2772
009c mov dx, 1
009f or dx, dx
00a1 je 0x2792
00a3 mov dx, 1
00a6 cmp si, 0x3e
00a9 jle 0x2798
00ab jmp 0x27bb
00ad nop 
00ae mov dx, word ptr [bp - 4]
00b1 jmp 0x278a
00b3 nop 
00b4 mov bx, word ptr [bp - 6]
00b7 mov cl, byte ptr [bx + 0x5928]
00bb sub ch, ch
00bd cmp cx, 0x20
00c0 jge 0x27aa
00c2 xor cx, cx
00c4 jmp 0x27b7
00c6 cmp cx, 0x2f
00c9 jle 0x27b4
00cb cmp cx, 0x4f
00ce jl 0x27a6
00d0 mov cx, 1
00d3 or cx, cx
00d5 je 0x27be
00d7 or dl, 2
00da cmp di, 0x3e
00dd jg 0x27e7
00df mov bx, word ptr [bp - 6]
00e2 mov cl, byte ptr [bx + 0x58e9]
00e6 sub ch, ch
00e8 cmp cx, 0x20
00eb jge 0x27d6
00ed xor cx, cx
00ef jmp 0x27e3
00f1 nop 
00f2 cmp cx, 0x2f
00f5 jle 0x27e0
00f7 cmp cx, 0x4f
00fa jl 0x27d1
00fc mov cx, 1
00ff or cx, cx
0101 je 0x27ea
0103 or dl, 4
0106 cmp si, 1
0109 jl 0x2813
010b mov bx, word ptr [bp - 6]
010e mov cl, byte ptr [bx + 0x58a8]
0112 sub ch, ch
0114 cmp cx, 0x20
0117 jge 0x2802
0119 xor cx, cx
011b jmp 0x280f
011d nop 
011e cmp cx, 0x2f
0121 jle 0x280c
0123 cmp cx, 0x4f
0126 jl 0x27fd
0128 mov cx, 1
012b or cx, cx
012d je 0x2816
012f or dx, 8
0132 or dx, dx
0134 je 0x282c
0136 add dl, byte ptr [bp - 2]
0139 add dl, 0x1f
013c mov bx, word ptr [bp - 6]
013f mov byte ptr [bx + 0x58e8], dl
0143 pop si
0144 pop di
0145 leave 
0146 retf 
0147 nop 
0148 cmp word ptr [bp - 2], 0
014c jne 0x2842
014e nop 
014f push cs
0150 call 0x15ee ; _SRand8
0153 mov bx, word ptr [bp - 6]
0156 mov byte ptr [bx + 0x58e8], al
015a pop si
015b pop di
015c leave 
015d retf 
015e mov bx, word ptr [bp - 6]
0161 mov byte ptr [bx + 0x58e8], 0x4e
0166 pop si
0167 pop di
0168 leave 
0169 retf 
```

## Known declaration examples

- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int far SRand8(void);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SmoothEdgesB', 'offset': 9562, 'source': None, 'size': 362}
- {'symbol': '_RIsItDirt', 'offset': 9924, 'source': 'src/recovered/wf_RIsItDirt-6adf524aef.c', 'size': 31}
- {'symbol': '_FixExitMapB', 'offset': 10318, 'source': 'src/recovered/wf_FixExitMapB-54c05d603e.c', 'size': 198}
- {'symbol': '_FixExitMapR', 'offset': 10516, 'source': 'src/recovered/wf_FixExitMapR-ab2edbcf6f.c', 'size': 198}
