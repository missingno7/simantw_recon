/*
 * PACK combat positions, map geometry and counters.  The six balloon points
 * and three mode vertices are coordinate records, map rectangles keep four
 * edges, and callback/string slots use far pointers.
 */
struct MapPoint {
    int x;
    int y;
};

struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

typedef void (far *CopyRectProc)(void);

int __based(__segname("PACK")) RedLocX = 0;
int __based(__segname("PACK")) StargLife = 0;
int __based(__segname("PACK")) MePrevDis = 0;
int __based(__segname("PACK")) RedLocY = 0;
long __based(__segname("PACK")) triBoundRise = 0L;
int __based(__segname("PACK")) gScrollPartCode = 0;
int __based(__segname("PACK")) CurGameType = 0;
CopyRectProc __based(__segname("PACK")) copyRectRtn = 0;
int __based(__segname("PACK")) LastThemeSong = 0;
unsigned char __based(__segname("PACK")) LionListY[10] = {0};
int __based(__segname("PACK")) MeGoalX = 0;
unsigned int __based(__segname("PACK")) CurCheat[4] = {0};
int __based(__segname("PACK")) triHeight = 0;
int __based(__segname("PACK")) MeGoalY = 0;
int __based(__segname("PACK")) BColoniesStarted = 0;
struct MapPoint __based(__segname("PACK")) CurBalloonPnts[6] = {0};
int __based(__segname("PACK")) popUpMenuId = 0;
int __based(__segname("PACK")) ListIndexA = 0;
int __based(__segname("PACK")) custRegHandle = 0;
struct MapPoint __based(__segname("PACK")) LastEggPnt = {0, 0};
struct MapPoint __based(__segname("PACK")) modeVerts[3] = {0};
long __based(__segname("PACK")) TileTotXB = 0L;
char far * __based(__segname("PACK")) EggMsgs = 0;
int __based(__segname("PACK")) RainCnt = 0;
int __based(__segname("PACK")) RFightBalloonIndex = 0;
struct Rect __based(__segname("PACK")) mapTileRect = {0, 0, 0, 0};
int __based(__segname("PACK")) LastColonyPopR = 0;
long __based(__segname("PACK")) TileTotYB = 0L;
unsigned long __based(__segname("PACK")) BFightBalloonTicks = 0UL;
int __based(__segname("PACK")) QueenBalloonCnt = 0;
