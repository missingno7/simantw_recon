struct MouseEvent {
    int pad[4];
    int x;
    int y;
};
struct WinRect { int left; int top; int right; int bottom; };
struct MapPoint { int x; int y; };

extern int near MapPlane;
extern int near MePlane;
extern const int near MeColor;

extern int near tileWidth;
extern int near tileHeight;
extern struct MapPoint far MapPnt;
extern struct WinRect far editTileRect;
extern int far CurGameType;
extern int far MeMode;
extern int far MeCmd;
extern int far MeTargIndex;
extern int far MeTargLife;
extern int far MeTargLifePlane;
extern int far MeTargLifeX;
extern int far MeTargLifeY;
extern int far MeGoalPlane;
extern int far MeGoalX;
extern int far MeGoalY;
extern int far MeCrazyCnt;
extern int far MeMoveMe;
extern int near MeType;

/* Candidate names for the two still-unmapped private dispatch words. */
extern int far editDispatchLatch;
extern int far editDispatchState;

extern int far GetLife(int plane, int x, int y);
extern int far GetMap(int plane, int x, int y);
extern int far IsItYellow(int plane, int x, int y);
extern int far IsYellowAnt(int ant);
extern int far FindAntIndex(int list, int x, int y, int life);
extern int far IsItDigable(int plane, int x, int y);
extern int IsThisGrass(int category, int tile);

extern int far IsLiftable(int plane, int x, int y);
extern int far MagnifyMenu(int x, int y, int plane);

extern long far TickCount(void);
extern void far UpdateEdit(void);
extern void far WinPrintf(char far *format, ...);
extern int far win_IsWinInFront(int window);
extern void far processExp(int x, int y, int special);
extern void near CenterAnt(void);
extern int near myButton(void);
extern int far AntMenu(volatile struct MouseEvent far *pt);

extern void far ExchangeLives(int plane, int x, int y);
extern void near processSpider(int x, int y, int mode);
extern int far pascal GetAsyncKeyState(int key);


void far processEdit(struct MouseEvent far * volatile event)
{
    unsigned int eventFlags;
    int special;
    long deadline;
    long now;
    int x;
    int y;
    int life;
    int tile;
    int index;
    int goalPlane;
    int command;

    eventFlags = event->pad[3];
    special = (eventFlags & 0x6000) != 0;
    WinPrintf("%x", eventFlags);

    if (special == 0) {
        if (win_IsWinInFront(0) == 0)
            return;
        deadline = TickCount() + 6L;
        do {
            now = TickCount();
        } while (now < deadline);
    }

    x = (event->x - editTileRect.left) / tileWidth + MapPnt.x;
    y = (event->y - editTileRect.top) / tileHeight + MapPnt.y;

    if (CurGameType == 3) {
        processExp(x, y, special);
        return;
    }

    if (editDispatchLatch != 0)
        editDispatchLatch = 0;

    switch (editDispatchState) {
    case -1:
        break;
    case 10:
        UpdateEdit();
        goalPlane = MapPlane;
        if (goalPlane == 0)
            goalPlane = 1;
        ExchangeLives(goalPlane, x, y);
        return;
    case 11:
        if (MapPlane <= 1 && MeMode == 1)
            processSpider(x, y, special);
        return;
    default:
        return;
    }

    if (special == 0) {
        if (IsItYellow(MePlane, x, y) == 1) {
            if (myButton() == 1 &&
                (GetAsyncKeyState(0x10) & 0x8000) == 0) {
                AntMenu(event);
                return;
            }
        }

        life = GetLife(MePlane, x, y);
        if (life == 0xfe)
            return;
        CenterAnt();

        if (myButton() == 1 &&
            (GetAsyncKeyState(0x10) & 0x8000) == 0) {
            if (MagnifyMenu(x, y, MapPlane) >= 0)
                return;
        }
    } else if (MeMode == 0) {
        life = GetLife(MapPlane, x, y);
        if (life >= 0 && (life & 0x7f) < 8 && IsYellowAnt(life)) {
            index = FindAntIndex(MapPlane, x, y, life);
            MeTargIndex = index;
            if (index < 0)
                return;

            MeTargLife = life;
            MeTargLifePlane = MapPlane;
            if (MapPlane == 0)
                MeTargLifePlane = 1;
            MeTargLifeX = x;
            MeTargLifeY = y;
            if (((MeColor ^ life) & 0x80) != 0)
                MeCmd = 3;
            else
                MeCmd = 4;

            goalPlane = MapPlane;
            if (goalPlane == 0)
                goalPlane = 1;
            MeGoalPlane = goalPlane;
            MeGoalX = x;
            MeGoalY = y;
            MeCrazyCnt = -2;

            if (goalPlane >= 2 || y >= 2) {
                MeMoveMe = 1;
                return;
            }
            if (x <= 0)
                x = 1;
            else if (x >= 0x3f)
                x = 0x3e;
            MeGoalX = x;
            MeMoveMe = 1;
            return;
        }
    }

    if (MapPlane <= 1) {
        if (MeMode == 1) {
            processSpider(x, y, special);
            return;
        }

        MeCmd = special;
        goalPlane = MapPlane;
        if (goalPlane == 0)
            goalPlane = 1;
        MeGoalPlane = goalPlane;
        MeGoalX = x;
        MeGoalY = y;
        MeCrazyCnt = -2;
        if (goalPlane >= 2 || y >= 2) {
            MeMoveMe = 1;
            return;
        }
        if (x <= 0)
            x = 1;
        else if (x >= 0x3f)
            x = 0x3e;
        MeGoalX = x;
        MeMoveMe = 1;
        return;
    }

    if (MeMode != 0) {
        if (MeMode == 1)
            processSpider(x, y, special);
        return;
    }

    if (special != 0) {
        if (IsItDigable(MapPlane, x, y) == 1) {
            MeCmd = 2;
        } else if (MePlane < 2 && y <= 0) {
            MeCmd = 2;
        } else {
            tile = GetMap(MapPlane, x, y);
            if (IsThisGrass(MapPlane, tile) == 1) {
                MeCmd = 2;
            } else if ((MeType & 8) != 0 || IsLiftable(MapPlane, x, y)) {
                MeCmd = 1;
            } else {
                MeCmd = 2;
            }
        }
    } else {
        MeCmd = 0;
    }

    command = MeCmd;
    goalPlane = MapPlane;
    if (goalPlane == 0)
        goalPlane = 1;
    MeGoalPlane = goalPlane;
    MeGoalX = x;
    MeGoalY = y;
    MeCrazyCnt = -2;

    if (goalPlane >= 2 || y >= 2) {
        MeMoveMe = 1;
        return;
    }
    if (x <= 0)
        x = 1;
    else if (x >= 0x3f)
        x = 0x3e;
    MeGoalX = x;
    MeMoveMe = 1;

    if (command == 0) {
        UpdateEdit();
        ExchangeLives(goalPlane, x, y);
    }
}
