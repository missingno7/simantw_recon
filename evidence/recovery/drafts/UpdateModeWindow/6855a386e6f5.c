/* Position and redraw the caste animation from its level and window geometry. */
struct WinRect { int left; int top; int right; int bottom; };
struct ModeImage { int width; int height; unsigned char pixels[1]; };
extern unsigned int near modeBitmap;
extern int far modeAnimHandle;
extern int near modeAnimObj;
extern unsigned int far modeLevels[];
extern int far modeVerts[];
extern unsigned int far triHeight;
extern unsigned int far triWidthL;
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
    register struct ModeImage far *bitmap;
    int freeWidth;
    int size;
    unsigned int level;

    bitmap = (struct ModeImage far *)mem_Lock(modeBitmap);
    win_GetObjRect(0x1202, &rect);
    level = modeLevels[0];
    modeKnobPnt[1] = ((0xffffUL - level) * (triHeight - 2)) / 0xffffUL + modeVerts[1];
    size = (unsigned long)triWidthL * level / 0xffffUL;
    freeWidth = triWidth - size * 2;
    if (level != 0xffffU && freeWidth >= 3)
        modeKnobPnt[0] = ((long)(freeWidth - 3) * modeLevels[2]) / (0xffffU - modeLevels[0]) + modeVerts[2] + size;
    else
        modeKnobPnt[0] = modeVerts[0] + 2;
    knobSize = size;
    if (modeAnimHandle == 0)
        modeAnimHandle = hanim_MakeAnimSet();
    if (modeAnimObj == 0)
        modeAnimObj = hanim_AddAnimObject(modeAnimHandle, modeKnobPnt[0], modeKnobPnt[1], size, -1);
    else
        hanim_SetObjectPos(modeKnobPnt[0], modeKnobPnt[1], size, modeAnimHandle, modeAnimObj, -1);
    hanim_RenderAnimSet(modeAnimHandle, 0x1200, rect.left, rect.top,
                        bitmap->pixels, bitmap->width, bitmap->height);
    mem_Unlock(modeBitmap);
    win_InvalidateObject(0x1209);
    win_InvalidateObject(0x120a);
    win_InvalidateObject(0x120b);
    win_InvalidateObject(0x120c);
    UpdateWindow(win_hwnd[0]);
}






