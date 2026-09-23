# Recovery task _ch_LookUpId

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 649 bytes.

```asm
0000 enter 0x18, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 0x10], 0
000b mov di, word ptr [bp + 6]
000e mov ax, word ptr [0xb582]
0011 or ax, word ptr [0xb580] ; _cacheHook
0015 je 0x9214
0017 push word ptr [bp + 8]
001a push di
001b lcall [0xb580] ; _cacheHook
001f add sp, 4
0022 mov si, ax
0024 or si, si
0026 je 0x9214
0028 mov ax, si
002a pop si
002b pop di
002c leave 
002d retf 
002e push word ptr [bp + 0xa]
0031 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0036 add sp, 2
0039 mov es, dx
003b mov bx, ax
003d mov si, bx
003f mov word ptr [bp - 0x14], bx
0042 mov word ptr [bp - 0x12], es
0045 mov ax, word ptr es:[bx]
0048 mov word ptr [bp - 0xe], ax
004b lea cx, [bx + 4]
004e mov word ptr [bp - 0xc], cx
0051 mov word ptr [bp - 0xa], es
0054 mov dx, ax
0056 mov ax, di
0058 mov al, ah
005a cwde 
005b mov bx, ax
005d mov ax, word ptr [bp + 8]
0060 mov word ptr [bp - 0x18], cx
0063 mov cx, ax
0065 shl ax, 1
0067 add ax, cx
0069 shl ax, 1
006b add ax, cx
006d add ax, bx
006f add ax, di
0071 mov cx, dx
0073 cdq 
0074 idiv cx
0076 mov word ptr [bp - 8], dx
0079 mov word ptr [bp - 6], dx
007c mov ax, dx
007e shl dx, 2
0081 add dx, word ptr [bp - 0x18]
0084 mov cx, es
0086 mov word ptr [bp - 2], cx
0089 mov word ptr [0xb594], 0
008f or ax, ax
0091 jl 0x92b1
0093 mov word ptr [bp - 0x14], si
0096 mov bx, dx
0098 mov di, ax
009a mov cx, word ptr [bp - 0x10]
009d mov ds, word ptr [bp - 2]
00a0 mov ax, word ptr [bp + 6]
00a3 cmp word ptr [bx], ax
00a5 jne 0x9295
00a7 mov ax, word ptr [bp + 8]
00aa cmp word ptr [bx + 2], ax
00ad je 0x9304
00af cmp word ptr ss:[0xb594], 0
00b5 jne 0x92a7
00b7 cmp word ptr [bx], -1
00ba jne 0x92a7
00bc mov word ptr ss:[0xb594], di
00c1 sub bx, 4
00c4 inc cx
00c5 dec di
00c6 jns 0x9286
00c8 mov word ptr [bp - 0x10], cx
00cb mov di, word ptr [bp - 0xe]
00ce dec di
00cf mov ax, di
00d1 shl ax, 2
00d4 add ax, word ptr [bp - 0xc]
00d7 mov dx, word ptr [bp - 0xa]
00da mov bx, ax
00dc mov ds, dx
00de cmp di, word ptr [bp - 8]
00e1 jge 0x92d0
00e3 push ss
00e4 pop ds
00e5 jmp 0x9448
00e8 nop 
00e9 nop 
00ea mov cx, word ptr [bp - 0x10]
00ed mov ax, word ptr [bp + 6]
00f0 cmp word ptr [bx], ax
00f2 jne 0x92e2
00f4 mov ax, word ptr [bp + 8]
00f7 cmp word ptr [bx + 2], ax
00fa je 0x9304
00fc cmp word ptr ss:[0xb594], 0
0102 jne 0x92f4
0104 cmp word ptr [bx], -1
0107 jne 0x92f4
0109 mov word ptr ss:[0xb594], di
010e inc cx
010f sub bx, 4
0112 dec di
0113 cmp di, word ptr [bp - 8]
0116 jge 0x92d3
0118 mov word ptr [bp - 0x10], cx
011b jmp 0x92c9
011d nop 
011e mov word ptr [bp - 0x10], cx
0121 mov word ptr [bp - 6], di
0124 push ss
0125 pop ds
0126 mov ax, cx
0128 cdq 
0129 add word ptr [0xb59e], ax
012d adc word ptr [0xb5a0], dx
0131 add word ptr [0xb596], 1
0136 adc word ptr [0xb598], 0
013b mov ax, di
013d mov word ptr [0xb594], ax
0140 mov si, di
0142 shl si, 1
0144 mov bx, word ptr [bp - 0xe]
0147 inc bx
0148 shl bx, 2
014b sub cx, cx
014d add bx, word ptr [bp - 0x14]
0150 adc cx, word ptr [bp - 0x12]
0153 mov es, cx
0155 mov si, word ptr es:[bx + si]
0158 push si
0159 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 348, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Freed
015e add sp, 2
0161 or ax, ax
0163 jne 0x934e
0165 jmp 0x9430
0168 push word ptr [bp + 0xa]
016b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 366, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0170 add sp, 2
0173 mov es, dx
0175 mov bx, ax
0177 mov si, bx
0179 mov word ptr [bp - 0xa], es
017c mov ax, word ptr es:[bx]
017f mov word ptr [bp - 0xe], ax
0182 mov ax, es
0184 mov cx, word ptr [bp - 0xe]
0187 inc cx
0188 shl cx, 2
018b add bx, cx
018d adc ax, 0
0190 mov word ptr [bp - 2], ax
0193 mov ax, si
0195 add ax, 4
0198 mov word ptr [bp - 8], ax
019b mov word ptr [bp - 6], dx
019e mov word ptr [bp - 0xc], si
01a1 mov si, bx
01a3 mov di, ax
01a5 jmp 0x9402
01a7 nop 
01a8 mov es, word ptr [bp - 6]
01ab cmp word ptr es:[di], -1
01af je 0x93fc
01b1 mov es, word ptr [bp - 2]
01b4 cmp word ptr es:[si], 0
01b8 je 0x93fc
01ba push word ptr es:[si]
01bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 448, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Freed
01c2 add sp, 2
01c5 or ax, ax
01c7 je 0x93fc
01c9 mov es, word ptr [bp - 2]
01cc push word ptr es:[si]
01cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 466, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_LockLevel
01d4 add sp, 2
01d7 or ax, ax
01d9 jne 0x93fc
01db mov es, word ptr [bp - 6]
01de push word ptr es:[di + 2]
01e2 push word ptr es:[di]
01e5 push ds
01e6 push 0xb618
01e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 492, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
01ee add sp, 8
01f1 mov es, word ptr [bp - 2]
01f4 push word ptr es:[si]
01f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 506, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
01fc add sp, 2
01ff mov es, word ptr [bp - 2]
0202 mov word ptr es:[si], 0
0207 mov es, word ptr [bp - 6]
020a mov word ptr es:[di], 0xffff
020f les bx, ptr [bp - 0xc]
0212 dec word ptr es:[bx + 2]
0216 add di, 4
0219 add si, 2
021c mov ax, word ptr [bp - 0xe]
021f dec word ptr [bp - 0xe]
0222 or ax, ax
0224 jne 0x938e
0226 push ds
0227 push 0xb623
022a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 557, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
022f add sp, 4
0232 les bx, ptr [bp - 0xc]
0235 mov ax, word ptr es:[bx + 2]
0239 mov word ptr [bp - 0xe], ax
023c push word ptr [bp + 0xa]
023f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 578, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0244 add sp, 2
0247 jmp 0x9448
0249 nop 
024a push si
024b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 590, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Freshen
0250 add sp, 2
0253 push word ptr [bp + 0xa]
0256 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 601, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
025b add sp, 2
025e jmp 0x920e
0261 nop 
0262 mov ax, word ptr [bp - 0x10]
0265 cdq 
0266 add word ptr [0xb5a2], ax
026a adc word ptr [0xb5a4], dx
026e add word ptr [0xb59a], 1
0273 adc word ptr [0xb59c], 0
0278 push word ptr [bp + 0xa]
027b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 638, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0280 add sp, 2
0283 xor ax, ax
0285 pop si
0286 pop di
0287 leave 
0288 retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern Hook near cacheHook;` — src/recovered/ch_SetCacheHooks.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
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

- {'symbol': '_ch_PurgeCache', 'offset': 37058, 'source': None, 'size': 128}
- {'symbol': '_ch_LookUpHandle', 'offset': 37186, 'source': None, 'size': 163}
- {'symbol': '_ch_AddEntry', 'offset': 38000, 'source': None, 'size': 706}
- {'symbol': '_ch_DeleteEntry', 'offset': 38706, 'source': None, 'size': 114}
