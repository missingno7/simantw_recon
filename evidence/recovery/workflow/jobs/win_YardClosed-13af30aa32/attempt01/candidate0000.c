/*
 * win_YardClosed: tear down the yard animation set when the yard window
 * closes.  yardAnimHandle is addressed here as a far word (DGROUP through
 * selector slot 0xc0ce) via a far pointer local that is stored once and
 * reloaded after every call.  When the handle is set: the clip state is
 * pushed and the yard window (0x1900) selected, all animation objects are
 * removed, and if the third argument is set the set is rendered once more
 * at the map tile point (far PACK mapTileRect, x/y words) with the two
 * coordinate arguments and the fixed size 0x200 / mode 0xe2 before the set
 * itself is removed; the clip state is popped and the handle cleared.
 */
struct TilePoint {
    int x;
    int y;
};

extern int far yardAnimHandle;
extern struct TilePoint far mapTileRect;
extern void far clip_Push(void);
extern void far clip_Pop(void);
extern void far clip_SetWin(int window);
extern void far hanim_RemoveAllAnimObjects(unsigned int setHandle);
extern void far hanim_RemoveAnimSet(unsigned int setHandle);
extern void far hanim_RenderAnimSet(unsigned int setHandle, int window,
                                    int left, int top, int a, int b,
                                    int size, int mode);

void far win_YardClosed(int a, int b, int render)
{
    int far *handle;

    handle = &yardAnimHandle;
    if (*handle) {
        clip_Push();
        clip_SetWin(0x1900);
        hanim_RemoveAllAnimObjects(*handle);
        if (render)
            hanim_RenderAnimSet(*handle, 0x1900, mapTileRect.x,
                                mapTileRect.y, a, b, 0x200, 0xe2);
        hanim_RemoveAnimSet(*handle);
        clip_Pop();
        *handle = 0;
    }
}
