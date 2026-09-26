/*
 * ExtractVariableLen: read a MIDI-style variable-length quantity from
 * **cursor (up to 4 bytes, continuation bit 0x80), decrementing
 * *remaining once per byte consumed and advancing *cursor past each byte
 * read.  Up to 3 leading 7-bit continuation groups (masked, collected
 * oldest-first into a local buffer) plus the trailing terminating byte
 * (continuation clear, taken verbatim since its top bit is already 0)
 * are packed little-endian, terminating byte first, into the 4-byte
 * output buffer as a continuous bitstream: the terminating byte fills
 * out[0] bits 0-6, and each earlier group -- most-recently-read
 * first -- contributes its low bits to finish the current output byte
 * (via OR) and its high bits to start the next (a plain store).  output
 * is zeroed first.
 */
void far ExtractVariableLen(unsigned char far * far *cursor,
                             unsigned char far *output,
                             long far *remaining)
{
    unsigned char buf[4];
    int n;
    unsigned char far *p;
    unsigned char far *out;
    unsigned char b;

    n = 0;
    *(long far *)out = 0;
    p = *cursor;
    out = output;
    while (*p & 0x80) {
        buf[n++] = *p & 0x7f;
        --*remaining;
        ++p;
        *cursor = p;
    }
    out[0] = *p;
    --*remaining;
    ++p;
    *cursor = p;

    if (--n >= 0) {
        b = buf[n];
        out[0] |= b << 7;
        out[1] = b >> 1;
        if (--n >= 0) {
            b = buf[n];
            out[1] |= b << 6;
            out[2] = b >> 2;
            if (--n >= 0) {
                b = buf[n];
                out[2] |= b << 5;
                out[3] = b >> 3;
            }
        }
    }
}
