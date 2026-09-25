/*
 * PACK population histories and simulation coordinates.  The four health/death
 * series are 64-word arrays; named map positions are two-coordinate records,
 * and timing/expiration counters retain 32-bit widths.
 */
struct BitmapSize {
    int width;
    int height;
};

struct MapPoint {
    int x;
    int y;
};

struct BitmapSize __based(__segname("PACK")) win_sliderIconSize = {0, 0};
unsigned long __based(__segname("PACK")) EditMsgDelay = 0UL;
int __based(__segname("PACK")) SaveGamePaused = 0;
int __based(__segname("PACK")) FoodB = 0;
int __based(__segname("PACK")) SimAntClientNum = 0;
int __based(__segname("PACK")) DdPtr = 0;
int __based(__segname("PACK")) EggBalloonIndex = 0;
int __based(__segname("PACK")) H_PDead[64] = {0};
struct MapPoint __based(__segname("PACK")) AMapPnt = {0, 0};
int __based(__segname("PACK")) H_BHeal[64] = {0};
int __based(__segname("PACK")) LessonTemp = 0;
struct MapPoint __based(__segname("PACK")) BMapPnt = {0, 0};
struct MapPoint __based(__segname("PACK")) LastFightPnt = {0, 0};
int __based(__segname("PACK")) TileMassXR = 0;
long __based(__segname("PACK")) BirdDelay = 0L;
long __based(__segname("PACK")) leftYSlope = 0L;
int __based(__segname("PACK")) spiderTileTop = 0;
long __based(__segname("PACK")) RAntsExpired = 0L;
