/* Initialize the info-window state before opening window 0x500. */
static unsigned __based(__segname("SIMANT_DATA_GROUP")) infoCard = 0x80;
static unsigned __based(__segname("SIMANT_DATA_GROUP")) infoMode = 0;
static unsigned __based(__segname("SIMANT_DATA_GROUP")) infoState = 0;
extern int far win_IsWinOpen(int);
extern void far win_Open(int);
void OpenInfoWindow(void)
{
    if (!win_IsWinOpen(0x500)) {
        infoCard = 0x80;
        infoMode = 0x80;
        infoState = 0;
        win_Open(0x500);
    }
}
