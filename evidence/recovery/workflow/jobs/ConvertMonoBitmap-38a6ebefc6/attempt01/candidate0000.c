/*
 * ConvertMonoBitmap: copy a packed monochrome bitmap into a bottom-up
 * device-independent bitmap.  The destination row stride is the width in
 * bits rounded up to 32 and expressed in bytes (((width + 31) / 32) * 4)
 * and the source stride is (width + 7) / 8 bytes; for each of the height
 * rows, starting with the last destination row (dst + (height - 1) *
 * dstStride) and the first source row, one source row is copied with the
 * inline memcpy expansion (shr cx,1; rep movsw; adc cx,cx; rep movsb) with
 * DS selecting the source segment, then the source advances a row and the
 * destination steps back a row.
 */
extern void far * far _fmemcpy(void far *dst, const void far *src, unsigned int n);

void far ConvertMonoBitmap(unsigned char far *dst, unsigned char far *src,
                           int height, int width)
{
    unsigned char far *srcRow;
    unsigned char far *dstRow;
    int rows;
    int srcStride;
    int dstStride;

    dstStride = ((width + 31) / 32) * 4;
    srcStride = (width + 7) / 8;
    if (height > 0) {
        srcRow = src;
        dstRow = dst + (height - 1) * dstStride;
        rows = height;
        do {
            _fmemcpy(dstRow, srcRow, srcStride);
            srcRow += srcStride;
            dstRow -= dstStride;
        } while (--rows);
    }
}
