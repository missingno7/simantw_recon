/* Copy the one-bit source into the destination, toggling only set pixels. */
void far CopyMonoBitmap(unsigned char huge *destination,
                        unsigned char huge *source,
                        int destinationHeight, int destinationWidth,
                        int sourceHeight, int sourceWidth,
                        int x, int y)
{
    int destinationStride;
    int sourceStride;
    int rows;
    int row;
    int sourceRowNumber;
    int sourceColumn;
    int destinationColumn;
    int sourceByte;
    int destinationByte;
    int sourceBit;
    int destinationBit;
    int sourceMask;
    int destinationMask;
    int byteCount;
    unsigned char huge *sourceRow;
    unsigned char huge *destinationRow;

    destinationStride = ((destinationWidth + 31) / 32) * 4;
    sourceStride = (sourceWidth + 7) / 8;
    rows = sourceHeight;
    if (rows > destinationHeight)
        rows = destinationHeight;
    byteCount = destinationStride - (x >> 3);
    if (byteCount > sourceStride)
        byteCount = sourceStride;
    if (byteCount <= 0 || rows <= 0)
        return;

    for (row = 0; row < rows; ++row) {
        sourceRowNumber = sourceHeight - row - 1;
        sourceRow = source + (long)sourceRowNumber * sourceStride;
        destinationRow = destination +
                         (long)(y + row) * destinationStride + (x >> 3);

        for (sourceColumn = 0; sourceColumn < sourceWidth; ++sourceColumn) {
            sourceByte = sourceColumn >> 3;
            sourceBit = sourceColumn & 7;
            sourceMask = 0x80 >> sourceBit;
            if (sourceRow[sourceByte] & sourceMask) {
                destinationColumn = x + sourceColumn;
                destinationByte = destinationColumn >> 3;
                destinationBit = destinationColumn & 7;
                destinationMask = 0x80 >> destinationBit;
                destinationRow[destinationByte] ^=
                    (unsigned char)destinationMask;
            }
        }
    }
}
