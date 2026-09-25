/*
 * win_ModeControlChanged: twin of win_CasteControlChanged for the mode
 * tool window (object 0x1200 family, rect object 0x120d, bitmap 0x11f8).
 * Same triangle-geometry math over the shared triWidth/triWidthR/
 * triWidthL/triHeight/leftYSlope state, writing modeVerts[0..2] and
 * modeKnobPnt from modeLevels instead of casteVerts/casteKnobPnt/
 * casteLevels, clearing modeAnimHandle via hanim_RemoveAnimSet, and
 * re-rendering the mode bitmap the same way as win_CasteControlChanged's
 * bitmap block (gr_BitMapSize/mem_Lock/DrawBitMapToBuffer/mem_Unlock).
 */
struct WinRect { int left; int top; int right; int bottom; };
struct Point { int x; int y; };
struct BitmapSize { int width; int height; };
struct BitmapBuffer { int width; int height; unsigned char pixels[1]; };

extern int far triWidth;
extern int far triWidthR;
extern int far triWidthL;
extern int far triHeight;
extern long far leftYSlope;
extern struct Point far modeVerts[3];
extern struct Point far modeKnobPnt;
extern unsigned int far modeLevels[3];
extern int far modeAnimHandle;
extern unsigned int near modeBitmap;

extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far hanim_RemoveAnimSet(unsigned int setHandle);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far DrawBitMapToBuffer(unsigned char far *buffer, int left, int top,
                                   int height, int width, int bitmap,
                                   int far *rowBytes, int far *planes);

void far win_ModeControlChanged(void)
{
    struct WinRect rect;
    struct BitmapSize size;
    struct BitmapBuffer far *buffer;
    int rowBytes, planes;
    int frac, di, si;

    win_GetObjRect(0x120d, &rect);

    triWidth = rect.right - rect.left;
    triWidthR = (unsigned int)triWidth >> 1;
    triWidthL = triWidthR;
    triHeight = rect.bottom - rect.top;
    leftYSlope = (long)triHeight / ((long)triWidthR << 8);

    modeVerts[0].x = rect.left + triWidthR;
    modeVerts[0].y = rect.top;
    modeVerts[2].y = rect.bottom;
    modeVerts[1].y = rect.bottom;
    modeVerts[1].x = rect.left;
    modeVerts[2].x = rect.right;

    frac = modeLevels[0];

    modeKnobPnt.y = (int)((unsigned long)(0xffffU - modeLevels[0]) * (triHeight - 2)
                           / 0xffffUL) + modeVerts[0].y;

    di = (int)((unsigned long)modeLevels[0] * (unsigned int)triWidthL / 0xffffUL);
    si = (rect.right - rect.left) - di * 2;
    if (frac != 0xffff && si >= 3) {
        modeKnobPnt.x = modeVerts[1].x
            + (int)(((long)modeLevels[2] * (long)(si - 3)) / (long)(0xffffU - modeLevels[0]))
            + di + 2;
    } else {
        modeKnobPnt.x = modeVerts[0].x + 2;
    }

    if (modeAnimHandle) {
        hanim_RemoveAnimSet(modeAnimHandle);
        modeAnimHandle = 0;
    }

    if (modeBitmap) {
        gr_BitMapSize(&size, 0x11f8);
        buffer = mem_Lock(modeBitmap);
        buffer->width = size.width;
        buffer->height = size.height;
        DrawBitMapToBuffer(buffer->pixels, 0, 0, size.height, size.width, 0x11f8,
                            &rowBytes, &planes);
        mem_Unlock(modeBitmap);
    }
}
