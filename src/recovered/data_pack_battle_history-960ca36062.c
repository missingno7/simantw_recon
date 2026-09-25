/*
 * PACK battle history and balloon state.  History/death samples use 64-word
 * series, dead-ant Y positions use a 100-byte list, six mode populations are
 * words, and message/callback slots are far pointers.
 */
typedef void (far *ShiftPutProc)(void);

unsigned long __based(__segname("PACK")) RestBalloonTicks = 0UL;
int __based(__segname("PACK")) BlackWon = 0;
unsigned int __based(__segname("PACK")) triWidth = 0;
int __based(__segname("PACK")) MigrateX = 0;
int __based(__segname("PACK")) MeHealthCntDwn = 0;
int __based(__segname("PACK")) H_ADead[64] = {0};
int __based(__segname("PACK")) MigrateY = 0;
int __based(__segname("PACK")) RedTask = 0;
unsigned char __based(__segname("PACK")) DeadY[100] = {0};
int __based(__segname("PACK")) IsGameOver = 0;
long __based(__segname("PACK")) TileTotXR = 0L;
unsigned int __based(__segname("PACK")) terrainTiles = 0;
long __based(__segname("PACK")) TileTotYR = 0L;
long __based(__segname("PACK")) DogBarkDelay = 0L;
int __based(__segname("PACK")) H_FDead[64] = {0};
unsigned long __based(__segname("PACK")) RFightBalloonTicks = 0UL;
int __based(__segname("PACK")) HistStart = 0;
int __based(__segname("PACK")) ModePopB[6] = {0};
int __based(__segname("PACK")) MeStartedFight = 0;
ShiftPutProc __based(__segname("PACK")) shiftPutRtn = 0;
int __based(__segname("PACK")) custOrgStrHandle = 0;
int __based(__segname("PACK")) FoodA = 0;
int __based(__segname("PACK")) RestBalloonIndex = 0;
char far * __based(__segname("PACK")) BoyMsgs = 0;
int __based(__segname("PACK")) InitialLions = 0;
char far * __based(__segname("PACK")) QueenMsgs = 0;
int __based(__segname("PACK")) lastTop = 0;
int __based(__segname("PACK")) modeAnimObj = 0;
long __based(__segname("PACK")) RAntsKilled = 0L;
