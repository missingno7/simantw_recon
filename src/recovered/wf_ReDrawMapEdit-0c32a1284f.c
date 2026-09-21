/*
 * Hypothesis: redraw ordering depends on whether the edit window is in
 * front.  The flags byte suppresses the map/edit follow-up when either low
 * flag bit is set; the two win_IsWinOpen tests use the target's 0x100 and 0
 * window ids on their respective paths.
 */
extern int far win_IsWinInFront(int window);
extern int far win_IsWinOpen(int window);
extern void far UpdateEdit(void);
extern void far DrawEdit(void);
extern void far MakeDMap(int mode);
extern void far DrawMap(void);

void far ReDrawMapEdit(unsigned char flags)
{
    if (win_IsWinInFront(0)) {
        UpdateEdit();
        DrawEdit();
        if (!win_IsWinOpen(0x100))
            return;
        if (flags & 3)
            return;
        MakeDMap(1);
        DrawMap();
        return;
    }

    MakeDMap(1);
    DrawMap();
    if (!win_IsWinOpen(0))
        return;
    if (flags & 3)
        return;
    UpdateEdit();
    DrawEdit();
}
