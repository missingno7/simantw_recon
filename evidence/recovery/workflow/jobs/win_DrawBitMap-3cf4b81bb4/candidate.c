/*
 * win_DrawBitMap: load and draw a bitmap resource at a position.  Loads the
 * resource with db_LoadObject(bitmapNumber, 2, 0); a zero handle returns 0
 * without drawing.  Otherwise the resource is locked and its leading word is
 * inspected: -1 or 0x8000 selects the packed renderer
 * GPutPacked(x, y, data); a leading word of 0 is an image record, subtyped
 * by byte data[2] & 0x7f (1 selects the uncompressed GPutImg(x, y, data+8,
 * mask), anything else selects GPutPic(x, y, data+8, mask)), with mask
 * derived from bit 0x80 of that same subtype byte (0 when set, 1 when
 * clear); a leading word of 3 reports "Unknown bitmap type" through
 * WinPrintf; any other leading word draws nothing.  Every path but the
 * initial load failure unlocks the resource, releases the database object
 * (type 2) and returns 1.
 */
extern unsigned int far db_LoadObject(int object, int type, int flags);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far db_ReleaseObject(unsigned int object, int type);
extern void far GPutPacked(int x, int y, void far *data);
extern void far GPutImg(int x, int y, unsigned char far *image, int mask);
extern void far GPutPic(int x, int y, unsigned char far *picture, int mask);
extern void far WinPrintf(char far *format, ...);

int far win_DrawBitMap(int x, int y, int bitmapNumber)
{
    unsigned int handle;
    int far *data;
    int mask;

    handle = db_LoadObject(bitmapNumber, 2, 0);
    if (!handle)
        return 0;
    data = (int far *)mem_Lock(handle);
    if (*data == -1) {
    packed:
        GPutPacked(x, y, data);
    done:
        mem_Unlock(handle);
        db_ReleaseObject(bitmapNumber, 2);
        return 1;
    }
    if (*data == 0x8000)
        goto packed;
    if (*data == 0) {
        if ((((unsigned char far *)data)[2] & 0x7f) == 1) {
            mask = (((unsigned char far *)data)[2] & 0x80) ? 0 : 1;
            GPutImg(x, y, (unsigned char far *)data + 8, mask);
        } else {
            mask = (((unsigned char far *)data)[2] & 0x80) ? 0 : 1;
            GPutPic(x, y, (unsigned char far *)data + 8, mask);
        }
        goto done;
    }
    if (*data == 3)
        WinPrintf("Unknown bitmap type");
    goto done;
}
