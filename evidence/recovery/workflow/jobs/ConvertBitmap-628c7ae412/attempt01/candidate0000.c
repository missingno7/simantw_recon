/*
 * Convert a four-plane, one-bit-per-pixel bitmap to a bottom-up Windows
 * 4bpp DIB.  The source stores the four plane rows consecutively for each
 * image row.  DIB rows are padded to a four-byte boundary.
 */
void far ConvertBitmap(unsigned char far *destination,
                       unsigned char far *source,
                       int height, int width)
{
    long sourceStride;
    long destinationStride;
    int y;
    int x;

    sourceStride = ((long)width + 7L) / 8L;
    destinationStride = ((((long)width * 4L) + 31L) / 32L) * 4L;

    for (y = 0; y < height; ++y) {
        unsigned char far *sourceRow;
        unsigned char far *destinationRow;
        int sourceByte;
        int pair;
        int plane0;
        int plane1;
        int plane2;
        int plane3;

        sourceRow = source + ((long)(height - y - 1) * sourceStride * 4L);
        destinationRow = destination + ((long)y * destinationStride);

        for (x = 0; x < destinationStride; ++x) {
            int firstShift;
            int secondShift;
            int firstPixel;
            int secondPixel;

            sourceByte = x / 4;
            pair = x % 4;
            firstShift = 7 - (pair * 2);
            secondShift = firstShift - 1;

            plane0 = sourceRow[sourceByte];
            plane1 = sourceRow[sourceStride + sourceByte];
            plane2 = sourceRow[(sourceStride * 2L) + sourceByte];
            plane3 = sourceRow[(sourceStride * 3L) + sourceByte];

            firstPixel = ((plane0 >> firstShift) & 1) |
                         (((plane1 >> firstShift) & 1) << 1) |
                         (((plane2 >> firstShift) & 1) << 2) |
                         (((plane3 >> firstShift) & 1) << 3);
            secondPixel = ((plane0 >> secondShift) & 1) |
                          (((plane1 >> secondShift) & 1) << 1) |
                          (((plane2 >> secondShift) & 1) << 2) |
                          (((plane3 >> secondShift) & 1) << 3);

            destinationRow[x] = (unsigned char)((firstPixel << 4) |
                                                secondPixel);
        }
    }
}
