/*
 * Prefer an already-open yard or map window, preserving the historical
 * window identifiers.  If neither is open, enter the yard-to-map view.
 */
extern int far win_IsWinOpen(int window);
extern void far win_ToTop(int window);
extern void far YardToMap(void);

void OpenMapYard(void)
{
    if (win_IsWinOpen(0x100)) {
        win_ToTop(0x100);
        return;
    }
    if (win_IsWinOpen(0x1900)) {
        win_ToTop(0x1900);
        return;
    }
    YardToMap();
}
