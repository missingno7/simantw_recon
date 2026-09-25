/*
 * PACK editor, mode and balloon tables.  Edit rectangles and caste vertices
 * use four-edge/two-coordinate records, mode-population and NCB offsets are
 * word arrays, and sine/message/buffer links retain their far-pointer types.
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

typedef void (far *PutTileProc)(void);

int far * __based(__segname("PACK")) FracSineTab = 0;
int __based(__segname("PACK")) ModeAuto = 0;
int __based(__segname("PACK")) CurBalloonCnt = 0;
int __based(__segname("PACK")) TileMassYR = 0;
int __based(__segname("PACK")) sizeA = 0;
struct Rect __based(__segname("PACK")) editTileBottom = {0, 0, 0, 0};
int __based(__segname("PACK")) win_rscVersion = 0;
int __based(__segname("PACK")) CurEditMode = 0;
int __based(__segname("PACK")) MeDis = 0;
int __based(__segname("PACK")) FuzLocX = 0;
int __based(__segname("PACK")) sizeB = 0;
int __based(__segname("PACK")) MeMode = 0;
int __based(__segname("PACK")) FuzLocY = 0;
int __based(__segname("PACK")) RebornX = 0;
int __based(__segname("PACK")) RebornY = 0;
int __based(__segname("PACK")) H_RHeal[64] = {0};
int __based(__segname("PACK")) sizeC = 0;
struct MapPoint far * __based(__segname("PACK")) yardBalloonPtr = 0;
char far * __based(__segname("PACK")) RestMsgs = 0;
PutTileProc __based(__segname("PACK")) putTileInBufRtn = 0;
int __based(__segname("PACK")) RestBalloonCnt = 0;
int __based(__segname("PACK")) tileDsp = 0;
int __based(__segname("PACK")) sizeD = 0;
int __based(__segname("PACK")) ModePopR[6] = {0};
struct MapPoint __based(__segname("PACK")) casteVerts[3] = {0};
int __based(__segname("PACK")) ncbOffset[10] = {0};
