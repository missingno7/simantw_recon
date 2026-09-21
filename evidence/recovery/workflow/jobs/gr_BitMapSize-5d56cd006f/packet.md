# Recovery task _gr_BitMapSize

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 185 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 push 1
0008 push 2
000a push word ptr [bp + 0xa]
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0012 add sp, 6
0015 mov word ptr [bp - 6], ax
0018 or ax, ax
001a jne 0x468c
001c les bx, ptr [bp + 6]
001f mov ax, 1
0022 mov word ptr es:[bx + 2], ax
0026 mov word ptr es:[bx], ax
0029 xor ax, ax
002b pop si
002c pop di
002d leave 
002e retf 
002f nop 
0030 push ax
0031 nop 
0032 push cs
0033 call 0x558e ; _mem_Lock
0036 add sp, 2
0039 mov es, dx
003b mov bx, ax
003d mov si, bx
003f mov word ptr [bp - 2], es
0042 cmp word ptr es:[bx], -1
0046 jne 0x46da
0048 mov di, word ptr [bp + 6]
004b push word ptr es:[si + 2]
004f lea ax, [si + 4]
0052 push es
0053 push ax
0054 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UnpackInit
0059 add sp, 6
005c push 0xc
005e lea ax, [bp - 0x12]
0061 push ss
0062 push ax
0063 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 102, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _Unpack
0068 add sp, 6
006b mov ax, word ptr [bp - 0xa]
006e mov es, word ptr [bp + 8]
0071 mov word ptr es:[di], ax
0074 mov ax, word ptr [bp - 8]
0077 mov word ptr es:[di + 2], ax
007b jmp 0x46f6
007d nop 
007e mov bx, word ptr [bp + 6]
0081 mov ax, word ptr es:[si + 8]
0085 mov cx, es
0087 mov es, word ptr [bp + 8]
008a mov word ptr es:[bx], ax
008d mov es, cx
008f mov ax, word ptr es:[si + 0xa]
0093 mov es, word ptr [bp + 8]
0096 mov word ptr es:[bx + 2], ax
009a push word ptr [bp - 6]
009d nop 
009e push cs
009f call 0x559c ; _mem_Unlock
00a2 add sp, 2
00a5 push 2
00a7 push word ptr [bp + 0xa]
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_ReleaseObject
00af add sp, 4
00b2 mov ax, 1
00b5 pop si
00b6 pop di
00b7 leave 
00b8 retf 
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

- {'symbol': '_gr_FastMaskTileNoMask', 'offset': 17930, 'source': None, 'size': 36}
- {'symbol': '_ms_Delay', 'offset': 17966, 'source': None, 'size': 46}
- {'symbol': '_StillDown', 'offset': 18198, 'source': 'src/recovered/wf_StillDown-a90f7d48e5.c', 'size': 161}
- {'symbol': '_WaitedEnough', 'offset': 18360, 'source': 'src/recovered/wf_WaitedEnough-b76919c4b5.c', 'size': 94}
