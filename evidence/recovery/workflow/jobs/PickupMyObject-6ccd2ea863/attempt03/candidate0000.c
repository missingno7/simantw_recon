/*
 * PickupMyObject: try to pick up whatever is at (plane, x, y) for the
 * player's ant. If MeType has bit 8 set (busy), fail immediately. If the
 * ant is idle (MeType==0x10) or too weak to carry (MeHealth<10), look
 * for an egg there via FindEggAt (far out-parameter gives the ant-list
 * index, the return value the egg's value/handle); MeEggCarried is
 * pre-set to the sentinel 0xfd. On success, SetAntIndex clears that
 * list slot, SetLife clears the cell when it isn't the ant's own tile,
 * and a weak ant just records MeFoodInType=3 and returns true, while a
 * healthy ant plays the pickup sound, records MeEggCarried and
 * MeType=8 (carrying an egg), and returns the egg value. Otherwise (no
 * egg found, or the gate above didn't apply), fall back to
 * PickupMyRock then PickupMyFood, returning whichever succeeds.
 */
extern int near MeType;
extern int near MeHealth;
extern int near MeLocX;
extern int near MeLocY;
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define MeEggCarried (*(int far *)&AT(0x8a6a))
#define MeFoodInType (*(int far *)&AT(0x8a6e))

extern int far FindEggAt(int far *outIndex, int plane, int x, int y);
extern void far SetAntIndex(int list, int index, int life, int column, int attribute, int state, int direction);
extern void far SetLife(int plane, int x, int y, int code);
extern void far myBeginSound(int id, int a, int b);
extern int far PickupMyRock(int plane, int x, int y);
extern int far PickupMyFood(int plane, int x, int y);

int far PickupMyObject(int plane, int x, int y)
{
    int eggIndex;
    int result;

    if (MeType & 8)
        return 0;
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
                return result;
            }
            MeFoodInType = 3;
            return 1;
        }
    }
    result = PickupMyRock(plane, x, y);
    if (result == 0)
        result = PickupMyFood(plane, x, y);
    return result;
}
