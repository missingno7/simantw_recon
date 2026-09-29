/*
 * KillSomeAnts: walk the A list from the top index down and kill up to 50
 * ants whose type byte (bit 7 clear = not already dead) matches the mode.
 * mode 1 kills every live ant unconditionally; any other mode only kills
 * ants that IsItYellow reports as not yellow.  A killed ant's type byte is
 * cleared through a pointer taken once per ant, and DeadAntHere is notified.
 * CompactListA and FullCount run once on exit.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
#define AlistYAt(i) (AlistY[i])
#define AlistXAt(i) (AlistX[i])
extern int far ListIndexA;

extern void far DeadAntHere(int x, int y, int mode);
extern int far IsItYellow(int x, int y, int mode);
extern void far CompactListA(void);
extern void far FullCount(void);

void far KillSomeAnts(int mode)
{
    int i;
    register int n;
    unsigned char far *p;
    unsigned char far * near *pp;
    int type;

    CompactListA();
    FullCount();
    n = 0;
    i = ListIndexA;
    if (--i >= 0) {
        do {
        pp = &p;
        *pp = AlistT + i;
        type = **pp;
        if (mode == 1) {
            if (!(type & 0x80)) {
                DeadAntHere(AlistXAt(i), AlistYAt(i), 0);
                **pp = 0;
                if (++n > 50)
                    break;
            }
        } else {
            if (type & 0x80) {
                if (!IsItYellow(AlistXAt(i), AlistYAt(i), 1)) {
                    DeadAntHere(AlistXAt(i), AlistYAt(i), 1);
                    **pp = 0;
                    if (++n > 50)
                        break;
                }
            }
        }
        } while (--i >= 0);
    }
    CompactListA();
    FullCount();
}
