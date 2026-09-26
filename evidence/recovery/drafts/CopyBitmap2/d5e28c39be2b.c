/* Copy a clipped 4-bit rectangle between two packed bitmap surfaces. */
extern void far *_fmemcpy(void far *dst, const void far *src, unsigned int count);

void far CopyBitmap2(unsigned char far *destination, unsigned char far *source,
                     int destinationHeight, int destinationWidth,
                     int sourceHeight, int sourceWidth, int x, int y)
{
    long destinationStride;
    long sourceStride;
    long destinationOffset;
    long sourceOffset;
    long clipY;
    int clipX;
    int copyWidth;
    int copyHeight;
    int copyBytes;
    int rows;

    destinationStride = ((destinationWidth * 4 + 31) / 32) * 4;
    sourceStride = ((sourceWidth * 4 + 31) / 32) * 4;
    if (sourceWidth % 2 == 0)
        copyBytes = (sourceWidth + 1) / 2;
    else
        copyBytes = (sourceWidth - 1) / 2 + 1;

    clipX = 0;
    clipY = 0L;
    if (x < 0)
        clipX = -x;
    if (y < 0)
        clipY = -(long)y;

    copyWidth = sourceWidth - clipX;
    if (x + sourceWidth > destinationWidth)
        copyWidth = destinationWidth - x;
    copyHeight = sourceHeight - (int)clipY;
    if (y + sourceHeight > destinationHeight)
        copyHeight = destinationHeight - y;
    if (copyWidth <= 0 || copyHeight <= 0)
        return;

    copyBytes -= clipX / 2;
    destinationOffset = ((long)y + clipY) * destinationStride + ((x + clipX) / 2);
    sourceOffset = clipY * sourceStride + (clipX / 2);
    destination = (unsigned char far *)((unsigned char huge *)destination + destinationOffset);
    source = (unsigned char far *)((unsigned char huge *)source + sourceOffset);
    rows = copyHeight;
    while (rows > 0) {
        _fmemcpy(destination, source, (unsigned int)copyBytes);
        destination += destinationStride;
        source += sourceStride;
        rows--;
    }
}
