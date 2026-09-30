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
    short rowBytes;
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
extern unsigned int mem_Alloc(unsigned long bytes, int kind,
                              char far *name);
extern void mem_Free(int handle);
extern void far *mem_Lock(unsigned int handle);
extern unsigned long mem_Size(unsigned int handle);
extern int mem_Unlock(unsigned int handle);
extern void far Punt(char far *message, ...);
extern void far gr_PutToBuf(short left, short top, int a, int b,
                            int size, int mode, void far *bitmap,
                            short right, short bottom);
extern void far gr_GetFromBuf(short left, short top, int a, int b,
                              int size, int mode, void far *bitmap,
                              short right, short bottom);
extern void far ConvertMaskBitmap2(int a, int b, void far *pixels,
                                   int mode, int size, short yardTop,
                                   short yardLeft, short frameLeft, int y);
extern void far CopyMaskBitmap2(int a, int b, void far *pixels,
                                int mode, int size, short yardTop,
                                short yardLeft, short frameLeft, int y);
extern void far CopyMonoMaskBitmap(int a, int b, void far *pixels,
                                   int mode, int size, short yardTop,
                                   short yardLeft, short frameLeft, int y);
extern void far DrawBitMapToBuffer(int a, int b, short frameLeft,
                                   short frameTop, int mode, int size,
                                   unsigned short rowBytes,
                                   short far *yardTop,
                                   short far *yardLeft);
extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);
extern void far pascal UpdateWindow(int window);
extern void far hanim_ActuallyRemoveAnimObjects(unsigned int handle);

void far hanim_RenderAnimSet(unsigned int handle, int window,
                             int left, int top, int a, int b,
                             int size, int mode)
{
    struct HanimSet far *set;
    struct HanimFrame far *frames;
    struct HanimFrame far *frame;
    struct YardBalloon far *yard;
    struct RenderRect rect;
    int temporary;
    unsigned int frameHandle;
    int index;
    int count;
    unsigned long bitmapSize;
    short yardLeft;
    short yardTop;
    int owner;

    PROFSTART();
    if (displayType & 1) {
        temporary = mem_Alloc(0x1770L, 1, "to flush");
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
            Punt("Buffer in set too small!!");
    }

    mem_Unlock(frameHandle);
    frames = (struct HanimFrame far *)mem_Lock(frameHandle);
    owner = window >> 8;
    for (index = 0; index < count; ++index) {
        frame = frames + index;
        if (frame->left != -1) {
            gr_PutToBuf(frame->left, frame->top, a, b, size, mode,
                        frame->bitmap, frame->right, frame->bottom);
            if (win_hwnd[owner]) {
                rect.left = frame->left + left - 2;
                rect.right = frame->right + rect.left + 8;
                rect.top = frame->top + top - 2;
                rect.bottom = frame->bottom + rect.top + 4;
                InvalidateRect(win_hwnd[owner], &rect, 0);
            }
        }
    }

    for (index = 0; index < count; ++index) {
        frame = frames + index;
        if (frame->live && frame->visible) {
            gr_GetFromBuf(frame->oldLeft, frame->oldTop, a, b, size, mode,
                          frame->bitmap, frame->oldRight, frame->oldBottom);
            frame->left = frame->oldLeft;
            frame->top = frame->oldTop;
            frame->right = frame->oldRight;
            frame->bottom = frame->oldBottom;
        }
    }

    if (count > 0) {
      for (index = 0; index < count; ++index) {
        frame = frames + index;
        frame->maskFlags = frame->drawn;
        if (frame->live && frame->visible) {
            if (frame->rowBytes >= 0x7530) {
                yard = yardBalloonPtr;
                yardLeft = yard->left;
                yardTop = yard->top;
                if ((displayType & 1) == 0) {
                    if ((yard->flags & 0x80) == 0)
                        ConvertMaskBitmap2(a, b, (char far *)yard + 12,
                                           mode, size, yardTop, yardLeft,
                                           frame->left,
                                           mode - frame->top - yardLeft);
                    else
                        CopyMaskBitmap2(a, b, (char far *)yard + 12,
                                        mode, size, yardTop, yardLeft,
                                        frame->left,
                                        mode - frame->top - yardLeft);
                } else {
                    CopyMonoMaskBitmap(a, b, (char far *)yard + 12,
                                       mode, size, yardTop, yardLeft,
                                       frame->left,
                                       mode - frame->top - yardLeft);
                }
            } else {
                DrawBitMapToBuffer(a, b, frame->left, frame->top,
                                   mode, size, frame->rowBytes,
                                   &yardTop, &yardLeft);
            }
            if (win_hwnd[owner]) {
                rect.left = frame->oldLeft + left - 2;
                rect.right = frame->oldRight + rect.left + 8;
                rect.top = frame->oldTop + top - 2;
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


