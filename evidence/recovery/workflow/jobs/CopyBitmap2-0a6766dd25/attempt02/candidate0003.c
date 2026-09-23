/* Copy a clipped 4-bit bitmap rectangle between packed bitmap surfaces. */
void far CopyBitmap2(unsigned char far *destination,
                     unsigned char far *source,
                     int destinationHeight, int destinationWidth,
                     int sourceHeight, int sourceWidth,
                     int x, int y)
{
    typedef unsigned long RowProduct;
    long destinationStride;
    long sourceStride;
    int clipX;
    int clipY;
    int copyWidth;
    int copyHeight;
    int copyBytes;
    int rows;
    int col;

    destinationStride = ((destinationWidth * 4 + 31) / 32) * 4;
    sourceStride = ((sourceWidth + 7) / 8) * 4;

    clipX = 0;
    clipY = 0;
    if (x < 0)
        clipX = -x;
    if (y < 0)
        clipY = -y;

    copyWidth = sourceWidth - clipX;
    if (x + sourceWidth > destinationWidth)
        copyWidth = destinationWidth - x;
    copyHeight = sourceHeight - clipY;
    if (y + sourceHeight > destinationHeight)
        copyHeight = destinationHeight - y;

    if (copyWidth <= 0 || copyHeight <= 0)
        return;

    copyBytes = ((sourceWidth + 1) / 2) - (clipX / 2);
    destination += (RowProduct)(y + clipY) * (RowProduct)destinationStride + (x / 2) + (clipX / 2);
    source += (RowProduct)(y + clipY) * (RowProduct)sourceStride + (x / 2) + (clipX / 2);
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
