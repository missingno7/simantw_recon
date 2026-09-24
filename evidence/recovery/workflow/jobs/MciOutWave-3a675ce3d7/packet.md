# Recovery task _MciOutWave

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 788 bytes.

```asm
0000 enter 0x36, 0
0004 push di
0005 push si
0006 mov bx, 0x8d08
0009 mov es, word ptr [0xbf78]
000d mov word ptr [bp - 0x2e], bx
0010 mov word ptr [bp - 0x2c], es
0013 push word ptr es:[bx]
0016 push ds
0017 push 0x1166
001a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
001f mov word ptr [bp - 0x14], ax
0022 mov word ptr [bp - 0x12], dx
0025 push word ptr [bp + 6]
0028 nop 
0029 push cs
002a call 0x558e ; _mem_Lock
002d add sp, 2
0030 mov word ptr [bp - 0xc], ax
0033 mov word ptr [bp - 0xa], dx
0036 push 0x2002
0039 push 0
003b push 0x20
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 15}}]
0042 mov word ptr [0xaf0], ax
0045 push ax
0046 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 18}}]
004b mov word ptr [bp - 0x10], ax
004e mov word ptr [bp - 0xe], dx
0051 push 0x2002
0054 push word ptr [bp + 6]
0057 nop 
0058 push cs
0059 call 0x55aa ; _mem_Size
005c add sp, 2
005f sub ax, 0x10
0062 shl ax, 1
0064 mov word ptr [bp - 0x16], ax
0067 push 0
0069 push ax
006a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 107, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 15}}]
006f mov word ptr [0xaf2], ax
0072 push ax
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 18}}]
0078 les bx, ptr [bp - 0x10]
007b mov word ptr es:[bx], ax
007e mov word ptr es:[bx + 2], dx
0082 mov ax, word ptr [bp - 0x16]
0085 mov word ptr [bp - 8], ax
0088 mov ax, word ptr es:[bx]
008b mov word ptr [bp - 0x1a], ax
008e mov word ptr [bp - 0x18], dx
0091 mov byte ptr [bp - 1], 0x80
0095 mov ax, word ptr [bp - 0xc]
0098 mov dx, word ptr [bp - 0xa]
009b mov cx, 8
009e push ds
009f lea di, [bp - 0x2a]
00a2 mov si, ax
00a4 push ss
00a5 pop es
00a6 mov ds, dx
00a8 rep movsw word ptr es:[di], word ptr [si]
00aa pop ds
00ab add ax, 0x10
00ae mov word ptr [bp - 6], ax
00b1 mov word ptr [bp - 4], dx
00b4 xor di, di
00b6 mov si, di
00b8 shr word ptr [bp - 8], 1
00bb cmp word ptr [bp - 8], si
00be je 0x96a4
00c0 mov cx, ax
00c2 mov ds, dx
00c4 mov bx, cx
00c6 add bx, di
00c8 mov bl, byte ptr [bx]
00ca mov ax, bx
00cc shr bl, 4
00cf sub bh, bh
00d1 lea dx, [bp - 0x2a]
00d4 add bx, dx
00d6 mov dl, byte ptr ss:[bx]
00d9 add byte ptr [bp - 1], dl
00dc les bx, ptr [bp - 0x1a]
00df mov dl, byte ptr [bp - 1]
00e2 mov byte ptr es:[bx + si], dl
00e5 mov bl, al
00e7 and bx, 0xf
00ea lea ax, [bp - 0x2a]
00ed add bx, ax
00ef mov al, byte ptr ss:[bx]
00f2 add byte ptr [bp - 1], al
00f5 les bx, ptr [bp - 0x1a]
00f8 inc si
00f9 mov al, byte ptr [bp - 1]
00fc mov byte ptr es:[bx + si], al
00ff inc si
0100 inc di
0101 cmp di, word ptr [bp - 8]
0104 jb 0x9660
0106 push ss
0107 pop ds
0108 les bx, ptr [bp - 0x10]
010b sub ax, ax
010d mov word ptr es:[bx + 0xa], ax
0111 mov word ptr es:[bx + 8], ax
0115 mov ax, word ptr [0xaf0]
0118 cdq 
0119 mov cx, word ptr [0xaf2]
011d mov di, cx
011f mov si, ax
0121 or di, dx
0123 mov word ptr es:[bx + 0xc], si
0127 mov word ptr es:[bx + 0xe], di
012b sub ax, ax
012d mov word ptr es:[bx + 0x12], ax
0131 mov word ptr es:[bx + 0x10], ax
0135 mov word ptr es:[bx + 0x16], ax
0139 mov word ptr es:[bx + 0x14], ax
013d push word ptr [0xcd78] ; _rootWnd
0141 mov ax, word ptr [bp - 0x16]
0144 sub dx, dx
0146 mov word ptr es:[bx + 4], ax
014a mov word ptr es:[bx + 6], dx
014e push dx
014f push ax
0150 push ds
0151 push 0x117b
0154 nop 
0155 push cs
0156 call 0x62bc ; _WinPrintf
0159 add sp, 0xa
015c mov bx, 0x8d1a
015f mov es, word ptr [0xbf78]
0163 mov word ptr [bp - 0x32], bx
0166 mov word ptr [bp - 0x30], es
0169 inc word ptr es:[bx]
016c mov ax, word ptr [bp - 0x12]
016f or ax, word ptr [bp - 0x14]
0172 jne 0x9713
0174 jmp 0x9826
0177 mov bx, 0x8d14
017a mov word ptr [bp - 0x36], bx
017d mov word ptr [bp - 0x34], es
0180 push word ptr es:[bx]
0183 push word ptr [bp - 0xe]
0186 push word ptr [bp - 0x10]
0189 push 0x20
018b lcall [bp - 0x14]
018e or ax, ax
0190 je 0x9731
0192 jmp 0x9826
0195 les bx, ptr [bp - 0x2e]
0198 push word ptr es:[bx]
019b push ds
019c push 0x11a0
019f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 416, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
01a4 mov word ptr [bp - 4], ax
01a7 mov word ptr [bp - 2], dx
01aa or dx, ax
01ac jne 0x974d
01ae jmp 0x98a1
01b1 les bx, ptr [bp - 0x36]
01b4 push word ptr es:[bx]
01b7 push word ptr [bp - 0xe]
01ba push word ptr [bp - 0x10]
01bd push 0x20
01bf lcall [bp - 4]
01c2 or ax, ax
01c4 jne 0x9765
01c6 jmp 0x98a1
01c9 les bx, ptr [bp - 0x2e]
01cc push word ptr es:[bx]
01cf push ds
01d0 push 0x11ad
01d3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 468, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
01d8 mov word ptr [bp - 4], ax
01db mov word ptr [bp - 2], dx
01de push ds
01df push 0x11c4
01e2 nop 
01e3 push cs
01e4 call 0x62bc ; _WinPrintf
01e7 add sp, 4
01ea les bx, ptr [bp - 0x10]
01ed push word ptr es:[bx + 0x12]
01f1 push word ptr es:[bx + 0x10]
01f5 push ds
01f6 push 0x11f1
01f9 nop 
01fa push cs
01fb call 0x62bc ; _WinPrintf
01fe add sp, 8
0201 mov ax, word ptr [bp - 2]
0204 or ax, word ptr [bp - 4]
0207 je 0x97b6
0209 les bx, ptr [bp - 0x36]
020c push word ptr es:[bx]
020f push word ptr [bp - 0xe]
0212 push word ptr [bp - 0x10]
0215 push 0x20
0217 lcall [bp - 4]
021a mov di, word ptr [0xaf0]
021e mov si, word ptr [0xaf2]
0222 or si, si
0224 je 0x97d4
0226 push si
0227 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 552, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
022c push si
022d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 558, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
0232 mov word ptr [0xaf2], 0
0238 cmp word ptr [0xaf0], 0
023d je 0x97ed
023f push di
0240 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 577, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
0245 push di
0246 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 583, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
024b mov word ptr [0xaf0], 0
0251 les bx, ptr [bp - 0x32]
0254 dec word ptr es:[bx]
0257 je 0x97f8
0259 jmp 0x98a1
025c les bx, ptr [bp - 0x2e]
025f push word ptr es:[bx]
0262 push ds
0263 push 0xc6d
0266 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 615, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
026b mov word ptr [bp - 4], ax
026e mov word ptr [bp - 2], dx
0271 or dx, ax
0273 je 0x981a
0275 les bx, ptr [bp - 0x36]
0278 push word ptr es:[bx]
027b lcall [bp - 4]
027e les bx, ptr [bp - 0x36]
0281 mov word ptr es:[bx], 0
0286 jmp 0x98a1
0288 nop 
0289 nop 
028a push ds
028b push 0x1209
028e nop 
028f push cs
0290 call 0x62bc ; _WinPrintf
0293 add sp, 4
0296 mov di, word ptr [0xaf0]
029a mov si, word ptr [0xaf2]
029e or si, si
02a0 je 0x9850
02a2 push si
02a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 676, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
02a8 push si
02a9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 682, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
02ae mov word ptr [0xaf2], 0
02b4 cmp word ptr [0xaf0], 0
02b9 je 0x9869
02bb push di
02bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 701, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
02c1 push di
02c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 707, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
02c7 mov word ptr [0xaf0], 0
02cd les bx, ptr [bp - 0x32]
02d0 dec word ptr es:[bx]
02d3 jne 0x98a1
02d5 les bx, ptr [bp - 0x2e]
02d8 push word ptr es:[bx]
02db push ds
02dc push 0xc6d
02df lcall <resolved loader operand; see bindings> ; [{'operand_offset': 736, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
02e4 mov word ptr [bp - 4], ax
02e7 mov word ptr [bp - 2], dx
02ea or dx, ax
02ec je 0x9896
02ee mov es, word ptr [0xbf78]
02f2 push word ptr es:[0x8d14]
02f7 lcall [bp - 4]
02fa mov es, word ptr [0xbf78]
02fe mov word ptr es:[0x8d14], 0
0305 push word ptr [bp + 6]
0308 nop 
0309 push cs
030a call 0x559c ; _mem_Unlock
030d add sp, 2
0310 pop si
0311 pop di
0312 leave 
0313 retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Extract24BitVal', 'offset': 34072, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c', 'size': 118}
- {'symbol': '_myBeginSong', 'offset': 34190, 'source': None, 'size': 4110}
- {'symbol': '_myBeginSound', 'offset': 39088, 'source': None, 'size': 2263}
- {'symbol': '_mySoundIsDone', 'offset': 41352, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c', 'size': 4}
