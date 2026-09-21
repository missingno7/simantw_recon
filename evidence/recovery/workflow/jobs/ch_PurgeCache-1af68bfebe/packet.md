# Recovery task _ch_PurgeCache

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 128 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 12, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
000e add sp, 2
0011 mov es, dx
0013 mov bx, ax
0015 mov di, ax
0017 mov ax, word ptr es:[bx]
001a mov si, ax
001c lea cx, [bx + 4]
001f mov word ptr [bp - 4], cx
0022 mov word ptr [bp - 2], es
0025 or ax, ax
0027 jle 0x9128
0029 lea ax, [si + 1]
002c shl ax, 2
002f sub dx, dx
0031 mov bx, es
0033 add ax, di
0035 adc dx, bx
0037 mov cx, ax
0039 mov word ptr [bp - 6], dx
003c mov word ptr [bp - 0xa], si
003f mov si, word ptr [bp - 4]
0042 mov di, cx
0044 mov es, word ptr [bp - 2]
0047 cmp word ptr es:[si], -1
004b je 0x911d
004d mov es, word ptr [bp - 6]
0050 push word ptr es:[di]
0053 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
0058 add sp, 2
005b add si, 4
005e add di, 2
0061 dec word ptr [bp - 0xa]
0064 jne 0x9106
0066 push word ptr [bp + 6]
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
006e add sp, 2
0071 push word ptr [bp + 6]
0074 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 119, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
0079 add sp, 2
007c pop si
007d pop di
007e leave 
007f retf 
```

## Known declaration examples

- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ch_CreateTable', 'offset': 36678, 'source': None, 'size': 265}
- {'symbol': '_ch_RemoveEntry', 'offset': 36944, 'source': None, 'size': 114}
- {'symbol': '_ch_LookUpHandle', 'offset': 37186, 'source': None, 'size': 163}
- {'symbol': '_ch_LookUpId', 'offset': 37350, 'source': None, 'size': 649}
