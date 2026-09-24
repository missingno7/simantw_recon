# Recovery task _snd_Install

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 804 bytes.

```asm
0000 enter 0x10c, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xbf78]
000a cmp word ptr es:[0x8d06], 0
0010 je 0x794f
0012 jmp 0x7c5a
0015 push ds
0016 push 0xb5a
0019 nop 
001a push cs
001b call 0x780e ; _IsDLLAvail
001e add sp, 4
0021 or ax, ax
0023 je 0x79a3
0025 push ds
0026 push 0xb67
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 42, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 95}}]
002e mov bx, 0x8d08
0031 mov es, word ptr [0xbf78]
0035 mov word ptr [bp - 0x108], bx
0039 mov word ptr [bp - 0x106], es
003d mov word ptr es:[bx], ax
0040 cmp ax, 0x20
0043 jb 0x79a3
0045 push ax
0046 push ds
0047 push 0xafa
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
004f mov word ptr [bp - 4], ax
0052 mov word ptr [bp - 2], dx
0055 or dx, ax
0057 je 0x799a
0059 lcall [bp - 4]
005c mov si, ax
005e jmp 0x799c
0060 xor si, si
0062 or si, si
0064 je 0x79a3
0066 jmp 0x7bc4
0069 push ds
006a push 0xb74
006d nop 
006e push cs
006f call 0x780e ; _IsDLLAvail
0072 add sp, 4
0075 or ax, ax
0077 jne 0x79b6
0079 jmp 0x7b04
007c push ds
007d push 0xb80
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 95}}]
0085 mov bx, 0x8d08
0088 mov es, word ptr [0xbf78]
008c mov word ptr [bp - 0x108], bx
0090 mov word ptr [bp - 0x106], es
0094 mov word ptr es:[bx], ax
0097 cmp ax, 0x20
009a jae 0x79d9
009c jmp 0x7b04
009f push ax
00a0 push ds
00a1 push 0xb8c
00a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 165, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
00a9 mov word ptr [bp - 8], ax
00ac mov word ptr [bp - 6], dx
00af les bx, ptr [bp - 0x108]
00b3 push word ptr es:[bx]
00b6 push ds
00b7 push 0xb9d
00ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
00bf mov word ptr [bp - 4], ax
00c2 mov word ptr [bp - 2], dx
00c5 mov ax, word ptr [bp - 6]
00c8 or ax, word ptr [bp - 8]
00cb je 0x7a50
00cd mov ax, dx
00cf or ax, word ptr [bp - 4]
00d2 je 0x7a50
00d4 lcall [bp - 8]
00d7 mov es, word ptr [0xbf78]
00db mov word ptr es:[0x8d00], ax
00df or ax, ax
00e1 je 0x7a50
00e3 lcall [bp - 4]
00e6 mov es, word ptr [0xbf78]
00ea mov word ptr es:[0x8d02], ax
00ee mov word ptr es:[0x8d04], dx
00f3 mov ax, dx
00f5 or ax, word ptr es:[0x8d02]
00fa je 0x7a50
00fc push ds
00fd push 0xbac
0100 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 257, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 118}}]
0105 mov word ptr [0xaf4], ax ; _wSoundBlasterMsg
0108 mov es, word ptr [0xbf78]
010c mov word ptr es:[0x8d0a], 0
0113 jmp 0x7bcf
0116 lea ax, [bp - 0x104]
011a push ss
011b push ax
011c push 0x100
011f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 288, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 134}}]
0124 lea di, [bp - 0x104]
0128 mov ax, ss
012a mov es, ax
012c mov cx, 0xffff
012f xor ax, ax
0131 repne scasb al, byte ptr es:[di]
0133 not cx
0135 dec cx
0136 mov si, cx
0138 cmp byte ptr [bp + si - 0x105], 0x5c
013d jne 0x7a86
013f lea ax, [bp - 0x104]
0143 push ss
0144 push ax
0145 push ds
0146 push 0xb1e
0149 jmp 0x7a90
014b nop 
014c lea ax, [bp - 0x104]
0150 push ss
0151 push ax
0152 push ds
0153 push 0xb32
0156 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 343, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 89}}]
015b push 0
015d lea ax, [bp - 0x104]
0161 push ss
0162 push ax
0163 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 358, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _access
0168 add sp, 6
016b or ax, ax
016d jne 0x7ae0
016f push ds
0170 push 0xb47
0173 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 372, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 95}}]
0178 les bx, ptr [bp - 0x108]
017c mov word ptr es:[bx], ax
017f cmp ax, 0x20
0182 jb 0x7ae0
0184 push ax
0185 push ds
0186 push 0xb0c
0189 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 394, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
018e mov word ptr [bp - 4], ax
0191 mov word ptr [bp - 2], dx
0194 or dx, ax
0196 je 0x7ada
0198 lcall [bp - 4]
019b mov si, ax
019d jmp 0x7adc
019f nop 
01a0 xor si, si
01a2 or si, si
01a4 jne 0x7ae9
01a6 les bx, ptr [bp - 0x108]
01aa mov word ptr es:[bx], 0
01af les bx, ptr [bp - 0x108]
01b3 cmp word ptr es:[bx], 0
01b7 jne 0x7af6
01b9 jmp 0x7bbf
01bc mov es, word ptr [0xbf78]
01c0 mov word ptr es:[0x8d0c], 1
01c7 jmp 0x7bc4
01ca lea ax, [bp - 0x104]
01ce push ss
01cf push ax
01d0 push 0x100
01d3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 468, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 134}}]
01d8 lea di, [bp - 0x104]
01dc mov ax, ss
01de mov es, ax
01e0 mov cx, 0xffff
01e3 xor ax, ax
01e5 repne scasb al, byte ptr es:[di]
01e7 not cx
01e9 dec cx
01ea mov si, cx
01ec cmp byte ptr [bp + si - 0x105], 0x5c
01f1 jne 0x7b3a
01f3 lea ax, [bp - 0x104]
01f7 push ss
01f8 push ax
01f9 push ds
01fa push 0xb1e
01fd jmp 0x7b44
01ff nop 
0200 lea ax, [bp - 0x104]
0204 push ss
0205 push ax
0206 push ds
0207 push 0xb32
020a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 523, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 89}}]
020f push 0
0211 lea ax, [bp - 0x104]
0215 push ss
0216 push ax
0217 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 538, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _access
021c add sp, 6
021f or ax, ax
0221 jne 0x7b9e
0223 push ds
0224 push 0xb47
0227 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 552, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 95}}]
022c mov bx, 0x8d08
022f mov es, word ptr [0xbf78]
0233 mov word ptr [bp - 0x108], bx
0237 mov word ptr [bp - 0x106], es
023b mov word ptr es:[bx], ax
023e cmp ax, 0x20
0241 jb 0x7b9e
0243 push ax
0244 push ds
0245 push 0xb0c
0248 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 585, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
024d mov word ptr [bp - 4], ax
0250 mov word ptr [bp - 2], dx
0253 or dx, ax
0255 je 0x7b98
0257 lcall [bp - 4]
025a mov si, ax
025c jmp 0x7b9a
025e xor si, si
0260 or si, si
0262 jne 0x7bb2
0264 mov bx, 0x8d08
0267 mov es, word ptr [0xbf78]
026b mov word ptr [bp - 0x108], bx
026f mov word ptr [bp - 0x106], es
0273 mov word ptr es:[bx], 0
0278 les bx, ptr [bp - 0x108]
027c cmp word ptr es:[bx], 0
0280 je 0x7bbf
0282 jmp 0x7af6
0285 mov word ptr es:[bx], 0
028a mov es, word ptr [0xbf78]
028e mov word ptr es:[0x8d0a], 1
0295 cmp word ptr es:[0x8d0a], 0
029b je 0x7c4f
029d les bx, ptr [bp - 0x108]
02a1 cmp word ptr es:[bx], 0
02a5 jne 0x7c4f
02a7 push ds
02a8 push 0xbb9
02ab nop 
02ac push cs
02ad call 0x780e ; _IsDLLAvail
02b0 add sp, 4
02b3 or ax, ax
02b5 je 0x7c44
02b7 push ds
02b8 push 0xbc4
02bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 700, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 95}}]
02c0 mov es, word ptr [0xbf78]
02c4 mov word ptr es:[0x8d28], ax
02c8 cmp ax, 0x20
02cb jb 0x7c44
02cd push ax
02ce push ds
02cf push 0xbcf
02d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 723, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
02d7 mov word ptr [bp - 0x10a], dx
02db mov word ptr [bp - 0x10c], ax
02df lcall [bp - 0x10c]
02e3 cmp ax, 2
02e6 jl 0x7c32
02e8 push ds
02e9 push 0xbe0
02ec nop 
02ed push cs
02ee call 0x62bc ; _WinPrintf
02f1 add sp, 4
02f4 jmp 0x7c4f
02f6 nop 
02f7 nop 
02f8 mov es, word ptr [0xbf78]
02fc mov word ptr es:[0x8d28], 0
0303 push ds
0304 push 0xbf1
0307 jmp 0x7c26
0309 nop 
030a mov es, word ptr [0xbf78]
030e mov word ptr es:[0x8d28], 0
0315 mov es, word ptr [0xbf78]
0319 mov word ptr es:[0x8d06], 1
0320 pop si
0321 pop di
0322 leave 
0323 retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern int far access(char far *path, int mode);` — src/recovered/db_Exists.c
- `extern int far access(const char far *path, int mode);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern int far access(char far *path, int mode);` — src/recovered/wf_tu_simtwo_81AC_db_SetDataBase_1_reviewed-7aea199e9a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CheckMMWave', 'offset': 30566, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c', 'size': 168}
- {'symbol': '_IsDLLAvail', 'offset': 30734, 'source': None, 'size': 300}
- {'symbol': '_snd_Deinstall', 'offset': 31838, 'source': None, 'size': 608}
- {'symbol': '_snd_IsSongDone', 'offset': 32446, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c', 'size': 44}
