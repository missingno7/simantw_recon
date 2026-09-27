/* Candidate translation unit text_534E_win_DrawInfoWindow_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _win_DrawInfoWindow
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

static unsigned __based(__segname("SIMANT_DATA_GROUP")) drawInfoCard = 0x80;
extern void far DisplayCard(unsigned);




void win_DrawInfoWindow(unsigned char flags)
{
    if (flags & 2)
        DisplayCard(drawInfoCard);
}

extern unsigned __based(__segname("SIMANT_DATA_GROUP")) yardMsgHandle[];
extern int far win_IsWinOpen(int);
extern void far win_Open(int);

void OpenInfoWindow(void)
{
    if (!win_IsWinOpen(0x500)) {
        drawInfoCard = 0x80;
        yardMsgHandle[0x287] = 0x80;
        yardMsgHandle[0x297] = 0;
    }
    win_Open(0x500);
}

