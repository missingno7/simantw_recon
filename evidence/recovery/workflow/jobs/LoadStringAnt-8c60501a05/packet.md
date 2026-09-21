# Recovery task _LoadStringAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 231 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 push 0
000b push 4
000d push si
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0013 add sp, 6
0016 mov word ptr [bp - 0xe], ax
0019 or ax, ax
001b jne 0x426
001d push si
001e push ds
001f push 0x229c
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0027 add sp, 6
002a xor ax, ax
002c cdq 
002d pop si
002e pop di
002f leave 
0030 retf 
0031 nop 
0032 push ax
0033 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0038 add sp, 2
003b mov di, ax
003d mov word ptr [bp - 6], dx
0040 mov es, dx
0042 inc di
0043 mov al, byte ptr es:[di]
0046 sub ah, ah
0048 mov si, ax
004a mov ax, di
004c inc ax
004d mov di, ax
004f mov word ptr [bp - 4], ax
0052 mov word ptr [bp - 2], dx
0055 lea ax, [si + 1]
0058 shl ax, 2
005b push ax
005c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 95, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _malloc
0061 add sp, 2
0064 mov word ptr [bp - 0x12], ax
0067 mov word ptr [bp - 0x10], dx
006a mov word ptr [bp - 0x14], 0
006f or si, si
0071 jle 0x4b5
0073 mov di, ax
0075 mov word ptr [bp - 0xa], dx
0078 mov word ptr [bp - 8], si
007b add word ptr [bp - 0x14], si
007e mov si, word ptr [bp - 4]
0081 mov ax, word ptr [bp - 2]
0084 mov es, word ptr [bp - 0xa]
0087 mov word ptr es:[di], si
008a mov word ptr es:[di + 2], ax
008e mov es, ax
0090 mov cl, byte ptr es:[si]
0093 sub ch, ch
0095 mov word ptr [bp - 6], cx
0098 push cx
0099 lea cx, [si + 1]
009c push ax
009d push cx
009e push ax
009f push si
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
00a5 add sp, 0xa
00a8 mov bx, si
00aa mov es, word ptr [bp - 2]
00ad add bx, word ptr [bp - 6]
00b0 mov byte ptr es:[bx], 0
00b4 lea ax, [bx + 1]
00b7 mov si, ax
00b9 add di, 4
00bc dec word ptr [bp - 8]
00bf jne 0x475
00c1 mov bx, word ptr [bp - 0x14]
00c4 shl bx, 2
00c7 les si, ptr [bp - 0x12]
00ca sub ax, ax
00cc mov word ptr es:[bx + si + 2], ax
00d0 mov word ptr es:[bx + si], ax
00d3 push word ptr [bp - 0xe]
00d6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 217, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
00db add sp, 2
00de mov ax, si
00e0 mov dx, word ptr [bp - 0x10]
00e3 pop si
00e4 pop di
00e5 leave 
00e6 retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far *malloc(unsigned int size);` — src/recovered/mem_malloc.c
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

- {'symbol': '_SimAllocate', 'offset': 576, 'source': 'src/recovered/SimAllocate.c', 'size': 1}
- {'symbol': '_PrepareStrings', 'offset': 578, 'source': None, 'size': 433}
- {'symbol': '_CreateSimPats', 'offset': 1244, 'source': 'src/recovered/CreateSimPats.c', 'size': 1}
- {'symbol': '_CountAnts', 'offset': 1246, 'source': None, 'size': 725}
