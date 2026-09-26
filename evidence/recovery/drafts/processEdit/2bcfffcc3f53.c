struct EditEvent {
    unsigned char pad0[6];
    unsigned int flags;
    int x;
    int y;
};
extern int near MapPlane;
extern int near MePlane;
extern int near MeColor;
extern int near MeType;
extern int near tileWidth;
extern int near tileHeight;
extern int far MapPnt;
extern int far editTileRect[4];
extern int far CurGameType;
extern int far MeMode;
extern int far MeCmd;
extern int far MeTargLifePlane;
extern int far MeTargLifeX;
extern int far MeTargLifeY;
extern int far MeGoalPlane;
extern int far MeGoalX;
extern int far MeGoalY;
extern int far MeCrazyCnt;
extern int far MeMoveMe;
extern int far MeColorState;
extern int far GetLife(int plane, int x, int y);
extern int far GetMap(int plane, int x, int y);
extern int far IsYellowAnt(int ant);
extern int far FindAntIndex(int list, int life, int column, int attribute);
extern int far IsItDigable(int map);
extern int far IsItGrass(int map);
extern int far IsLiftable(int map);
extern void far MagnifyMenu(int x, int y, int plane);
extern unsigned long far TickCount(void);
extern void far UpdateEdit(void);
extern void far WinPrintf(char far *format, ...);
extern int far win_IsWinInFront(int window);
extern int far processExp(int tool);
extern void far CenterAnt(int plane, int x, int y);
extern void far myButton(int plane, int x, int y, int button);
extern void far AntMenu(int x, int y, int plane);
extern void far ExchangeLives(int plane, int x, int y);
extern void far processSpider(int x, int y, int plane);

void far processEdit(struct EditEvent far *event)
{
    int x;
    int y;
    int map;
    int life;
    int tool;
    int ant;
    int button;

    if (event == 0)
        return;
    if ((event->flags & 0x6000) != 0)
        return;
    if (win_IsWinInFront(0) == 0)
        return;

    x = (event->x - editTileRect[0]) / tileWidth + MapPnt;
    y = (event->y - editTileRect[1]) / tileHeight + MapPnt;
    tool = CurGameType;
    map = GetMap(MapPlane, x, y);
    life = GetLife(MapPlane, x, y);

    if (tool == 3) {
        MagnifyMenu(x, y, MapPlane);
        return;
    }

    if (MeMode != 0) {
        MeMode = 0;
        UpdateEdit();
    }
    if (MePlane == 2) {
        ExchangeLives(MapPlane, x, y);
        return;
    }

    ant = FindAntIndex(MapPlane, life, x, y);
    if (IsYellowAnt(ant)) {
        MeTargLifePlane = MapPlane;
        MeTargLifeX = x;
        MeTargLifeY = y;
        MeCmd = 2;
        UpdateEdit();
        return;
    }

    if (IsItDigable(map)) {
        MeGoalPlane = MapPlane;
        MeGoalX = x;
        MeGoalY = y;
        MeCrazyCnt = -2;
        MeCmd = 1;
        MeMoveMe = 1;
    } else if (IsLiftable(map)) {
        MeGoalPlane = MapPlane;
        MeGoalX = x;
        MeGoalY = y;
        MeCrazyCnt = -2;
        MeCmd = 0;
    } else if (IsItGrass(map)) {
        CenterAnt(MapPlane, x, y);
    } else {
        button = (event->flags & 1) != 0;
        if (button)
            myButton(MapPlane, x, y, button);
        else
            AntMenu(x, y, MapPlane);
    }
    TickCount();
    UpdateEdit();
}
