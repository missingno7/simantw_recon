/* Copy a clipped 4-bit rectangle between two packed bitmap surfaces. */
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
    int col;

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
    destinationOffset = ((long)y + clipY) * destinationStride + (x / 2) + (clipX / 2);
    sourceOffset = ((long)y + clipY) * sourceStride + (x / 2) + (clipX / 2);
    { unsigned char huge *hd = (unsigned char huge *)destination;
      unsigned char huge *hs = (unsigned char huge *)source;
      hd += destinationOffset; hs += sourceOffset;
      destination = (unsigned char far *)hd; source = (unsigned char far *)hs; }
    rows = copyHeight;
    while (rows > 0) {
        for (col = 0; col < (copyBytes >> 1); col++)
            ((unsigned int far *)destination)[col] = ((unsigned int far *)source)[col];
        if (copyBytes & 1)
            destination[copyBytes - 1] = source[copyBytes - 1];
        destination += destinationStride;
        source += sourceStride;
        rows--;
    }
}
