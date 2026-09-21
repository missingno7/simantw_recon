/*
 * UpdateYard redraws the open yard window, temporarily clears the private
 * redraw flag around USER's UpdateWindow call on win_hwnd[25] (window id
 * 0x1900 >> 8), then refreshes yard data.
 */
extern int far win_IsWinOpen(int window);
extern void far Draw_SimYard(int mode, int selector);
extern void far pascal UpdateWindow(int window);
extern void far DrawYardData(void);
extern int near YardMode;
static int near yardDrawFlag = 1;
extern int near win_hwnd[];

void UpdateYard(void)
{
    if (!win_IsWinOpen(0x1900))
        return;
    Draw_SimYard(YardMode, 1);
    yardDrawFlag = 0;
    UpdateWindow(win_hwnd[25]);
    yardDrawFlag = 1;
    DrawYardData();
}
