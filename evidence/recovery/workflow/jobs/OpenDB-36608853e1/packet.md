# Recovery task _OpenDB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 517 bytes.

```asm
0000 enter 0x74, 0
0004 push di
0005 push si
0006 cmp word ptr [0xb4e2], 0
000b jne 0x8c17
000d mov word ptr [0xb4e2], 1
0013 mov bx, 0x7408
0016 mov <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0019 mov ds, ax
001b mov byte ptr [bx], 0
001e add bx, 0x7c
0021 cmp bx, 0x75f8
0025 jb 0x8c0b
0027 xor cx, cx
0029 mov bx, 0x7408
002c mov <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
002f mov ds, ax
0031 cmp byte ptr [bx], 0
0034 je 0x8c8a
0036 inc cx
0037 add bx, 0x7c
003a cmp bx, 0x75f8
003e jb 0x8c21
0040 push ss
0041 pop ds
0042 mov di, 0xffff
0045 cmp di, -1
0048 jne 0x8c46
004a push ds
004b push 0xb4b2
004e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0053 add sp, 4
0056 push 0x4f
0058 push word ptr [bp + 8]
005b push word ptr [bp + 6]
005e imul ax, di, 0x7c
0061 mov word ptr [bp - 0x70], ax
0064 add ax, 0x7408
0067 mov <resolved loader operand; see bindings> ; [{'operand_offset': 104, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
006a mov si, ax
006c mov word ptr [bp - 2], cx
006f push cx
0070 push ax
0071 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strncpy
0076 add sp, 0xa
0079 mov es, word ptr [bp - 2]
007c mov byte ptr es:[si + 0x4f], 0
0081 cmp byte ptr es:[si], 0x2e
0085 jne 0x8c90
0087 mov word ptr [bp - 0xa], di
008a mov ds, word ptr [bp - 2]
008d inc si
008e cmp byte ptr [si], 0x2e
0091 je 0x8c7d
0093 mov word ptr [bp - 4], si
0096 push ss
0097 pop ds
0098 jmp 0x8c93
009a push ss
009b pop ds
009c mov di, cx
009e jmp 0x8c35
00a0 mov word ptr [bp - 4], si
00a3 push 0x2e
00a5 push word ptr [bp - 2]
00a8 push si
00a9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 172, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strrchr
00ae add sp, 6
00b1 mov si, ax
00b3 mov word ptr [bp - 6], dx
00b6 or dx, ax
00b8 je 0x8cc5
00ba push 0x5c
00bc push word ptr [bp - 2]
00bf push word ptr [bp - 4]
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strrchr
00c7 add sp, 6
00ca cmp ax, si
00cc jae 0x8cc5
00ce mov es, word ptr [bp - 6]
00d1 mov byte ptr es:[si], 0
00d5 mov ax, word ptr [bp - 0x70]
00d8 add ax, 0x7408
00db mov <resolved loader operand; see bindings> ; [{'operand_offset': 220, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00de push cx
00df push ax
00e0 push ds
00e1 push 0xb4c2
00e4 lea ax, [bp - 0x6e]
00e7 push ss
00e8 push ax
00e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 236, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
00ee add sp, 0xc
00f1 lea ax, [bp - 0x6e]
00f4 push ss
00f5 push ax
00f6 push 2
00f8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 249, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 85}}]
00fd mov bx, word ptr [bp - 0x70]
0100 add bx, 0x7480
0104 mov es, word ptr [0xc68a]
0108 mov word ptr [bp - 0x74], bx
010b mov word ptr [bp - 0x72], es
010e mov word ptr es:[bx], ax
0111 or ax, ax
0113 jg 0x8d6c
0115 lea ax, [bp - 0x6e]
0118 push ss
0119 push ax
011a push 0
011c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 285, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 83}}]
0121 les bx, ptr [bp - 0x74]
0124 mov word ptr es:[bx], ax
0127 or ax, ax
0129 jg 0x8d51
012b cmp word ptr [0xacf8], 0x18 ; _errno
0130 jne 0x8d2e
0132 push ds
0133 push 0xb4e4
0136 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 313, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
013b add sp, 4
013e mov bx, word ptr [0xacf8] ; _errno
0142 shl bx, 2
0145 push word ptr [bx - 0x5092]
0149 push word ptr [bx - 0x5094]
014d push word ptr [0xacf8] ; _errno
0151 push ds
0152 push 0xb4c9
0155 push ds
0156 push 0xb56a
0159 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 348, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
015e add sp, 0xe
0161 push di
0162 mov ax, word ptr [bp - 0x70]
0165 add ax, 0x7408
0168 mov <resolved loader operand; see bindings> ; [{'operand_offset': 361, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
016b push cx
016c push ax
016d nop 
016e push cs
016f call 0x9b48 ; _CreateIndex
0172 add sp, 6
0175 mov <resolved loader operand; see bindings> ; [{'operand_offset': 374, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0178 mov ds, ax
017a jmp 0x8dc6
017c mov es, word ptr [bp - 0x72]
017f push word ptr es:[bx]
0182 mov ax, word ptr [bp - 0x70]
0185 add ax, 0x7470
0188 mov <resolved loader operand; see bindings> ; [{'operand_offset': 393, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
018b push cx
018c push ax
018d push 0xe
018f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 400, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 82}}]
0194 cmp ax, 0xe
0197 jne 0x8d65
0199 mov <resolved loader operand; see bindings> ; [{'operand_offset': 410, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
019c mov ds, ax
019e mov bx, word ptr [bp - 0x70]
01a1 cmp word ptr [bx + 0x7470], 0x5678
01a7 jne 0x8dc6
01a9 cmp word ptr [bx + 0x7472], 0x1234
01af jne 0x8dc6
01b1 push ss
01b2 pop ds
01b3 push di
01b4 mov ax, bx
01b6 add ax, 0x7408
01b9 mov <resolved loader operand; see bindings> ; [{'operand_offset': 442, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
01bc push cx
01bd push ax
01be nop 
01bf push cs
01c0 call 0x9a86 ; _OpenIndex
01c3 add sp, 6
01c6 mov es, word ptr [0xc68a]
01ca mov bx, word ptr [bp - 0x70]
01cd mov word ptr es:[bx + 0x7482], 0
01d4 jmp 0x8ded
01d6 mov bx, word ptr [bp - 0x70]
01d9 mov word ptr [bx + 0x7470], 0x5678
01df mov word ptr [bx + 0x7472], 0x1234
01e5 sub ax, ax
01e7 mov word ptr [bx + 0x7478], ax
01eb mov word ptr [bx + 0x7476], ax
01ef mov word ptr [bx + 0x747c], ax
01f3 mov word ptr [bx + 0x747a], ax
01f7 mov word ptr [bx + 0x7482], 1
01fd mov ax, di
01ff push ss
0200 pop ds
0201 pop si
0202 pop di
0203 leave 
0204 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_gr_0000_InitGraphics_1-8959d65c41.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_simtwo_81AC_db_SetDataBase_1_reviewed-7aea199e9a.c
- `extern char far * far strrchr(const char far *text, int character);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DBPack', 'offset': 35106, 'source': None, 'size': 547}
- {'symbol': '_DBReplace', 'offset': 35654, 'source': 'src/recovered/wf_DBReplace-da4c045f1a.c', 'size': 169}
- {'symbol': '_FlushDB', 'offset': 36342, 'source': 'src/recovered/FlushDB.c', 'size': 1}
- {'symbol': '_CloseDB', 'offset': 36344, 'source': None, 'size': 95}
