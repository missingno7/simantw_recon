/* Candidate translation unit antedit_C19C_AllocateMapBuffer_1: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _AllocateMapBuffer */

extern unsigned int near mapBuf;
extern unsigned char near displayType;
extern int far mapXsize;
extern int far mapYsize;
extern char near mapOwner[];
extern long far BitmapImageSize(int width, int height, int planes);
extern unsigned int far mem_Alloc(long bytes, int type, void far *owner);

void AllocateMapBuffer(void)
{
    long bytes;
    int planes;

    if (mapBuf == 0) {
        planes = (displayType & 1) ? 1 : 4;
        bytes = BitmapImageSize(mapXsize << 7, mapYsize << 6, planes);
        mapBuf = mem_Alloc(bytes + 0x20L, 1, mapOwner);
    }
}

