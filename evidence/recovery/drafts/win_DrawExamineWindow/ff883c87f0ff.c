/* win_DrawExamineWindow: when flags (bp+6) has bit 0x2 set, draw the
 * examine-tile popup for (ExamineX,ExamineY) in the list selected by
 * ExamineList (<=1: A-list/LifeA, ==2: B-list/LifeB, else: R-list/
 * LifeR).  The tile's terrain byte splits into caste ((terrain&0x78)>>3)
 * and, when caste==0, an egg stage (terrain&7): object 0x1d02 prints
 * either EggStr[stage] or CasteStr[caste].  Then, by ExamineList (1/2/3),
 * the matching FindIn?List call resolves the occupant's mode field
 * (A/B/RlistM, masked to a byte; 0 when not found); object 0x1d03 prints
 * ModeStr[mode] and object 0x1d04 prints LoadStr[caste], both with font
 * 2, before restoring font 0.
 */

extern int near ExamineX;
extern int near ExamineY;
extern int near ExamineList;

extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[128][64];
extern unsigned char near LifeR[128][64];

extern int far AlistM[];
extern int far BlistM[];
extern int far RlistM[];

extern char far * far * far EggStr;
extern char far * far * far CasteStr;
extern char far * far * far ModeStr;
extern char far * far * far LoadStr;

extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, char far *format, ...);
extern int far FindInAList(int x, int y);
extern int far FindInBList(int x, int y, int ant);
extern int far FindInRList(int x, int y, int ant);

void far win_DrawExamineWindow(int flags)
{
    int terrain;
    int caste;
    char far *text;
    int mode;
    int si;

    if (!(flags & 2))
        return;

    if (ExamineList <= 1)
        terrain = LifeA[ExamineX][ExamineY];
    else if (ExamineList == 2)
        terrain = LifeB[ExamineX][ExamineY];
    else
        terrain = LifeR[ExamineX][ExamineY];

    caste = (terrain & 0x78) >> 3;
    if (caste == 0)
        text = EggStr[terrain & 7];
    else
        text = CasteStr[caste];
    font_SetFont(2);
    win_PrintfAtObj(0x1d02, text);

    if (ExamineList == 1) {
        si = FindInAList(ExamineX, ExamineY);
        mode = (si < 0) ? 0 : (AlistM[si] & 0xff);
    } else if (ExamineList == 2) {
        terrain = LifeB[ExamineX][ExamineY];
        si = FindInBList(ExamineX, ExamineY, terrain);
        mode = (si < 0) ? 0 : (BlistM[si] & 0xff);
    } else if (ExamineList == 3) {
        terrain = LifeR[ExamineX][ExamineY];
        si = FindInRList(ExamineX, ExamineY, terrain);
        mode = (si < 0) ? 0 : (RlistM[si] & 0xff);
    } else {
        int uninit;
        mode = uninit;
    }

    win_PrintfAtObj(0x1d03, ModeStr[mode]);
    win_PrintfAtObj(0x1d04, LoadStr[caste]);
    font_SetFont(0);
}
