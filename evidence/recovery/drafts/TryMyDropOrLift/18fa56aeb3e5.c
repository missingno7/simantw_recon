/* Semantic hypothesis: dispatch drops by carried-object type, then try egg
 * recovery or object pickup. The target call graph and named global operands
 * supply these actions and state changes. */
extern int near MeType;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeHealth;
extern int near MePlane;
extern int far MeEggCarried;
extern int far MeFoodInType;
extern int far CommandKey;
extern int far MeNestStarted;
extern int near DropMyEgg(int, int, int, int, int);
extern int near DropMyFood(int, int, int, int, int);
extern int near DropMyRock(int, int, int, int, int);
extern int near PickupMyRock(int, int, int);
extern int near PickupMyFood(int, int, int);
extern void far EnterNest(void);
extern void far GotoMyAnt(void);
extern int near FindEggAt(int far *, int, int, int);
extern void near SetAntIndex(int, int, int, int, int, int, int);
extern void near SetLife(int, int, int, int);
extern void far myBeginSound(unsigned int, unsigned int, unsigned int);
extern void far MoveMyLife(int, int, int, int, int);
extern void far DoEditUpdateDraw(void);
extern void near EatMyFood(int);
extern int near DigMyNewHole(int, int);
extern int near GetDir(int, int, int, int);

int far TryMyDropOrLift(int plane, int x, int y)
{
    int type;
    int eggIndex;
    int oldX;
    int oldY;
    int result;
    int egg;
    int direction;

    type = MeType;
    if (type & 8) {
        oldX = MeLocX;
        oldY = MeLocY;
        switch (type) {
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
        return result == 1;
    }

    if (MeType == 0x10 || MeHealth < 10) {
        MeEggCarried = 0xfd;
        egg = FindEggAt(&eggIndex, plane, x, y);
        if (egg >= 0) {
            SetAntIndex(plane, eggIndex, 0, 0, 0, 0, 0);
            if (x != MeLocX || y != MeLocY)
                SetLife(plane, x, y, 0);
            if (MeHealth < 10) {
                MeFoodInType = 3;
                return 1;
            }
            myBeginSound(0x1c, 0, 0x7e);
            MeEggCarried = egg;
            MeType = 8;
            return 1;
        }
    }

    result = PickupMyRock(plane, x, y);
    if (result == 0)
        result = PickupMyFood(plane, x, y);
    if (result != 0) {
        direction = GetDir(MeLocX, MeLocY, x, y);
        if (direction > 0)
            MoveMyLife(MePlane, MeLocX, MeLocY, MeType, direction - 1);
        DoEditUpdateDraw();
        if (MeFoodInType >= 0) {
            EatMyFood(MeFoodInType);
            MeFoodInType = -1;
        }
        return 1;
    }

    if (CommandKey == result) {
        if (MeType != 0x40)
            return 0;
        if (MeNestStarted != result)
            return 0;
    }
    if (MePlane != 1 || x != MeLocX || y != MeLocY)
        return 0;
    if (DigMyNewHole(x, y) == 0)
        return -1;
    EnterNest();
    GotoMyAnt();
    return 1;
}


