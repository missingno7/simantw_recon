/* Rebind the displayed card value through the MAPSYM yardMsgHandle owner. */
static unsigned __based(__segname("SIMANT_DATA_GROUP")) drawInfoCard = 0x80;
extern unsigned int far yardMsgHandle[];
extern void far DisplayCard(unsigned);

void win_DrawInfoWindow(unsigned char flags)
{
    if (flags & 2)
        DisplayCard(yardMsgHandle[0x298]);
}
