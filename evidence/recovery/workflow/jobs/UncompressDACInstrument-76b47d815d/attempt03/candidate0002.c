/*
 * UncompressDACInstrument: expand a 4-bit delta-coded DAC sample.  The
 * first sixteen source bytes are a delta table, copied into a local
 * structure (inline rep movsw with DS switched, as in the admitted struct
 * copies), after which the source advances past them.  The byte count is
 * halved in place and compared unsigned; a running byte value starting at
 * 0x80 is advanced by the table entry selected by the high nibble and
 * then the low nibble of each packed byte, and each intermediate value is
 * stored to the destination.  The destination pointer is returned.  The
 * output index and loop counter have frame homes zeroed at entry while
 * living in SI and DI.
 */
struct DeltaTable {
    char delta[16];
};

unsigned char far * far UncompressDACInstrument(unsigned char far *src,
                                                unsigned char far *dst,
                                                unsigned int length)
{
    unsigned char value;
    unsigned int i;
    struct DeltaTable table;

    value = 0x80;
    table = *(struct DeltaTable far *)src;
    src += 16;
    length >>= 1;
    i = 0;
    while (i < length) {
        value += table.delta[src[i] >> 4];
        dst[2 * i] = value;
        value += table.delta[src[i] & 0xf];
        dst[2 * i + 1] = value;
        i++;
    }
    return dst;
}

