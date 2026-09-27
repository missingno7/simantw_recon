/* The shared info state uses one far-segment selector. Target ES accesses place drawInfoCard at A456, infoMode at A434, and infoState at A454 inside the measured _yardMsgHandle public span. */
static unsigned __based(__segname("SIMANT_DATA_GROUP")) drawInfoCard = 0x80;
static unsigned __based(__segname("SIMANT_DATA_GROUP")) infoMode = 0;
static unsigned __based(__segname("SIMANT_DATA_GROUP")) infoState = 0;
extern void far DisplayCard(unsigned);
extern int far win_IsWinOpen(int);
extern void far win_Open(int);
void win_DrawInfoWindow(unsigned char flags)
{
    if (flags & 2)
        DisplayCard(drawInfoCard);
}
void OpenInfoWindow(void)
{
    if (!win_IsWinOpen(0x500)) {
        drawInfoCard = 0x80;
        infoMode = 0x80;
        infoState = 0;
    }
    win_Open(0x500);
}
