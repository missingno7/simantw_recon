/*
 * Unit review: PACK words reached as match_position[K] are the public
 * symbols match_position[0x3957] -> mapCursorRect (one selector word per symbol in the object).
 *
 * Erase the map cursor only while the map window is open and the cursor is
 * active.  Preserve the clip stack, invert the saved match-position outline,
 * clear the cursor state, and restore the prior clip context.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int far win_IsWinOpen(int window);
extern int near mapCursorState;
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far GRectInvOutline(struct Rect far *rect, int color);
extern void far clip_Pop(void);
extern int far match_position[];
extern int far mapCursorRect;

void EraseMapCursor(void)
{
    if (!win_IsWinOpen(0x100) || mapCursorState != 1)
        return;

    clip_Push();
    clip_SetWin(0x100);
    GRectInvOutline((struct Rect far *)&mapCursorRect, 2);
    mapCursorState = 0;
    clip_Pop();
}
