# Recovery task _ConvertMonoToTandy

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 119 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 push di
0005 push ds
0006 les di, ptr [bp + 6]
0009 lds si, ptr [bp + 0xa]
000c mov dx, word ptr [bp + 0xe]
000f inc dx
0010 shr dx, 1
0012 mov cx, dx
0014 mov ah, byte ptr [si]
0016 inc si
0017 mov bh, ah
0019 xor bl, bl
001b rol bx, 1
001d rol bx, 1
001f mov ah, bh
0021 xor bh, bh
0023 mov al, byte ptr cs:[bx - 0x835]
0028 stosb byte ptr es:[di], al
0029 dec cx
002a je 0xf83c
002c mov bh, ah
002e xor bl, bl
0030 rol bx, 1
0032 rol bx, 1
0034 mov ah, bh
0036 xor bh, bh
0038 mov al, byte ptr cs:[bx - 0x835]
003d stosb byte ptr es:[di], al
003e dec cx
003f je 0xf83c
0041 mov bh, ah
0043 xor bl, bl
0045 rol bx, 1
0047 rol bx, 1
0049 mov ah, bh
004b xor bh, bh
004d mov al, byte ptr cs:[bx - 0x835]
0052 stosb byte ptr es:[di], al
0053 dec cx
0054 je 0xf83c
0056 mov bh, ah
0058 xor bl, bl
005a rol bx, 1
005c rol bx, 1
005e mov ah, bh
0060 xor bh, bh
0062 mov al, byte ptr cs:[bx - 0x835]
0067 stosb byte ptr es:[di], al
0068 dec cx
0069 je 0xf83c
006b jmp 0xf7e3
006d dec word ptr [bp + 0x10]
0070 jne 0xf7e1
0072 pop ds
0073 pop di
0074 pop si
0075 pop bp
0076 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_IsCursorInObj', 'offset': 63298, 'source': 'src/recovered/win_IsCursorInObj.c', 'size': 50}
- {'symbol': '_MemRChr', 'offset': 63348, 'source': None, 'size': 33}
- {'symbol': '_invert', 'offset': 63558, 'source': None, 'size': 21}
- {'symbol': '_DoInt3', 'offset': 63579, 'source': None, 'size': None}
