/* Semantic hypothesis: when carrying a movable object, drop it through the
 * matching DropMy* routine. Otherwise process nest entry, pickup, egg transfer,
 * or food consumption at the selected square. The named globals and calls
 * come from the inspection packet and adjacent admitted routines. */
extern int near MeType;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeHealth;
extern int near MePlane;
extern int far MeEggCarried;
extern int far MeFoodInType;
extern int far CommandKey;
extern int far MeNestStarted;
extern int far DropMyEgg(int, int, int, int, int);
extern int far DropMyFood(int, int, int, int, int);
extern int far DropMyRock(int, int, int, int, int);
extern int far PickupMyRock(int, int, int);
extern int far PickupMyFood(int, int, int);
extern int far EnterNest(void);
extern void far GotoMyAnt(void);
extern int far FindEggAt(int far *, int, int, int);
extern void far SetAntIndex(int, int, int, int, int, int, int);
extern void far SetLife(int, int, int, int);
extern void far myBeginSound(unsigned int, unsigned int, unsigned int);
extern void far MoveMyLife(int, int, int, int, int);
extern void far DoEditUpdateDraw(void);
extern void far EatMyFood(int);
extern int near IsClear3x3(int, int);
extern int near IsLiftable(int, int, int);

int far TryMyDropOrLift(int plane, int x, int y)
{
    int oldX;
    int oldY;
    int result;
    int eggIndex;
    int egg;
    int direction;

    if (MeType & 8) {
        oldX = MeLocX;
        oldY = MeLocY;
        switch (MeType) {
        case 8:
            result = DropMyEgg(plane, oldX, oldY, x, y);
            break;
        case 0x18:
        case 0x38:
            result = DropMyFood(plane, oldX, oldY, x, y);
            break;
        case 0x28:
        case 0x48:
            result = DropMyRock(plane, oldX, oldY, x, y);
            break;
        default:
            result = 0;
            break;
        }
        if (result == 1)
            return 1;
        return 0;
    }

    if (MeType == 0x10 || MeHealth >= 10) {
        EnterNest();
        GotoMyAnt();
        return 1;
    }

    result = PickupMyRock(plane, x, y);
    if (result == 0)
        result = PickupMyFood(plane, x, y);
    if (result != 0) {
        direction = IsLiftable(plane, MeLocX, MeLocY);
        if (direction <= 0)
            return 0;
        MoveMyLife(plane, MeLocX, MeLocY, MeType, direction - 1);
        DoEditUpdateDraw();
        if (MeFoodInType >= 0) {
            EatMyFood(MeFoodInType);
            MeFoodInType = -1;
            return 1;
        }
        return 1;
    }

    if (CommandKey == 0 && MeType != 0x40 && MeNestStarted == 0)
        return 0;
    if (plane != 1 || x != MeLocX || y != MeLocY)
        return 0;
    if (IsClear3x3(x, y) == 0)
        return 0;
    EnterNest();
    GotoMyAnt();
    return 1;
}
