/* Copy each packed source row into its aligned destination row. */
extern void far *_fmemcpy(void far *destination, const void far *source,
                          unsigned int count);

void far CopyMonoBitmap(unsigned char far *destination,
                        unsigned char far *source,
                        int destinationHeight, int destinationWidth,
                        int sourceHeight, int sourceWidth,
                        int x, int y)
{
    unsigned int destinationStride;
    unsigned int sourceStride;
    int rows;
    int row;
    unsigned char far *destinationRow;
    unsigned char far *sourceRow;

    destinationStride = ((destinationWidth + 31) / 32) * 4;
    sourceStride = (sourceWidth + 7) / 8;
    rows = sourceHeight;
    if (rows > destinationHeight)
        rows = destinationHeight;
    destinationRow = destination + y * destinationStride + (x >> 3);
    sourceRow = source;
    for (row = 0; row < rows; ++row) {
        _fmemcpy(destinationRow, sourceRow, sourceStride);
        destinationRow += destinationStride;
        sourceRow += sourceStride;
    }
}
