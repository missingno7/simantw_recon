/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern int far win_IsWinInFront(int window);
extern void far OpenMapYard(void);
extern void far OpenEditWindow(void);

void DoTab(void)
{
    if (win_IsWinInFront(0)) OpenMapYard();
    else OpenEditWindow();
}
