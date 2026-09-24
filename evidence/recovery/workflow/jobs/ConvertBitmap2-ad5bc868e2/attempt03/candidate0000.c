/* Convert a clipped, bottom-up four-plane bitmap to packed 4bpp output.
   The target rounds destination rows to DWORDs and packs two pixels per byte. */
void far ConvertBitmap2(unsigned char huge *destination,
                        unsigned char huge *source,
                        int destinationHeight, int destinationWidth,
                        int sourceHeight, int sourceWidth,
                        int x, int y)
{
    long destinationStride;
    long sourceStride;
    long sourceRowOffset;
    long destinationRowOffset;
    int clipX;
    int clipY;
    int copyWidth;
    int copyHeight;
    int row;
    int byteIndex;

    destinationStride = ((destinationWidth * 4 + 31) / 32) * 4;
    if ((sourceWidth % 8) == 0)
        sourceStride = sourceWidth / 8;
    else
        sourceStride = (sourceWidth + ((sourceWidth < 0) ? 7 : 0)) / 8 + 1;

    clipX = 0;
    clipY = 0;
    if (x < 0)
        clipX = -x;
    if (y < 0)
        clipY = -y;

    copyWidth = sourceWidth;
    if (x + sourceWidth > destinationWidth)
        copyWidth = destinationWidth - x;
    copyHeight = sourceHeight;
    if (y + sourceHeight > destinationHeight)
        copyHeight = destinationHeight - y;
    if (copyWidth <= 0 || copyHeight <= 0 ||
        clipX >= copyWidth || clipY >= copyHeight)
        return;

    sourceRowOffset = (long)(sourceHeight - clipY - 1) * sourceStride * 4L;
    destinationRowOffset = (long)(y + clipY) * destinationStride +
                           (x + clipX) / 2;
    for (row = clipY; row < copyHeight; ++row) {
        for (byteIndex = clipX / 2; byteIndex < copyWidth / 2; ++byteIndex) {
            int sourceX;
            int sourceByte;
            int firstShift;
            int secondShift;
            unsigned char plane0;
            unsigned char plane1;
            unsigned char plane2;
            unsigned char plane3;
            unsigned char firstPixel;
            unsigned char secondPixel;

            sourceX = byteIndex * 2;
            sourceByte = sourceX / 8;
            firstShift = 7 - (sourceX & 7);
            secondShift = firstShift - 1;
            plane3 = source[sourceRowOffset + sourceStride * 3 + sourceByte];
            plane0 = source[sourceRowOffset + sourceByte];
            plane1 = source[sourceRowOffset + sourceStride + sourceByte];
            plane2 = source[sourceRowOffset + sourceStride * 2 + sourceByte];

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

            destination[destinationRowOffset + byteIndex] =
                (unsigned char)((firstPixel << 4) | secondPixel);
        }
        sourceRowOffset -= sourceStride * 4L;
        destinationRowOffset += destinationStride;
    }
}
