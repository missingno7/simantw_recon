/*
 * PACK mode, colony and prompt state.  The temporary black-mode population is
 * a 20-word array, while saved counters use their recovered 32-bit forms and
 * the named prompt tables retain far string-table pointers.
 */
struct MapPoint {
    int x;
    int y;
};

int __based(__segname("PACK")) oldSoundOn = 0;
unsigned int __based(__segname("PACK")) TemBModePop[20] = {0};
char far * __based(__segname("PACK")) LoadStr = 0;
int __based(__segname("PACK")) RColoniesKilled = 0;
long __based(__segname("PACK")) OverallScore = 0L;
int __based(__segname("PACK")) DogPy = 0;
struct MapPoint __based(__segname("PACK")) YMapPnt = {0, 0};
int __based(__segname("PACK")) casteAnimObj = 0;
int __based(__segname("PACK")) MeCrazyRot = 0;
int __based(__segname("PACK")) spiderTileLeft = 0;
long __based(__segname("PACK")) QueenBalloonTicks = 0L;
char far * __based(__segname("PACK")) EndGameRatingStrs = 0;
int __based(__segname("PACK")) BoyPx = 0;
char far * __based(__segname("PACK")) ModeStr = 0;
