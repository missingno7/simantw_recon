/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
void invert(register unsigned char far *buffer, register unsigned int count)
{
    for (; count; --count) {
        *buffer = (unsigned char)~*buffer;
        buffer++;
    }
}
