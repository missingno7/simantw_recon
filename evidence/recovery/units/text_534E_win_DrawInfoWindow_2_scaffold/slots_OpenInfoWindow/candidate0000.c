/* Reset the three fields owned by the MAPSYM yardMsgHandle object, then open. */
extern unsigned __based(__segname("SIMANT_DATA_GROUP")) yardMsgHandle[];
extern int far win_IsWinOpen(int);
extern void far win_Open(int);
void OpenInfoWindow(void)
{
    if (!win_IsWinOpen(0x500)) {
        yardMsgHandle[0x298] = 0x80;
        yardMsgHandle[0x287] = 0x80;
        yardMsgHandle[0x297] = 0;
    }
    win_Open(0x500);
}
