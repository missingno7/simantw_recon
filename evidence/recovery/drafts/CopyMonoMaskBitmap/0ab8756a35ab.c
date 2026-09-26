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
    bitOffset = x & 7;

    if (x < 0) {
        sourceX = -x;
        width = copyWidth;
        bitOffset = 0;
    } else {
        sourceX = 0;
        if (x + copyWidth > destinationWidth) {
            width = destinationWidth - x;
        } else {
            width = copyWidth;
        }
    }

    if (y < 0) {
        sourceY = -y;
        height = copyHeight - sourceY;
        y = 0;
    } else {
        sourceY = 0;
        height = copyHeight;
        if (y + height > destinationHeight)
            height = destinationHeight - y;
    }

    if (width <= 0 || height <= 0)
        return;

    for (row = 0; row < height; ++row) {
        int sourceRow = (sourceY + row) * sourceStride;
        int destinationRow = (y + row) * destinationStride;
        int sourceByte = sourceX >> 3;
        int destinationByte = x >> 3;
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
