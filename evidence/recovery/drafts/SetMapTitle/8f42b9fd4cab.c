/*
 * SetMapTitle: refresh the map and yard window titles.  The map title
 * object (0x101) takes the far MwinTitle string for the current MapMode
 * and the yard title object (0x1901) the string for YardMode + 9.  Then,
 * inside a pushed clip, the title is redrawn for whichever of the map
 * window (0x100) or otherwise the yard window (0x1900) is open.
 */
extern int far MapMode;
extern int near YardMode;
extern char far * far * far MwinTitle;

extern void far win_SetObjFormatStr(int object, char far *text);
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far win_DrawTitle(int object);

void far SetMapTitle(void)
{
    win_SetObjFormatStr(0x101, MwinTitle[MapMode]);
    win_SetObjFormatStr(0x1901, MwinTitle[YardMode + 9]);
    if (win_IsWinOpen(0x100)) {
        clip_Push();
        clip_SetWin(0x100);
        win_DrawTitle(0x101);
        clip_Pop();
    } else if (win_IsWinOpen(0x1900)) {
        clip_Push();
        clip_SetWin(0x1900);
        win_DrawTitle(0x1901);
        clip_Pop();
    }
}
