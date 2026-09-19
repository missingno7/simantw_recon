/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern void far win_Open(int flags);

void OpenHistoryWindow(void)
{
    win_Open(0x1500);
}
