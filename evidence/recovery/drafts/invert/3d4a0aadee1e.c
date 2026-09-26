/* Invert count bytes in place (inline assembly in the original). */
void invert(unsigned char far *bytes, int count)
{
    _asm {
        mov cx, count
        les di, bytes
    next:
        mov al, es:[di]
        not al
        stosb
        loop next
    }
}
