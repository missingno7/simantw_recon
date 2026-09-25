/* Convert a clipped four-plane bitmap to packed 4bpp output.  Source rows
   are stored bottom-up; each destination byte contains two adjacent pixels. */
void far ConvertBitmap2(unsigned char huge *destination,
                        unsigned char huge *source,
                        int destinationHeight, register int destinationWidth,
                        int sourceHeight, register int sourceWidth,
                        int x, int y)
{
    long destinationStride;
    long sourceStride;
    register int outputWidth = destinationWidth;
    register int inputWidth = sourceWidth;
    int clipX;
    int clipY;
    int copyWidth;
    int copyHeight;
    int row;
    int byteIndex;

    destinationStride = (long)(((outputWidth * 4 + 31) / 32) * 4);
    if ((inputWidth % 8) == 0)
        sourceStride = inputWidth / 8;
    else
        sourceStride = (inputWidth + ((inputWidth < 0) ? 7 : 0)) / 8 + 1;

    clipX = 0;
    clipY = 0;
    if (x < 0)
        clipX = -x;
    if (y < 0)
        clipY = -y;

    copyWidth = inputWidth;
    if (x + inputWidth > outputWidth)
        copyWidth = outputWidth - x;
    copyHeight = sourceHeight;
    if (y + sourceHeight > destinationHeight)
        copyHeight = destinationHeight - y;

    if (copyWidth <= 0 || copyHeight <= 0 ||
        clipX >= copyWidth || clipY >= copyHeight)
        return;

    for (row = 0; row < copyHeight; ++row) {
        int sourceY;
        int destinationY;

        sourceY = sourceHeight - clipY - row - 1;
        destinationY = y + clipY + row;
        for (byteIndex = 0; byteIndex < ((copyWidth + 1) / 2); ++byteIndex) {
            int sourceX;
            int firstShift;
            int secondShift;
            unsigned char plane0;
            unsigned char plane1;
            unsigned char plane2;
            unsigned char plane3;
            unsigned char firstPixel;
            unsigned char secondPixel;

            sourceX = clipX + byteIndex * 2;
            firstShift = 7 - ((sourceX & 7) + (x & 1)) % 8;
            secondShift = firstShift - 1;

            plane3 = source[(long)sourceY * sourceStride * 4L +
                            sourceStride * 3L + sourceX / 8];
            plane0 = source[(long)sourceY * sourceStride * 4L + sourceX / 8];
            plane1 = source[(long)sourceY * sourceStride * 4L +
                            sourceStride + sourceX / 8];
            plane2 = source[(long)sourceY * sourceStride * 4L +
                            sourceStride * 2L + sourceX / 8];

            firstPixel = (unsigned char)((plane3 >> firstShift) & 1);
            firstPixel = (unsigned char)((firstPixel << 1) |
                                         ((plane2 >> firstShift) & 1));
            firstPixel = (unsigned char)((firstPixel << 1) |
                                         ((plane1 >> firstShift) & 1));
            firstPixel = (unsigned char)((firstPixel << 1) |
                                         ((plane0 >> firstShift) & 1));
            secondPixel = (unsigned char)((plane3 >> secondShift) & 1);
            secondPixel = (unsigned char)((secondPixel << 1) |
                                          ((plane2 >> secondShift) & 1));
            secondPixel = (unsigned char)((secondPixel << 1) |
                                          ((plane1 >> secondShift) & 1));
            secondPixel = (unsigned char)((secondPixel << 1) |
                                          ((plane0 >> secondShift) & 1));

            destination[(long)destinationY * destinationStride +
                        (x + clipX) / 2 + byteIndex] =
                (unsigned char)((firstPixel << 4) | secondPixel);
        }
    }
}
