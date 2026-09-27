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
    int destinationX;
    int destinationY;
    long width;
    long height;
    long row;
    int column;
    long inputRow;
    long outputRow;
    long p0;
    long p1;
    long p2;
    long p3;
    int sourceColumn;
    int shiftLeft;
    int shiftRight;
    int topPair;
    int leftValue;
    int rightValue;
    unsigned char first;
    unsigned char second;
    unsigned char third;
    unsigned char fourth;
    unsigned char huge *out;

    destinationPitch = ((destinationWidth * 4 + 31) / 32) * 4;
    sourcePitch = sourceWidth / 8;
    if (sourceWidth % 8 != 0)
        sourcePitch = (sourceWidth + 7) / 8;
    sourceX = 0;
    sourceY = 0;
    destinationX = x;
    destinationY = y;
    width = sourceWidth;
    height = sourceHeight;

    if (destinationX < 0) {
        sourceX = -destinationX;
        width += destinationX;
        destinationX = 0;
    }
    if (destinationY < 0) {
        sourceY = -destinationY;
        height += destinationY;
        destinationY = 0;
    }
    if (destinationX + width > destinationWidth)
        width = destinationWidth - destinationX;
    if (destinationY + height > destinationHeight)
        height = destinationHeight - destinationY;
    if (width <= 0 || height <= 0)
        return;

    outputRow = (long)destinationY * destinationPitch;
    inputRow = (long)sourceY * sourcePitch;
    for (row = 0; row < height / 2; ++row) {
        for (column = 0; column < width / 2; ++column) {
            sourceColumn = sourceX + column * 2;
            shiftLeft = 7 - (sourceColumn & 7);
            shiftRight = 7 - ((sourceColumn + 1) & 7);
            p0 = inputRow + (sourceColumn >> 3);
            p1 = p0 + sourcePitch;
            p2 = p0 + sourcePitch * 2L;
            p3 = p0 + sourcePitch * 3L;
            first = source[p0];
            topPair = ((first >> shiftLeft) & 1) << 1;
            if (((sourceColumn + 1) >> 3) == (sourceColumn >> 3))
                topPair |= (first >> shiftRight) & 1;
            else
                topPair |= (source[p0 + 1] >> shiftRight) & 1;
            out = destination + outputRow + (destinationX >> 1) + column;
            switch (topPair) {
            case 0:
                break;
            case 1:
                second = source[p1];
                third = source[p2];
                fourth = source[p3];
                rightValue = (((first >> shiftRight) & 1) << 3) |
                             (((second >> shiftRight) & 1) << 2) |
                             (((third >> shiftRight) & 1) << 1) |
                              ((fourth >> shiftRight) & 1);
                *out = (unsigned char)((*out & 0xf0) | rightValue);
                break;
            case 2:
                second = source[p1];
                third = source[p2];
                fourth = source[p3];
                leftValue = (((first >> shiftLeft) & 1) << 3) |
                            (((second >> shiftLeft) & 1) << 2) |
                            (((third >> shiftLeft) & 1) << 1) |
                             ((fourth >> shiftLeft) & 1);
                *out = (unsigned char)((*out & 0x0f) | (leftValue << 4));
                break;
            default:
                second = source[p1];
                third = source[p2];
                fourth = source[p3];
                leftValue = (((first >> shiftLeft) & 1) << 3) |
                            (((second >> shiftLeft) & 1) << 2) |
                            (((third >> shiftLeft) & 1) << 1) |
                             ((fourth >> shiftLeft) & 1);
                rightValue = (((first >> shiftRight) & 1) << 3) |
                             (((second >> shiftRight) & 1) << 2) |
                             (((third >> shiftRight) & 1) << 1) |
                              ((fourth >> shiftRight) & 1);
                *out = (unsigned char)((leftValue << 4) | rightValue);
                break;
            }
        }
        inputRow += sourcePitch * 2L;
        outputRow += destinationPitch;
    }
}
