/* When the draw-info flag is set, display the selected card. */
static unsigned __based(__segname("SIMANT_DATA_GROUP")) drawInfoCard = 0x80;
extern void far DisplayCard(unsigned);
void win_DrawInfoWindow(unsigned char flags)
{
    if (flags & 2)
        DisplayCard(drawInfoCard);
}
