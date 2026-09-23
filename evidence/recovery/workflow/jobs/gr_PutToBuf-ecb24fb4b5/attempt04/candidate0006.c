/* Transfer packed buffer rows onto a GR surface using the current display mode. */
extern unsigned char near displayType;
void far gr_PutToBuf(int x, int top, unsigned char far *surface,
                     int surfaceWidth, int bottom, unsigned char far *buffer,
                     int width, int rows)
{
    int stride;
    int rowBytes;
    unsigned char far *destination;
    unsigned char far *source;
    int remaining;
    int col;
    if ((displayType & 1) == 0) {
        stride = ((surfaceWidth * 4 + 31) / 32) * 4;
        rowBytes = (width + 1) / 2 + 3;
        destination = surface + (bottom - top - 1) * stride + (x >> 1);
        source = buffer;
        remaining = rows;
        while (remaining > 0) {
            for (col = 0; col < (rowBytes >> 1); col++)
                ((unsigned int far *)destination)[col] = ((unsigned int far *)source)[col];
            if (rowBytes & 1)
                destination[rowBytes - 1] = source[rowBytes - 1];
            destination -= stride;
            source += rowBytes;
            remaining--;
        }
    } else {
        stride = ((surfaceWidth + 31) / 32) * 4;
        rowBytes = (width + 7) / 8;
        destination = surface + (bottom - top - 1) * stride + (x >> 3);
        source = buffer;
        remaining = rows;
        while (remaining > 0) {
            for (col = 0; col < (rowBytes >> 1); col++)
                ((unsigned int far *)destination)[col] = ((unsigned int far *)source)[col];
            if (rowBytes & 1)
                destination[rowBytes - 1] = source[rowBytes - 1];
            destination -= stride;
            source += rowBytes;
            remaining--;
        }
    }
}
