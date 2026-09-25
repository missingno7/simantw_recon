/*
 * PACK's interface and yard state.  Balloon flags are six words, saved sow
 * coordinates are three words, the minimap rectangle is four coordinates,
 * and the recovered six-byte color records form forty rows.
 */
struct MiniMapRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct MapPoint {
    int x;
    int y;
};

int __based(__segname("PACK")) tileBufOver = 0;
int __based(__segname("PACK")) SuserX = 0;
int __based(__segname("PACK")) multiplier = 0;
int __based(__segname("PACK")) BirdGoalX = 0;
unsigned int __based(__segname("PACK")) CurBalloonFlags[6] = {0};
int __based(__segname("PACK")) OrigResFileNum = 0;
int __based(__segname("PACK")) SowSave[3] = {0};
int __based(__segname("PACK")) BoyPy = 0;
int __based(__segname("PACK")) PillarSeg = 0;
int __based(__segname("PACK")) QueenBalloonIndex = 0;
int __based(__segname("PACK")) BirdGoalY = 0;
int __based(__segname("PACK")) SCorpseBase = 0;
unsigned int __based(__segname("PACK")) JustToBeMean = 0;
int __based(__segname("PACK")) win_numOfWindows = 0;
struct MiniMapRect __based(__segname("PACK")) miniMapCursorRect = {0, 0, 0, 0};
int __based(__segname("PACK")) BlkQueens = 0;
int __based(__segname("PACK")) SuserY = 0;
char __based(__segname("PACK")) win_colors[40][6] = {0};
int __based(__segname("PACK")) RedQueens = 0;
struct MapPoint __based(__segname("PACK")) LastQueenPnt = {0, 0};
int __based(__segname("PACK")) CurExpTool = 0;
int __based(__segname("PACK")) BlackLost = 0;
