/*
 * DrawChar: OR-blit an unaligned bitmap of `width` x `height` bits from a
 * source bit position (srcx) into a destination bit position (dstx),
 * merging two source bytes per column to shift across the byte boundary,
 * masking the final partial column, then advancing by the global row
 * pitches for the next row.
 */
extern int source_bitmap_width;
extern int dest_bitmap_width;

static unsigned char near byteMask[8] = {
    0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01
};

void far DrawChar(unsigned char far *src, unsigned char far *dst, int width, int height, int srcx, int dstx)
{
    unsigned char far *s;
    unsigned char far *d;
    int xshift;
    int yshift;
    int n;
    int cnt;
    unsigned val;

    xshift = srcx & 7;
    s = src + (srcx >> 3);
    yshift = dstx & 7;
    d = dst + (dstx >> 3);
    n = (unsigned)width >> 3;

    while (height--) {
        cnt = n;
        if (cnt) {
            do {
                val = *(unsigned int far *)s;
                val = (val << 8) | (val >> 8);
                val <<= xshift;
                val &= 0xff00;
                val >>= yshift;
                val = (val << 8) | (val >> 8);
                *(unsigned int far *)d |= val;
                d = (unsigned char far *)d + 1;
                s = (unsigned char far *)s + 1;
            } while (--cnt);
        }
        if (width & 7) {
            val = *(unsigned int far *)s;
            val = (val << 8) | (val >> 8);
            val <<= xshift;
            val &= 0xff00;
            val &= (unsigned)byteMask[width & 7] << 8;
            val >>= yshift;
            val = (val << 8) | (val >> 8);
            *(unsigned int far *)d |= val;
        }
        s += source_bitmap_width;
        d += dest_bitmap_width;
    }
}
