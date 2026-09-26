/* Position and redraw the caste animation from its level and window geometry. */
struct WinRect { int left; int top; int right; int bottom; };
struct CasteImage { int width; int height; unsigned char pixels[1]; };
extern unsigned int near casteBitmap;
extern unsigned int near casteAnimHandle;
extern int near casteAnimObj;
extern int far casteLevels[];
extern int far casteVerts[];
extern int far triHeight;
extern int far triWidthL;
extern int far triWidth;
extern int far knobSize;
extern int far casteKnobPnt[2];
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

void far UpdateCasteWindow(void)
{
    struct WinRect rect;
    register struct CasteImage far *bitmap;
    int width;
    int height;
    int x;
    int y;
    int size;
    unsigned int level;

    bitmap = (struct CasteImage far *)mem_Lock(casteBitmap);
    win_GetObjRect(0x1302, &rect);
    level = casteLevels[0];
    y = ((0xffffUL - level) * (triHeight - 2)) / 0xffffUL + casteVerts[1];
    casteKnobPnt[1] = y;
    size = (long)0xffff * level / triWidthL;
    knobSize = size;
    if (level != 0xffffU && triWidth - size * 2 >= 3)
        x = ((long)(0xffffU - casteLevels[0]) * (triWidth - size * 2 - 3)) / casteLevels[2] + casteVerts[2] + size;
    else
        x = casteVerts[0] + 2;
    casteKnobPnt[0] = x;
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
    if (casteAnimHandle == 0)
        casteAnimHandle = hanim_MakeAnimSet();
    if (casteAnimObj == 0)
        casteAnimObj = hanim_AddAnimObject(casteAnimHandle, x, y, size, -1);
    else
        hanim_SetObjectPos(x, y, size, casteAnimHandle, casteAnimObj, -1);
    hanim_RenderAnimSet(casteAnimHandle, 0x1300, rect.left, rect.top,
                        bitmap->pixels, bitmap->width, bitmap->height);
    mem_Unlock(casteBitmap);
    win_InvalidateObject(0x1309);
    win_InvalidateObject(0x130a);
    win_InvalidateObject(0x130b);
    win_InvalidateObject(0x130c);
    UpdateWindow(win_hwnd[0]);
}






