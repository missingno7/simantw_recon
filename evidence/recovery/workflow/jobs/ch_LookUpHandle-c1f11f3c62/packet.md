# Recovery task _ch_LookUpHandle

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 163 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 8]
0009 push si
000a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
000f add sp, 2
0012 mov es, dx
0014 mov bx, ax
0016 mov ax, word ptr es:[bx]
0019 mov word ptr [bp - 0xc], ax
001c lea cx, [bx + 4]
001f mov di, cx
0021 mov word ptr [bp - 2], es
0024 mov cx, ax
0026 inc ax
0027 shl ax, 2
002a sub dx, dx
002c mov word ptr [bp - 0x10], ax
002f mov ax, es
0031 add bx, word ptr [bp - 0x10]
0034 adc ax, dx
0036 or cx, cx
0038 jle 0x91d4
003a mov word ptr [bp - 4], di
003d lds si, ptr [bp - 4]
0040 mov es, ax
0042 mov cx, dx
0044 cmp word ptr [si], -1
0047 je 0x9193
0049 mov ax, word ptr [bp + 6]
004c cmp word ptr es:[bx], ax
004f je 0x91a4
0051 add si, 4
0054 add bx, 2
0057 inc cx
0058 cmp cx, word ptr [bp - 0xc]
005b jl 0x9186
005d push ss
005e pop ds
005f jmp 0x91d4
0061 nop 
0062 mov word ptr [bp - 4], si
0065 push ss
0066 pop ds
0067 les bx, ptr [bp - 4]
006a mov ax, word ptr es:[bx]
006d les si, ptr [bp + 0xa]
0070 mov word ptr es:[si], ax
0073 mov es, word ptr [bp - 2]
0076 mov ax, word ptr es:[bx + 2]
007a les bx, ptr [bp + 0xe]
007d mov word ptr es:[bx], ax
0080 push word ptr [bp + 8]
0083 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 134, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0088 add sp, 2
008b mov ax, 1
008e pop si
008f pop di
0090 leave 
0091 retf 
0092 push word ptr [bp + 8]
0095 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
009a add sp, 2
009d xor ax, ax
009f pop si
00a0 pop di
00a1 leave 
00a2 retf 
```

## Known declaration examples

- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ch_RemoveEntry', 'offset': 36944, 'source': None, 'size': 114}
- {'symbol': '_ch_PurgeCache', 'offset': 37058, 'source': None, 'size': 128}
- {'symbol': '_ch_LookUpId', 'offset': 37350, 'source': None, 'size': 649}
- {'symbol': '_ch_AddEntry', 'offset': 38000, 'source': None, 'size': 706}
