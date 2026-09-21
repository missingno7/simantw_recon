/*
 * KillSomeAnts: walk the A list from the top index down and kill up to 50
 * ants whose type byte (bit 7 clear = not already dead) matches the mode.
 * mode 1 kills every live ant unconditionally; any other mode only kills
 * ants that IsItYellow reports as not yellow.  A killed ant's type byte is
 * cleared through a pointer taken once per ant, and DeadAntHere is notified.
 * CompactListA and FullCount run once on exit.
 */
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define AlistY(i) AT((i) + 0x278e)
#define AlistX(i) AT((i) + 0x23a4)
extern int far ListIndexA;

extern void far DeadAntHere(int x, int y, int mode);
extern int far IsItYellow(int x, int y, int mode);
extern void far CompactListA(void);
extern void far FullCount(void);

void far KillSomeAnts(int mode)
{
    int i;
    int n;
    unsigned char far *p;
    int type;

    n = 0;
    i = ListIndexA;
    while (--i >= 0) {
        p = &AT(i + 0x2f62);
        type = *p;
        if (mode == 1) {
            if (!(type & 0x80)) {
                DeadAntHere(AlistX(i), AlistY(i), 0);
                *p = 0;
                if (++n > 50)
                    break;
            }
        } else {
            if (type & 0x80) {
                if (!IsItYellow(AlistX(i), AlistY(i), 1)) {
                    DeadAntHere(AlistX(i), AlistY(i), 1);
                    *p = 0;
                    if (++n > 50)
                        break;
                }
            }
        }
    }
    CompactListA();
    FullCount();
}
