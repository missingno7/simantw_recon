# Recovery task _SaveGame

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 626 bytes.

```asm
0000 enter 0xde, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 8], 0
000b mov byte ptr [bp - 0x74], 0
000f mov ax, 0x9520
0012 mov <resolved loader operand; see bindings> ; [{'operand_offset': 19, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0015 mov word ptr [bp - 0xdc], ax
0019 mov word ptr [bp - 0xda], cx
001d or cx, ax
001f je 0xa291
0021 les bx, ptr [bp - 0xdc]
0025 cmp byte ptr es:[bx], 0
0029 je 0xa291
002b cmp word ptr [bp + 6], 0
002f je 0xa291
0031 lea si, [bp - 0x74]
0034 push ds
0035 les di, ptr [bp - 0xdc]
0039 mov cx, 0xffff
003c xor ax, ax
003e repne scasb al, byte ptr es:[di]
0040 not cx
0042 sub di, cx
0044 xchg si, di
0046 push ds
0047 push es
0048 pop ds
0049 pop es
004a shr cx, 1
004c rep movsw word ptr es:[di], word ptr [si]
004e adc cx, cx
0050 rep movsb byte ptr es:[di], byte ptr [si]
0052 pop ds
0053 cmp byte ptr [bp - 0x74], 0
0057 jne 0xa2ad
0059 push 1
005b lea ax, [bp - 0x74]
005e push ss
005f push ax
0060 nop 
0061 push cs
0062 call 0x9920 ; _FileSelect
0065 add sp, 6
0068 or ax, ax
006a jne 0xa2ad
006c jmp 0xa4a9
006f mov al, byte ptr [bp - 0x74]
0072 cwde 
0073 mov bx, ax
0075 mov word ptr [bp - 0xde], bx
0079 test byte ptr [bx - 0x52cd], 2
007e je 0xa2c6
0080 mov ax, bx
0082 sub ax, 0x20
0085 jmp 0xa2c8
0087 nop 
0088 mov ax, bx
008a mov word ptr [bp - 2], ax
008d lea ax, [bp - 0x10]
0090 push ss
0091 push ax
0092 mov ax, word ptr [bp - 2]
0095 sub ax, 0x40
0098 push ax
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 156, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __dos_getdiskfree
009e add sp, 6
00a1 xor di, di
00a3 mov ax, 0x9570
00a6 mov <resolved loader operand; see bindings> ; [{'operand_offset': 167, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00a9 mov si, ax
00ab mov word ptr [bp - 4], cx
00ae mov es, cx
00b0 cmp word ptr es:[0x9572], di
00b5 je 0xa309
00b7 mov ds, cx
00b9 mov ax, word ptr [si + 2]
00bc imul word ptr [si]
00be add di, ax
00c0 add si, 8
00c3 cmp word ptr [si + 2], 0
00c7 jne 0xa2f7
00c9 push ss
00ca pop ds
00cb push 0
00cd push word ptr [bp - 0xa]
00d0 mov ax, word ptr [bp - 0xe]
00d3 mul word ptr [bp - 0xc]
00d6 push dx
00d7 push ax
00d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 219, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
00dd mov cx, ax
00df imul ax, di, 0x7d
00e2 mov bx, 0x64
00e5 mov si, dx
00e7 sub dx, dx
00e9 div bx
00eb sub dx, dx
00ed cmp si, dx
00ef jge 0xa332
00f1 jmp 0xa496
00f4 jg 0xa33b
00f6 cmp cx, ax
00f8 ja 0xa33b
00fa jmp 0xa496
00fd lea di, [bp - 0x74]
0100 mov cx, ss
0102 mov es, cx
0104 push ds
0105 lds si, ptr [bp - 0xdc]
0109 mov cx, 0xffff
010c xor ax, ax
010e repne scasb al, byte ptr es:[di]
0110 not cx
0112 sub di, cx
0114 xchg si, di
0116 push ds
0117 push es
0118 pop ds
0119 pop es
011a shr cx, 1
011c rep movsw word ptr es:[di], word ptr [si]
011e adc cx, cx
0120 rep movsb byte ptr es:[di], byte ptr [si]
0122 pop ds
0123 push ax
0124 lea ax, [bp - 0x74]
0127 push ss
0128 push ax
0129 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 300, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _access
012e add sp, 6
0131 or ax, ax
0133 jne 0xa382
0135 lea ax, [bp - 0x74]
0138 push ss
0139 push ax
013a push 1
013c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 317, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 85}}]
0141 jmp 0xa38e
0143 nop 
0144 lea ax, [bp - 0x74]
0147 push ss
0148 push ax
0149 push 0
014b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 332, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 83}}]
0150 mov di, ax
0152 or di, di
0154 jg 0xa397
0156 jmp 0xa474
0159 mov ax, 0x9570
015c mov <resolved loader operand; see bindings> ; [{'operand_offset': 349, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
015f mov si, ax
0161 mov word ptr [bp - 4], cx
0164 mov word ptr [bp - 2], di
0167 mov es, cx
0169 cmp word ptr es:[0x9572], 0
016f je 0xa3d7
0171 push di
0172 push word ptr es:[si + 6]
0176 push word ptr es:[si + 4]
017a mov ax, word ptr es:[si + 2]
017e imul word ptr es:[si]
0181 push ax
0182 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 387, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 86}}]
0187 cmp ax, 0xffff
018a je 0xa43c
018c add si, 8
018f mov es, word ptr [bp - 4]
0192 cmp word ptr es:[si + 2], 0
0197 jne 0xa3af
0199 mov es, word ptr [0xc190]
019d mov word ptr es:[0x8370], 0
01a4 lea cx, [bp - 0x74]
01a7 push ss
01a8 push cx
01a9 push ds
01aa push 0x1840
01ad lea dx, [bp - 0xd8]
01b1 push ss
01b2 push dx
01b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 438, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
01b8 add sp, 0xc
01bb lea ax, [bp - 0xd8]
01bf push ss
01c0 push ax
01c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 452, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _PopMsg
01c6 add sp, 4
01c9 lea di, [bp - 0x74]
01cc mov cx, ss
01ce mov es, cx
01d0 push ds
01d1 lds si, ptr [bp - 0xdc]
01d5 mov cx, 0xffff
01d8 xor ax, ax
01da repne scasb al, byte ptr es:[di]
01dc not cx
01de sub di, cx
01e0 xchg si, di
01e2 push ds
01e3 push es
01e4 pop ds
01e5 pop es
01e6 shr cx, 1
01e8 rep movsw word ptr es:[di], word ptr [si]
01ea adc cx, cx
01ec rep movsb byte ptr es:[di], byte ptr [si]
01ee pop ds
01ef mov word ptr [bp - 8], 1
01f4 push word ptr [bp - 2]
01f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 504, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 81}}]
01fc jmp 0xa4a9
01fe les bx, ptr [bp - 0xdc]
0202 mov byte ptr es:[bx], 0
0206 mov bx, word ptr [0xacf8] ; _errno
020a shl bx, 2
020d push word ptr [bx - 0x5092]
0211 push word ptr [bx - 0x5094]
0215 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 536, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Error
021a add sp, 4
021d push di
021e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 543, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 81}}]
0223 lea ax, [bp - 0x74]
0226 push ss
0227 push ax
0228 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 555, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _unlink,_remove
022d add sp, 4
0230 xor ax, ax
0232 pop si
0233 pop di
0234 leave 
0235 retf 
0236 mov bx, word ptr [0xacf8] ; _errno
023a shl bx, 2
023d push word ptr [bx - 0x5092]
0241 push word ptr [bx - 0x5094]
0245 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 584, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Error
024a add sp, 4
024d les bx, ptr [bp - 0xdc]
0251 mov byte ptr es:[bx], 0
0255 jmp 0xa4a9
0257 nop 
0258 push word ptr [0xcd78] ; _rootWnd
025c push ds
025d push 0x1862
0260 push ds
0261 push 0x1853
0264 push 0x10
0266 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 615, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
026b mov ax, word ptr [bp - 8]
026e pop si
026f pop di
0270 leave 
0271 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far access(char far *path, int mode);` — src/recovered/db_Exists.c
- `extern int far access(const char far *path, int mode);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern int far access(char far *path, int mode);` — src/recovered/wf_tu_simtwo_81AC_db_SetDataBase_1_reviewed-7aea199e9a.c
- `extern int far pascal PeekMessage(void far *message, int window, unsigned int first, unsigned int last, unsigned int remove);` — src/recovered/StopSimulation.c
- `extern int far pascal PeekMessage(void far *message, int window, unsigned int first, unsigned int last, unsigned int remove);` — src/recovered/wf_UpdateAllWindows-97a1ff92dc.c
- `extern int far pascal PeekMessage(struct MSG far *message, int hwnd, unsigned int first, unsigned int last, unsigned int remove);` — src/recovered/wf_win_FlushEvents-3010537d93.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_gr_0000_InitGraphics_1-8959d65c41.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_simtwo_81AC_db_SetDataBase_1_reviewed-7aea199e9a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoLoadInitializations', 'offset': 40382, 'source': None, 'size': 481}
- {'symbol': '_LoadGame', 'offset': 40864, 'source': None, 'size': 669}
- {'symbol': '_ClearLastFileName', 'offset': 42160, 'source': 'src/recovered/ClearLastFileName.c', 'size': 11}
- {'symbol': '_CheckRainArray', 'offset': 42172, 'source': 'src/recovered/wf_CheckRainArray-5188fd7161.c', 'size': 97}
