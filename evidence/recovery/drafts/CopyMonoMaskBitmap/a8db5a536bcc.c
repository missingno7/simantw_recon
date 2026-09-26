/*
 * Clip a monochrome bitmap copy to the destination rectangle.  Source and
 * destination pixels are packed least-significant bit first.  The byte
 * updates preserve destination bits outside the clipped copy rectangle.
 */
void far CopyMonoMaskBitmap(unsigned char huge *destination,
                            unsigned char huge *source,
                            int destinationHeight,
                            int destinationWidth,
                            int copyHeight,
                            int copyWidth,
                            int x,
                            int y)
{
    int sourceX = 0;
    int sourceY = 0;
    int row;
    int column;
    int destinationStride = ((destinationWidth + 31) / 32) * 4;
    int sourceStride = (copyWidth + 7) / 8;

    if (x < 0) {
        sourceX = -x;
        copyWidth -= sourceX;
        x = 0;
    }
    if (y < 0) {
        sourceY = -y;
        copyHeight -= sourceY;
        y = 0;
    }
    if (x + copyWidth > destinationWidth)
        copyWidth = destinationWidth - x;
    if (y + copyHeight > destinationHeight)
        copyHeight = destinationHeight - y;

    if (copyWidth <= 0 || copyHeight <= 0)
        return;

    for (row = 0; row < copyHeight; ++row) {
        for (column = 0; column < copyWidth; ++column) {
            int sourceBit = sourceX + column;
            int destinationBit = x + column;
            unsigned char sourceMask = (unsigned char)(1 << (sourceBit & 7));
            unsigned char destinationMask = (unsigned char)(1 << (destinationBit & 7));
            unsigned char huge *sourceByte;
            unsigned char huge *destinationByte;

            sourceByte = source + (sourceY + row) * sourceStride + (sourceBit >> 3);
            destinationByte = destination + (y + row) * destinationStride + (destinationBit >> 3);
            if (*sourceByte & sourceMask)
                *destinationByte |= destinationMask;
            else
                *destinationByte &= (unsigned char)~destinationMask;
        }
    }
}
