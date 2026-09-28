/* Reconstruct a MIDI variable-length value while advancing the caller's cursor. */
void far ExtractVariableLen(unsigned char far * far *cursor,
                             unsigned char far *output,
                             long far *remaining)
{
    unsigned char buf[4];
    int n;
    unsigned char b;
    n = 0;
    *(long far *)output = 0;
    while (**cursor & 0x80) {
        buf[n++] = **cursor & 0x7f;
        --*remaining;
        ++*cursor;
    }
    output[0] = **cursor;
    --*remaining;
    ++*cursor;
    if (--n >= 0) {
        b = buf[n];
        output[0] |= b << 7;
        output[1] = b >> 1;
        if (--n >= 0) {
            b = buf[n];
            output[1] |= b << 6;
            output[2] = b >> 2;
            if (--n >= 0) {
                b = buf[n];
                output[2] |= b << 5;
                output[3] = b >> 3;
            }
        }
    }
}
