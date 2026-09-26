/*
 * SetYardMode changes the active yard plane and rebuilds its map bitmap.  The
 * draw path locks the window and map buffer, measures and copies the selected
 * bitmap, then restores the clipping/window state and refreshes the map title.
 * The historical object and plane branches are still being refined from the
 * aligned packet; this source keeps the full state transition in C.
 */
struct BitmapSize { int width; int height; };

extern int near YardMode;
extern int near OldMapPlane;
extern int near mapBuf;
extern int far mapXsize;
extern int far mapYsize;
extern int far match_position[];
extern void far SetMapPlane(int plane);
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
extern void far win_GetObjRect(int object, int far *rect);
extern void far win_Swap(int first, int second);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far DrawBitMapToBuffer(void far *buffer, int bitmap,
                                  int x, int y, int width, int height,
                                  int mapWidth, int mapHeight,
                                  int mode, int left, int top);
extern int near win_YardClosed(void);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far DrawYard(void);
extern void far SetMapTitle(void);

void far SetYardMode(int mode)
{
    struct BitmapSize size;
    int bitmap;
    int width;
    int height;
    int windowOpen;
    int object;
    void far *buffer;
    int rect[4];

    if (mode == 4) {
        SetMapPlane(mapBuf);
        return;
    }

    AllocateMapBuffer();
    buffer = mem_Lock(mapBuf);

    YardMode = mode;
    SetMapPlane(mode);
    win_MakeObjInvisible(0x1900);
    win_MakeObjInvisible(0x1903);
    win_MakeObjInvisible(0x190f);
    win_MakeObjInvisible(0x1900);
    win_MakeObjInvisible(0x1902);

    bitmap = match_position[mode];
    gr_BitMapSize(&size, bitmap);
    width = size.width;
    height = size.height;

    if (mode == 0 || mode == 1) {
        DrawBitMapToBuffer(buffer, bitmap, 0, 0, width, height,
                           mapXsize, mapYsize, 0, 0, 0);
    } else {
        DrawBitMapToBuffer(buffer, bitmap, 0, 0, width, height,
                           mapXsize, mapYsize, 1, 0, 0);
    }

    mem_Unlock(mapBuf);

    win_LockWin(0x1900);
    gr_BitMapSize(&size, bitmap);
    win_MakeObjSelectable(0x1900);
    win_MakeObjVisible(0x1900);
    win_SetObjBitmap(0x1900, mapBuf);
    win_UnlockWin(0x1900);

    windowOpen = win_IsWinOpen(0x1900);
    if (windowOpen) {
        clip_Push();
        clip_SetWin(0x1900);
        win_MakeObjSelected(0x1903);
        DrawYard();
        clip_Pop();
    }

    if (mode == 2)
        win_Swap(0x1900, 0x1902);
    win_GetObjRect(0x1903, rect);
    SetMapTitle();
    if (win_YardClosed())
        win_MakeObjInvisible(0x190f);
}
