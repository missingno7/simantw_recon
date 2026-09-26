/* The info-window reset writes the card field also consumed by the draw member. */
static unsigned __based(__segname("SIMANT_DATA_GROUP")) infoMode = 0;
static unsigned __based(__segname("SIMANT_DATA_GROUP")) infoState = 0;
extern int far win_IsWinOpen(int window);
extern void far win_Open(int flags);
void far OpenInfoWindow(void)
{
    if (win_IsWinOpen(0x500))
        goto open_window;
    drawInfoCard = 0x80;
    infoMode = 0x80;
    infoState = 0;
open_window:
    win_Open(0x500);
}
