; Construction-only wait helper for a persistent historical compiler host.
; CONTROL.BIN is precreated: ASCII 0 idle, 1 run, 2 stop.
bits 16
org 100h
again:
push cs
pop ds
mov ax,3d00h
mov dx,control
int 21h
jc idle
mov bx,ax
mov ah,3fh
mov cx,1
mov dx,value
int 21h
mov ah,3eh
int 21h
cmp byte [value],'2'
je stop
cmp byte [value],'1'
je run
idle:
jmp again
run:
mov ax,3d01h
mov dx,control
int 21h
jc failed
mov bx,ax
mov ah,40h
mov cx,1
mov dx,zero
int 21h
mov ah,3eh
int 21h
mov ax,4c01h
int 21h
stop:
mov ax,4c02h
int 21h
failed:
mov ax,4cffh
int 21h
control: db 'CONTROL.BIN',0
value: db '0'
zero: db '0'
