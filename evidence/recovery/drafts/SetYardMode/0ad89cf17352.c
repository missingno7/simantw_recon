/* Reconstructed yard-plane display and bitmap refresh. */
struct BitmapSize { int width; int height; };
struct WinRect { int left; int top; int right; int bottom; };
struct FarWords { unsigned int offset; unsigned int segment; };
union LockedBuffer { void far *pointer; struct FarWords words; };

extern int near OldMapPlane;
extern int near YardMode;
extern unsigned char near displayType;
extern int near ribbonBarWnd;
extern int near win_hwnd[];
extern int far mapBuf;
extern int far mapXsize;
extern int far mapYsize;

extern void near SetMapPlane(int plane);
extern void far AllocateMapBuffer(void);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far win_LockWin(int object);
extern void far win_UnlockWin(int object);
extern void far win_MakeObjInvisible(int object);
extern void far win_MakeObjVisible(int object);
extern void far win_MakeObjSelectable(int object);
extern void far win_MakeObjSelected(int object);
extern int far win_IsWinOpen(int object);
extern void far win_SetObjBitmap(int object, unsigned int bitmap);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far win_Swap(int first, int second);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far DrawBitMapToBuffer(int x, int y, int sourceX, int sourceY,
                                   int width, int height, int bitmap,
                                   struct BitmapSize far *info,
                                   struct BitmapSize far *bufferInfo);
extern void near win_YardClosed(int x, int y, int render);
extern void far pascal InvalidateRect(int window, struct WinRect far *rect,
                                      int erase);
extern void far pascal UpdateWindow(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far DrawYard(void);
extern void near SetMapTitle(void);

void far SetYardMode(int mode)
{
    union LockedBuffer map;
    struct BitmapSize firstSize;
    struct BitmapSize secondSize;
    struct BitmapSize thirdSize;
    struct BitmapSize drawInfo;
    struct WinRect dirty;
    int bitmap;
    int width;
    int height;
    int bitmapHeight;
    int maxMapHeight;
    register int selectedMode;

    if (mode == 4) {
        SetMapPlane(OldMapPlane);
        goto finish;
    }

    selectedMode = mode;
    AllocateMapBuffer();
    map.pointer = mem_Lock(mapBuf);

    if (selectedMode == 0)
        goto common;
    if (selectedMode == 1)
        goto common;

    {
        YardMode = selectedMode;
        win_LockWin(0x1900);
        win_MakeObjInvisible(0x1903);
        win_MakeObjInvisible(0x190f);
        win_UnlockWin(0x1900);
        win_MakeObjSelectable(0x1902);
        win_YardClosed(map.words.offset, map.words.segment, 0);
        win_MakeObjInvisible(0x1914);

        if (displayType & 1) {
            gr_BitMapSize(&firstSize, 0x1b5a);
            win_MakeObjVisible(0x1914);
            width = mapXsize * 128;
            maxMapHeight = mapYsize * 64;
            height = maxMapHeight;
            if (height > firstSize.height)
                height = firstSize.height;
            DrawBitMapToBuffer(map.words.offset, map.words.segment,
                               0, 0, width, height, 0x1b5a,
                               &drawInfo, &thirdSize);
        } else if (displayType == 9 || displayType == 10) {
            gr_BitMapSize(&firstSize, 0x1b6c);
            width = mapXsize * 128;
            maxMapHeight = mapYsize * 64;
            height = maxMapHeight;
            if (height > firstSize.height)
                height = firstSize.height;
            DrawBitMapToBuffer(map.words.offset, map.words.segment,
                               0, 0, width, height, 0x1b6c,
                               &drawInfo, &thirdSize);
        } else {
            gr_BitMapSize(&firstSize, 0x1b6c);
            bitmapHeight = firstSize.height;
            gr_BitMapSize(&firstSize, 0x1b6d);
            bitmapHeight += firstSize.height;
            gr_BitMapSize(&firstSize, 0x1b6e);
            width = mapXsize * 128;
            maxMapHeight = mapYsize * 64;
            height = maxMapHeight;
            if (height > bitmapHeight)
                height = bitmapHeight;
            DrawBitMapToBuffer(map.words.offset, map.words.segment,
                               0, 0, width, height, 0x1b6e,
                               &drawInfo, &thirdSize);
            DrawBitMapToBuffer(map.words.offset, map.words.segment,
                               0, firstSize.width, width, height, 0x1b6d,
                               &drawInfo, &thirdSize);
            DrawBitMapToBuffer(map.words.offset, map.words.segment,
                               firstSize.width, 0, width, height, 0x1b6c,
                               &drawInfo, &thirdSize);
        }
    }

common:
    YardMode = selectedMode;
    win_LockWin(0x1900);
    win_MakeObjInvisible(0x1903);
    win_MakeObjInvisible(0x190f);
    win_MakeObjSelectable(0x1902);
    win_MakeObjInvisible(0x1914);
    win_UnlockWin(0x1900);
    win_YardClosed(map.words.offset, map.words.segment, 1);

    bitmap = selectedMode + 0x1b58;
    win_SetObjBitmap(0x1903, bitmap);
    gr_BitMapSize(&firstSize, bitmap);
    width = mapXsize * 128;
    height = mapYsize * 64;
    if (height > firstSize.height)
        height = firstSize.height;
    DrawBitMapToBuffer(map.words.offset, map.words.segment,
                       0, 0, width, height, bitmap,
                       &drawInfo, &thirdSize);

    if (displayType == 10)
        bitmap = 0x1b5a;
    else
        bitmap = 0x1b5b;
    maxMapHeight = mapYsize * 64;
    bitmapHeight = maxMapHeight;
    if (bitmapHeight > firstSize.height)
        bitmapHeight = firstSize.height;
    DrawBitMapToBuffer(map.words.offset, map.words.segment,
                       firstSize.width - 1, 0, width, bitmapHeight, bitmap,
                       &drawInfo, &thirdSize);

    mem_Unlock(mapBuf);
    if (!win_IsWinOpen(0x1900) && win_IsWinOpen(0x0100))
        win_Swap(0x1900, 0x0100);

    win_GetObjRect(0x1903, &dirty);
    dirty.right += 0x200;
    dirty.top += 0xe2;
    InvalidateRect(win_hwnd[25], &dirty, 0);
    UpdateWindow(win_hwnd[25]);

    clip_Push();
    clip_SetWin(0x1900);
    if (ribbonBarWnd)
        win_MakeObjSelected(selectedMode + 0x2200);
    else
        win_MakeObjSelected(selectedMode + 0x1900);
    clip_Pop();
    DrawYard();
finish:
    SetMapTitle();
}
