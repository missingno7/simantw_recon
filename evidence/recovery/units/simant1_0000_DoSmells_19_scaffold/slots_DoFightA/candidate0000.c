/*
 * DoFightA: one tick of a fighting ant in the generic A list (index).  The
 * ant's type byte keeps its caste/colour bits and gets a fresh random
 * direction (SRand1(7)), and the LifeA cell at (x, y) is redrawn with it.
 * One time in sixteen (SRand16() == 0) the fight is decided: the stamina
 * byte (AlistS) becomes the cell's and the ant's new type, the current
 * record's mode (AlistM[Tindex]) is recomputed by GetNewMode(caste, type),
 * the stamina is cleared and DeadAntHere(x, y, colour bit) leaves the loser
 * on the map.  Otherwise, when OptionStates[5] (MAPSYM _OptionStates+10; the candidate had invented a BalloonModeFlag name) is set, fight balloons are
 * drawn.  Only x and y are declared locals; the repeated AlistT[index] and
 * LifeA cell addresses are common subexpressions the compiler keeps in
 * frame temporaries below them.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern unsigned char near LifeA[];
extern int far Tindex;
extern int far OptionStates[];
extern int far SRand1(int range);
extern int far SRand16(void);
extern int far GetNewMode(int caste, int type);
extern void far DeadAntHere(int x, int y, int colour);
extern void far FightBalloons(int x, int y, int plane);

void near DoFightA(int index)
{
    int x;
    int y;

    x = AlistX[index];
    y = AlistY[index];
    AlistT[index] = (AlistT[index] & 0xf8) + SRand1(7);
    LifeA[(x << 6) + y] = AlistT[index];
    if (SRand16() == 0) {
        LifeA[(x << 6) + y] = AlistS[index];
        AlistT[index] = LifeA[(x << 6) + y];
        AlistM[Tindex] = GetNewMode((AlistT[index] & 0x78) >> 3, AlistT[index]);
        AlistS[index] = 0;
        DeadAntHere(x, y, AlistT[index] & 0x80);
    } else if (OptionStates[5] == 1)
        FightBalloons(x, y, 1);
}
