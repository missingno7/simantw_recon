/*
 * Convert a four-plane, one-bit-per-pixel bitmap to a bottom-up Windows
 * 4bpp DIB.  The source stores the four plane rows consecutively for each
 * image row.  DIB rows are padded to a four-byte boundary.
 */
void far ConvertBitmap(unsigned char huge *destination,
                       unsigned char huge *source,
                       int height, int width)
{
    long destinationStride;
    long sourceStride;
    long y;
    long x;

    destinationStride = (long)((((width * 4) + 31) / 32) * 4);

    if ((width % 8) == 0)
        sourceStride = (long)(width / 8);
    else
        sourceStride = (long)(((width + ((width < 0) ? 7 : 0)) >> 3) + 1);

    for (y = 0; y < height; ++y) {
        unsigned char huge *sourceRow;
        unsigned char huge *destinationRow;
        long sourceByte;
        long pair;
        unsigned char plane0;
        unsigned char plane1;
        unsigned char plane2;
        unsigned char plane3;

        sourceRow = source + ((long)(height - y - 1) * sourceStride * 4L);
        destinationRow = destination + ((long)y * destinationStride);

        for (x = 0; x < destinationStride; ++x) {
            int firstShift;
            int secondShift;
            unsigned char firstPixel;
            unsigned char secondPixel;

            sourceByte = x / 4;
            pair = x % 4;
            firstShift = 6 - (pair * 2) + 1;
            secondShift = 7 - (pair * 2) - 1;

            plane0 = sourceRow[sourceByte];
            plane1 = sourceRow[sourceStride + sourceByte];
            plane2 = sourceRow[(sourceStride * 2L) + sourceByte];
            plane3 = sourceRow[(sourceStride * 3L) + sourceByte];

            firstPixel = (plane0 >> firstShift) & 1;
            firstPixel |= (unsigned char)(((plane1 >> firstShift) & 1) << 1);
            firstPixel |= (unsigned char)(((plane2 >> firstShift) & 1) << 2);
            firstPixel |= (unsigned char)(((plane3 >> firstShift) & 1) << 3);
            secondPixel = (plane0 >> secondShift) & 1;
            secondPixel |= (unsigned char)(((plane1 >> secondShift) & 1) << 1);
            secondPixel |= (unsigned char)(((plane2 >> secondShift) & 1) << 2);
            secondPixel |= (unsigned char)(((plane3 >> secondShift) & 1) << 3);

            destinationRow[x] = (unsigned char)((firstPixel * 16) + secondPixel);
        }
    }
}
