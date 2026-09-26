/* Convert a one bit, 2x mask into a packed four bit mask. */
void far ConvertMaskBitmap2(unsigned char huge *destination,
                            unsigned char huge *source,
                            int destinationHeight, int destinationWidth,
                            int sourceHeight, int sourceWidth,
                            int x, int y)
{
    int dh = destinationHeight, dw = destinationWidth;
    int sh = sourceHeight, sw = sourceWidth;
    long destinationPitch;
    long sourcePitch;
    int sourceX;
    int sourceY;
    int destinationX;
    int destinationY;
    int width;
    int height;
    int row;
    int column;
    long inputRow;
    long outputRow;
    unsigned int bits;
    unsigned char value;
    unsigned char *out;

    destinationPitch = (((long)dw * 4L + 31L) / 32L) * 4L;
    sourcePitch = ((long)sw + 7L) / 8L;
    sourceX = 0;
    sourceY = 0;
    destinationX = x;
    destinationY = y;
    width = sw / 2;
    height = sh / 2;

    if (destinationX < 0) {
        sourceX = -destinationX * 2;
        width += destinationX;
        destinationX = 0;
    }
    if (destinationY < 0) {
        sourceY = -destinationY * 2;
        height += destinationY;
        destinationY = 0;
    }
    if (destinationX + width > dw)
        width = dw - destinationX;
    if (destinationY + height > dh)
        height = dh - destinationY;
    if (width <= 0 || height <= 0)
        return;

    outputRow = (long)destinationY * destinationPitch;
    inputRow = (long)sourceY * sourcePitch;
    for (row = 0; row < height; ++row) {
        for (column = 0; column < width; ++column) {
            int sx;
            int sy;
            unsigned int shift0;
            unsigned int shift1;
            unsigned int pair;
            unsigned char b2;
            unsigned char b3;
            long p0;
            long p1;
            long p2;
            long p3;
            sx = sourceX + column * 2;
            sy = sourceY + row * 2;
            p0 = inputRow + (long)(sx >> 3);
            p1 = inputRow + sourcePitch + (long)(sx >> 3);
            p2 = p0 + (long)((sx + 1) >> 3);
            p3 = p1 + (long)((sx + 1) >> 3);
            shift0 = 7 - (sx & 7);
            shift1 = 7 - ((sx + 1) & 7);
            pair = (unsigned int)(((source[p0] >> shift0) & 1) << 1) |
                                 (unsigned int)((source[p2] >> shift1) & 1);
            switch (pair) {
            case 0:
                b2 = (unsigned char)((source[p1] >> shift0) & 1);
                b3 = (unsigned char)((source[p3] >> shift1) & 1);
                value = (unsigned char)((b2 << 1) | b3);
                break;
            case 1:
                b2 = (unsigned char)((source[p1] >> shift0) & 1);
                b3 = (unsigned char)((source[p3] >> shift1) & 1);
                value = (unsigned char)(4 | (b2 << 1) | b3);
                break;
            case 2:
                b2 = (unsigned char)((source[p1] >> shift0) & 1);
                b3 = (unsigned char)((source[p3] >> shift1) & 1);
                value = (unsigned char)(8 | (b2 << 1) | b3);
                break;
            default:
                b2 = (unsigned char)((source[p1] >> shift0) & 1);
                b3 = (unsigned char)((source[p3] >> shift1) & 1);
                value = (unsigned char)(12 | (b2 << 1) | b3);
                break;
            }
            out = destination + outputRow + (destinationX + column) / 2;
            if (((destinationX + column) & 1) == 0)
                *out = (unsigned char)((*out & 0x0f) | (value << 4));
            else
                *out = (unsigned char)((*out & 0xf0) | value);
        }
        inputRow += sourcePitch * 2L;
        outputRow += destinationPitch;
    }
}
