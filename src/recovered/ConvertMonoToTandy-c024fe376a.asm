; Convert monochrome pixels four at a time through the existing CS-relative Tandy lookup table.
.8086
SIMTWO_MODULE SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE
PUBLIC _ConvertMonoToTandy
_ConvertMonoToTandy PROC FAR
    push bp
    mov bp, sp
    push si
    push di
    push ds
    les di, [bp+6]
    lds si, [bp+0Ah]
    mov dx, [bp+0Eh]
    inc dx
    shr dx, 1
convert_width_setup:
    mov cx, dx
convert_width_loop:
    mov ah, [si]
    inc si
    mov bh, ah
    xor bl, bl
    rol bx, 1
    rol bx, 1
    mov ah, bh
    xor bh, bh
    mov al, BYTE PTR CS:[bx-0835h]
    stosb
    dec cx
    je convert_finish_row
convert_pixel_2:
    mov bh, ah
    xor bl, bl
    rol bx, 1
    rol bx, 1
    mov ah, bh
    xor bh, bh
    mov al, BYTE PTR CS:[bx-0835h]
    stosb
    dec cx
    je convert_finish_row
convert_pixel_3:
    mov bh, ah
    xor bl, bl
    rol bx, 1
    rol bx, 1
    mov ah, bh
    xor bh, bh
    mov al, BYTE PTR CS:[bx-0835h]
    stosb
    dec cx
    je convert_finish_row
convert_pixel_4:
    mov bh, ah
    xor bl, bl
    rol bx, 1
    rol bx, 1
    mov ah, bh
    xor bh, bh
    mov al, BYTE PTR CS:[bx-0835h]
    stosb
    dec cx
    je convert_finish_row
    jmp SHORT convert_width_loop
convert_finish_row:
    dec WORD PTR [bp+10h]
    jne convert_width_setup
    pop ds
    pop di
    pop si
    pop bp
    retf
_ConvertMonoToTandy ENDP
SIMTWO_MODULE ENDS
END
