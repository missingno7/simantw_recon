/*
 * Ant editing and simulation state, followed by seven bookmark records and
 * the matching ribbon-button help identifiers.
 */
int __based(__segname("SIMANT_DATA_GROUP")) MakeMe = 2;
int __based(__segname("SIMANT_DATA_GROUP")) ModeMe = 2;
int __based(__segname("SIMANT_DATA_GROUP")) RevSpider = 0;
int __based(__segname("SIMANT_DATA_GROUP")) Invincible = 0;
int __based(__segname("SIMANT_DATA_GROUP")) NeverHungry = 0;
int __based(__segname("SIMANT_DATA_GROUP")) AlwaysHealthy = 0;
int __based(__segname("SIMANT_DATA_GROUP")) NextFeed = 40;
int __based(__segname("SIMANT_DATA_GROUP")) RedInitOn = 0;
int __based(__segname("SIMANT_DATA_GROUP")) ClearRainFlag = 0;
int __based(__segname("SIMANT_DATA_GROUP")) ColonyUpdateFlag = 1;
int __based(__segname("SIMANT_DATA_GROUP")) MeEggCarried = 0x00fd;
int __based(__segname("SIMANT_DATA_GROUP")) MeNestStarted = 0;
int __based(__segname("SIMANT_DATA_GROUP")) MeFoodInType = -1;
int __based(__segname("SIMANT_DATA_GROUP")) BoyWait = 20;
int __based(__segname("SIMANT_DATA_GROUP")) BoyDir = 2;
int __based(__segname("SIMANT_DATA_GROUP")) BoyTurnCnt = 12;
int __based(__segname("SIMANT_DATA_GROUP")) BxTab[2] = { 0x0604, 0xfafc };
int __based(__segname("SIMANT_DATA_GROUP")) ByTab[2] = { 0x00fc, 0x0004 };
int __based(__segname("SIMANT_DATA_GROUP")) FootHere = 0;
int __based(__segname("SIMANT_DATA_GROUP")) BoyStandCnt = 0;
int __based(__segname("SIMANT_DATA_GROUP")) FootTog = 0;
int __based(__segname("SIMANT_DATA_GROUP")) NodeCnt = 0;
int __based(__segname("SIMANT_DATA_GROUP")) NodeNum = 0;
int __based(__segname("SIMANT_DATA_GROUP")) LionIndex = 0;
int __based(__segname("SIMANT_DATA_GROUP")) PillarState = 0;
int __based(__segname("SIMANT_DATA_GROUP")) PillarX = 0;
int __based(__segname("SIMANT_DATA_GROUP")) PillarY = 0;
int __based(__segname("SIMANT_DATA_GROUP")) SowTab[4] = {
    0x7372, 0x7071, 0x7372, 0x7071
};
int __based(__segname("SIMANT_DATA_GROUP")) SimAntServerFlag = 0;
int __based(__segname("SIMANT_DATA_GROUP")) SimAntClientFlag = 0;
unsigned long __based(__segname("SIMANT_DATA_GROUP")) SimAntDataFlag = 0UL;

struct BookMark {
    int object;
    int plane;
    int x;
    int y;
    int flags;
};

struct BookMark __based(__segname("SIMANT_DATA_GROUP")) bookMark[7] = {
    { -1, 0, 0, 0, 0 }, { -1, 0, 0, 0, 0 }, { -1, 0, 0, 0, 0 },
    { -1, 0, 0, 0, 0 }, { -1, 0, 0, 0, 0 }, { -1, 0, 0, 0, 0 },
    { -1, 0, 0, 0, 0 }
};
unsigned long __based(__segname("SIMANT_DATA_GROUP")) userButtonHelpId[16] = {
    0x0000023fUL, 0x0000023eUL, 0x0000023dUL, 0x0000023cUL,
    0x00000237UL, 0x0000023aUL, 0x00000239UL, 0x0000fd32UL,
    0x00000238UL, 0x0000fd33UL, 0x0000fd36UL, 0x0000fd31UL,
    0x0000fd35UL, 0x0000fd34UL, 0x0000023bUL, 0x0000fd47UL
};
