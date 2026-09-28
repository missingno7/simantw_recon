/* Initialize the two cursors after the table copy, before decoding starts. */
struct DeltaTable { char delta[16]; };
unsigned char far * far UncompressDACInstrument(unsigned char far *src,
                                                unsigned char far *dst,
                                                unsigned int length)
{
    unsigned char value;
    int j;
    unsigned int i;
    struct DeltaTable table;

    value = 0x80;
    table = *(struct DeltaTable far *)src;
    src += 16;
    i = 0;
    j = 0;
    length >>= 1;
    while (i < length) {
        value += table.delta[src[i] >> 4];
        dst[j++] = value;
        value += table.delta[src[i] & 0xf];
        dst[j++] = value;
        i++;
    }
    return dst;
}
