/*
 * PACK's zeroed history series, map prompt references and open-database
 * records.  The history arrays are 64 signed samples each; the database
 * entries use the recovered 0x7c-byte record layout, so this 496-byte public
 * span contains four complete records.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

struct MapPoint {
    int x;
    int y;
};

struct WindPromptTable;

struct OpenDB {
    char name[0x50];
    void far *indexTable;
    int recordCount;
    unsigned char pad1[0x6c - 0x56];
    int count;
    long freeBytes;
    long wastedBytes;
    int pad2;
    int file;
    int dirty;
};

int __based(__segname("PACK")) hHelpCursor = 0;
long __based(__segname("PACK")) triBoundRun = 0L;
struct Rect __based(__segname("PACK")) spiderRect = {0, 0, 0, 0};
int __based(__segname("PACK")) FoodR = 0;
int __based(__segname("PACK")) DeathCnt = 0;
int __based(__segname("PACK")) custIdNumStrHandle = 0;
int __based(__segname("PACK")) MeCrazyCnt = 0;
int __based(__segname("PACK")) gInBackground = 0;
char far * __based(__segname("PACK")) HistGraphStrs = 0;
int __based(__segname("PACK")) ChaseSpid = 0;
int __based(__segname("PACK")) MeTargLife = 0;
int __based(__segname("PACK")) UDMapFlip = 0;
int __based(__segname("PACK")) BoyMsgOffset = 0;
int __based(__segname("PACK")) LastSMode = 0;
struct MapPoint __based(__segname("PACK")) RMapPnt = {0, 0};
int __based(__segname("PACK")) H_BPop[64] = {0};
struct WindPromptTable far * __based(__segname("PACK")) WindPromptStrs = 0;
long __based(__segname("PACK")) CatDelay = 0L;
int __based(__segname("PACK")) H_FoodA[64] = {0};
int __based(__segname("PACK")) EatCountB = 0;
int __based(__segname("PACK")) FightBalloonCnt = 0;
int __based(__segname("PACK")) LastEggPlane = 0;
struct OpenDB __based(__segname("PACK")) openDBData[4] = {0};
