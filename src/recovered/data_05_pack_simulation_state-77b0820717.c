/*
 * This contiguous zero-initialized PACK block holds the simulation cursor,
 * colony swarm coordinates, edit state, map dimensions, and balloon/message
 * handles.  The swarm and dead-ant buffers are byte arrays; code uses words
 * for the counters, three-entry sow tables, and mode shares.  The two point
 * records and the bitmap size retain their coordinate fields.
 */
struct BitmapSize { int width; int height; };
struct MapPoint { int x; int y; };

int __based(__segname("PACK")) gameCycles[2] = {0};
int __based(__segname("PACK")) SwarmDelayR = {0};
char __based(__segname("PACK")) SwarmXB[50] = {0};
unsigned int __based(__segname("PACK")) casteLevels[3] = {0};
int __based(__segname("PACK")) Tindex = {0};
int __based(__segname("PACK")) EditRows = {0};
int __based(__segname("PACK")) TERRAINset = {0};
int __based(__segname("PACK")) MapButtStates[12] = {0};
int __based(__segname("PACK")) miniXSize = {0};
int __based(__segname("PACK")) StrategicModeB = {0};
char __based(__segname("PACK")) SwarmYB[50] = {0};
int __based(__segname("PACK")) LastMowX = {0};
char far * __based(__segname("PACK")) tileBufA = {0};
int __based(__segname("PACK")) MeCmd = {0};
int __based(__segname("PACK")) just = {0};
int __based(__segname("PACK")) SowX[3] = {0};
struct BitmapSize __based(__segname("PACK")) knobSize = {0};
int __based(__segname("PACK")) SpidOn = {0};
int __based(__segname("PACK")) LastMowY = {0};
char far * __based(__segname("PACK")) tileBufB = {0};
int __based(__segname("PACK")) SowY[3] = {0};
int __based(__segname("PACK")) MeGoalPlane = {0};
int __based(__segname("PACK")) miniYSize = {0};
int __based(__segname("PACK")) casteButtonState = {0};
char far * far * far __based(__segname("PACK")) MwinTitle = {0};
int __based(__segname("PACK")) WantBFightBalloon = {0};
int __based(__segname("PACK")) MeWarnHealth = {0};
int __based(__segname("PACK")) RedDestX = {0};
char __based(__segname("PACK")) SwarmXR[50] = {0};
int __based(__segname("PACK")) RedDestY = {0};
int __based(__segname("PACK")) YellowDied = {0};
int __based(__segname("PACK")) SwarmCntR = {0};
int __based(__segname("PACK")) GamePaused = {0};
int __based(__segname("PACK")) SowDir[3] = {0};
struct MapPoint __based(__segname("PACK")) EditCentPnt = {0};
char __based(__segname("PACK")) SwarmYR[50] = {0};
int __based(__segname("PACK")) DROPdir = {0};
char far * far * far __based(__segname("PACK")) BFightMsgs = {0};
int __based(__segname("PACK")) MeTargLifePlane = {0};
int __based(__segname("PACK")) AntsEatenByLions = {0};
int __based(__segname("PACK")) JustXfered = {0};
int __based(__segname("PACK")) CurQueenPlane = {0};
int __based(__segname("PACK")) modeLevels[3] = {0};
struct MapPoint __based(__segname("PACK")) lastPos = {0};
int __based(__segname("PACK")) MeSteps = {0};
int __based(__segname("PACK")) RColoniesStarted = {0};
char __based(__segname("PACK")) DeadX[100] = {0};
