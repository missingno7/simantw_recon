/*
 * Zero-initialized map and colony state in PACK.  Cursor rectangles and map
 * points use the same four-word rectangle and two-coordinate layouts used by
 * admitted callers; handle, plane and counter fields are 16-bit integers.
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

struct Rect __based(__segname("PACK")) mapCursorRect = {0, 0, 0, 0};
int __based(__segname("PACK")) CatCycle = 0;
int __based(__segname("PACK")) custNameStrHandle = 0;
int __based(__segname("PACK")) ncbHead = 0;
int __based(__segname("PACK")) CatDir = 0;
int __based(__segname("PACK")) WantRestBalloon = 0;
int __based(__segname("PACK")) LastColonyPopB = 0;
int __based(__segname("PACK")) SpidRevenge = 0;
struct MapPoint __based(__segname("PACK")) LastRestPnt = {0, 0};
int __based(__segname("PACK")) TilesDugB = 0;
unsigned int __based(__segname("PACK")) lastMapMapBuf = 0;
int __based(__segname("PACK")) ListIndexR = 0;
