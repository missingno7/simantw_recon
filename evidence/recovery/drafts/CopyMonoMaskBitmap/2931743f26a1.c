/*
 * Copy a clipped, one-bit source rectangle into the destination.  Transfer
 * source bytes through a two-byte window so an unaligned X origin can feed
 * both destination bytes; edge masks preserve pixels outside the rectangle.
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
    int destinationX = x;
    int destinationY = y;
    int width = copyWidth;
    int height = copyHeight;
    int destinationStride = ((destinationWidth + 31) / 32) * 4;
    int sourceStride = (copyWidth + 7) / 8;
    int bitOffset = x & 7;
    int row;

    if (destinationX < 0) {
        sourceX = -destinationX;
        width -= sourceX;
        destinationX = 0;
        bitOffset = 0;
    } else if (destinationX + width > destinationWidth) {
        width = destinationWidth - destinationX;
    }

    if (destinationY < 0) {
        sourceY = -destinationY;
        height -= sourceY;
        destinationY = 0;
    } else if (destinationY + height > destinationHeight) {
        height = destinationHeight - destinationY;
    }

    if (width <= 0 || height <= 0)
        return;

    for (row = 0; row < height; ++row) {
        int firstSourceByte = sourceX >> 3;
        int firstDestinationByte = destinationX >> 3;
        int byteCount = (width + (destinationX & 7) + 7) >> 3;
        int byteIndex;

        for (byteIndex = 0; byteIndex < byteCount; ++byteIndex) {
            unsigned int window;
            unsigned char incoming;
            unsigned char mask = 0xff;
            int destinationBit = (destinationX & 7) + width - byteIndex * 8;
            unsigned char huge *out;

            window = source[(sourceY + row) * sourceStride + firstSourceByte + byteIndex];
            window |= (unsigned int)source[(sourceY + row) * sourceStride + firstSourceByte + byteIndex + 1] << 8;
            incoming = (unsigned char)(window >> bitOffset);
            if (byteIndex == 0)
                mask &= (unsigned char)(0xff >> (destinationX & 7));
            if (byteIndex == byteCount - 1 && destinationBit < 8)
                mask &= (unsigned char)(0xff << (8 - destinationBit));

            out = destination + (destinationY + row) * destinationStride + firstDestinationByte + byteIndex;
            *out = (unsigned char)((*out & (unsigned char)~mask) | (incoming & mask));
        }
    }
}
