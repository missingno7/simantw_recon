/* drawInfoCard is the shared based anchor at segment-8 offset A456.
   The two companion words are the measured fields 17 and 1 words before it. */
static unsigned __based(__segname("SIMANT_DATA_GROUP")) drawInfoCard = 0x80;
extern int far win_IsWinOpen(int window);
extern void far win_Open(int flags);
void far OpenInfoWindow(void)
{
    if (!win_IsWinOpen(0x500)) {
        drawInfoCard = 0x80;
        (&drawInfoCard)[-17] = 0x80;
        (&drawInfoCard)[-1] = 0;
    }
    win_Open(0x500);
}
