/*
 * PACK census, balloon and colony state.  The temporary red-mode population
 * and pillar map are word arrays, six balloon messages are far string
 * pointers, and the census scratch table is a 64-entry byte table.
 */
struct MapPoint {
    int x;
    int y;
};

int __based(__segname("PACK")) TemRModePop[20] = {0};
int __based(__segname("PACK")) custIDStrHandle = 0;
int __based(__segname("PACK")) PillarMap[6] = {0};
struct MapPoint __based(__segname("PACK")) modeKnobPnt = {0, 0};
long __based(__segname("PACK")) TotalEggsDiedB = 0L;
int __based(__segname("PACK")) CurGameTool = 0;
char far * __based(__segname("PACK")) CurBalloonMsgs[6] = {0};
int __based(__segname("PACK")) WantQueenBalloon = 0;
void far * __based(__segname("PACK")) lastAddedPtr = 0;
int __based(__segname("PACK")) ncbTail = 0;
unsigned int __based(__segname("PACK")) FlyAwayB = 0;
int __based(__segname("PACK")) LastRestPlane = 0;
int __based(__segname("PACK")) TileMassXB = 0;
int __based(__segname("PACK")) casteAnimHandle = 0;
int __based(__segname("PACK")) OrigVolNum = 0;
unsigned char __based(__segname("PACK")) TemCensus[64] = {0};
int __based(__segname("PACK")) EatCountR = 0;
int __based(__segname("PACK")) TileMassYB = 0;
int __based(__segname("PACK")) BoyIsMowing = 0;
char far * __based(__segname("PACK")) AdviceStrs = 0;
int __based(__segname("PACK")) H_BFood[64] = {0};
