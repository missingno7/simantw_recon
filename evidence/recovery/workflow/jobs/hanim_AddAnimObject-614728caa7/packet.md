# Recovery task _hanim_AddAnimObject

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 650 bytes.

```asm
0000 enter 0x1e, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 nop 
000a push cs
000b call 0x558e ; _mem_Lock
000e add sp, 2
0011 mov es, dx
0013 mov bx, ax
0015 mov si, bx
0017 mov word ptr [bp - 0x14], es
001a mov di, word ptr es:[bx + 2]
001e mov ax, word ptr es:[bx]
0021 mov word ptr [bp - 0xe], ax
0024 cmp word ptr es:[bx + 4], ax
0028 jne 0x645b
002a add ax, 2
002d mov word ptr es:[si + 4], ax
0031 push 1
0033 imul ax, ax, 0x2c
0036 push 0
0038 push ax
0039 push di
003a nop 
003b push cs
003c call 0x552a ; _mem_Realloc
003f add sp, 8
0042 mov es, word ptr [bp - 0x14]
0045 mov word ptr es:[si + 2], ax
0049 mov di, ax
004b mov word ptr [bp - 0x16], si
004e push di
004f nop 
0050 push cs
0051 call 0x558e ; _mem_Lock
0054 add sp, 2
0057 mov word ptr [bp - 0x12], ax
005a mov word ptr [bp - 0x10], dx
005d mov word ptr [bp - 0x1e], di
0060 mov ds, word ptr [bp - 0x14]
0063 mov bx, word ptr [bp - 0x16]
0066 mov di, word ptr [bx + 6]
0069 and di, 0x7fff
006d inc word ptr [bx + 6]
0070 mov ax, word ptr [bp - 0x12]
0073 mov dx, word ptr [bp - 0x10]
0076 mov word ptr [bp - 4], ax
0079 mov es, dx
007b mov word ptr [bp - 6], 0
0080 cmp word ptr [bx], 0
0083 jle 0x64ae
0085 mov bx, ax
0087 mov cx, word ptr [bp - 6]
008a mov word ptr [bp - 0x18], di
008d cmp word ptr es:[bx + 0x20], di
0091 je 0x64e4
0093 add bx, 0x2c
0096 inc cx
0097 mov si, word ptr [bp - 0x16]
009a cmp word ptr [si], cx
009c jg 0x649d
009e xor ax, ax
00a0 cdq 
00a1 mov cx, ax
00a3 mov word ptr [bp - 8], dx
00a6 mov ax, word ptr [bp - 8]
00a9 or ax, cx
00ab jne 0x6473
00ad mov word ptr [bp - 0x18], di
00b0 push ss
00b1 pop ds
00b2 mov di, word ptr [bp + 0xc]
00b5 cmp di, 0x7530
00b9 jl 0x64f6
00bb mov es, word ptr [0xbf74]
00bf les bx, ptr es:[0xa072]
00c4 mov ax, word ptr es:[bx + 8]
00c8 mov word ptr [bp - 0x1c], ax
00cb mov ax, word ptr es:[bx + 0xa]
00cf mov word ptr [bp - 0x1a], ax
00d2 jmp 0x6504
00d4 mov word ptr [bp - 6], cx
00d7 mov di, cx
00d9 mov word ptr [bp - 0xc], di
00dc mov cx, bx
00de mov word ptr [bp - 8], es
00e1 mov di, word ptr [bp - 0x18]
00e4 jmp 0x64b6
00e6 push di
00e7 lea ax, [bp - 0x1c]
00ea push ss
00eb push ax
00ec nop 
00ed push cs
00ee call 0x465c ; _gr_BitMapSize
00f1 add sp, 6
00f4 cmp word ptr [bp + 0xe], -1
00f8 jne 0x6513
00fa mov ax, word ptr [bp - 0x1a]
00fd add ax, word ptr [bp + 0xa]
0100 mov word ptr [bp + 0xe], ax
0103 lds si, ptr [bp - 0x12]
0106 mov word ptr [bp - 0xc], 0
010b cmp word ptr [bp - 0xe], 0
010f jle 0x6537
0111 mov cx, word ptr [bp + 0xe]
0114 mov bx, word ptr [bp - 0xe]
0117 cmp word ptr [si + 0x24], cx
011a jg 0x6537
011c add si, 0x2c
011f inc word ptr [bp - 0xc]
0122 cmp word ptr [bp - 0xc], bx
0125 jl 0x6527
0127 mov ax, word ptr [bp - 0xc]
012a cmp word ptr [bp - 0xe], ax
012d jne 0x6542
012f jmp 0x6612
0132 mov word ptr [bp - 4], ds
0135 push ss
0136 pop ds
0137 mov ax, word ptr [bp - 0xe]
013a sub ax, word ptr [bp - 0xc]
013d imul ax, ax, 0x2c
0140 push ax
0141 push word ptr [bp - 4]
0144 push si
0145 mov ax, si
0147 mov dx, word ptr [bp - 4]
014a add ax, 0x2c
014d push dx
014e push ax
014f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 338, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
0154 add sp, 0xa
0157 les bx, ptr [bp - 0x16]
015a inc word ptr es:[bx]
015d mov <resolved loader operand; see bindings> ; [{'operand_offset': 350, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0160 mov ds, ax
0162 mov ax, word ptr [bp - 4]
0165 mov word ptr [0x7c3e], si
0169 mov word ptr [0x7c40], ax
016c mov cl, 1
016e mov es, ax
0170 mov byte ptr es:[si + 3], cl
0174 mov ds, ax
0176 mov byte ptr [si], cl
0178 xor bl, bl
017a mov byte ptr [si + 4], bl
017d mov byte ptr es:[si + 1], bl
0181 mov byte ptr [si + 5], bl
0184 mov dx, word ptr [bp + 0xe]
0187 mov word ptr es:[si + 0x24], dx
018b mov dx, word ptr [bp - 0x1c]
018e mov word ptr es:[si + 0x1a], dx
0192 mov dx, word ptr [bp - 0x1a]
0195 mov word ptr es:[si + 0x1c], dx
0199 mov di, word ptr [bp + 8]
019c mov word ptr es:[si + 0x16], di
01a0 mov dx, word ptr [bp + 0xa]
01a3 mov word ptr es:[si + 0x18], dx
01a7 mov ax, word ptr [bp - 0x18]
01aa mov word ptr es:[si + 0x20], ax
01ae and di, 0xfff8
01b1 mov word ptr es:[si + 0xe], di
01b5 mov ax, di
01b7 add ax, word ptr [bp - 0x1c]
01ba add ax, 0xf
01bd and al, 0xf8
01bf mov word ptr [bp - 2], ax
01c2 mov word ptr es:[si + 0x12], ax
01c6 mov word ptr es:[si + 0x10], dx
01ca add dx, word ptr [bp - 0x1a]
01cd mov word ptr es:[si + 0x14], dx
01d1 mov ax, 0xffff
01d4 mov word ptr es:[si + 8], ax
01d8 mov word ptr es:[si + 0xc], ax
01dc mov word ptr es:[si + 0xa], ax
01e0 mov word ptr es:[si + 6], ax
01e4 test byte ptr ss:[0xcc7e], 1
01ea je 0x6618
01ec mov ax, word ptr [bp - 2]
01ef sub ax, di
01f1 cdq 
01f2 and dx, 7
01f5 add ax, dx
01f7 sar ax, 3
01fa imul word ptr [bp - 0x1a]
01fd add ax, 4
0200 jmp 0x664a
0202 mov word ptr [bp - 4], ds
0205 jmp 0x6567
0208 cmp byte ptr ss:[0xcc7e], 2
020e jne 0x6632
0210 mov ax, word ptr [bp - 2]
0213 sub ax, di
0215 cdq 
0216 sub ax, dx
0218 sar ax, 1
021a imul word ptr [bp - 0x1a]
021d add ax, 4
0220 jmp 0x6647
0222 mov ax, word ptr [bp - 2]
0225 sub ax, di
0227 cdq 
0228 and dx, 7
022b add ax, dx
022d sar ax, 3
0230 imul word ptr [bp - 0x1a]
0233 inc ax
0234 shl ax, 2
0237 mov es, word ptr [bp - 4]
023a mov word ptr es:[si + 0x1e], ax
023e push ss
023f pop ds
0240 mov ax, word ptr [bp + 0xc]
0243 mov es, word ptr [bp - 4]
0246 mov word ptr es:[si + 0x26], ax
024a push ds
024b push 0xa0c
024e push 1
0250 mov ax, word ptr es:[si + 0x1e]
0254 mov cx, ax
0256 shl ax, 1
0258 add ax, cx
025a push 0
025c push ax
025d mov di, es
025f nop 
0260 push cs
0261 call 0x54da ; _mem_Alloc
0264 add sp, 0xa
0267 mov es, di
0269 mov word ptr es:[si + 0x22], ax
026d push word ptr [bp - 0x1e]
0270 nop 
0271 push cs
0272 call 0x559c ; _mem_Unlock
0275 add sp, 2
0278 push word ptr [bp + 6]
027b nop 
027c push cs
027d call 0x559c ; _mem_Unlock
0280 add sp, 2
0283 mov ax, word ptr [bp - 0x18]
0286 pop si
0287 pop di
0288 leave 
0289 retf 
```

## Known declaration examples

- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_B324_InitTriVars_6_scaffold-355c471c2b.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_B324_initControls_1_scaffold-03091459d8.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_hanim_PrintSet', 'offset': 25532, 'source': 'src/recovered/hanim_PrintSet.c', 'size': 13}
- {'symbol': '__hanim_FindObject', 'offset': 25546, 'source': 'src/recovered/wf_hanim_FindObject-9334905165.c', 'size': 69}
- {'symbol': '_hanim_RemoveAnimObject', 'offset': 26266, 'source': None, 'size': 260}
- {'symbol': '_hanim_RemoveAllAnimObjects', 'offset': 26526, 'source': None, 'size': 109}
