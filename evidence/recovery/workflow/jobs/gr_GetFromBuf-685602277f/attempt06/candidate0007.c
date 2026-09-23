/* Transfer surface rows into a buffer, accounting for the active pixel packing. */
extern unsigned char near displayType;
extern void far * far memcpy(void far *, void far *, unsigned int);
void far gr_GetFromBuf(int x, int top, unsigned char far *surface,
                       int surfaceWidth, int bottom, unsigned char far *buffer,
                       int width, int rows)
{
    unsigned char far *destination;
    unsigned char far *source;
    int stride;
    unsigned unsigned int rowBytes;
    int remaining;
    int col;
    if ((displayType & 1) == 0) {
        stride = ((surfaceWidth * 4 + 31) / 32) * 4;
        rowBytes = (width + 1) / 2 + 3;
        source = surface + (bottom - top - 1) * stride + (x >> 1);
        destination = buffer;
        remaining = rows;
        while (remaining > 0) {
            memcpy(destination, source, rowBytes);
            source -= stride;
            destination += rowBytes;
            remaining--;
        }
    } else {
        stride = ((surfaceWidth + 31) / 32) * 4;
        rowBytes = (width + 7) / 8;
        source = surface + (bottom - top - 1) * stride + (x >> 3);
        destination = buffer;
        remaining = rows;
        while (remaining > 0) {
            {
                unsigned int far *dword = (unsigned int far *)destination;
                unsigned int far *sword = (unsigned int far *)source;
                for (col = 0; col < (rowBytes >> 1); col++)
                    *dword++ = *sword++;
                if (rowBytes & 1)
                    *((unsigned char far *)dword) = *((unsigned char far *)sword);
            }
            source -= stride;
            destination += rowBytes;
            remaining--;
        }
    }
}

