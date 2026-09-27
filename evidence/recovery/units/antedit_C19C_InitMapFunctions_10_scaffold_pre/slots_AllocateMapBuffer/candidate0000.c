/*
 * Unit review (antedit:C19C): the allocation owner tag is this object's own
 * string literal "mapbuf" (DGROUP 0x19C4, right after DrawMapData's format
 * strings), not an external near array.
 *
 * Hypothesis: mapBuf is a one-time handle.  The allocator receives the
 * unnamed DGROUP owner object observed at DS:19cc, type 1, and the byte size
 * for a bitmap whose width and height are the PACK words mapXsize/mapYsize.
 * The display flag selects one plane for the single-display path and four
 * planes otherwise; the explicit shifts preserve the observed 128/64 scale.
 */
extern unsigned int near mapBuf;
extern unsigned char near displayType;
extern int far mapXsize;
extern int far mapYsize;

extern long far BitmapImageSize(int width, int height, int planes);
extern unsigned int far mem_Alloc(long bytes, int type, void far *owner);

void AllocateMapBuffer(void)
{
    long bytes;
    int planes;

    if (mapBuf == 0) {
        planes = (displayType & 1) ? 1 : 4;
        bytes = BitmapImageSize(mapXsize << 7, mapYsize << 6, planes);
        mapBuf = mem_Alloc(bytes + 0x20L, 1, "mapbuf");
    }
}
