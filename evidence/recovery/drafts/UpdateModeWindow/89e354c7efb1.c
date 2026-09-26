/* Position and redraw the caste animation from its level and window geometry. */
struct WinRect { int left; int top; int right; int bottom; };
struct CasteImage { int width; int height; unsigned char pixels[1]; };
extern unsigned int near modeBitmap;
extern unsigned int near modeAnimHandle;
extern int near modeAnimObj;
extern int far modeLevels[];
extern int far modeVerts[];
extern int far triHeight;
extern int far triWidthL;
extern int far triWidth;
extern int far knobSize;
extern int far modeKnobPnt[2];
extern int near win_hwnd[];
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern unsigned int far hanim_MakeAnimSet(void);
extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);
extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);
extern void far hanim_RenderAnimSet(unsigned int setHandle, int window, int left, int top, unsigned char far *pixels, int width, int height);
extern void far win_InvalidateObject(int object);
extern void far pascal UpdateWindow(unsigned int window);

void far UpdateModeWindow(void)
{
    struct WinRect rect;
    register struct CasteImage far *bitmap;
    int width;
    int height;
    int x;
    int y;
    int size;
    int level;

    bitmap = (struct CasteImage far *)mem_Lock(modeBitmap);
    win_GetObjRect(0x1202, &rect);
    y = (((long)0xffff - modeLevels[0]) * (triHeight - 2)) / modeLevels[0] + modeVerts[1];
    modeKnobPnt[1] = y;
    size = (long)0xffff * modeLevels[0] / triWidthL;
    knobSize = size;
    if (modeLevels[0] != -1 && triWidth - size * 2 >= 3)
        x = (((long)0xffff - modeLevels[0]) * (triWidth - size * 2 - 3)) / modeLevels[2] + modeVerts[2] + size;
    else
        x = modeVerts[0] + 2;
    modeKnobPnt[0] = x;
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
    if (modeAnimHandle == 0)
        modeAnimHandle = hanim_MakeAnimSet();
    if (modeAnimObj == 0)
        modeAnimObj = hanim_AddAnimObject(modeAnimHandle, x, y, size, -1);
    else
        hanim_SetObjectPos(x, y, size, modeAnimHandle, modeAnimObj, -1);
    hanim_RenderAnimSet(modeAnimHandle, 0x1200, rect.left, rect.top,
                        bitmap->pixels, bitmap->width, bitmap->height);
    mem_Unlock(modeBitmap);
    win_InvalidateObject(0x1209);
    win_InvalidateObject(0x120a);
    win_InvalidateObject(0x120b);
    win_InvalidateObject(0x120c);
    UpdateWindow(win_hwnd[0]);
}








