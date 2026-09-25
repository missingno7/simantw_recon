/*
 * PACK window, map and simulation tables.  The window-offset block is forty-
 * five four-coordinate rectangles, matching the 45 far draw-hook slots;
 * map limits, counters and the two table-builder callbacks remain typed.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

typedef void (far *MakeTableProc)();

char __based(__segname("PACK")) EwinStr[256] = {0};
struct Rect __based(__segname("PACK")) miniMapRect = {0, 0, 0, 0};
int __based(__segname("PACK")) SwarmCentY = 0;
unsigned int __based(__segname("PACK")) triWidthL = 0;
struct Rect __based(__segname("PACK")) win_offsets[45] = {0};
MakeTableProc __based(__segname("PACK")) makea = 0;
unsigned long __based(__segname("PACK")) LastThemeTime = 0UL;
int __based(__segname("PACK")) SpidBurpCnt = 0;
char far * __based(__segname("PACK")) CasteStr = 0;
unsigned int __based(__segname("PACK")) FlyAwayR = 0;
int __based(__segname("PACK")) SwarmCntB = 0;
int __based(__segname("PACK")) mapXsize = 0;
unsigned int __based(__segname("PACK")) ncbSegment[10] = {0};
MakeTableProc __based(__segname("PACK")) makeb = 0;
int __based(__segname("PACK")) mapYsize = 0;
char far * __based(__segname("PACK")) EggStr = 0;
unsigned char __based(__segname("PACK")) LionListX[10] = {0};
