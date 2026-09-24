/*
 * Copy the source bitmap's leading 1bpp plane to the mask buffer, then
 * convert the four color planes to padded 4bpp DIB bytes.  Each source
 * image row contains five consecutive 1bpp rows: mask followed by color
 * planes.  The source row order is reversed for the DIB output.
 */
void far ConvertMaskBitmap(unsigned char huge *colorBits,
                           unsigned char huge *maskBits,
                           unsigned char huge *source,
                           int height, int width)
{
    long sourceStride;
    long colorStride;
    register int y;
    register int x;

    colorStride = (long)((((width * 4) + 31) / 32) * 4);
    if ((width % 8) == 0)
        sourceStride = (long)(width / 8);
    else
        sourceStride = (long)(width / 8 + 1);

    for (y = 0; y < height; ++y) {
        long sourceRowOffset;
        long sourcePlaneRowOffset;
        long colorRowOffset;

        sourceRowOffset = (long)(height - y - 1) * sourceStride;
        sourcePlaneRowOffset = sourceRowOffset * 5L;
        colorRowOffset = (long)y * colorStride;

        for (x = 0; x < sourceStride; ++x)
            maskBits[sourceRowOffset + x] = source[sourcePlaneRowOffset + x];

        for (x = 0; x < colorStride; ++x) {
            int sourceByte;
            int pair;
            int firstShift;
            int secondShift;
            unsigned char plane1;
            unsigned char plane2;
            unsigned char plane3;
            unsigned char plane4;
            unsigned char outputByte;

            sourceByte = x / 4;
            pair = x % 4;
            firstShift = 7 - (pair * 2);
            secondShift = firstShift - 1;

            plane1 = source[sourcePlaneRowOffset + sourceStride + sourceByte];
            plane2 = source[sourcePlaneRowOffset + (sourceStride * 2L) + sourceByte];
            plane4 = source[sourcePlaneRowOffset + (sourceStride * 4L) + sourceByte];
            plane3 = source[sourcePlaneRowOffset + (sourceStride * 3L) + sourceByte];

            outputByte = (unsigned char)((plane3 >> firstShift) & 1);
            outputByte = (unsigned char)((outputByte << 1) |
                                         ((plane4 >> firstShift) & 1));
            outputByte = (unsigned char)((outputByte << 1) |
                                         ((plane2 >> firstShift) & 1));
            outputByte = (unsigned char)((outputByte << 1) |
                                         ((plane1 >> firstShift) & 1));
            outputByte = (unsigned char)((outputByte << 1) |
                                         ((plane3 >> secondShift) & 1));
            outputByte = (unsigned char)((outputByte << 1) |
                                         ((plane4 >> secondShift) & 1));
            outputByte = (unsigned char)((outputByte << 1) |
                                         ((plane2 >> secondShift) & 1));
            outputByte = (unsigned char)((outputByte << 1) |
                                         ((plane1 >> secondShift) & 1));

            colorBits[colorRowOffset + x] = outputByte;
        }
    }
}
