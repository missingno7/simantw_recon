# Recovery task _ExpIncSmell

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 445 bytes.

```asm
0000 enter 6, 0
0004 push si
0005 cmp word ptr [0xcc76], 1 ; _MapPlane
000a jle 0x7bad
000c jmp 0x7d58
000f mov ax, word ptr [bp + 8]
0012 sar ax, 1
0014 mov word ptr [bp - 2], ax
0017 mov ax, word ptr [bp + 6]
001a sar ax, 1
001c mov word ptr [bp - 4], ax
001f or ax, ax
0021 jl 0x7bd8
0023 cmp ax, 0x3f
0026 jg 0x7bd8
0028 cmp word ptr [bp - 2], 0
002c jl 0x7bd8
002e cmp word ptr [bp - 2], 0x1f
0032 jg 0x7bd8
0034 mov dx, 1
0037 jmp 0x7bda
0039 nop 
003a xor dx, dx
003c or dx, dx
003e jne 0x7be4
0040 mov si, 0xffff
0043 jmp 0x7c68
0046 mov es, word ptr [0xc270]
004a mov al, byte ptr es:[0x8605]
004e cwde 
004f or ax, ax
0051 je 0x7c02
0053 dec ax
0054 je 0x7c16
0056 dec ax
0057 je 0x7c2a
0059 dec ax
005a je 0x7c3e
005c dec ax
005d je 0x7c52
005f mov bx, word ptr [bp - 6]
0062 jmp 0x7c66
0064 mov es, word ptr [0xc27a]
0068 mov bx, word ptr [bp - 4]
006b shl bx, 5
006e add bx, word ptr [bp - 2]
0071 mov bl, byte ptr es:[bx + 0x62d2]
0076 jmp 0x7c64
0078 mov es, word ptr [0xc27a]
007c mov bx, word ptr [bp - 4]
007f shl bx, 5
0082 add bx, word ptr [bp - 2]
0085 mov bl, byte ptr es:[bx + 0x6ad2]
008a jmp 0x7c64
008c mov es, word ptr [0xc27a]
0090 mov bx, word ptr [bp - 4]
0093 shl bx, 5
0096 add bx, word ptr [bp - 2]
0099 mov bl, byte ptr es:[bx + 0x72d2]
009e jmp 0x7c64
00a0 mov es, word ptr [0xc27a]
00a4 mov bx, word ptr [bp - 4]
00a7 shl bx, 5
00aa add bx, word ptr [bp - 2]
00ad mov bl, byte ptr es:[bx + 0x7ad2]
00b2 jmp 0x7c64
00b4 mov es, word ptr [0xc27a]
00b8 mov bx, word ptr [bp - 4]
00bb shl bx, 5
00be add bx, word ptr [bp - 2]
00c1 mov bl, byte ptr es:[bx + 0x52d2]
00c6 sub bh, bh
00c8 mov si, bx
00ca push 0x11
00cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 205, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
00d1 test ah, 0x80
00d4 je 0x7c7a
00d6 sub si, 0x28
00d9 jmp 0x7c7d
00db nop 
00dc add si, 0x46
00df or si, si
00e1 jge 0x7c83
00e3 xor si, si
00e5 cmp si, 0xff
00e9 jle 0x7c8c
00eb mov si, 0xff
00ee mov cx, si
00f0 cmp word ptr [bp - 4], 0
00f4 jl 0x7cac
00f6 cmp word ptr [bp - 4], 0x3f
00fa jg 0x7cac
00fc cmp word ptr [bp - 2], 0
0100 jl 0x7cac
0102 cmp word ptr [bp - 2], 0x1f
0106 jg 0x7cac
0108 mov dx, 1
010b jmp 0x7cae
010d nop 
010e xor dx, dx
0110 or dx, dx
0112 jne 0x7cb5
0114 jmp 0x7d3c
0117 cmp cx, 0xff
011b jle 0x7cbe
011d mov cx, 0xff
0120 mov es, word ptr [0xc270]
0124 mov al, byte ptr es:[0x8605]
0128 cwde 
0129 or ax, ax
012b je 0x7cda
012d dec ax
012e je 0x7cee
0130 dec ax
0131 je 0x7d02
0133 dec ax
0134 je 0x7d16
0136 dec ax
0137 je 0x7d2a
0139 jmp 0x7d3c
013b nop 
013c mov es, word ptr [0xc27a]
0140 mov bx, word ptr [bp - 4]
0143 shl bx, 5
0146 add bx, word ptr [bp - 2]
0149 mov byte ptr es:[bx + 0x62d2], cl
014e jmp 0x7d3c
0150 mov es, word ptr [0xc27a]
0154 mov bx, word ptr [bp - 4]
0157 shl bx, 5
015a add bx, word ptr [bp - 2]
015d mov byte ptr es:[bx + 0x6ad2], cl
0162 jmp 0x7d3c
0164 mov es, word ptr [0xc27a]
0168 mov bx, word ptr [bp - 4]
016b shl bx, 5
016e add bx, word ptr [bp - 2]
0171 mov byte ptr es:[bx + 0x72d2], cl
0176 jmp 0x7d3c
0178 mov es, word ptr [0xc27a]
017c mov bx, word ptr [bp - 4]
017f shl bx, 5
0182 add bx, word ptr [bp - 2]
0185 mov byte ptr es:[bx + 0x7ad2], cl
018a jmp 0x7d3c
018c mov es, word ptr [0xc27a]
0190 mov bx, word ptr [bp - 4]
0193 shl bx, 5
0196 add bx, word ptr [bp - 2]
0199 mov byte ptr es:[bx + 0x52d2], cl
019e push word ptr [bp - 2]
01a1 push word ptr [bp - 4]
01a4 nop 
01a5 push cs
01a6 call 0x889c ; _SmoothMany
01a9 add sp, 4
01ac push 0x7e
01ae push 0
01b0 push 0x1b
01b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 437, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
01b7 add sp, 6
01ba pop si
01bb leave 
01bc retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ExpAddAnt', 'offset': 31228, 'source': 'src/recovered/wf_ExpAddAnt-6ef6c47e91.c', 'size': 266}
- {'symbol': '_ExpAddFood', 'offset': 31494, 'source': 'src/recovered/wf_ExpAddFood-cd1bed365e.c', 'size': 152}
- {'symbol': '_ExpKillAnts', 'offset': 32092, 'source': None, 'size': 478}
- {'symbol': '_IncFoodHere', 'offset': 32570, 'source': None, 'size': 287}
