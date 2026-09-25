/*
 * GetTriLatDist: inverse of the knob-position math in win_CasteControlChanged
 * / win_ModeControlChanged -- convert a screen point inside the iso-triangle
 * diagram back into a TriLevel record.  dy = pt->y - rect->top measures how
 * far down from the apex the point is; when it is beyond the usable height
 * (triHeight-2, compared unsigned so an above-apex point also clamps) frac
 * is forced to 0, otherwise frac = (triHeight-dy-2)*0xffff / (triHeight-2)
 * (0xffff at the apex, 0 at the base).  horiz = frac*triWidthL/0xffff turns
 * that back into a half-width in pixels and "remaining" is the triangle's
 * width at that row; when remaining is too small (<=2) weight/unused2 are
 * both cleared.  Otherwise dx = (pt->x-rect->right) - frac locates the
 * point relative to the right edge at that offset: beyond the far edge
 * clamps weight to 0xffff-frac, within 2px of the left edge clamps weight
 * to 0, otherwise weight is interpolated proportionally.  unused2 always
 * completes the three shares to 0xffff.
 */
struct WinRect { int left; int top; int right; int bottom; };
struct Point { int x; int y; };
struct TriLevel { unsigned int frac; int unused2; unsigned int weight; };

extern int far triWidth;
extern int far triWidthL;
extern int far triHeight;

void far GetTriLatDist(struct TriLevel far *level, struct WinRect far *rect, struct Point far *pt)
{
    int dx, dy;
    int remaining, horiz;

    dx = pt->x - rect->right;
    dy = pt->y - rect->top;

    if ((unsigned int)dy <= (unsigned int)(triHeight - 2)) {
        level->frac = (unsigned int)((long)(triHeight - dy - 2) * 0xffff / (long)(triHeight - 2));
    } else {
        level->frac = 0;
    }

    horiz = (int)((unsigned long)level->frac * (unsigned int)triWidthL / 0xffffUL);
    remaining = triWidth - horiz * 2;

    if (remaining > 2) {
        int localA = dx - level->frac;
        if (localA >= remaining - 2) {
            level->weight = 0xffff - level->frac;
        } else if (localA <= 2) {
            level->weight = 0;
        } else {
            level->weight = (unsigned int)(((long)localA * (0xffffL - (long)level->frac))
                                            / (long)(remaining - 2));
        }
        level->unused2 = 0xffff - level->weight - level->frac;
    } else {
        level->unused2 = 0;
        level->weight = 0;
    }
}
