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
    int width;
    int height;
    int row;
    int column;
    long inputRow;
    long outputRow;
    int leftX;
    int rightX;
    int outputX;
    int shiftLeft;
    int shiftRight;
    int topPair;
    int sampleLeft;
    int sampleRight;
    unsigned char row0;
    unsigned char row1;
    unsigned char row2;
    unsigned char row3;
    unsigned char *out;

    destinationPitch = ((destinationWidth * 4 + 31) / 32) * 4;
    sourcePitch = (sourceWidth + 7) / 8;
    sourceX = 0;
    sourceY = 0;
    destinationX = x;
    destinationY = y;
    width = sourceWidth;
    height = sourceHeight / 2;

    if (destinationX < 0) {
        sourceX = -destinationX;
        width += destinationX;
        destinationX = 0;
    }
    if (destinationY < 0) {
        sourceY = -destinationY * 2;
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
    for (row = 0; row < height; ++row) {
        for (column = 0; column < (width + 1) / 2; ++column) {
            leftX = sourceX + column * 2;
            rightX = leftX + 1;
            outputX = destinationX + column * 2;
            shiftLeft = 7 - (leftX & 7);
            shiftRight = 7 - (rightX & 7);
            row0 = source[inputRow + (leftX >> 3)];
            topPair = (row0 >> shiftLeft) & 1;
            if (column * 2 + 1 < width) {
                topPair = (topPair << 1) |
                          ((source[inputRow + (rightX >> 3)] >> shiftRight) & 1);
            } else {
                topPair <<= 1;
            }
            switch (topPair) {
            case 0:
                break;
            case 1:
                row1 = source[inputRow + sourcePitch + (leftX >> 3)];
                row2 = source[inputRow + sourcePitch * 2L + (leftX >> 3)];
                row3 = source[inputRow + sourcePitch * 3L + (leftX >> 3)];
                sampleLeft = (((row0 >> shiftLeft) & 1) << 3) |
                             (((row1 >> shiftLeft) & 1) << 2) |
                             (((row2 >> shiftLeft) & 1) << 1) |
                              ((row3 >> shiftLeft) & 1);
                out = destination + outputRow + (outputX >> 1);
                if (outputX & 1)
                    *out = (unsigned char)((*out & 0xf0) | sampleLeft);
                else
                    *out = (unsigned char)((*out & 0x0f) | (sampleLeft << 4));
                break;
            case 2:
                row1 = source[inputRow + sourcePitch + (rightX >> 3)];
                row2 = source[inputRow + sourcePitch * 2L + (rightX >> 3)];
                row3 = source[inputRow + sourcePitch * 3L + (rightX >> 3)];
                sampleRight = (((row0 >> shiftRight) & 1) << 3) |
                              (((row1 >> shiftRight) & 1) << 2) |
                              (((row2 >> shiftRight) & 1) << 1) |
                               ((row3 >> shiftRight) & 1);
                out = destination + outputRow + ((outputX + 1) >> 1);
                if ((outputX + 1) & 1)
                    *out = (unsigned char)((*out & 0xf0) | sampleRight);
                else
                    *out = (unsigned char)((*out & 0x0f) | (sampleRight << 4));
                break;
            default:
                row1 = source[inputRow + sourcePitch + (leftX >> 3)];
                row2 = source[inputRow + sourcePitch * 2L + (leftX >> 3)];
                row3 = source[inputRow + sourcePitch * 3L + (leftX >> 3)];
                sampleLeft = (((row0 >> shiftLeft) & 1) << 3) |
                             (((row1 >> shiftLeft) & 1) << 2) |
                             (((row2 >> shiftLeft) & 1) << 1) |
                              ((row3 >> shiftLeft) & 1);
                row1 = source[inputRow + sourcePitch + (rightX >> 3)];
                row2 = source[inputRow + sourcePitch * 2L + (rightX >> 3)];
                row3 = source[inputRow + sourcePitch * 3L + (rightX >> 3)];
                sampleRight = (((row0 >> shiftRight) & 1) << 3) |
                              (((row1 >> shiftRight) & 1) << 2) |
                              (((row2 >> shiftRight) & 1) << 1) |
                               ((row3 >> shiftRight) & 1);
                if (outputX & 1) {
                    out = destination + outputRow + (outputX >> 1);
                    *out = (unsigned char)((*out & 0xf0) | sampleLeft);
                    out = destination + outputRow + ((outputX + 1) >> 1);
                    *out = (unsigned char)((*out & 0x0f) | (sampleRight << 4));
                } else {
                    out = destination + outputRow + (outputX >> 1);
                    *out = (unsigned char)((sampleLeft << 4) | sampleRight);
                }
                break;
            }
        }
        inputRow += sourcePitch * 2L;
        outputRow += destinationPitch;
    }
}
