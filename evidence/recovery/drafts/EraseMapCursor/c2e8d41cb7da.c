/*
 * Erase the map cursor only while the map window is open and the cursor is
 * active.  Preserve the clip stack, invert the saved match-position outline,
 * clear the cursor state, and restore the prior clip context.
 */
struct MapCursorRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int far win_IsWinOpen(int window);
extern int near mapCursorState;
extern void far clip_Push(int window);
extern void far clip_SetWin(int window);
extern void far GRectInvOutline(struct MapCursorRect far *rect, int color);
extern void far clip_Pop(void);
extern struct MapCursorRect far match_position;

void EraseMapCursor(void)
{
    if (!win_IsWinOpen(0x100) || mapCursorState != 1)
        return;

    clip_Push(0x100);
    clip_SetWin(0x100);
    GRectInvOutline(&match_position, 2);
    mapCursorState = 0;
    clip_Pop();
}
