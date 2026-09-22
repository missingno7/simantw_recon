/*
 * PickupMyObject: try to pick up whatever is at (plane, x, y) for the
 * player's ant; returns non-zero when something was picked up.
 *
 * An ant already carrying (MeType bit 8) fails at once.  An idle ant
 * (MeType 0x10) or a weak one (MeHealth < 10) first looks for an egg:
 * MeEggCarried (far word in the ant-state segment) is preset to the 0xfd
 * sentinel and FindEggAt (same-segment far call, far out-parameter for
 * the list index) is asked; a non-negative answer is an egg.  The egg's
 * list slot is cleared with SetAntIndex, the cell is cleared with SetLife
 * unless it is the ant's own cell (exact MAPSYM MeLocX/MeLocY), and a
 * healthy ant plays the pickup sound (myBeginSound, cross-segment far
 * call), records the egg in MeEggCarried and switches MeType to 8
 * (carrying an egg) while a weak ant only records MeFoodInType = 3; in
 * both cases the result is TRUE.  Without an egg (or when the gate did
 * not apply) the result is FALSE and the rock and then the food pickup
 * are tried in turn (PickupMyRock, PickupMyFood, same-segment far
 * calls), whichever succeeds first.  The far state words each load
 * their own selector (MeEggCarried first, MeFoodInType later).
 */
extern int near MeType;
extern int near MeHealth;
extern int near MeLocX;
extern int near MeLocY;
extern int far MeEggCarried;
extern int far MeFoodInType;

extern int far FindEggAt(int far *outIndex, int plane, int x, int y);
extern void far SetAntIndex(int list, int index, int life, int column, int attribute, int state, int direction);
extern void far SetLife(int plane, int x, int y, int code);
extern void far myBeginSound(int id, int a, int b);
extern int far PickupMyRock(int plane, int x, int y);
extern int far PickupMyFood(int plane, int x, int y);

#define TRUE 1
#define FALSE 0

int far PickupMyObject(int plane, int x, int y)
{
    int eggIndex;
    int result;

    if (MeType & 8)
        return FALSE;
    if (MeType == 0x10 || MeHealth < 10) {
        MeEggCarried = 0xfd;
        result = FindEggAt(&eggIndex, plane, x, y);
        if (result >= 0) {
            SetAntIndex(plane, eggIndex, 0, 0, 0, 0, 0);
            if (x != MeLocX || y != MeLocY)
                SetLife(plane, x, y, 0);
            if (MeHealth >= 10) {
                myBeginSound(0x1c, 0, 0x7e);
                MeEggCarried = result;
                MeType = 8;
            } else {
                MeFoodInType = 3;
            }
            result = TRUE;
        } else {
            result = FALSE;
        }
    } else {
        result = FALSE;
    }
    if (result == FALSE) {
        result = PickupMyRock(plane, x, y);
        if (result == FALSE)
            result = PickupMyFood(plane, x, y);
    }
    return result;
}
