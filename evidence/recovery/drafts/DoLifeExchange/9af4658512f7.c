extern unsigned char near LifeA[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern int near MeColor;
extern int near MeDir;
extern int near MeEgg;
extern int near MeHealth;
extern int near MeLocX;
extern int near MeLocY;
extern int near MePlane;
extern int near MeType;
extern int near SpidX;
extern int near SpidY;
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern int far GetDis(int x1, int y1, int x2, int y2);
extern void far AddAntToAList(int life, int column, int state,
                              int attribute, int direction);
extern void far AddAntToBList(int life, int column, int state,
                              int attribute, int direction);
extern void far AddAntToRList(int life, int column, int state,
                              int attribute, int direction);
extern int far GetAntIndex(int list, int index, int far *life,
                           int far *column, int far *attribute,
                           int far *state, int far *direction);
extern void far SetAntIndex(int list, int index, int life, int column,
                            int attribute, int state, int direction);
extern void far SetLife(int plane, int x, int y, int value);
extern void far ResetYellowVars(int plane, int x, int y);
extern void far ZapEuMapAt(int plane, int x, int y);

int far DoLifeExchange(int plane, int x, int y)
{
    int life;
    int oldLife;
    int kind;
    int direction;
    int index;
    int count;
    int oldPlane;
    int oldX;
    int oldY;
    int oldType;
    int oldDirection;
    int oldColor;
    int oldEgg;
    int oldHealth;
    int newX;
    int newY;
    int sourceLife;
    int sourceColumn;
    int sourceAttribute;
    int sourceState;
    int sourceDirection;
    int distance;
    int success;

    success = -1;
    if (plane <= 1) {
        if (x < 0 || x > 0x7f || y < 0 || y > 0x3f)
            return success;
    } else {
        if (x < 0 || x > 0x3f || y < 0 || y > 0x3f)
            return success;
    }

    life = 0;
    if (plane == 1)
        life = LifeA[(x << 6) + y];
    else if (plane == 2)
        life = LifeB[(x << 6) + y];
    else if (plane == 3)
        life = LifeR[(x << 6) + y];
    if (life == 0)
        return success;

    oldPlane = MePlane;
    oldX = MeLocX;
    oldY = MeLocY;
    oldType = MeType;
    oldDirection = MeDir;
    oldColor = MeColor;
    oldEgg = MeEgg;
    oldHealth = MeHealth;
    oldLife = (oldType & 0x78) | (oldDirection & 7);
    kind = (life & 0x78) >> 3;
    direction = life & 7;

    if (plane == 1) {
        distance = GetDis((x << 4) + 8, (y << 4) + 8, SpidX, SpidY);
        if (distance < 0 || distance >= 0x200)
            return 0;
    }

    if (life == 0xff || life == 0xfe) {
        if (kind == 0)
            return 0;
    }
    if (kind <= 0 || kind > 13 || kind == 10 || kind == 11)
        return 0;

    newX = oldX;
    newY = oldY;
    if (plane <= 1) {
        newX = x;
        newY = y;
    } else {
        newX = x;
        newY = y;
    }

    count = 0;
    if (plane <= 1)
        count = 1000;
    else
        count = 500;
    for (index = 0; index < count; ++index) {
        if (GetAntIndex(plane, index, &sourceLife, &sourceColumn,
                        &sourceAttribute, &sourceState, &sourceDirection)) {
            if (sourceLife == x && sourceColumn == y &&
                sourceState == life) {
                oldLife = sourceLife;
                sourceAttribute = kind;
                sourceDirection = direction;
                if (kind == 12) {
                    SetAntIndex(plane, index, sourceLife, sourceColumn,
                                sourceAttribute, sourceState, sourceDirection);
                }
                break;
            }
        }
    }

    ZapEuMapAt(oldPlane, oldX, oldY);
    if (oldType == 0x60) {
        ZapEuMapAt(oldPlane, oldX + Dx8[oldDirection ^ 4],
                   oldY + Dy8[oldDirection ^ 4]);
    }
    ZapEuMapAt(plane, x, y);

    if (plane <= 1) {
        AddAntToAList(oldX, oldY, oldLife, oldType, oldDirection);
        SetLife(plane, x, y, 0xff);
    } else if (plane == 2) {
        AddAntToBList(oldX, oldY, oldLife, oldType, oldDirection);
        SetLife(plane, x, y, 0xff);
    } else {
        AddAntToRList(oldX, oldY, oldLife, oldType, oldDirection);
        SetLife(plane, x, y, 0xff);
    }

    if (kind == 12) {
        SetLife(plane, x + Dx8[direction ^ 4],
                y + Dy8[direction ^ 4], 0xfe);
        SetAntIndex(plane, index, oldLife, sourceColumn,
                    sourceAttribute, sourceState, sourceDirection);
    }
    ResetYellowVars(plane, x, y);

    MeLocX = newX;
    MeLocY = newY;
    MePlane = plane;
    MeType = (kind << 3) | (life & 0x80);
    MeDir = direction;
    MeColor = oldColor;
    MeEgg = oldEgg;
    MeHealth = oldHealth;
    success = 1;
    return success;
}
