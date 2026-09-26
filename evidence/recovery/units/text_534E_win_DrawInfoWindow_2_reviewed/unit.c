/* Shared based state for the info-window draw and open paths.  drawInfoCard is
   declared once because both members address the same segment-8 word at 0xA456.
   The two additional words reflect the stores at 0xA434 and 0xA454. */
static unsigned __based(__segname("SIMANT_DATA_GROUP")) drawInfoCard = 0x80;
static unsigned __based(__segname("SIMANT_DATA_GROUP")) infoMode = 0;
static unsigned __based(__segname("SIMANT_DATA_GROUP")) infoState = 0;
extern void far DisplayCard(unsigned card);
extern int far win_IsWinOpen(int window);
extern void far win_Open(int flags);
void far win_DrawInfoWindow(unsigned char flags)
{
    if (flags & 2)
        DisplayCard(drawInfoCard);
}
void far OpenInfoWindow(void)
{
    if (!win_IsWinOpen(0x500)) {
        drawInfoCard = 0x80;
        infoMode = 0x80;
        infoState = 0;
    }
    win_Open(0x500);
}
