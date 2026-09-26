/* Render the bitmap members of one locked animation set, restoring each
 * saved rectangle before copying its newly drawn pixels to the surface. */
typedef unsigned char BYTE;
struct HanimSet {
    unsigned short count;
    unsigned short objects;
    unsigned short reserved1;
    unsigned short reserved2;
};
struct HanimFrame {
    BYTE live;
    BYTE drawn;
    BYTE maskFlags;
    BYTE visible;
    unsigned short field04;
    short left;
    short top;
    short right;
    short bottom;
    unsigned short field0e;
    unsigned short field10;
    unsigned short field12;
    unsigned short field14;
    short oldLeft;
    short oldTop;
    short oldRight;
    short oldBottom;
    unsigned short width;
    unsigned short height;
    unsigned short bitmapHandle;
    unsigned short flags;
    unsigned short rowBytes;
    void far *bitmap;
};
struct YardBalloon {
    unsigned short count;
    unsigned short flags;
    unsigned short field04;
    unsigned short field06;
    short top;
    short left;
};
extern char near displayType;
extern struct YardBalloon far * far yardBalloonPtr;
extern unsigned int far mem_Alloc(const char far *owner, unsigned int clear,
                                  unsigned int flags, unsigned int bytes);
extern void far mem_Free(unsigned int handle);
extern void far * mem_Lock(unsigned int handle);
extern unsigned long far mem_Size(unsigned int handle);
extern void far mem_Unlock(unsigned int handle);
extern void far Punt(const char far *message);
extern void far gr_PutToBuf(short, short, void far *, void far *, void far *,
                            short, short);
extern void far gr_GetFromBuf(short, short, void far *, void far *, void far *,
                              short, short);
extern void far ConvertMaskBitmap2(short, short, short, short, short,
                                   void far *, void far *, void far *,
                                   short, short);
extern void far CopyMaskBitmap2(short, short, short, short, short,
                                void far *, void far *, void far *,
                                short, short);
extern void far CopyMonoMaskBitmap(short, short, short, short, short,
                                   void far *, void far *, void far *,
                                   short, short);
extern void far DrawBitMapToBuffer(short, short, short, short, short,
                                   void far *, void far *, void far *,
                                   short, short);
extern void far hanim_ActuallyRemoveAnimObjects(unsigned int handle);
void far hanim_RenderAnimSet(unsigned int handle, unsigned int frameCode,
                             short originX, short originY,
                             void far *surface, void far *clip)
{
    struct HanimSet far *set;
    struct HanimFrame far *frames;
    struct HanimFrame far *frame;
    struct YardBalloon far *yard;
    unsigned int temporary;
    unsigned int frameHandle;
    unsigned int index;
    unsigned int count;
    unsigned long bitmapSize;
    short x;
    short y;

    if (displayType & 1) {
        temporary = mem_Alloc("animation probe", 1, 0, 0x1770);
        mem_Free(temporary);
    }
    set = (struct HanimSet far *)mem_Lock(handle);
    frameHandle = set->objects;
    frames = (struct HanimFrame far *)mem_Lock(frameHandle);
    count = set->count;
    index = 0;
    while (index < count) {
        frame = frames + index;
        frame->bitmap = mem_Lock(frame->bitmapHandle);
        bitmapSize = mem_Size(frame->bitmapHandle);
        if (frame->width * 3U > bitmapSize)
            Punt("Bad animation bitmap");
        index++;
    }

    index = 0;
    while (index < count) {
        frame = frames + index;
        if (frame->drawn) {
            gr_PutToBuf(frame->left, frame->top, frame->bitmap,
                        surface, clip, frame->right, frame->bottom);
            if (frame->bitmapHandle != 0) {
                x = frame->left + originX - 2;
                y = frame->top + originY - 2;
                frame->oldLeft = x;
                frame->oldRight = x + frame->width + 8;
                frame->oldTop = y;
                frame->oldBottom = y + frame->height + 4;
                gr_GetFromBuf(frame->oldLeft, frame->oldTop, frame->bitmap,
                              surface, clip, frame->oldRight, frame->oldBottom);
            }
        }
        index++;
    }

    index = 0;
    while (index < count) {
        frame = frames + index;
        yard = yardBalloonPtr;
        x = originX - frame->left - yard->left;
        y = originY - frame->top - yard->top;
        if (frame->live && frame->visible && frame->height >= 0x7530) {
            if ((displayType & 1) == 0 && (yard->flags & 0x80) == 0) {
                if (frame->maskFlags & 1)
                    ConvertMaskBitmap2(x, frame->oldLeft, frame->width,
                                       frame->height, frameCode, frame->bitmap,
                                       surface, clip, originX, originY);
                else if (frame->maskFlags & 2)
                    CopyMaskBitmap2(x, frame->oldLeft, frame->width,
                                    frame->height, frameCode, frame->bitmap,
                                    surface, clip, originX, originY);
                else
                    CopyMonoMaskBitmap(x, frame->oldLeft, frame->width,
                                       frame->height, frameCode, frame->bitmap,
                                       surface, clip, originX, originY);
            } else {
                DrawBitMapToBuffer(frame->width, frame->height,
                                   frame->oldLeft, frame->oldTop,
                                   frame->rowBytes, frame->bitmap,
                                   surface, clip, originX, originY);
            }
            frame->drawn = 1;
        } else {
            frame->drawn = 0;
        }
        index++;
    }
    while (count != 0) {
        count--;
        mem_Unlock(frames[count].bitmapHandle);
    }
    mem_Unlock(frameHandle);
    mem_Unlock(handle);
    hanim_ActuallyRemoveAnimObjects(handle);
}
