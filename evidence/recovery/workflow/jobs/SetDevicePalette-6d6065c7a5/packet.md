# Recovery task _SetDevicePalette

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 185 bytes.

```asm
0000 enter 0x48, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 2], 4
000b push word ptr [bp + 6]
000e push 8
0010 push 2
0012 lea ax, [bp - 2]
0015 push ss
0016 push ax
0017 push 0
0019 push 0
001b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 28, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 38}}]
0020 or ax, ax
0022 jne 0x460b
0024 jmp 0x4699
0027 lds si, ptr [bp + 0xc]
002a mov ax, ds
002c or ax, si
002e je 0x4680
0030 mov al, byte ptr [bp + 8]
0033 mov byte ptr [bp - 0x44], al
0036 mov di, word ptr [bp + 0xa]
0039 mov ax, di
003b mov byte ptr [bp - 0x43], al
003e mov word ptr [bp - 2], 0
0043 or di, di
0045 jle 0x466f
0047 mov bx, word ptr [bp - 2]
004a shl bx, 2
004d mov ax, bx
004f add bx, si
0051 mov cl, byte ptr [bx]
0053 mov dl, byte ptr [bx + 2]
0056 sub dh, dh
0058 mov word ptr [bp - 0x46], ax
005b mov word ptr [bp - 0x48], cx
005e mov cx, dx
0060 sub ax, ax
0062 mov al, byte ptr [bx + 1]
0065 mov ah, al
0067 sub al, al
0069 mov bx, ax
006b mov al, byte ptr [bp - 0x48]
006e sub ah, ah
0070 or bx, ax
0072 lea ax, [bp - 0x42]
0075 mov dx, bx
0077 mov bx, word ptr [bp - 0x46]
007a add bx, ax
007c mov word ptr ss:[bx], dx
007f mov word ptr ss:[bx + 2], cx
0083 inc word ptr [bp - 2]
0086 cmp word ptr [bp - 2], di
0089 jl 0x462b
008b push ss
008c pop ds
008d push word ptr [bp + 6]
0090 push 4
0092 push 0x42
0094 lea ax, [bp - 0x44]
0097 push ss
0098 push ax
0099 jmp 0x468d
009b nop 
009c push ss
009d pop ds
009e push word ptr [bp + 6]
00a1 push 4
00a3 push 0
00a5 push 0
00a7 push 0
00a9 push 0
00ab push 0
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 174, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 38}}]
00b2 mov ax, 1
00b5 pop si
00b6 pop di
00b7 leave 
00b8 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PatchColorArrays', 'offset': 16140, 'source': None, 'size': 206}
- {'symbol': 'WINMAIN', 'offset': 16346, 'source': None, 'size': 1546}
- {'symbol': '_SetUpPalette', 'offset': 18078, 'source': None, 'size': 565}
- {'symbol': '_MyPow', 'offset': 18644, 'source': 'src/recovered/MyPow.c', 'size': 105}
