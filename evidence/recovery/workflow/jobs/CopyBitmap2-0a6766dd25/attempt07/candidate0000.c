/* Copy a clipped 4-bit bitmap rectangle between packed bitmap surfaces. */
extern void far *memcpy(void far *, const void far *, unsigned int);
void far CopyBitmap2(unsigned char far *destination,
                     unsigned char far *source,
                     int destinationHeight, int destinationWidth,
                     int sourceHeight, int sourceWidth,
                     int x, int y)
{
    long destinationStride;
    long sourceStride;
    long destinationOffset;
    long sourceOffset;
    int clipX;
    long clipY;
    int copyWidth;
    int copyHeight;
    int copyBytes;
    int rows;
    int col;

    destinationStride = ((destinationWidth * 4 + 31) / 32) * 4;
    sourceStride = ((sourceWidth * 4 + 31) / 32) * 4;

    clipX = 0;
    clipY = 0;
    if (x < 0)
        clipX = -x;
    if (y < 0)
        clipY = -(long)y;

    copyWidth = sourceWidth - clipX;
    if (x + sourceWidth > destinationWidth)
        copyWidth = destinationWidth - x;
    copyHeight = sourceHeight - clipY;
    if (y + sourceHeight > destinationHeight)
        copyHeight = destinationHeight - y;

    if (copyWidth <= 0 || copyHeight <= 0)
        return;

    copyBytes = ((sourceWidth + 1) / 2) - (clipX / 2);
    destinationOffset = ((long)y + clipY) * destinationStride + (x / 2) + (clipX / 2);
    sourceOffset = ((long)y + clipY) * sourceStride + (x / 2) + (clipX / 2);
    destination += destinationOffset;
    source += sourceOffset;
    rows = copyHeight;
    while (rows > 0) {
        memcpy(destination, source, copyBytes);
        destination += destinationStride;
        source += sourceStride;
        rows--;
    }
}


