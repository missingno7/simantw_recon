/* Test whether MSC 7 tail-merges the common window-open call. */
extern unsigned int far yardMsgHandle[];
extern int far win_IsWinOpen(int);
extern void far win_Open(int);

void OpenInfoWindow(void)
{
    if (win_IsWinOpen(0x500)) {
        win_Open(0x500);
    } else {
        yardMsgHandle[0x298] = 0x80;
        yardMsgHandle[0x287] = 0x80;
        yardMsgHandle[0x297] = 0;
        win_Open(0x500);
    }
}
