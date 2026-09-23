/* Transfer surface rows into a buffer, accounting for the active pixel packing. */
extern unsigned char near displayType;
void far gr_GetFromBuf(int x, int top, unsigned char far *surface,
                       int surfaceWidth, int bottom, unsigned char far *buffer,
                       int width, int rows)
{
    unsigned char far *destination;
    unsigned char far *source;
    int stride;
    unsigned int rowBytes;
    int remaining;
    int col;
    if ((displayType & 1) == 0) {
        stride = ((surfaceWidth * 4 + 31) / 32) * 4;
        rowBytes = (width + 1) / 2 + 3;
        source = surface + (bottom - top - 1) * stride + (x >> 1);
        destination = buffer;
        remaining = rows;
        while (remaining > 0) {
            for (col = 0; col < (rowBytes >> 1); col++)
                ((unsigned int far *)destination)[col] = ((unsigned int far *)source)[col];
            if (rowBytes & 1)
                destination[rowBytes - 1] = source[rowBytes - 1];
            source -= stride;
            destination += rowBytes;
            remaining--;
        }
    } else {
        stride = ((surfaceWidth + 31) / 32) * 4;
        rowBytes = (width + 7) / 8;
        source = surface; source += (bottom - top - 1) * stride; source += x >> 3;
        destination = buffer;
        remaining = rows;
        while (remaining > 0) {
            for (col = 0; col < (rowBytes >> 1); col++)
                ((unsigned int far *)destination)[col] = ((unsigned int far *)source)[col];
            if (rowBytes & 1)
                destination[rowBytes - 1] = source[rowBytes - 1];
            source -= stride;
            destination += rowBytes;
            remaining--;
        }
    }
}

