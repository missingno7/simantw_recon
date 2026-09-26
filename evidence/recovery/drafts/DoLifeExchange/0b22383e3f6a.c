extern unsigned char __based(__segname("DGROUP")) LifeA[];
extern unsigned char __based(__segname("DGROUP")) LifeB[];
extern unsigned char __based(__segname("DGROUP")) LifeR[];
extern int __based(__segname("DGROUP")) MeColor;
extern int __based(__segname("DGROUP")) MeDir;
extern int __based(__segname("DGROUP")) MeEgg;
extern int __based(__segname("DGROUP")) MeHealth;
extern int __based(__segname("DGROUP")) MeLocX;
extern int __based(__segname("DGROUP")) MeLocY;
extern int __based(__segname("DGROUP")) MePlane;
extern int __based(__segname("DGROUP")) MeType;
extern int __based(__segname("DGROUP")) SpidX;
extern int __based(__segname("DGROUP")) SpidY;
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern char __based(__segname("PACK")) match_position[];
extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;
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
    register int success;

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

    if (plane <= 1)
        count = ListIndexA;
    else if (plane == 2)
        count = ListIndexB;
    else
        count = ListIndexR;
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
    match_position[0x9fe8] = 1;
    match_position[0x7d60] = 0;
    match_position[0x9cf0] = 0;
    if (MeHealth + 0x64 > 10)
        match_position[0x9af2] = 0;
    else
        match_position[0x9af2] = 1;

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
