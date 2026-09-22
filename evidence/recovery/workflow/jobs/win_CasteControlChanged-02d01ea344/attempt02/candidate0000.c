/*
 * win_CasteControlChanged: refresh the caste triangle diagram after a level
 * change.  Queries object 0x130d's rect, derives triWidth/triHeight and the
 * half-widths (triWidthL/triWidthR, both triWidth>>1), the apex-to-base Y
 * slope (leftYSlope, a fixed-point ratio triHeight/(triWidthR<<8)), the
 * three triangle vertices (casteVerts[0]=apex top-center, [1]=bottom-left,
 * [2]=bottom-right) and the knob marker position (casteKnobPnt) from the
 * current casteLevels record (frac drives Y always; frac+weight drive X
 * with a degenerate apex fallback when frac==0xffff or the remaining
 * width is under 3).  It then clears any live caste animation
 * (hanim_RemoveAnimSet(casteAnimHandle)) and, while the caste bitmap
 * buffer exists, re-renders bitmap 0x120c into it the same way as the
 * exact-matched win_CasteControlClosed (gr_BitMapSize, mem_Lock, a
 * width/height header pair, DrawBitMapToBuffer into buffer+4, mem_Unlock).
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
extern struct Point far casteVerts[3];
extern struct Point far casteKnobPnt;
extern volatile unsigned int far casteLevels[];
extern int far casteAnimHandle;
extern unsigned int near casteBitmap;

extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far hanim_RemoveAnimSet(unsigned int setHandle);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far DrawBitMapToBuffer(unsigned char far *buffer, int left, int top,
                                   int height, int width, int bitmap,
                                   int far *rowBytes, int far *planes);

void far win_CasteControlChanged(void)
{
    struct WinRect rect;
    struct BitmapSize size;
    struct BitmapBuffer far *buffer;
    int rowBytes, planes;
    int frac, di, si;

    win_GetObjRect(0x130d, &rect);

    triWidth = rect.right - rect.left;
    triWidthL = triWidthR = (unsigned int)triWidth >> 1;
    triHeight = rect.bottom - rect.top;
    leftYSlope = (long)triHeight / ((long)triWidthR << 8);

    casteVerts[0].x = rect.left + triWidthR;
    casteVerts[0].y = rect.top;
    casteVerts[2].y = rect.bottom;
    casteVerts[1].y = rect.bottom;
    casteVerts[1].x = rect.left;
    casteVerts[2].x = rect.right;

    frac = casteLevels[0];

    casteKnobPnt.y = (int)((unsigned long)(0xffffU - casteLevels[0]) * (triHeight - 2)
                            / 0xffffUL) + casteVerts[0].y;

    di = (int)((unsigned long)casteLevels[0] * (unsigned int)triWidthL / 0xffffUL);
    si = triWidth - di * 2;
    if (frac != 0xffff && si >= 3) {
        casteKnobPnt.x = casteVerts[1].x
            + (int)(((long)casteLevels[2] * (long)(si - 3)) / (long)(0xffffU - casteLevels[0]))
            + di + 2;
    } else {
        casteKnobPnt.x = casteVerts[0].x + 2;
    }

    if (casteAnimHandle) {
        hanim_RemoveAnimSet(casteAnimHandle);
        casteAnimHandle = 0;
    }

    if (casteBitmap) {
        gr_BitMapSize(&size, 0x120c);
        buffer = mem_Lock(casteBitmap);
        buffer->width = size.width;
        buffer->height = size.height;
        DrawBitMapToBuffer(buffer->pixels, 0, 0, size.height, size.width, 0x120c,
                            &rowBytes, &planes);
        mem_Unlock(casteBitmap);
    }
}
