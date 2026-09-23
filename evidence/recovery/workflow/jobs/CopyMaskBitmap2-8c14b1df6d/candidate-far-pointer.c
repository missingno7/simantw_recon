/* Copy a clipped packed 4-bit bitmap through its D-transparent mask. */
struct MaskCopyState {
    int sourceX;
    int copyWidth;
    int sourceY;
    int copyHeight;
    int destinationStride;
    int sourceStride;
    unsigned char far *destinationRow;
    unsigned char far *sourceRow;
};
static struct MaskCopyState maskCopy = {0};

void far CopyMaskBitmap2(unsigned char far *destination,
                         unsigned char far *source,
                         int destinationHeight, int destinationWidth,
                         int sourceHeight, int sourceWidth,
                         int x, int y)
{
    int row;
    int column;
    unsigned char sourceByte;
    unsigned char highPixel;
    unsigned char lowPixel;

    if (x < 0) {
        maskCopy.sourceX = -x;
        maskCopy.copyWidth = sourceWidth;
    } else if (x >= destinationWidth) {
        goto done;
    } else {
        maskCopy.sourceX = 0;
        maskCopy.copyWidth = sourceWidth;
        if (x + sourceWidth > destinationWidth)
            maskCopy.copyWidth = destinationWidth - x;
    }

    if (y < 0) {
        maskCopy.sourceY = -y;
        maskCopy.copyHeight = sourceHeight;
    } else if (y >= destinationHeight) {
        goto done;
    } else {
        maskCopy.sourceY = 0;
        maskCopy.copyHeight = sourceHeight;
        if (y + sourceHeight > destinationHeight)
            maskCopy.copyHeight = destinationHeight - y;
    }

    maskCopy.sourceX >>= 1;
    maskCopy.copyWidth >>= 1;
    maskCopy.destinationStride = ((destinationWidth * 4 + 31) >> 5) << 2;
    maskCopy.sourceStride = ((sourceWidth * 4 + 31) >> 5) << 2;
    maskCopy.sourceRow = (unsigned char far *)source +
                         maskCopy.sourceY * maskCopy.sourceStride;
    maskCopy.destinationRow = (unsigned char far *)destination +
                              (y + maskCopy.sourceY) * maskCopy.destinationStride +
                              x / 2;

    for (row = maskCopy.sourceY; row < maskCopy.copyHeight; ++row) {
        for (column = 0; column < maskCopy.copyWidth; ++column) {
            sourceByte = maskCopy.sourceRow[maskCopy.sourceX + column];
            highPixel = sourceByte >> 4;
            lowPixel = sourceByte & 0x0f;
            if (x & 1) {
                if (highPixel != 0x0d)
                    maskCopy.destinationRow[column] =
                        (maskCopy.destinationRow[column] & 0xf0) | highPixel;
                if (lowPixel != 0x0d)
                    maskCopy.destinationRow[column + 1] =
                        (maskCopy.destinationRow[column + 1] & 0x0f) | (lowPixel << 4);
            } else {
                if (highPixel != 0x0d)
                    maskCopy.destinationRow[column] =
                        (maskCopy.destinationRow[column] & 0x0f) | (highPixel << 4);
                if (lowPixel != 0x0d)
                    maskCopy.destinationRow[column] =
                        (maskCopy.destinationRow[column] & 0xf0) | lowPixel;
            }
        }
        maskCopy.sourceRow += maskCopy.sourceStride;
        maskCopy.destinationRow += maskCopy.destinationStride;
    }

done:
    return;
}
