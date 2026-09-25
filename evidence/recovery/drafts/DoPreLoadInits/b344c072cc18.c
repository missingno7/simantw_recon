/* NE selector slots C174..C17A resolve PACK. Exact MAPSYM names identify
 * JustXfered and three 32-bit values. Clear the timing values, initialize
 * TimeTemp to 300 and then randomize the yard. No synthetic struct padding.
 */
extern int far JustXfered;
extern unsigned long far LastThemeTime;
extern unsigned long far TimeTemp;
extern unsigned long far EditMsgDelay;
extern void far RandYard(void);
void DoPreLoadInits(void)
{
    JustXfered = 1;
    LastThemeTime = 0;
    TimeTemp = 300;
    EditMsgDelay = 0;
    RandYard();
}
