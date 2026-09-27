/* Candidate translation unit text_534E_win_DrawInfoWindow_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _win_DrawInfoWindow, _OpenInfoWindow
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

extern unsigned int far yardMsgHandle[];
extern void far DisplayCard(unsigned);
extern int far win_IsWinOpen(int);
extern void far win_Open(int);


void OpenInfoWindow(void);

#pragma alloc_text(RUN2_TEXT, OpenInfoWindow)

void win_DrawInfoWindow(unsigned char flags)
{
    if (flags & 2)
        DisplayCard(yardMsgHandle[0x298]);
}

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

