/*
 * ExpAddFood: add food at map cell (x, y).  Normally a single IncFoodHere
 * at the cell plays the food sound when it succeeds.  When experiment
 * sub-state 4 (far ExpSubStates byte) is set the food is scattered
 * instead: the scatter sound plays and twenty random cells within +/-4 of
 * (x, y) each receive food when IsValidLocation accepts them on the
 * current MapPlane.
 */
extern unsigned char far ExpSubStates;
#define SUBSTATE(i) ((&ExpSubStates)[i])
extern int near MapPlane;

extern int far IncFoodHere(int x, int y);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern int far SRand1(int range);
extern int far IsValidLocation(int plane, int x, int y);

void far ExpAddFood(int x, int y)
{
    int i;
    int fx;
    int fy;

    if (SUBSTATE(4) == 0) {
        if (IncFoodHere(x, y))
            myBeginSound(0x1d, 0, 0x7e);
    } else {
        myBeginSound(0x20, 0, 0x7e);
        for (i = 20; i != 0; i--) {
            fx = SRand1(9) + x - 4;
            fy = SRand1(9) + y - 4;
            if (IsValidLocation(MapPlane, fx, fy))
                IncFoodHere(fx, fy);
        }
    }
}
