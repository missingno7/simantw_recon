/*
 * Clear the map/scent window's button selection while preserving clipping.
 * The clip stack is opened only for an already-open window and is popped
 * after the operation if the window is still available.
 */
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far win_MakeGroupUnselected(int window, int group);
extern void far clip_Pop(void);

void ClearMapScentButtons(void)
{
    if (win_IsWinOpen(0x100)) {
        clip_Push();
        clip_SetWin(0x100);
    }
    win_MakeGroupUnselected(0x100, 2);
    if (win_IsWinOpen(0x100))
        clip_Pop();
}
