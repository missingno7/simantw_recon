/*
 * Lock the animation set and its frame table, preflight each bitmap, restore
 * previously drawn rectangles, draw the active frames, then release every
 * bitmap and handle.  The two frame passes are separate because locking a
 * bitmap can move the frame table, so the table is unlocked and reacquired
 * before its stored pointers are used for drawing.
 */
typedef unsigned char BYTE;
struct HanimSet {
    int count;
    unsigned int objects;
    unsigned int reserved1;
    unsigned int reserved2;
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
struct RenderRect { short left, top, right, bottom; };
extern unsigned char near displayType;
extern int near win_hwnd[];
extern void far PROFSTART(void);
extern void far PROFSTOP(void);
extern struct YardBalloon far * far yardBalloonPtr;
extern unsigned int far mem_Alloc(unsigned int bytes, unsigned int flags,
                                  unsigned int clear, const char far *owner);
extern void far mem_Free(unsigned int handle);
extern void far *mem_Lock(unsigned int handle);
extern unsigned long far mem_Size(unsigned int handle);
extern void far mem_Unlock(unsigned int handle);
extern void far Punt(char far *message, ...);
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
extern int far pascal InvalidateRect(int window, struct RenderRect far *rect,
                                    int erase);
extern int far pascal UpdateWindow(int window);
extern void far hanim_ActuallyRemoveAnimObjects(unsigned int handle);

void far hanim_RenderAnimSet(unsigned int handle, unsigned int frameCode,
                             short originX, short originY,
                             void far *surface, void far *clip)
{
    struct HanimSet far *set;
    struct HanimFrame far *frames;
    struct HanimFrame far *frame;
    struct YardBalloon far *yard;
    struct RenderRect rect;
    unsigned int temporary;
    unsigned int frameHandle;
    int index;
    int count;
    unsigned long bitmapSize;
    short x;
    short y;
    int owner;

    PROFSTART();
    if (displayType & 1) {
        temporary = mem_Alloc(0x1770, 0, 1, "animation probe");
        mem_Free(temporary);
    }

    set = (struct HanimSet far *)mem_Lock(handle);
    frameHandle = set->objects;
    frames = (struct HanimFrame far *)mem_Lock(frameHandle);
    count = set->count;
    for (index = 0; index < count; ++index) {
        frame = frames + index;
        frame->bitmap = mem_Lock(frame->bitmapHandle);
        bitmapSize = mem_Size(frame->bitmapHandle);
        if ((unsigned long)frame->width * 3UL > bitmapSize)
            Punt("Bad animation bitmap");
    }

    mem_Unlock(frameHandle);
    frames = (struct HanimFrame far *)mem_Lock(frameHandle);
    owner = frameCode >> 8;
    for (index = 0; index < count; ++index) {
        frame = frames + index;
        if (frame->left != -1) {
            gr_PutToBuf(frame->left, frame->top, frame->bitmap,
                        surface, clip, frame->right, frame->bottom);
            rect.left = frame->left + originX - 2;
            rect.right = frame->right + rect.left + 8;
            rect.top = frame->top + originY - 2;
            rect.bottom = frame->bottom + rect.top + 4;
            InvalidateRect(win_hwnd[owner], &rect, 0);
            frame->oldLeft = rect.left;
            frame->oldRight = rect.right;
            frame->oldTop = rect.top;
            frame->oldBottom = rect.bottom;
        }
    }

    for (index = 0; index < count; ++index) {
        frame = frames + index;
        if (frame->live && frame->visible) {
            gr_GetFromBuf(frame->oldLeft, frame->oldTop, frame->bitmap,
                          surface, clip, frame->oldRight, frame->oldBottom);
            frame->left = frame->oldLeft;
            frame->top = frame->oldTop;
            frame->right = frame->oldRight;
            frame->bottom = frame->oldBottom;
        }
    }

    yard = yardBalloonPtr;
    for (index = 0; index < count; ++index) {
        frame = frames + index;
        frame->maskFlags = frame->drawn;
        x = frameCode - frame->left - yard->left;
        y = originX - frame->top - yard->top;
        if (frame->live && frame->visible && frame->rowBytes >= 0x7530) {
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
            if (win_hwnd[owner]) {
                rect.left = frame->oldLeft + originX - 2;
                rect.right = frame->oldRight + rect.left + 8;
                rect.top = frame->oldTop + originY - 2;
                rect.bottom = frame->oldBottom + rect.top + 4;
                InvalidateRect(win_hwnd[owner], &rect, 0);
                frame->drawn = 1;
            } else {
                frame->drawn = 0;
            }
        } else {
            frame->drawn = 0;
        }
    }

    if (win_hwnd[owner])
        UpdateWindow(win_hwnd[owner]);
    mem_Unlock(frameHandle);
    set = (struct HanimSet far *)mem_Lock(handle);
    frameHandle = set->objects;
    frames = (struct HanimFrame far *)mem_Lock(frameHandle);
    count = set->count;
    for (index = 0; index < count; ++index)
        mem_Unlock(frames[index].bitmapHandle);
    mem_Unlock(frameHandle);
    mem_Unlock(handle);
    mem_Unlock(handle);
    hanim_ActuallyRemoveAnimObjects(handle);
    PROFSTOP();
}
