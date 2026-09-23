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
    int y;
    int x;

    colorStride = (long)((((width * 4) + 31) / 32) * 4);
    if ((width % 8) == 0)
        sourceStride = (long)(width / 8);
    else
        sourceStride = (long)(((width + ((width < 0) ? 7 : 0)) >> 3) + 1);

    for (y = 0; y < height; ++y) {
        unsigned char huge *sourceRow;
        unsigned char huge *maskRow;
        unsigned char huge *colorRow;
        long sourceRowOffset;

        sourceRowOffset = (long)(height - y - 1) * sourceStride * 5L;
        sourceRow = source + sourceRowOffset;
        maskRow = maskBits + ((long)(height - y - 1) * sourceStride);
        colorRow = colorBits + ((long)y * colorStride);

        for (x = 0; x < sourceStride; ++x)
            maskRow[x] = sourceRow[x];

        for (x = 0; x < colorStride; ++x) {
            long sourceByte;
            int pair;
            int firstShift;
            int secondShift;
            unsigned char plane1;
            unsigned char plane2;
            unsigned char plane3;
            unsigned char plane4;
            unsigned char firstPixel;
            unsigned char secondPixel;

            sourceByte = x / 4;
            pair = x % 4;
            firstShift = 7 - (pair * 2);
            secondShift = firstShift - 1;

            plane1 = sourceRow[sourceStride + sourceByte];
            plane2 = sourceRow[(sourceStride * 2L) + sourceByte];
            plane3 = sourceRow[(sourceStride * 3L) + sourceByte];
            plane4 = sourceRow[(sourceStride * 4L) + sourceByte];

            firstPixel = (unsigned char)(((plane1 >> firstShift) & 1) |
                                         (((plane2 >> firstShift) & 1) << 1) |
                                         (((plane3 >> firstShift) & 1) << 2) |
                                         (((plane4 >> firstShift) & 1) << 3));
            secondPixel = (unsigned char)(((plane1 >> secondShift) & 1) |
                                          (((plane2 >> secondShift) & 1) << 1) |
                                          (((plane3 >> secondShift) & 1) << 2) |
                                          (((plane4 >> secondShift) & 1) << 3));

            colorRow[x] = (unsigned char)((firstPixel << 4) | secondPixel);
        }
    }
}
