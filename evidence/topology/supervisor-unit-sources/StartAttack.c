/* StartAttack: begin the attack phase - a random delay of 30..129 cycles in
 * JustToBeMean, the attack song, and the advice message pair 10/11.
 *
 * Unit review (simtwo:0000): the isolated candidate had modelled the far words
 * as padded private structs (attackState.attackDelay, attackWindows.message);
 * the objects are the MAPSYM publics JustToBeMean and the AdviceStrs pointer
 * table, exactly as the admitted unit spells them. */
extern unsigned int far JustToBeMean;
extern unsigned int far * far AdviceStrs;
extern int far SRand1(unsigned int range);
extern void far myBeginSong(unsigned int song, unsigned int mode);
extern void far EditMessage(int first, int second, int width, int fourth, int fifth);

void StartAttack(void)
{
    JustToBeMean = SRand1(100) + 30;
    myBeginSong(0x2b0a, 0x3f);
    EditMessage(AdviceStrs[10], AdviceStrs[11], 0x78, 0, 0);
}
