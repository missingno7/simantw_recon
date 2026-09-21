# Recovery task _LoadMonoPats

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 278 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 push 0
0008 push 0x16
000a push 0x2710
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0012 add sp, 6
0015 mov si, ax
0017 mov word ptr [bp - 0xe], si
001a push si
001b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0020 add sp, 2
0023 mov di, ax
0025 mov word ptr [bp - 0xa], dx
0028 or si, si
002a je 0xd539
002c mov es, dx
002e cmp word ptr es:[di], 0x300
0033 je 0xd545
0035 push ds
0036 push 0x15f8
0039 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 60, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
003e add sp, 4
0041 add di, 2
0044 mov ax, 0x2688
0047 mov dx, ds
0049 mov cx, ax
004b mov es, dx
004d mov word ptr [bp - 8], 0x18
0052 mov word ptr [bp - 6], 0x18
0057 mov word ptr [bp - 4], cx
005a mov si, ax
005c mov cx, word ptr [bp - 6]
005f mov ds, word ptr [bp - 0xa]
0062 mov bx, di
0064 inc di
0065 mov al, byte ptr [bx]
0067 not al
0069 mov byte ptr es:[si], al
006c inc si
006d dec cx
006e jne 0xd566
0070 push ss
0071 pop ds
0072 mov si, word ptr [bp - 0xe]
0075 push si
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
007b add sp, 2
007e push 0x16
0080 push 0x2710
0083 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 134, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
0088 add sp, 4
008b push 0
008d push 0x16
008f push 0x271a
0092 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 149, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0097 add sp, 6
009a mov si, ax
009c or si, si
009e jne 0xd5b0
00a0 push ds
00a1 push 0x1619
00a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 167, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
00a9 add sp, 4
00ac push si
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
00b2 add sp, 2
00b5 mov es, dx
00b7 mov bx, ax
00b9 mov al, byte ptr es:[bx + 1]
00bd cwde 
00be shl ax, 3
00c1 mov word ptr [bp - 8], ax
00c4 lea ax, [bx + 2]
00c7 mov di, ax
00c9 mov word ptr [bp - 0xa], es
00cc mov word ptr [bp - 4], 0x26a0
00d1 mov word ptr [bp - 2], ds
00d4 cmp word ptr [bp - 8], 0
00d8 jle 0xd600
00da mov word ptr [bp - 0xe], si
00dd mov cx, word ptr [bp - 8]
00e0 mov si, word ptr [bp - 4]
00e3 mov ds, word ptr [bp - 0xa]
00e6 mov es, word ptr [bp - 2]
00e9 mov bx, di
00eb inc di
00ec mov al, byte ptr [bx]
00ee not al
00f0 mov byte ptr es:[si], al
00f3 inc si
00f4 dec cx
00f5 jne 0xd5ed
00f7 mov si, word ptr [bp - 0xe]
00fa push ss
00fb pop ds
00fc push si
00fd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 256, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0102 add sp, 2
0105 push 0x16
0107 push 0x271a
010a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 269, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_PurgeObject
010f add sp, 4
0112 pop si
0113 pop di
0114 leave 
0115 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern void far db_PurgeObject(int object, int kind);` — src/recovered/wf_PictStrnDialog-d2f52b0e98.c
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

- {'symbol': '_AboutDialog', 'offset': 53050, 'source': None, 'size': 1192}
- {'symbol': '_ShowIntro', 'offset': 54242, 'source': None, 'size': 290}
- {'symbol': '_Quit', 'offset': 54810, 'source': 'src/recovered/Quit.c', 'size': 13}
- {'symbol': '_MenuQuit', 'offset': 54824, 'source': None, 'size': 66}
