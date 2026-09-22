# Recovery task _DrawMapFoot

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 484 bytes.

```asm
0000 enter 0x1e, 0
0004 push di
0005 push si
0006 push word ptr [0x19aa] ; _mapBuf
000a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
000f add sp, 2
0012 mov word ptr [bp - 6], ax
0015 mov word ptr [bp - 4], dx
0018 mov es, word ptr [0xc202]
001c cmp word ptr es:[0x8a7e], 0
0022 jne 0xd24d
0024 jmp 0xd406
0027 mov es, word ptr [0xc204]
002b mov ax, word ptr es:[0x7a58]
002f shl ax, 2
0032 mov si, ax
0034 lea cx, [bp - 8]
0037 push ss
0038 push cx
0039 lea dx, [bp - 0xa]
003c push ss
003d push dx
003e mov es, word ptr [0xc206]
0042 mov bl, byte ptr es:[0x8a72]
0047 and bx, 3
004a add bx, 0x4b0
004e push bx
004f mov es, word ptr [0xc1e4]
0053 mov bx, word ptr es:[0x807c]
0058 shl bx, 7
005b push bx
005c mov es, word ptr [0xc1e2]
0060 mov bx, word ptr es:[0x8096]
0065 shl bx, 6
0068 push bx
0069 push ax
006a mov es, word ptr [0xc208]
006e mov di, word ptr es:[0x7a4e]
0073 shl di, 2
0076 push di
0077 push word ptr [bp - 4]
007a push word ptr [bp - 6]
007d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 128, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DrawBitMapToBuffer
0082 add sp, 0x16
0085 mov es, word ptr [0xc1f2]
0089 add si, word ptr es:[0x8112]
008e mov word ptr [bp - 0x18], si
0091 add di, word ptr es:[0x8110]
0096 mov word ptr [bp - 0x1a], di
0099 add di, word ptr [bp - 8]
009c mov word ptr [bp - 0x16], di
009f add si, word ptr [bp - 0xa]
00a2 mov word ptr [bp - 0x14], si
00a5 push word ptr [0xbca8]
00a9 lea ax, [bp - 0x1a]
00ac push ss
00ad push ax
00ae push 0
00b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
00b5 cmp word ptr [0xac74], 3 ; _BoyHere
00ba je 0xd2ec
00bc cmp word ptr [0xac74], 4 ; _BoyHere
00c1 je 0xd2ec
00c3 jmp 0xd37c
00c6 mov es, word ptr [0xc20a]
00ca mov ax, word ptr es:[0x9afc]
00ce shl ax, 2
00d1 mov si, ax
00d3 lea cx, [bp - 8]
00d6 push ss
00d7 push cx
00d8 lea dx, [bp - 0xa]
00db push ss
00dc push dx
00dd mov es, word ptr [0xc206]
00e1 mov bx, word ptr es:[0x8a72]
00e6 not bx
00e8 and bx, 1
00eb add bx, 0x4ba
00ef push bx
00f0 mov es, word ptr [0xc1e4]
00f4 mov bx, word ptr es:[0x807c]
00f9 shl bx, 7
00fc push bx
00fd mov es, word ptr [0xc1e2]
0101 mov bx, word ptr es:[0x8096]
0106 shl bx, 6
0109 push bx
010a push ax
010b mov es, word ptr [0xc20c]
010f mov di, word ptr es:[0x9af4]
0114 shl di, 2
0117 push di
0118 push word ptr [bp - 4]
011b push word ptr [bp - 6]
011e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 289, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DrawBitMapToBuffer
0123 add sp, 0x16
0126 mov es, word ptr [0xc1f2]
012a add si, word ptr es:[0x8112]
012f mov word ptr [bp - 0x10], si
0132 add di, word ptr es:[0x8110]
0137 mov word ptr [bp - 0x12], di
013a add di, word ptr [bp - 8]
013d mov word ptr [bp - 0xe], di
0140 add si, word ptr [bp - 0xa]
0143 mov word ptr [bp - 0xc], si
0146 push word ptr [0xbca8]
014a lea ax, [bp - 0x12]
014d push ss
014e push ax
014f push 0
0151 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 338, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
0156 push word ptr [0x19aa] ; _mapBuf
015a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 349, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
015f add sp, 2
0162 mov es, word ptr [0xc204]
0166 mov si, word ptr es:[0x7a58]
016b mov bx, 0x72ca
016e mov es, word ptr [0xc1e0]
0172 mov word ptr [bp - 0x1e], bx
0175 mov word ptr [bp - 0x1c], es
0178 cmp word ptr es:[bx], 0
017c je 0xd400
017e push word ptr es:[bx]
0181 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 388, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0186 add sp, 2
0189 mov di, ax
018b mov word ptr [bp - 4], dx
018e mov es, word ptr [0xc200]
0192 mov ax, word ptr es:[0x78ba]
0196 imul si
0198 add di, ax
019a lea ax, [si + 8]
019d mov word ptr [bp - 2], ax
01a0 cmp ax, si
01a2 jle 0xd3f2
01a4 mov cx, ax
01a6 mov ds, word ptr [bp - 4]
01a9 mov <resolved loader operand; see bindings> ; [{'operand_offset': 426, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
01ac mov es, ax
01ae cmp si, 0x40
01b1 jl 0xd3de
01b3 push ss
01b4 pop ds
01b5 jmp 0xd3f2
01b7 nop 
01b8 or si, si
01ba jl 0xd3e5
01bc mov byte ptr [di], 0xff
01bf mov ax, word ptr es:[0x78ba]
01c3 add di, ax
01c5 inc si
01c6 cmp si, cx
01c8 jl 0xd3d4
01ca jmp 0xd3d9
01cc les bx, ptr [bp - 0x1e]
01cf push word ptr es:[bx]
01d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 469, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
01d7 add sp, 2
01da mov word ptr [0x1994], 1 ; _newMapForce
01e0 pop si
01e1 pop di
01e2 leave 
01e3 retf 
```

## Known declaration examples

- `extern int near BoyHere;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_11_scaffold-af3668fd7e.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawMapWindow', 'offset': 52806, 'source': None, 'size': 712}
- {'symbol': '_DrawMapSpider', 'offset': 53518, 'source': None, 'size': 280}
- {'symbol': '_MapToYellowAnt', 'offset': 54282, 'source': None, 'size': 105}
- {'symbol': '_Mini_DrawMapI', 'offset': 54388, 'source': None, 'size': 811}
