/*
 * PACK yard, combat and prompt state.  RxTab/RyTab are paired 50-word
 * coordinate tables; the named map positions are two-coordinate records,
 * LionListM and the database handles retain their byte/word array forms, and
 * the current wind prompt is a 256-character buffer.
 */
struct MapPoint {
    int x;
    int y;
};

struct YardPoint {
    int x;
    int y;
};

int __based(__segname("PACK")) RxTab[50] = {0};
char far * __based(__segname("PACK")) ScenarioNameStrs = 0;
int __based(__segname("PACK")) FootX = 0;
int __based(__segname("PACK")) BFightBalloonIndex = 0;
struct MapPoint __based(__segname("PACK")) CurFightPnt = {0, 0};
int __based(__segname("PACK")) TilesDugR = 0;
int __based(__segname("PACK")) FootY = 0;
int __based(__segname("PACK")) DogTurnCnt = 0;
int __based(__segname("PACK")) YardCycle = 0;
int __based(__segname("PACK")) Starg = 0;
struct YardPoint __based(__segname("PACK")) CurYardPnt = {0, 0};
struct MapPoint __based(__segname("PACK")) CenterPnt = {0, 0};
unsigned char __based(__segname("PACK")) LionListM[10] = {0};
int __based(__segname("PACK")) RyTab[50] = {0};
int __based(__segname("PACK")) db_handles[4] = {0};
struct MapPoint __based(__segname("PACK")) EditPrevPnt = {0, 0};
int __based(__segname("PACK")) modeAnimHandle = 0;
char __based(__segname("PACK")) CurWindPrompt[256] = {0};
