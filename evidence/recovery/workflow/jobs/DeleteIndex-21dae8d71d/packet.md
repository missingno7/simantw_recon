# Recovery task _DeleteIndex

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 245 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 push word ptr [bp + 0xa]
0009 push word ptr [bp + 8]
000c push word ptr [bp + 6]
000f nop 
0010 push cs
0011 call 0x9d24 ; _FindIndex
0014 add sp, 6
0017 or dx, ax
0019 jne 0xa0a4
001b push ds
001c push 0xb784
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0024 add sp, 4
0027 xor ax, ax
0029 pop si
002a pop di
002b leave 
002c retf 
002d nop 
002e push ds
002f push 0xb794
0032 mov es, word ptr [0xc68c]
0036 imul bx, word ptr [bp + 6], 0x7c
003a mov word ptr [bp - 0xc], bx
003d dec word ptr es:[bx + 0x745c]
0042 mov ax, word ptr es:[bx + 0x745c]
0047 mov word ptr [bp - 0xa], ax
004a shl ax, 3
004d push ax
004e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
0053 add sp, 6
0056 mov word ptr [bp - 4], ax
0059 mov word ptr [bp - 2], dx
005c or dx, ax
005e jne 0xa0e2
0060 push ds
0061 push 0xb79b
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 103, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0069 add sp, 4
006c mov es, word ptr [0xc68c]
0070 mov bx, word ptr [bp - 0xc]
0073 mov ax, word ptr es:[bx + 0x7458]
0078 mov dx, word ptr es:[bx + 0x745a]
007d mov word ptr [bp - 8], ax
0080 mov es, word ptr [0xc68e]
0084 mov cx, word ptr es:[0x9e92]
0089 mov si, cx
008b inc cx
008c shl cx, 3
008f mov bx, si
0091 push ds
0092 mov si, ax
0094 mov ds, dx
0096 les di, ptr [bp - 4]
0099 shr cx, 1
009b rep movsw word ptr es:[di], word ptr [si]
009d adc cx, cx
009f rep movsb byte ptr es:[di], byte ptr [si]
00a1 pop ds
00a2 mov ax, bx
00a4 shl bx, 3
00a7 mov cx, bx
00a9 add bx, word ptr [bp - 8]
00ac lea si, [bx + 0x10]
00af mov bx, word ptr [bp - 4]
00b2 mov di, cx
00b4 mov cx, word ptr [bp - 0xa]
00b7 sub cx, ax
00b9 dec cx
00ba shl cx, 3
00bd push es
00be push ds
00bf lea di, [bx + di + 8]
00c2 mov ds, dx
00c4 shr cx, 1
00c6 rep movsw word ptr es:[di], word ptr [si]
00c8 adc cx, cx
00ca rep movsb byte ptr es:[di], byte ptr [si]
00cc pop ds
00cd pop es
00ce push dx
00cf push word ptr [bp - 8]
00d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
00d7 add sp, 4
00da mov ax, word ptr [bp - 4]
00dd mov dx, word ptr [bp - 2]
00e0 mov es, word ptr [0xc68c]
00e4 mov bx, word ptr [bp - 0xc]
00e7 mov word ptr es:[bx + 0x7458], ax
00ec mov word ptr es:[bx + 0x745a], dx
00f1 pop si
00f2 pop di
00f3 leave 
00f4 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DeleteCurrentIndex', 'offset': 40466, 'source': None, 'size': 259}
- {'symbol': '_AddIndex', 'offset': 40726, 'source': None, 'size': 351}
- {'symbol': '_PackWriteByte', 'offset': 41473, 'source': None, 'size': 64}
- {'symbol': '_PackReadByte', 'offset': 41578, 'source': None, 'size': 81}
