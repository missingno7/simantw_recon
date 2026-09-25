/*
 * PACK cursor, database, yard and message state.  The balloon planes and
 * message lists use six entries, the lion marker lists are ten bytes each,
 * and output-buffer and map-point records keep their recovered field shapes.
 */
struct MapPoint {
    int x;
    int y;
};

struct OutBuffer {
    int width;
    int height;
    void far *image;
};

int __based(__segname("PACK")) CursType = 0;
int __based(__segname("PACK")) theDDEDataH = 0;
struct OutBuffer __based(__segname("PACK")) out_buffer = {0, 0, 0};
int __based(__segname("PACK")) MeMoveMe = 0;
int __based(__segname("PACK")) vScrollMax = 0;
int __based(__segname("PACK")) FilVolNum = 0;
struct MapPoint __based(__segname("PACK")) CurEggPnt = {0, 0};
struct MapPoint __based(__segname("PACK")) MapPnt = {0, 0};
int __based(__segname("PACK")) mapOutBuf = 0;
unsigned char __based(__segname("PACK")) LionListS[10] = {0};
int __based(__segname("PACK")) tileBufNest = 0;
struct MapPoint __based(__segname("PACK")) CurRestPnt = {0, 0};
int __based(__segname("PACK")) EggBalloonCnt = 0;
struct MapPoint __based(__segname("PACK")) ExpLastPnt = {0, 0};
unsigned long __based(__segname("PACK")) BoyMsgCnt = 0UL;
unsigned char __based(__segname("PACK")) LionListT[10] = {0};
int __based(__segname("PACK")) SwarmCentX = 0;
int __based(__segname("PACK")) DogDir = 0;
long __based(__segname("PACK")) RAntsEaten = 0L;
int __based(__segname("PACK")) MeSMode = 0;
int __based(__segname("PACK")) TutHowLong = 0;
struct MapPoint __based(__segname("PACK")) CurQueenPnt = {0, 0};
int __based(__segname("PACK")) CurBalloonPlane[6] = {0};
int __based(__segname("PACK")) SimAntServerNum = 0;
int __based(__segname("PACK")) H_RFood[64] = {0};
