/*
 * win_CasteControlClosed: tear down the caste control window state.  The
 * far PACK casteAnimHandle is addressed through a far pointer local that
 * is stored once and reloaded after the call (as in the admitted
 * win_YardClosed); a live animation set is removed and the handle cleared.
 * If the caste bitmap buffer exists, the size of bitmap 0x120c is queried,
 * the buffer is locked, its leading width/height words are filled from
 * that size and the bitmap is drawn into the pixel area that follows them
 * (origin 0,0, full height and width) with two result words returned on
 * the stack; the buffer is then unlocked.
 */
struct BitmapSize {
    int width;
    int height;
};

struct BitmapBuffer {
    int width;
    int height;
    unsigned char pixels[1];
};

extern int far casteAnimHandle;
extern unsigned int near casteBitmap;

extern void far hanim_RemoveAnimSet(unsigned int setHandle);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far DrawBitMapToBuffer(unsigned char far *buffer, int left, int top,
                                   int height, int width, int bitmap,
                                   int far *rowBytes, int far *planes);

void far win_CasteControlClosed(void)
{
    struct { int far *p; int spare; } h;
    struct BitmapSize size;
    int rowBytes;
    int planes;
    struct BitmapBuffer far *buffer;

    h.p = (void far *)&casteAnimHandle;
    if (*h.p) {
        hanim_RemoveAnimSet(*h.p);
        *h.p = 0;
    }
    if (casteBitmap) {
        gr_BitMapSize(&size, 0x120c);
        buffer = mem_Lock(casteBitmap);
        buffer->width = size.width;
        buffer->height = size.height;
        DrawBitMapToBuffer(buffer->pixels, 0, 0, size.height, size.width, 0x120c,
                           &rowBytes, &planes);
        mem_Unlock(casteBitmap);
    }
}
