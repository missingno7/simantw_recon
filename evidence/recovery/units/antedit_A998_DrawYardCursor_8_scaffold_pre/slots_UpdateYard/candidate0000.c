/* Candidate translation unit antedit_A998_DrawYard_2: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DrawYard, _UpdateYard */

extern int far win_IsWinOpen(int window);
extern void far Draw_SimYard(int mode, int selector);
extern void far pascal UpdateWindow(int window);
extern void far DrawYardData(void);
extern int near YardMode;
static int near yardDrawFlag = 1;
extern int near win_hwnd[];

void DrawYard(void)
{
    if (!win_IsWinOpen(0x1900))
        return;
    Draw_SimYard(YardMode, 1);
    yardDrawFlag = 0;
    UpdateWindow(win_hwnd[25]);
    yardDrawFlag = 1;
    DrawYardData();
}

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

