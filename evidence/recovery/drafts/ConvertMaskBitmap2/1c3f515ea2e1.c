void far ConvertMaskBitmap2(unsigned char huge *destination,
                            unsigned char huge *source,
                            int destinationHeight, int destinationWidth,
                            int sourceHeight, int sourceWidth,
                            int x, int y)
{
    long destinationPitch;
    long sourcePitch;
    int sourceX;
    int sourceY;
    int width;
    int height;
    long row;
    long column;
    long columnEnd;
    long maskRow;
    long sourceRow;
    long destinationRow;
    long byteColumn;
    int bit;
    int shift;
    unsigned char mask;
    unsigned char plane0;
    unsigned char plane1;
    unsigned char plane2;
    unsigned char plane3;
    int leftPixel;
    int rightPixel;

    destinationPitch = ((destinationWidth * 4 + 31) / 32) * 4;
    if (sourceWidth % 8 == 0)
        sourcePitch = sourceWidth / 8;
    else
        sourcePitch = sourceWidth / 8 + 1;
    sourceX = 0;
    sourceY = 0;
    width = sourceWidth;
    height = sourceHeight;

    if (x < 0) {
        sourceX = -x;
    } else {
        if (x + width > destinationWidth)
            width = destinationWidth - x;
    }

    if (y < 0) {
        sourceY = -y;
    } else {
        if (y + height > destinationHeight)
            height = destinationHeight - y;
    }

    if ((long)sourceY >= (long)height)
        return;

    column = (long)sourceX / 2L;
    columnEnd = (long)(width / 2);
    if (column >= columnEnd)
        return;

    for (row = (long)sourceY; row < (long)height; ++row) {
        /* Each logical source row is mask plus four one-bit color planes. */
        maskRow = (sourcePitch * ((long)sourceHeight - row - 1L)) * 5L;
        sourceRow = maskRow + sourcePitch;
        destinationRow = destinationPitch * ((long)y + row) + (long)(x >> 1);

        for (column = (long)sourceX / 2L; column < columnEnd; ++column) {
            byteColumn = column / 4L;
            bit = (int)(column % 4L);
            shift = 7 - bit * 2;
            mask = (unsigned char)((source[maskRow + byteColumn] << (bit * 2)) & 0xc0);

            switch (mask) {
            case 0x40:
                plane0 = source[sourceRow + byteColumn];
                plane1 = source[sourceRow + sourcePitch + byteColumn];
                plane2 = source[sourceRow + sourcePitch * 2L + byteColumn];
                plane3 = source[sourceRow + sourcePitch * 3L + byteColumn];
                rightPixel = (((plane0 >> (shift - 1)) & 1) << 3) |
                             (((plane1 >> (shift - 1)) & 1) << 2) |
                             (((plane2 >> (shift - 1)) & 1) << 1) |
                              ((plane3 >> (shift - 1)) & 1);
                destination[destinationRow + column] =
                    (unsigned char)((destination[destinationRow + column] & 0xf0) |
                                    rightPixel);
                break;

            case 0x80:
                plane0 = source[sourceRow + byteColumn];
                plane1 = source[sourceRow + sourcePitch + byteColumn];
                plane2 = source[sourceRow + sourcePitch * 2L + byteColumn];
                plane3 = source[sourceRow + sourcePitch * 3L + byteColumn];
                leftPixel = (((plane0 >> shift) & 1) << 3) |
                            (((plane1 >> shift) & 1) << 2) |
                            (((plane2 >> shift) & 1) << 1) |
                             ((plane3 >> shift) & 1);
                destination[destinationRow + column] =
                    (unsigned char)((destination[destinationRow + column] & 0x0f) |
                                    (leftPixel << 4));
                break;

            case 0xc0:
                plane0 = source[sourceRow + byteColumn];
                plane1 = source[sourceRow + sourcePitch + byteColumn];
                plane2 = source[sourceRow + sourcePitch * 2L + byteColumn];
                plane3 = source[sourceRow + sourcePitch * 3L + byteColumn];
                leftPixel = (((plane0 >> shift) & 1) << 3) |
                            (((plane1 >> shift) & 1) << 2) |
                            (((plane2 >> shift) & 1) << 1) |
                             ((plane3 >> shift) & 1);
                rightPixel = (((plane0 >> (shift - 1)) & 1) << 3) |
                             (((plane1 >> (shift - 1)) & 1) << 2) |
                             (((plane2 >> (shift - 1)) & 1) << 1) |
                              ((plane3 >> (shift - 1)) & 1);
                destination[destinationRow + column] =
                    (unsigned char)((leftPixel << 4) | rightPixel);
                break;
            }
        }
    }
}
