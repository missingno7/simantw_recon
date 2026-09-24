# Recovery task _ch_AddEntry

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 706 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 push word ptr [bp + 0xa]
0009 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 12, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
000e add sp, 2
0011 mov es, dx
0013 mov bx, ax
0015 mov di, ax
0017 mov word ptr [bp - 0x16], bx
001a mov word ptr [bp - 0x14], es
001d mov ax, word ptr es:[bx]
0020 mov word ptr [bp - 0x12], ax
0023 mov cx, word ptr es:[bx + 2]
0027 mov word ptr [bp - 0xc], cx
002a inc word ptr [0xb5a6]
002e cmp cx, ax
0030 je 0x94ac
0032 cmp word ptr [0xb5a6], 0x1e
0037 jg 0x94ac
0039 jmp 0x96c0
003c push word ptr [bp - 0xc]
003f push word ptr [bp + 8]
0042 push word ptr [bp + 6]
0045 push ds
0046 push 0xb5a8
0049 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 76, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
004e add sp, 0xa
0051 mov word ptr [0xb5a6], 0
0057 push word ptr [bp + 0xa]
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
005f add sp, 2
0062 mov es, dx
0064 mov bx, ax
0066 mov si, ax
0068 mov word ptr [bp - 0xe], es
006b mov ax, word ptr es:[bx]
006e mov word ptr [bp - 0xa], ax
0071 inc ax
0072 shl ax, 2
0075 sub dx, dx
0077 mov cx, es
0079 add ax, bx
007b adc dx, cx
007d mov word ptr [bp - 4], ax
0080 mov word ptr [bp - 2], dx
0083 lea ax, [bx + 4]
0086 mov word ptr [bp - 6], es
0089 mov word ptr [bp - 0x10], si
008c mov si, word ptr [bp - 4]
008f mov di, ax
0091 jmp 0x9578
0093 nop 
0094 mov es, word ptr [bp - 6]
0097 cmp word ptr es:[di], -1
009b je 0x9572
009d mov es, word ptr [bp - 2]
00a0 cmp word ptr es:[si], 0
00a4 je 0x9572
00a6 push word ptr es:[si]
00a9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 172, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Freed
00ae add sp, 2
00b1 or ax, ax
00b3 je 0x9572
00b5 mov es, word ptr [bp - 2]
00b8 push word ptr es:[si]
00bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 190, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_LockLevel
00c0 add sp, 2
00c3 or ax, ax
00c5 jne 0x9572
00c7 mov es, word ptr [bp - 6]
00ca push word ptr es:[di + 2]
00ce push word ptr es:[di]
00d1 push ds
00d2 push 0xb618
00d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 216, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
00da add sp, 8
00dd mov es, word ptr [bp - 2]
00e0 push word ptr es:[si]
00e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 230, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
00e8 add sp, 2
00eb mov es, word ptr [bp - 2]
00ee mov word ptr es:[si], 0
00f3 mov es, word ptr [bp - 6]
00f6 mov word ptr es:[di], 0xffff
00fb les bx, ptr [bp - 0x10]
00fe dec word ptr es:[bx + 2]
0102 add di, 4
0105 add si, 2
0108 mov ax, word ptr [bp - 0xa]
010b dec word ptr [bp - 0xa]
010e or ax, ax
0110 jne 0x9504
0112 mov di, word ptr [bp + 0xa]
0115 push ds
0116 push 0xb623
0119 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 284, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
011e add sp, 4
0121 les bx, ptr [bp - 0x10]
0124 mov si, word ptr es:[bx + 2]
0128 push di
0129 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 300, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
012e add sp, 2
0131 cmp si, word ptr [bp - 0x12]
0134 je 0x95a9
0136 jmp 0x96c0
0139 push si
013a push word ptr [bp + 8]
013d push word ptr [bp + 6]
0140 push ds
0141 push 0xb5c7
0144 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 327, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0149 add sp, 0xa
014c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 335, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Flush
0151 push di
0152 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 341, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0157 add sp, 2
015a mov es, dx
015c mov bx, ax
015e mov si, ax
0160 mov word ptr [bp - 0xe], es
0163 mov ax, word ptr es:[bx]
0166 mov word ptr [bp - 0xa], ax
0169 inc ax
016a shl ax, 2
016d sub dx, dx
016f mov cx, es
0171 add ax, bx
0173 adc dx, cx
0175 mov word ptr [bp - 4], ax
0178 mov word ptr [bp - 2], dx
017b lea ax, [bx + 4]
017e mov word ptr [bp - 6], es
0181 mov word ptr [bp - 0x10], si
0184 mov si, word ptr [bp - 4]
0187 mov di, ax
0189 jmp 0x9670
018b nop 
018c mov es, word ptr [bp - 6]
018f cmp word ptr es:[di], -1
0193 je 0x966a
0195 mov es, word ptr [bp - 2]
0198 cmp word ptr es:[si], 0
019c je 0x966a
019e push word ptr es:[si]
01a1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 420, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Freed
01a6 add sp, 2
01a9 or ax, ax
01ab je 0x966a
01ad mov es, word ptr [bp - 2]
01b0 push word ptr es:[si]
01b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 438, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_LockLevel
01b8 add sp, 2
01bb or ax, ax
01bd jne 0x966a
01bf mov es, word ptr [bp - 6]
01c2 push word ptr es:[di + 2]
01c6 push word ptr es:[di]
01c9 push ds
01ca push 0xb618
01cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 464, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
01d2 add sp, 8
01d5 mov es, word ptr [bp - 2]
01d8 push word ptr es:[si]
01db lcall <resolved loader operand; see bindings> ; [{'operand_offset': 478, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
01e0 add sp, 2
01e3 mov es, word ptr [bp - 2]
01e6 mov word ptr es:[si], 0
01eb mov es, word ptr [bp - 6]
01ee mov word ptr es:[di], 0xffff
01f3 les bx, ptr [bp - 0x10]
01f6 dec word ptr es:[bx + 2]
01fa add di, 4
01fd add si, 2
0200 mov ax, word ptr [bp - 0xa]
0203 dec word ptr [bp - 0xa]
0206 or ax, ax
0208 jne 0x95fc
020a mov si, word ptr [bp - 0x12]
020d push ds
020e push 0xb623
0211 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 532, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0216 add sp, 4
0219 les bx, ptr [bp - 0x10]
021c mov di, word ptr es:[bx + 2]
0220 push word ptr [bp + 0xa]
0223 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 550, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0228 add sp, 2
022b cmp di, si
022d jne 0x96c0
022f push word ptr [bp + 0xa]
0232 nop 
0233 push cs
0234 call 0x9886 ; _ch_DumpOldest
0237 add sp, 2
023a cmp ax, si
023c jne 0x96c0
023e push word ptr [bp + 0xa]
0241 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 580, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0246 add sp, 2
0249 xor ax, ax
024b pop si
024c pop di
024d leave 
024e retf 
024f nop 
0250 push word ptr [bp + 0xa]
0253 push word ptr [bp + 8]
0256 push word ptr [bp + 6]
0259 nop 
025a push cs
025b call 0x91e6 ; _ch_LookUpId
025e add sp, 6
0261 or ax, ax
0263 je 0x96e1
0265 push ds
0266 push 0xb5e7
0269 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 620, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
026e add sp, 4
0271 mov ax, word ptr [bp + 6]
0274 mov bx, word ptr [0xb594]
0278 shl bx, 2
027b mov es, word ptr [bp - 0x14]
027e add bx, word ptr [bp - 0x16]
0281 mov word ptr es:[bx + 4], ax
0285 mov ax, word ptr [bp + 8]
0288 mov word ptr es:[bx + 6], ax
028c mov ax, word ptr [bp + 0xc]
028f mov bx, word ptr [bp - 0x12]
0292 inc bx
0293 shl bx, 2
0296 sub cx, cx
0298 add bx, word ptr [bp - 0x16]
029b adc cx, word ptr [bp - 0x14]
029e mov es, cx
02a0 mov si, word ptr [0xb594]
02a4 shl si, 1
02a6 mov word ptr es:[bx + si], ax
02a9 les bx, ptr [bp - 0x16]
02ac inc word ptr es:[bx + 2]
02b0 push word ptr [bp + 0xa]
02b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 694, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
02b8 add sp, 2
02bb mov ax, 1
02be pop si
02bf pop di
02c0 leave 
02c1 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern int far ch_LookUpId(int object, int type, int cacheTable);` — src/recovered/db_PurgeObject.c
- `extern int far ch_LookUpId(int object, int type, int cacheTable);` — src/recovered/db_ReleaseObject.c
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

- {'symbol': '_ch_LookUpHandle', 'offset': 37186, 'source': None, 'size': 163}
- {'symbol': '_ch_LookUpId', 'offset': 37350, 'source': None, 'size': 649}
- {'symbol': '_ch_DeleteEntry', 'offset': 38706, 'source': None, 'size': 114}
- {'symbol': '_ch_CleanupTable', 'offset': 38820, 'source': None, 'size': 226}
