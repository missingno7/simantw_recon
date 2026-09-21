# Recovery task _KillSomeAnts

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 198 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _CompactListA
000b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 14, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FullCount
0010 xor di, di
0012 mov es, word ptr [0xc0da]
0016 mov si, word ptr es:[0x80f0]
001b dec si
001c jns 0x9d7f
001e jmp 0x9e16
0021 mov bx, si
0023 add bx, 0x2f62
0027 mov es, word ptr [0xc0de]
002b mov word ptr [bp - 4], bx
002e mov word ptr [bp - 2], es
0031 mov cl, byte ptr es:[bx]
0034 sub ch, ch
0036 cmp word ptr [bp + 6], 1
003a jne 0x9dc6
003c test cl, 0x80
003f jne 0x9e10
0041 push 0
0043 mov al, byte ptr es:[si + 0x278e]
0048 sub ah, ah
004a push ax
004b mov al, byte ptr es:[si + 0x23a4]
0050 push ax
0051 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 84, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _DeadAntHere
0056 add sp, 6
0059 les bx, ptr [bp - 4]
005c mov byte ptr es:[bx], 0
0060 inc di
0061 cmp di, 0x32
0064 jle 0x9e10
0066 jmp 0x9e16
0068 test cl, 0x80
006b je 0x9e10
006d mov al, byte ptr es:[si + 0x278e]
0072 sub ah, ah
0074 push ax
0075 mov al, byte ptr es:[si + 0x23a4]
007a push ax
007b push 1
007d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 128, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsItYellow
0082 add sp, 6
0085 or ax, ax
0087 jne 0x9e10
0089 push 1
008b mov es, word ptr [0xc0de]
008f mov al, byte ptr es:[si + 0x278e]
0094 sub ah, ah
0096 push ax
0097 mov al, byte ptr es:[si + 0x23a4]
009c push ax
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 160, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _DeadAntHere
00a2 add sp, 6
00a5 les bx, ptr [bp - 4]
00a8 mov byte ptr es:[bx], 0
00ac inc di
00ad cmp di, 0x32
00b0 jg 0x9e16
00b2 dec si
00b3 js 0x9e16
00b5 jmp 0x9d7f
00b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _CompactListA
00bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 192, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FullCount
00c2 pop si
00c3 pop di
00c4 leave 
00c5 retf 
```

## Known declaration examples

- `extern void far FullCount(void);` — src/recovered/wf_AddSomeAnts-f71da72a1c.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DialogAbortAll', 'offset': 40166, 'source': 'src/recovered/wf_DialogAbortAll-1f3ea4f9f2.c', 'size': 30}
- {'symbol': '_AddSomeAnts', 'offset': 40196, 'source': 'src/recovered/wf_AddSomeAnts-f71da72a1c.c', 'size': 90}
- {'symbol': '_SubtractFood', 'offset': 40484, 'source': None, 'size': 77}
- {'symbol': '_SetEditMode', 'offset': 40562, 'source': 'src/recovered/SetEditMode.c', 'size': 16}
