/*
 * Zero-initialized rendering and simulation state in PACK.  The history,
 * temporary population, help-file and draw-hook spans use the admitted array
 * element types and counts; point and string references retain their typed
 * forms even though their initial values are null or zero.
 */
struct StrPos {
    int x;
    int y;
};

typedef void (far *Hook)(void);

int __based(__segname("PACK")) WantSpiderBalloon = 0;
int __based(__segname("PACK")) MeDropAlarm = 0;
int __based(__segname("PACK")) Cycle = 0;
int __based(__segname("PACK")) YDMapFlip = 0;
int __based(__segname("PACK")) oldMusicOn = 0;
int __based(__segname("PACK")) ShowPercentMode = 0;
int __based(__segname("PACK")) Barrier = 0;
int __based(__segname("PACK")) RedPlane = 0;
int __based(__segname("PACK")) H_RPop[64] = {0};
char far * __based(__segname("PACK")) FontNameStrs = 0;
void (far * __based(__segname("PACK")) shiftMaskPutRtn)(void) = 0;
int __based(__segname("PACK")) StrategicModeR = 0;
struct StrPos __based(__segname("PACK")) lastStrPos = {0, 0};
long __based(__segname("PACK")) triBoundMaxD = 0L;
int __based(__segname("PACK")) hScrollMax = 0;
int __based(__segname("PACK")) BlkWarnHealth = 0;
int __based(__segname("PACK")) win_numOfGroups = 0;
long __based(__segname("PACK")) BAntsEaten = 0L;
char far * __based(__segname("PACK")) SpiderMsgs = 0;
unsigned long __based(__segname("PACK")) GameTime = 0UL;
char __based(__segname("PACK")) helpFile[256] = {0};
int __based(__segname("PACK")) Scycle2 = 0;
int __based(__segname("PACK")) EatCnt = 0;
int __based(__segname("PACK")) DogPx = 0;
Hook __based(__segname("PACK")) win_drawHooks[45] = {0};
int __based(__segname("PACK")) GlobalKey = 0;
