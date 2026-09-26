/*
 * Clip a one-bit bitmap transfer and preserve destination pixels outside its
 * rectangle.  An aligned transfer copies whole bytes; an unaligned transfer
 * shifts a two-byte source window and merges it through first/last byte masks.
 */
void far CopyMonoMaskBitmap(unsigned char huge *destination,
                            unsigned char huge *source,
                            int destinationHeight,
                            int destinationWidth,
                            int copyHeight,
                            int copyWidth,
                            register int x,
                            register int y)
{
    register int xPosition = x;
    register int widthInput = copyWidth;
    int yPosition = y;
    int sourceX;
    int sourceY;
    int width;
    int height;
    int destinationStride;
    int sourceStride;
    int bitOffset;
    int row;

    destinationStride = ((destinationWidth + 31) / 32) * 4;
    sourceStride = (copyWidth + 7) / 8;
    bitOffset = xPosition & 7;

    if (xPosition < 0) {
        sourceX = -xPosition;
        width = widthInput;
        bitOffset = 0;
    } else {
        sourceX = 0;
        if (xPosition + widthInput > destinationWidth) {
            width = destinationWidth - xPosition;
        } else {
            width = widthInput;
        }
    }

    if (yPosition < 0) {
        sourceY = -yPosition;
        height = copyHeight - sourceY;
        yPosition = 0;
    } else {
        sourceY = 0;
        height = copyHeight;
        if (yPosition + height > destinationHeight)
            height = destinationHeight - yPosition;
    }

    if (width <= 0 || height <= 0)
        return;

    for (row = 0; row < height; ++row) {
        int sourceRow = (sourceY + row) * sourceStride;
        int destinationRow = (yPosition + row) * destinationStride;
        int sourceByte = sourceX >> 3;
        int destinationByte = xPosition >> 3;
        int byteCount = (width + 7) / 8;
        int index;

        if (bitOffset == 0) {
            for (index = 0; index < byteCount; ++index) {
                unsigned char mask = 0xff;
                unsigned char incoming = source[sourceRow + sourceByte + index];
                unsigned char huge *out = destination + destinationRow + destinationByte + index;
                if (index == byteCount - 1 && (width & 7) != 0)
                    mask = (unsigned char)(0xff << (8 - (width & 7)));
                *out ^= (unsigned char)((*out ^ incoming) & mask);
            }
        } else {
            int last = byteCount - 1;
            for (index = 0; index <= last; ++index) {
                unsigned int window = source[sourceRow + sourceByte + index];
                unsigned char incoming;
                unsigned char mask = 0xff;
                unsigned char huge *out = destination + destinationRow + destinationByte + index;
                window |= (unsigned int)source[sourceRow + sourceByte + index + 1] << 8;
                incoming = (unsigned char)(window >> bitOffset);
                if (index == 0)
                    mask &= (unsigned char)(0xff >> bitOffset);
                if (index == last && (width & 7) != 0)
                    mask &= (unsigned char)(0xff << (8 - (width & 7)));
                *out ^= (unsigned char)((*out ^ incoming) & mask);
            }
        }
    }
}
