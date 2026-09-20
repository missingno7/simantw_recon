/*
 * Redraw the yard window only while it exists.  The simulation draw receives
 * the current yard mode and the historical redraw selector, then the window
 * is updated and the yard data pass is refreshed.
 */
extern int far win_IsWinOpen(int window);
extern void far Draw_SimYard(int mode, int selector);
extern void far pascal UpdateWindow(int window);
extern void far DrawYardData(void);
extern int near YardMode;
extern int near yardDrawFlag;
extern int near yardWindow;

void DrawYard(void)
{
    if (!win_IsWinOpen(0x1900))
        return;
    Draw_SimYard(YardMode, 1);
    yardDrawFlag = 0;
    UpdateWindow(yardWindow);
    yardDrawFlag = 1;
    DrawYardData();
}
