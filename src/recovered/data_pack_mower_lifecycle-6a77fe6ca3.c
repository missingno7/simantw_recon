/*
 * PACK colony-life, mower and fight state.  Caste knob and tile rectangles
 * are coordinate records, error/window messages are character buffers, and
 * elapsed-life counters keep their 32-bit storage width.
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

long __based(__segname("PACK")) triBoundDSlope = 0L;
int __based(__segname("PACK")) ListIndexB = 0;
unsigned int __based(__segname("PACK")) triWidthR = 0;
int __based(__segname("PACK")) WaterTable = 0;
int __based(__segname("PACK")) BoyMessOn = 0;
struct MapPoint __based(__segname("PACK")) casteKnobPnt = {0, 0};
long __based(__segname("PACK")) BAntsKilled = 0L;
int __based(__segname("PACK")) MeTargIndex = 0;
int __based(__segname("PACK")) SwarmDelayB = 0;
int __based(__segname("PACK")) MeTargLifeX = 0;
int __based(__segname("PACK")) MeTargLifeY = 0;
char __based(__segname("PACK")) MwinStr[256] = {0};
int __based(__segname("PACK")) LastFightPlane = 0;
void far * __based(__segname("PACK")) initialMemory = 0;
int __based(__segname("PACK")) MeWantFood = 0;
int __based(__segname("PACK")) MowX = 0;
int __based(__segname("PACK")) ExpCursAnimCycle = 0;
long __based(__segname("PACK")) TotalEggsLaidB = 0L;
int __based(__segname("PACK")) MowY = 0;
int __based(__segname("PACK")) WantEggBalloon = 0;
int __based(__segname("PACK")) UDcntr = 0;
char far * __based(__segname("PACK")) FilErrStr = 0;
int __based(__segname("PACK")) tilesInA = 0;
struct Rect __based(__segname("PACK")) editTileRect = {0, 0, 0, 0};
unsigned long __based(__segname("PACK")) TimeTemp = 0UL;
int __based(__segname("PACK")) CurFightPlane = 0;
int __based(__segname("PACK")) tilesInB = 0;
int __based(__segname("PACK")) iniDrive = 0;
long __based(__segname("PACK")) gScrollDirection = 0L;
int __based(__segname("PACK")) PillDir = 0;
int __based(__segname("PACK")) toofar = 0;
int __based(__segname("PACK")) HouseColonies = 0;
int __based(__segname("PACK")) tilesInC = 0;
long __based(__segname("PACK")) BAntsExpired = 0L;
int __based(__segname("PACK")) tilesInD = 0;
